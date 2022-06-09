#pragma once
#include "vectorHolder.h"
#include<vector>
#include<cmath>
#include<memory>
#include <SFML/Graphics.hpp>


//lista figur geometrycznych
//class Shape;

class SegmentShape;
class TriangleShape;
class LineShape;
class CircleShape;
class PointShape;

inline double doubleAbs (double r) {
    return r >= 0 ? r : -r;
}


typedef vectorHolder <PointShape*, LineShape*, CircleShape*, SegmentShape*, TriangleShape*> constructionElements;
typedef vectorHolder <std::unique_ptr<PointShape>, std::unique_ptr<LineShape>, std::unique_ptr<CircleShape>, std::unique_ptr<SegmentShape>, std::unique_ptr<TriangleShape> > shapesType;

struct uiOptionConditions {
    uint8_t lineCount, pointCount, circleCount, segmentCount, triangleCount;
};

void resetUiOptionConditions (uiOptionConditions& op);

struct Point {
    double x, y;
};

//class Shape {
//    protected:
//        constexpr static double hitEpsilon = 4;
//    public:
//        void setExistance (bool) = 0;
//        bool getExistance () const = 0;
//        void setActivity (bool) = 0;
//        bool getActivity () const = 0;
//        void setCurrent (bool) = 0;
//        bool getCurrent () const = 0;
//        void setDependent (bool) = 0; 
//        bool getDependent () const = 0;
//        double distFromPoint(const Point&) const =0;
//        void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const {}
//        void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const {}
//        void addToConstructionElements (constructionElements&) {}
//        void removeFromConstructionElements (constructionElements&) {}
//        void addToCurrentConditions (uiOptionConditions& op, int c) {}
//        unsigned int getHitPriority () = 0;
//        bool isHit (const Point& p) = 0;
//        void moveShape (double x, double y) {}
//        ~Shape() {}
//
//};

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

class PointShape {
    private:
        static constexpr double radiusOfDrawing=3;
        Point coordinates;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
        constexpr static double hitEpsilon = 4;
    public:
        ~PointShape () {}

        void setExistance (bool ex);
        bool getExistance () const;
        void setActivity (bool ac);
        bool getActivity () const;
        void setCurrent (bool cu);
        bool getCurrent () const;
        void setDependent (bool de);
        bool getDependent () const;
        double getX () const;
        double getY () const;

        void setX (double newX);
        void setY (double newY);

        void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const;

        void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const;

        double distFromPoint(const Point&) const;

        PointShape(double=0, double=0);

        double abs() const;

        void addToConstructionElements (constructionElements& el);
        void removeFromConstructionElements (constructionElements& el);

        void addToCurrentConditions (uiOptionConditions& op, int c);
        bool isHit (const Point& p);

        unsigned int getHitPriority ();

        void moveShape (double xMov, double yMov);

        PointShape (const LineShape&,const LineShape&);
};

PointShape* makePointShape (double = 0, double = 0);
PointShape* makePointShape (const LineShape&, const LineShape&);

Point getPointLocation (PointShape&);

class SegmentShape {
    private:
        Point p1, p2;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
        constexpr static double hitEpsilon = 4;
    public:
        ~SegmentShape () {}

        void setExistance (bool ex);
        bool getExistance () const;
        void setActivity (bool ac);
        bool getActivity () const;
        void setCurrent (bool cu);
        bool getCurrent () const;
        void setDependent (bool de);
        bool getDependent () const;

        double getFromX () const;
        double getToX () const;
        double getFromY () const;
        double getToY () const;

        void setFromX (double newX);
        void setToX (double newX);
        void setFromY (double newY);
        void setToY (double newY);

        SegmentShape(const Point&, const Point&);
        SegmentShape () {}

        double distFromPoint(const Point&) const;

        void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const;

        double abs() const;
        void addToConstructionElements (constructionElements& el);
        void removeFromConstructionElements (constructionElements& el);
        void addToCurrentConditions (uiOptionConditions& op, int c);
        bool isHit (const Point& p);
        unsigned int getHitPriority ();

        void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const {}
};

SegmentShape* makeSegmentShape ();
SegmentShape* makeSegmentShape (const Point&, const Point&);

