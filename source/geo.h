#pragma once
#include "vectorHolder.h"
#include<vector>
#include<cmath>
#include<memory>
#include <SFML/Graphics.hpp>


//lista figur geometrycznych
class SegmentShape;
class TriangleShape;
class LineShape;
class CircleShape;
class PointShape;
class Shape;

inline double doubleAbs (double r) {
    return r >= 0 ? r : -r;
}

struct floatRect {
    float left, top, width, height;
};

typedef vectorHolder <PointShape*, LineShape*, CircleShape*, SegmentShape*, TriangleShape*> constructionElements;

struct uiOptionConditions {
    uint8_t lineCount, pointCount, circleCount, segmentCount, triangleCount;
};

void resetUiOptionConditions (uiOptionConditions& op);

struct Point {
    double x, y;
};

class Shape {
    protected:
        constexpr static double hitEpsilon = 4;
    public:
        virtual void setExistance (bool) = 0;
        virtual bool getExistance () const = 0;
        virtual void setActivity (bool) = 0;
        virtual bool getActivity () const = 0;
        virtual void setCurrent (bool) = 0;
        virtual bool getCurrent () const = 0;
        virtual void setDependent (bool) = 0; 
        virtual bool getDependent () const = 0;
        virtual double distFromPoint(const Point&) const =0;
        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const {}
        virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const {}
        virtual void addToConstructionElements (constructionElements&) {}
        virtual void removeFromConstructionElements (constructionElements&) {}
        virtual void addToCurrentConditions (uiOptionConditions& op, int c) {}
        virtual unsigned int getHitPriority () = 0;
        virtual bool isHit (const Point& p) = 0;
        virtual void moveShape (double x, double y) {}
        virtual ~Shape() {}

};

double dist (double x1, double y1, double x2, double y2);
double dist(const Point &p1, const Point &p2);
double length(const Point &p);

const Point operator+(const Point &p1, const Point &p2);
const Point operator-(const Point &p1, const Point &p2);
const Point operator*(const Point &p, double a);
const Point operator*(double a, const Point &p);
const Point operator/(const Point &p, double a);
double operator*(const Point &p1, const Point &p2);
double operator%(const Point &p1, const Point &p2);
bool operator==(const Point &p1, const Point &p2);

class PointShape : public Shape {
    public:
        virtual ~PointShape () {}

        virtual double getX () const = 0;
        virtual double getY () const = 0;

        virtual void setX (double newX) = 0;
        virtual void setY (double newY) = 0;

        virtual double abs() const = 0;
};

PointShape* makePointShape (double = 0, double = 0);
PointShape* makePointShape (const LineShape&, const LineShape&);

Point getPointLocation (PointShape&);

class SegmentShape : public Shape{
    public:
        virtual ~SegmentShape () {}

        virtual double getFromX () const = 0;
        virtual double getToX () const = 0;
        virtual double getFromY () const = 0;
        virtual double getToY () const = 0;

        virtual void setFromX (double newX) = 0;
        virtual void setToX (double newX) = 0;
        virtual void setFromY (double newY) = 0;
        virtual void setToY (double newY) = 0;


        virtual double abs() const = 0;
};

SegmentShape* makeSegmentShape ();
SegmentShape* makeSegmentShape (const Point&, const Point&);

Point getSegmentFrom (const SegmentShape& seg);
Point getSegmentTo (const SegmentShape& seg);

class LineShape : public Shape{
    public:
        virtual ~LineShape () {}
        virtual double getNormalX () const = 0;
        virtual double getNormalY () const = 0;
        virtual double getC () const = 0;

        virtual void setNormalX (double x) = 0;
        virtual void setNormalY (double y) = 0;
        virtual void setC (double _c) = 0;

        virtual void goThroughPoints (const double px, const double py, const double qx, const double qy) = 0;

};

LineShape* makeLineShape (double, double, double);
LineShape* makeLineShape (const SegmentShape&);
LineShape* makeLineShape (const Point&, const Point&);

Point getLineNormal (const LineShape&);

class CircleShape : public Shape {
    public:
        virtual ~CircleShape () {}
        virtual double getMiddleX () const = 0;
        virtual double getMiddleY () const = 0;
        virtual double getR () const = 0;

        virtual void setMiddleX (double x) = 0;
        virtual void setMiddleY (double y) = 0;
        virtual void setR (double _r) = 0;

};

CircleShape* makeCircleShape (const Point&, double);
CircleShape* makeCircleShape (const Point&, const Point&);
CircleShape* makeCircleShape (double, double, double);
CircleShape* makeCircleShape (const Point&, const Point&, const Point&);

Point getCircleCenter (CircleShape&);

//TODO: Triangle class
class TriangleShape : public Shape {
    public:
        virtual ~TriangleShape () {}
        virtual double getAX () const = 0;
        virtual double getAY () const = 0;

        virtual double getBX () const = 0;
        virtual double getBY () const = 0;
        
        virtual double getCX () const = 0;
        virtual double getCY () const = 0;

        virtual void setAX (double) = 0;
        virtual void setAY (double) = 0;

        virtual void setBX (double) = 0;
        virtual void setBY (double) = 0;
        
        virtual void setCX (double) = 0;
        virtual void setCY (double) = 0;
        
};
TriangleShape* makeTriangleShape(const Point&, const Point&, const Point&);
TriangleShape* makeTriangleShape(double, double, double, double, double, double);
