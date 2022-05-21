#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>

//lista figur geometrycznych
class Segment;
class Triangle;
class Line;
class Circle;
class Point;
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
    virtual std::string what_is()=0;
    virtual ~Shape() {}

};
class Construction {
    public:
    virtual ~Construction () {}
    virtual void adjust () {}
};

typedef Construction* (*constructionMaker)(std::vector<Shape*>&, std::vector<Shape*>&);
//typedef void* (*parseState)(charParsingData&, const char*, parsedstd::string&);



class segmentMiddle : public Construction { //constructs middle point from segment
    private:
        Segment *segment;
        Point *midPoint;
    public:
        segmentMiddle (Segment *_segment, Point *_midPoint) : segment(_segment), midPoint(_midPoint) {}
        virtual void adjust ();
};


Construction *makeSegmentMiddle(std::vector<Shape *> &segment,
                                std::vector<Shape *> &mid);

class pointsMiddle : public Construction { //constructs middle point from two points
    private:
        Point *pointA, *pointB;
        Point *midPoint;
    public:
        pointsMiddle (Point *_pointA, Point *_pointB, Point *_midPoint) : pointA (_pointA), pointB (_pointB), midPoint(_midPoint) {}
        virtual void adjust ();
};

Construction *makePointsMiddle(std::vector<Shape *> &points,
                               std::vector<Shape *> &mid);

class orthogonalLine : public Construction { //constructs orthogonal line from line and a point
    private:
        Line *line;
        Point *point;
        Line *orthogonal;
    public:
        orthogonalLine (Line *_line, Point *_point, Line *_orthogonal) : line(_line), point(_point), orthogonal(_orthogonal) {}
        virtual void adjust ();
};

Construction *makeOrthogonal(std::vector<Shape *> &shapes,
                             std::vector<Shape *> &ortho);

class parallelLine : public Construction { //constructs parallel line from line and a point
    private:
        Line *line;
        Point *point;
        Line *parallel;
    public:
        parallelLine (Line *_line, Point *_point, Line *_parallel) : line(_line), point(_point), parallel(_parallel) {}
        virtual void adjust ();
};

Construction *makeParallel(std::vector<Shape *> &shapes,
                           std::vector<Shape *> &parall);

class lineThroughPoints : public Construction {
    private:
        Point *pointA, *pointB;
        Line *line;
    public:
        lineThroughPoints (Point *_pointA, Point *_pointB, Line *_line) : pointA (_pointA), pointB (_pointB), line(_line) {}
        virtual void adjust ();
};

Construction *makeLineThroughPoints(std::vector<Shape *> &shapes,
                                    std::vector<Shape *> &line);

class segmentFromPoints : public Construction {
    private:
        Point *pointA, *pointB;
        Segment *segment;
    public:
        segmentFromPoints (Point *_pointA, Point *_pointB, Segment *_segment) : pointA (_pointA), pointB (_pointB), segment(_segment) {}
        virtual void adjust ();
};

Construction *makeSegmentFromPoints(std::vector<Shape *> &input,
                          std::vector<Shape *> &shapes);

class circleWithCenter : public Construction {
    private:
        Point *center, *point;
        Circle *circle;
    public:
        circleWithCenter (Point *_center, Point *_point, Circle *_circle) : center(_center), point(_point), circle(_circle) {}
        virtual void adjust ();
};

Construction *makeCircleWithCenter(std::vector<Shape *> &input,
                                   std::vector<Shape *> &shapes);

class Point : public Shape {
    double radiusOfDrawing=3;
public:
	double x,y;

    static Point zero();

    std::string nazwa;

    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) override;

    void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) override;

    double dist(Point) override;

    std::string what_is() override;

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

    std::string what_is() override;

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

    std::string what_is() override;

    friend std::ostream& operator<<(std::ostream&, const Line&);

    Line(Circle,Circle);
};
class Circle: public Shape {
public:
    Point middle;
    double r;
    double dist(Point) override;
    void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) override;
    std::string what_is() override;
    friend std::ostream& operator<<(std::ostream&, const Circle&);
    Circle(Point, Point, Point);
    Circle(Point, double);
    Circle(Point, Point);
};