Point getSegmentFrom (const SegmentShape& seg);
Point getSegmentTo (const SegmentShape& seg);

class LineShape {
    private:
        Point n;
        double c;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
        void goThroughPoints (const Point& p, const Point& q);
        constexpr static double hitEpsilon = 4;
    public:
        ~LineShape () {}
        void setExistance (bool ex);
        bool getExistance () const;
        void setActivity (bool ac);
        bool getActivity () const;
        void setCurrent (bool cu);
        bool getCurrent () const;
        void setDependent (bool de);
        bool getDependent () const;

        double getNormalX () const;
        double getNormalY () const;
        double getC () const;

        void setNormalX (double x);
        void setNormalY (double y);
        void setC (double _c);

        LineShape(double,double,double); //line ax+by+c=0
        LineShape(const Point&,const Point&); //line through two points
        LineShape(const SegmentShape&);

        double distFromPoint(const Point&) const;
        void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const;


        void goThroughPoints (const double px, const double py, const double qx, const double qy);

        LineShape(const CircleShape&,const CircleShape&);
        void addToConstructionElements (constructionElements& el);
        void removeFromConstructionElements (constructionElements& el);
        void addToCurrentConditions (uiOptionConditions& op, int c);
        bool isHit (const Point& p);

        unsigned int getHitPriority ();
        void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const {}
};

LineShape* makeLineShape (double, double, double);
LineShape* makeLineShape (const SegmentShape&);
LineShape* makeLineShape (const Point&, const Point&);

Point getLineNormal (const LineShape&);


class CircleShape {
        Point middle;
        double r;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
        constexpr static double hitEpsilon = 4;
    public:

        ~CircleShape () {}
        
        void setExistance (bool ex);
        bool getExistance () const;
        void setActivity (bool ac);
        bool getActivity () const;
        void setCurrent (bool cu);
        bool getCurrent () const;
        void setDependent (bool de);
        bool getDependent () const;

        double getMiddleX () const;
        double getMiddleY () const;
        double getR () const;

        void setMiddleX (double x);
        void setMiddleY (double y);
        void setR (double _r);

        double distFromPoint(const Point&) const;
        void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const;
        void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const;
        CircleShape(const Point&, const Point&, const Point&);
        CircleShape(const Point&, double);
        CircleShape(const Point&, const Point&);
        CircleShape (double, double, double);
        void addToConstructionElements (constructionElements& el);
        void removeFromConstructionElements (constructionElements& el);
        void addToCurrentConditions (uiOptionConditions& op, int c);
        bool isHit (const Point& p);
        unsigned int getHitPriority ();
};

CircleShape* makeCircleShape (const Point&, double);
CircleShape* makeCircleShape (const Point&, const Point&);
CircleShape* makeCircleShape (double, double, double);
CircleShape* makeCircleShape (const Point&, const Point&, const Point&);

Point getCircleCenter (CircleShape&);

//TODO: Triangle class

class TriangleShape {
        Point A, B, C;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
        constexpr static double hitEpsilon = 4;
    public:

        ~TriangleShape () {}
        
        void setExistance (bool ex);
        bool getExistance () const;
        void setActivity (bool ac);
        bool getActivity () const;
        void setCurrent (bool cu);
        bool getCurrent () const;
        void setDependent (bool de);
        bool getDependent () const;

        double getAX () const;
        double getAY () const;
        double getBX () const;
        double getBY () const;
        double getCX () const;
        double getCY () const;

        void setAX (double _x);
        void setAY (double _y);
        void setBX (double _x);
        void setBY (double _y);
        void setCX (double _x);
        void setCY (double _y);
        

        double distFromPoint(const Point&) const;
        void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const;
        void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const;
        TriangleShape(const Point&, const Point&, const Point&);
        TriangleShape (double, double, double, double, double, double);
        void addToConstructionElements (constructionElements& el);
        void removeFromConstructionElements (constructionElements& el);
        void addToCurrentConditions (uiOptionConditions& op, int c);
        bool isHit (const Point& p);
        unsigned int getHitPriority ();
};
TriangleShape* makeTriangleShape(const Point&, const Point&, const Point&);
TriangleShape* makeTriangleShape(double, double, double, double, double, double);

sf::Color getShapeColor (bool active, bool current, bool dependent);
