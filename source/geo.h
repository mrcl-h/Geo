#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<cmath>

template <typename T>
class shapeTypeId {
    public:
        enum {typeId = 0};
};

//lista figur geometrycznych
class Segment;
template <> class shapeTypeId<Segment> { public: enum {typeId = 5}; };
class Triangle;
template <> class shapeTypeId<Triangle> { public: enum {typeId = 4}; };
class Line;
template <> class shapeTypeId<Line> { public: enum {typeId = 3}; };
class Circle;
template <> class shapeTypeId<Circle> { public: enum {typeId = 2}; };
class Point;
template <> class shapeTypeId<Point> { public: enum {typeId = 1}; };
class Shape;

inline double doubleAbs (double r) {
    return r >= 0 ? r : -r;
}


class Shape {
public:
    bool exists = true;
    bool isActive = false;
    bool isCurrent = false;
    bool isDependent = false;
    //std::string name;
    virtual const double dist(Point) const =0;
    virtual void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const {}
    virtual void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const {}
    //virtual std::string what_is()=0;
    virtual const uint32_t what_is() = 0;
    virtual ~Shape() {}

};

struct constructionElements {
    std::vector<Point*> points;
    std::vector<Line*> lines;
    std::vector<Circle*> circles;
    std::vector<Segment*> segments;
};

inline void resetConstructionElements (constructionElements& el) {
    el.points.clear();
    el.lines.clear();
    el.circles.clear();
    el.segments.clear();
}


class Point : public Shape {
    double radiusOfDrawing=3;
public:
	double x,y;

    //static Point zero();

    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;

    void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;

    const double dist(Point) const override;

    //std::string what_is() override;
    virtual const uint32_t what_is () override {return shapeTypeId<Point>::typeId;}

    friend std::ostream& operator<<(std::ostream&, const Point&);

	Point(double=0, double=0);

    const bool operator==(Point p) const {
        return ((dist(p))<0.01);
    }

    const Point operator+(Point p) const {
        return Point(x+p.x,y+p.y);
    }
    const Point operator-(Point p) const {
        return Point(x-p.x,y-p.y);
    }
    const Point operator*(double a) const {
        return Point(a*x,a*y);
    }
    const Point operator/(double a) const {
        return Point(x/a, y/a);
    }
    const double operator*(Point p) const {
        return x*p.x+y*p.y;
    }
    const double operator%(Point p) const {
        return x*p.y-y*p.x;
    }

    //długość do (0,0) +
    const double abs() const {
        return std::sqrt (x*x+y*y);
    }

    Point(Line,Line);
};


class Segment : public Shape{
public:
	Point p1, p2;

	Segment(Point,Point);
    Segment () {}

    const double dist(Point) const override;

    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;

    //std::string what_is() override;
    virtual const uint32_t what_is () override {return shapeTypeId<Segment>::typeId;}

    friend std::ostream& operator<<(std::ostream&, const Segment&);

	//dlugosc odcinka +
	const double abs();

};


class Line : public Shape{
public:

    Point n;
	double c;

	Line(double,double,double); //line ax+by+c=0
	Line(Point,Point); //line through two points
	Line(Segment);

    const double dist(Point) const override;
    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;

    //std::string what_is() override;
    virtual const uint32_t what_is () override {return shapeTypeId<Line>::typeId;}

    void goThroughPoints (const Point& p, const Point& q) {
        if(p==q){
            throw std::invalid_argument("Points lay to close to each other");
        } else {
            if(p==Point(0,0)){
                c=0;
                n=Point(q.y, -q.x);
            } else if(q==Point(0,0)){
                c=0;
                n=Point(p.y, -p.x);
            } else {
                c=-1;
                n=Point((q.y-p.y)/(p%q), (-q.x+p.x)/(p%q));
            }
        }
    }

    friend std::ostream& operator<<(std::ostream&, const Line&);

    Line(Circle,Circle);
};


class Circle: public Shape {
public:
    Point middle;
    double r;
    const double dist(Point) const override;
    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;
    //std::string what_is() override;
    virtual const uint32_t what_is () override {return shapeTypeId<Circle>::typeId;}
    friend std::ostream& operator<<(std::ostream&, const Circle&);
    Circle(Point, Point, Point);
    Circle(Point, double);
    Circle(Point, Point);
};

//TODO: Triangle class

class Construction {
    public:
    virtual ~Construction () {}
    virtual void adjust () {}
};

typedef Construction* (*constructionMaker)(const constructionElements&, std::vector<Shape*>&);

//------------------------------------------------

