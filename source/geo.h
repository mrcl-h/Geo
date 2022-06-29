#pragma once
#include "vectorHolder.h"
#include<vector>
#include<cmath>
#include<memory>
#include <SFML/Graphics.hpp>
//#include "drawersFWD.h"


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
    floatRect (float _left = 0, float _top = 0, float _width = 0, float _height = 0) :left (_left), top(_top), width (_width), height(_height) {}
};

typedef vectorHolder <PointShape*, LineShape*, CircleShape*, SegmentShape*, TriangleShape*> constructionElements;

struct uiOptionConditions {
    uint8_t lineCount, pointCount, circleCount, segmentCount, triangleCount;
};

void resetUiOptionConditions (uiOptionConditions& op);

struct Point {
    double x, y;
};

struct color {
    unsigned int r, g, b, a;
};

class ShapeVisitor {
    public:
        virtual ~ShapeVisitor () {}
        virtual void visitSegment (SegmentShape*) {}
        virtual void visitTriangle (TriangleShape*) {}
        virtual void visitLine (LineShape*) {}
        virtual void visitCircle (CircleShape*) {}
        virtual void visitPoint (PointShape*) {}
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
        //virtual void draw(drawingClass* drawer) const {}
        virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const {}
        //virtual void addToConstructionElements (constructionElements&) {}
        //virtual void removeFromConstructionElements (constructionElements&) {}
        virtual void addToCurrentConditions (uiOptionConditions& op, int c) {}
        virtual unsigned int getHitPriority () = 0;
        virtual bool isHit (const Point& p) = 0;
        virtual void moveShape (double x, double y) {}
        virtual ~Shape() {}

        virtual void getPreferredColor (color&) = 0;
        virtual void acceptVisitor (ShapeVisitor*) = 0;

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

Point getPointLocation (const PointShape&);

class SegmentShape : public Shape {
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

Point getCircleCenter (const CircleShape&);

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
Point getTrianglePointA (const TriangleShape& ts);
Point getTrianglePointB (const TriangleShape& ts);
Point getTrianglePointC (const TriangleShape& ts);

TriangleShape* makeTriangleShape(const Point&, const Point&, const Point&);
TriangleShape* makeTriangleShape(double, double, double, double, double, double);

class constructionElementsAddingShapeVisitor : public ShapeVisitor {
    private:
        constructionElements* elements;
    public:
        void setElements (constructionElements* _elements) {elements = _elements;}
        virtual ~constructionElementsAddingShapeVisitor () {}
        virtual void visitSegment (SegmentShape* ss) {
            elements->getVector<SegmentShape*>().push_back(ss);
        }
        virtual void visitTriangle (TriangleShape* ts) {
            elements->getVector<TriangleShape*>().push_back(ts);
        }
        virtual void visitLine (LineShape* ls) {
            elements->getVector<LineShape*>().push_back(ls); 
        }
        virtual void visitCircle (CircleShape* cs) {
            elements->getVector<CircleShape*>().push_back(cs);
        }
        virtual void visitPoint (PointShape* ps) {
            elements->getVector<PointShape*>().push_back(ps);
        }
};

class constructionElementsRemovingShapeVisitor : public ShapeVisitor {
    private:
        constructionElements* elements;
    public:
        void setElements (constructionElements* _elements) {elements = _elements;}
        virtual ~constructionElementsRemovingShapeVisitor () {}
        virtual void visitSegment (SegmentShape* ss) {
            elements->getVector<PointShape*>().erase (std::find (elements->getVector<PointShape*>().begin(), elements->getVector<PointShape*>().end(), static_cast<Shape*>(ss)));
        }
        virtual void visitTriangle (TriangleShape* ts) {
            elements->getVector<PointShape*>().erase (std::find (elements->getVector<PointShape*>().begin(), elements->getVector<PointShape*>().end(), static_cast<Shape*>(ts)));
        }
        virtual void visitLine (LineShape* ls) {
            elements->getVector<PointShape*>().erase (std::find (elements->getVector<PointShape*>().begin(), elements->getVector<PointShape*>().end(), static_cast<Shape*>(ls)));
        }
        virtual void visitCircle (CircleShape* cs) {
            elements->getVector<PointShape*>().erase (std::find (elements->getVector<PointShape*>().begin(), elements->getVector<PointShape*>().end(), static_cast<Shape*>(cs)));
        }
        virtual void visitPoint (PointShape* ps) {
            elements->getVector<PointShape*>().erase (std::find (elements->getVector<PointShape*>().begin(), elements->getVector<PointShape*>().end(), static_cast<Shape*>(ps)));
        }
};
