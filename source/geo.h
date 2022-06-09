#pragma once
#include "vectorHolder.h"
#include<vector>
#include<cmath>
#include<memory>
#include <SFML/Graphics.hpp>


//lista figur geometrycznych
class Shape;

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

class PointShape : public Shape{
    private:
        static constexpr double radiusOfDrawing=3;
        Point coordinates;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:
        virtual ~PointShape () {}

        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;
        virtual double getX () const;
        virtual double getY () const;

        virtual void setX (double newX);
        virtual void setY (double newY);

        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;

        virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;

        virtual double distFromPoint(const Point&) const override;

        PointShape(double=0, double=0);

        virtual double abs() const;

        virtual void addToConstructionElements (constructionElements& el) override;
        virtual void removeFromConstructionElements (constructionElements& el) override;

        virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p) override;

        virtual unsigned int getHitPriority () override;

        virtual void moveShape (double xMov, double yMov) override;

        PointShape (const LineShape&,const LineShape&);
};

PointShape* makePointShape (double = 0, double = 0);
PointShape* makePointShape (const LineShape&, const LineShape&);

Point getPointLocation (PointShape&);

class SegmentShape : public Shape {
    private:
        Point p1, p2;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:
        virtual ~SegmentShape () {}

        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;

        virtual double getFromX () const;
        virtual double getToX () const;
        virtual double getFromY () const;
        virtual double getToY () const;

        virtual void setFromX (double newX);
        virtual void setToX (double newX);
        virtual void setFromY (double newY);
        virtual void setToY (double newY);

        SegmentShape(const Point&, const Point&);
        SegmentShape () {}

        virtual double distFromPoint(const Point&) const override;

        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;

        virtual double abs() const;
        virtual void addToConstructionElements (constructionElements& el) override;
        virtual void removeFromConstructionElements (constructionElements& el) override;
        virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p) override;
        virtual unsigned int getHitPriority () override;

};

SegmentShape* makeSegmentShape ();
SegmentShape* makeSegmentShape (const Point&, const Point&);

Point getSegmentFrom (const SegmentShape& seg);
Point getSegmentTo (const SegmentShape& seg);

class LineShape : public Shape {
    private:
        Point n;
        double c;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
        void goThroughPoints (const Point& p, const Point& q);
    public:
        virtual ~LineShape () {}
        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;

        virtual double getNormalX () const;
        virtual double getNormalY () const;
        virtual double getC () const;

        virtual void setNormalX (double x);
        virtual void setNormalY (double y);
        virtual void setC (double _c);

        LineShape(double,double,double); //line ax+by+c=0
        LineShape(const Point&,const Point&); //line through two points
        LineShape(const SegmentShape&);

        double distFromPoint(const Point&) const override;
        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;


        virtual void goThroughPoints (const double px, const double py, const double qx, const double qy);

        LineShape(const CircleShape&,const CircleShape&);
        virtual void addToConstructionElements (constructionElements& el) override;
        virtual void removeFromConstructionElements (constructionElements& el) override;
        virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p) override;

        virtual unsigned int getHitPriority () override;
};

LineShape* makeLineShape (double, double, double);
LineShape* makeLineShape (const SegmentShape&);
LineShape* makeLineShape (const Point&, const Point&);

Point getLineNormal (const LineShape&);


class CircleShape : public Shape {
        Point middle;
        double r;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:

        virtual ~CircleShape () {}
        
        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;

        virtual double getMiddleX () const;
        virtual double getMiddleY () const;
        virtual double getR () const;

        virtual void setMiddleX (double x);
        virtual void setMiddleY (double y);
        virtual void setR (double _r);

        virtual double distFromPoint(const Point&) const override;
        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;
        virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;
        CircleShape(const Point&, const Point&, const Point&);
        CircleShape(const Point&, double);
        CircleShape(const Point&, const Point&);
        CircleShape (double, double, double);
        virtual void addToConstructionElements (constructionElements& el) override;
        virtual void removeFromConstructionElements (constructionElements& el) override;
        virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p) override;
        virtual unsigned int getHitPriority () override;
};

CircleShape* makeCircleShape (const Point&, double);
CircleShape* makeCircleShape (const Point&, const Point&);
CircleShape* makeCircleShape (double, double, double);
CircleShape* makeCircleShape (const Point&, const Point&, const Point&);

Point getCircleCenter (CircleShape&);

//TODO: Triangle class

class TriangleShape : public Shape {
        Point A, B, C;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:

        virtual ~TriangleShape () {}
        
        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;

        virtual double getAX () const;
        virtual double getAY () const;
        virtual double getBX () const;
        virtual double getBY () const;
        virtual double getCX () const;
        virtual double getCY () const;

        virtual void setAX (double _x);
        virtual void setAY (double _y);
        virtual void setBX (double _x);
        virtual void setBY (double _y);
        virtual void setCX (double _x);
        virtual void setCY (double _y);
        

        virtual double distFromPoint(const Point&) const override;
        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;
        virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;
        TriangleShape(const Point&, const Point&, const Point&);
        TriangleShape (double, double, double, double, double, double);
        virtual void addToConstructionElements (constructionElements& el) override;
        virtual void removeFromConstructionElements (constructionElements& el) override;
        virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p) override;
        virtual unsigned int getHitPriority () override;
};
TriangleShape* makeTriangleShape(const Point&, const Point&, const Point&);
TriangleShape* makeTriangleShape(double, double, double, double, double, double);

sf::Color getShapeColor (bool active, bool current, bool dependent);