class segmentMiddle : public Construction { //constructs middle point from segment
    private:
        Segment * const segment;
        Point *midPoint;
    public:
        segmentMiddle (const constructionElements& el, std::vector<Shape*>& shapes) : segment(el.segments[0]), midPoint(new Point) {
            midPoint->isDependent = true;
            shapes.push_back(midPoint);
        }
        virtual void adjust ();
};

class pointsMiddle : public Construction { //constructs middle point from two points
    private:
        Point * const pointA, * const pointB;
        Point *midPoint;
    public:
        pointsMiddle (const constructionElements& el, std::vector<Shape*>& shapes) : pointA (el.points[0]), pointB (el.points[1]), midPoint(new Point) {
            midPoint->isDependent = true;
            shapes.push_back (midPoint);
        }
        virtual void adjust ();
};

class orthogonalLine : public Construction { //constructs orthogonal line from line and a point
    private:
        Line * const line;
        Point * const point;
        Line *orthogonal;
    public:
        orthogonalLine (const constructionElements& el, std::vector<Shape*>& shapes) : line(el.lines[0]), point(el.points[0]), orthogonal(new Line (1,0,0)) {
            orthogonal->isDependent = true;
            shapes.push_back(orthogonal);
        }
        virtual void adjust ();
};

class parallelLine : public Construction { //constructs parallel line from line and a point
    private:
        Line * const line;
        Point * const point;
        Line *parallel;
    public:
        parallelLine (const constructionElements& el, std::vector<Shape*>& shapes) : line(el.lines[0]), point(el.points[0]), parallel(new Line (1,0,0)) {
            parallel->isDependent = true;
            shapes.push_back(parallel);
        }
        virtual void adjust ();
};

class lineThroughPoints : public Construction {
    private:
        Point * const pointA, * const pointB;
        Line *line;
    public:
        lineThroughPoints (const constructionElements& el, std::vector<Shape*>& shapes) : pointA (el.points[0]), pointB (el.points[1]), line(new Line(1,0,0)) {
            line->isDependent = true;
            shapes.push_back (line);
        }
        virtual void adjust ();
};

class segmentFromPoints : public Construction {
    private:
        Point * const pointA, * const pointB;
        Segment *segment;
    public:
        segmentFromPoints (const constructionElements& el, std::vector<Shape*>& shapes) : pointA (el.points[0]), pointB (el.points[1]), segment(new Segment) {
            segment->isDependent = true;
            shapes.push_back (segment);
        }
        virtual void adjust ();
};

class circleWithCenter : public Construction {
    private:
        Point * const center, * const point;
        Circle *circle;
    public:
        circleWithCenter (const constructionElements& el, std::vector<Shape*>& shapes) : center(el.points[0]), point(el.points[1]), circle(new Circle(0,0,0)) {
            circle->isDependent = true;
            shapes.push_back (circle);
        }
        virtual void adjust ();
};

class centerOfMass : public Construction {
    private:
        Point * const pointA, * const pointB, * const pointC;
        Point *center;
    public:
        centerOfMass (const constructionElements& el, std::vector<Shape*>& shapes) : pointA(el.points[0]), pointB(el.points[1]), pointC (el.points[2]), center (new Point) {
            center->isDependent = true;
            shapes.push_back(center);
        }
        virtual void adjust ();
};

class bisectorThreePoints : public Construction {
    private:
        Point * const pointA, * const pointB, * const pointC;
        Line *line;
    public:
        bisectorThreePoints (const constructionElements& el, std::vector<Shape*>& shapes) : pointA (el.points[0]), pointB(el.points[1]), pointC(el.points[2]), line (new Line (1,0,0)) {
            line->isDependent = true;
            shapes.push_back(line);
        }
        virtual void adjust ();
};

//TODO: Circle through 3 points construction
//TODO: Intersections of two circles
//TODO: Power line of two circles
//TODO: Intersections of circle and line
//TODO: Symmetrical line of a segment/two points
//TODO: bisector of 3 points / bisectors of two Lines
//TODO: described circle on triangle
//TODO: inscribed circle in triangle
//TODO: Orthocenter of triangle
//TODO: nine point circle
//TODO: Euler's line
//TODO: Symmedian
//TODO: Space transformations: HOMOTHETY, ROTATION, SYMMETRY about point/line, SHIFT, INVERSION, AFINIC 

template <typename T>
Construction *makeConstruction (const constructionElements& el, std::vector<Shape*>& shapes) {
    T* newT = new T (el, shapes);
    if (newT == NULL) return NULL;
    newT->adjust();
    return newT;
}
