#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>

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
    //TODO delete
    bool isActive = false;
    bool isCurrent = false;
    bool isDependent = false;
    //std::string name;
    virtual double dist(Point) =0;
    virtual void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) {}
    virtual void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) {}
    //virtual std::string what_is()=0;
    virtual uint32_t what_is() = 0;
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

    static Point zero();

    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) override;

    void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) override;

    double dist(Point) override;

    //std::string what_is() override;
    virtual uint32_t what_is () override {return shapeTypeId<Point>::typeId;}

    friend std::ostream& operator<<(std::ostream&, const Point&);

	Point(double=0, double=0);

	bool operator==(Point);
	Point operator+(Point);
	Point operator-(Point);
	Point operator*(double);
	Point operator/(double);
	double operator*(Point);
	double operator%(Point);

	//długość do (0,0) +
	double abs();

    Point(Line,Line);
};


class Segment : public Shape{
public:
	Point p1, p2;

	Segment(Point,Point);
    Segment () {}

    double dist(Point) override;

    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) override;

    //std::string what_is() override;
    virtual uint32_t what_is () override {return shapeTypeId<Segment>::typeId;}

    friend std::ostream& operator<<(std::ostream&, const Segment&);

	//dlugosc odcinka +
	double abs();

};


class Line : public Shape{
public:

    Point n;
	double c;

	Line(double,double,double); //line ax+by+c=0
	Line(Point,Point); //line through two points
	Line(Segment);

    double dist(Point) override;

    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) override;

    //std::string what_is() override;
    virtual uint32_t what_is () override {return shapeTypeId<Line>::typeId;}

    friend std::ostream& operator<<(std::ostream&, const Line&);

    Line(Circle,Circle);
};


class Circle: public Shape {
public:
    Point middle;
    double r;
    double dist(Point) override;
    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) override;
    //std::string what_is() override;
    virtual uint32_t what_is () override {return shapeTypeId<Circle>::typeId;}
    friend std::ostream& operator<<(std::ostream&, const Circle&);
    Circle(Point, Point, Point);
    Circle(Point, double);
    Circle(Point, Point);
};

class Construction {
    public:
    virtual ~Construction () {}
    virtual void adjust () {}
};

typedef Construction* (*constructionMaker)(constructionElements&, std::vector<Shape*>&);

class segmentMiddle : public Construction { //constructs middle point from segment
    private:
        Segment *segment;
        Point *midPoint;
    public:
        segmentMiddle (constructionElements& el, std::vector<Shape*>& shapes) : segment(el.segments[0]), midPoint(new Point) {
            midPoint->isDependent = true;
            shapes.push_back(midPoint);
        }
        virtual void adjust ();
};


class pointsMiddle : public Construction { //constructs middle point from two points
    private:
        Point *pointA, *pointB;
        Point *midPoint;
    public:
        pointsMiddle (constructionElements& el, std::vector<Shape*>& shapes) : pointA (el.points[0]), pointB (el.points[1]), midPoint(new Point) {
            midPoint->isDependent = true;
            shapes.push_back (midPoint);
        }
        virtual void adjust ();
};

class orthogonalLine : public Construction { //constructs orthogonal line from line and a point
    private:
        Line *line;
        Point *point;
        Line *orthogonal;
    public:
        orthogonalLine (constructionElements& el, std::vector<Shape*>& shapes) : line(el.lines[0]), point(el.points[0]), orthogonal(new Line (1,0,0)) {
            orthogonal->isDependent = true;
            shapes.push_back(orthogonal);
        }
        virtual void adjust ();
};

class parallelLine : public Construction { //constructs parallel line from line and a point
    private:
        Line *line;
        Point *point;
        Line *parallel;
    public:
        parallelLine (constructionElements& el, std::vector<Shape*>& shapes) : line(el.lines[0]), point(el.points[0]), parallel(new Line (1,0,0)) {
            parallel->isDependent = true;
            shapes.push_back(parallel);
        }
        virtual void adjust ();
};

class lineThroughPoints : public Construction {
    private:
        Point *pointA, *pointB;
        Line *line;
    public:
        lineThroughPoints (constructionElements& el, std::vector<Shape*>& shapes) : pointA (el.points[0]), pointB (el.points[1]), line(new Line(1,0,0)) {
            line->isDependent = true;
            shapes.push_back (line);
        }
        virtual void adjust ();
};

class segmentFromPoints : public Construction {
    private:
        Point *pointA, *pointB;
        Segment *segment;
    public:
        segmentFromPoints (constructionElements& el, std::vector<Shape*>& shapes) : pointA (el.points[0]), pointB (el.points[1]), segment(new Segment) {
            segment->isDependent = true;
            shapes.push_back (segment);
        }
        virtual void adjust ();
};

class circleWithCenter : public Construction {
    private:
        Point *center, *point;
        Circle *circle;
    public:
        circleWithCenter (constructionElements& el, std::vector<Shape*>& shapes) : center(el.points[0]), point(el.points[1]), circle(new Circle(0,0,0)) {
            circle->isDependent = true;
            shapes.push_back (circle);
        }
        virtual void adjust ();
};

template <typename T>
Construction *makeConstruction (constructionElements& el, std::vector<Shape*>& shapes) {
    T* newT = new T (el, shapes);
    if (newT == NULL) return NULL;
    newT->adjust();
    return newT;
}
