#pragma once
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

struct constructionElements {
    std::vector<PointShape*> points;
    std::vector<LineShape*> lines;
    std::vector<CircleShape*> circles;
    std::vector<SegmentShape*> segments;
};

void resetConstructionElements (constructionElements& el);

struct uiOptionConditions {
    uint8_t lineCount, pointCount, circleCount, segmentCount;
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
        const virtual bool getExistance () const = 0;
        virtual void setActivity (bool) = 0;
        const virtual bool getActivity () const = 0;
        virtual void setCurrent (bool) = 0;
        const virtual bool getCurrent () const = 0;
        virtual void setDependent (bool) = 0; 
        const virtual bool getDependent () const = 0;
        //std::string name;
        virtual const double distFromPoint(const Point&) const =0;
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

const double dist (double x1, double y1, double x2, double y2);
const double dist(const Point &p1, const Point &p2);
const double length(const Point &p);

const Point operator+(const Point &p1, const Point &p2);
const Point operator-(const Point &p1, const Point &p2);
const Point operator*(const Point &p, double a);
const Point operator*(double a, const Point &p);
const Point operator/(const Point &p, double a);
const double operator*(const Point &p1, const Point &p2);
const double operator%(const Point &p1, const Point &p2);
const bool operator==(const Point &p1, const Point &p2);

class PointShape : public Shape {
    public:
        virtual ~PointShape () {}

        virtual const double getX () const = 0;
        virtual const double getY () const = 0;

        virtual void setX (double newX) = 0;
        virtual void setY (double newY) = 0;

        //długość do (0,0) +
        virtual const double abs() const = 0;
};

PointShape* makePointShape (double = 0, double = 0);
PointShape* makePointShape (const LineShape&, const LineShape&);

class SegmentShape : public Shape{
    public:
        virtual ~SegmentShape () {}

        virtual const double getFromX () const = 0;
        virtual const double getToX () const = 0;
        virtual const double getFromY () const = 0;
        virtual const double getToY () const = 0;

        virtual void setFromX (double newX) = 0;
        virtual void setToX (double newX) = 0;
        virtual void setFromY (double newY) = 0;
        virtual void setToY (double newY) = 0;


        //dlugosc odcinka +
        virtual const double abs() const = 0;
};

SegmentShape* makeSegmentShape ();
SegmentShape* makeSegmentShape (const Point&, const Point&);


class LineShape : public Shape{
    public:
        virtual ~LineShape () {}
        virtual const double getNormalX () const = 0;
        virtual const double getNormalY () const = 0;
        virtual const double getC () const = 0;

        virtual void setNormalX (double x) = 0;
        virtual void setNormalY (double y) = 0;
        virtual void setC (double _c) = 0;

        //void goThroughPoints (const Point& p, const Point& q) {
        virtual void goThroughPoints (const double px, const double py, const double qx, const double qy) = 0;

};

LineShape* makeLineShape (double, double, double);
LineShape* makeLineShape (const SegmentShape&);
LineShape* makeLineShape (const Point&, const Point&);

class CircleShape : public Shape {
    public:
        virtual ~CircleShape () {}
        virtual const double getMiddleX () const = 0;
        virtual const double getMiddleY () const = 0;
        virtual const double getR () const = 0;

        virtual void setMiddleX (double x) = 0;
        virtual void setMiddleY (double y) = 0;
        virtual void setR (double _r) = 0;

};

CircleShape* makeCircleShape (const Point&, double);
CircleShape* makeCircleShape (const Point&, const Point&);
CircleShape* makeCircleShape (double, double, double);
CircleShape* makeCircleShape (const Point&, const Point&, const Point&);

//TODO: Triangle class
