#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
//lista figur geometrycznych
class Segment;
class Triangle;
class Line;
class Circle;
class Point;
class Shape;
class Construction;
class Shape {
public:
    //string name;
    virtual double dist(Point)=0;
    virtual void draw(sf::RenderWindow*) {}
    virtual void hull_draw(sf::RenderWindow*) {}
    virtual string what_is()=0;

};
class Construction {
public:
    string name;
    Shape* make(vector<Shape*>);
    static Point middle(Point, Point);

    /*static Point* middle(Segment);

    static Point* middle(Circle);

    static Line orthogonal(Line, Point);

    static Line parrarel(Line, Point);

    static Line bisection(Segment);

    static Line bisection(Point, Point);

    static Line bisector(Line, Line);

    static Line bisector(Point, Point, Point);

    static Line tangent_to_c(Point, Line);*/

    //Punkt na półprostej od (1) w kierunku (2) odległy o (3) od (1) +
    static Point lengthen(Point, Point, double);
};
class Point : public Shape {
    double radiusOfDrawing=3;
public:
	double x,y;

    static Point zero();

    string nazwa;

    void draw(sf::RenderWindow*) override;

    double dist(Point) override;

    string what_is() override;

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

    double dist(Point) override;

    void draw(sf::RenderWindow*) override;

    string what_is() override;

    friend std::ostream& operator<<(std::ostream&, const Segment&);

	//dlugosc odcinka +
	double abs();

};
class Line : public Shape{
public:

    Point n;
	double c;

	//Line ax+by+c=0 +
	Line(double,double,double);

	//prosta przechodząca przez (1) i (2) +
	Line(Point,Point);

	Line(Segment);

    double dist(Point) override;

    void draw(sf::RenderWindow*) override;

    string what_is() override;

    friend std::ostream& operator<<(std::ostream&, const Line&);

    Line(Circle,Circle);
};
class Circle: public Shape {
public:
    Point middle;
    double r;
    double dist(Point) override;
    void draw(sf::RenderWindow*) override;
    string what_is() override;
    friend std::ostream& operator<<(std::ostream&, const Circle&);
    Circle(Point, Point, Point);
    Circle(Point, double);
    Circle(Point, Point);
};
