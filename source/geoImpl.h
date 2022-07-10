/* file responsible for creating implementations of shape classes
 * */
#pragma once
#include "geo.h"

class PointShapeImpl : public PointShape {
    private:
        static constexpr double radiusOfDrawing=3;
        Point coordinates;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:
        virtual ~PointShapeImpl () {}

        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;
        virtual double getX () const override;
        virtual double getY () const override;

        virtual void setX (double newX) override;
        virtual void setY (double newY) override;

        //virtual void draw(drawingClass* drawer) const override;

        //virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;

        virtual double distFromPoint(const Point&) const override;

        PointShapeImpl(double=0, double=0);

        virtual double abs() const override;

        //virtual void addToConstructionElements (constructionElements& el) override;
        //virtual void removeFromConstructionElements (constructionElements& el) override;

        //virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p, float scalingFactor) override;

        virtual unsigned int getHitPriority () override;

        virtual void moveShape (double xMov, double yMov) override;

        PointShapeImpl (const LineShape&,const LineShape&);

        virtual void getPreferredColor (color& c) override;

        virtual void acceptVisitor (ShapeVisitor* vis) override {vis->visitPoint (this);}
};

class SegmentShapeImpl : public SegmentShape{
    private:
        Point p1, p2;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:
        virtual ~SegmentShapeImpl () {}

        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;

        virtual double getFromX () const override;
        virtual double getToX () const override;
        virtual double getFromY () const override;
        virtual double getToY () const override;

        virtual void setFromX (double newX) override;
        virtual void setToX (double newX) override;
        virtual void setFromY (double newY) override;
        virtual void setToY (double newY) override;

        SegmentShapeImpl(const Point&, const Point&);
        SegmentShapeImpl () {}

        virtual double distFromPoint(const Point&) const override;

        //virtual void draw(drawingClass* drawer) const override;

        virtual double abs() const override;
        //virtual void addToConstructionElements (constructionElements& el) override;
        //virtual void removeFromConstructionElements (constructionElements& el) override;
        //virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p, float scalingFactor) override;
        virtual unsigned int getHitPriority () override;

        virtual void getPreferredColor (color& c) override;

        virtual void acceptVisitor (ShapeVisitor* vis) override {vis->visitSegment (this);}

};

class LineShapeImpl : public LineShape{
    private:
        Point n;
        double c;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
        void goThroughPoints (const Point& p, const Point& q);
    public:
        virtual ~LineShapeImpl () {}
        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;

        virtual double getNormalX () const override;
        virtual double getNormalY () const override;
        virtual double getC () const override;

        virtual void setNormalX (double x) override;
        virtual void setNormalY (double y) override;
        virtual void setC (double _c) override;

        LineShapeImpl(double,double,double); //line ax+by+c=0
        LineShapeImpl(const Point&,const Point&); //line through two points
        LineShapeImpl(const SegmentShape&);

        double distFromPoint(const Point&) const override;
        //virtual void draw(drawingClass* drawer) const override;


        virtual void goThroughPoints (const double px, const double py, const double qx, const double qy) override;

        LineShapeImpl(const CircleShape&,const CircleShape&);
        //virtual void addToConstructionElements (constructionElements& el) override;
        //virtual void removeFromConstructionElements (constructionElements& el) override;
        //virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p, float scalingFactor) override;

        virtual unsigned int getHitPriority () override;

        virtual void getPreferredColor (color& c) override;

        virtual void acceptVisitor (ShapeVisitor* vis) override {vis->visitLine (this);}
};

class CircleShapeImpl : public CircleShape {
        Point middle;
        double r;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:

        virtual ~CircleShapeImpl () {}

        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;

        virtual double getMiddleX () const override;
        virtual double getMiddleY () const override;
        virtual double getR () const override;

        virtual void setMiddleX (double x) override;
        virtual void setMiddleY (double y) override;
        virtual void setR (double _r) override;

        virtual double distFromPoint(const Point&) const override;
        //virtual void draw(drawingClass* drawer) const override;
        //virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;
        CircleShapeImpl(const Point&, const Point&, const Point&);
        CircleShapeImpl(const Point&, double);
        CircleShapeImpl(const Point&, const Point&);
        CircleShapeImpl (double, double, double);
        //virtual void addToConstructionElements (constructionElements& el) override;
        //virtual void removeFromConstructionElements (constructionElements& el) override;
        //virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p, float scalingFactor) override;
        virtual unsigned int getHitPriority () override;

        virtual void getPreferredColor (color& c) override;

        virtual void acceptVisitor (ShapeVisitor* vis) override {vis->visitCircle (this);}
};

class TriangleShapeImpl : public TriangleShape {
        Point A, B, C;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:

        virtual ~TriangleShapeImpl () {}

        virtual void setExistance (bool ex) override;
        virtual bool getExistance () const override;
        virtual void setActivity (bool ac) override;
        virtual bool getActivity () const override;
        virtual void setCurrent (bool cu) override;
        virtual bool getCurrent () const override;
        virtual void setDependent (bool de) override;
        virtual bool getDependent () const override;

        virtual double getAX () const override;
        virtual double getAY () const override;
        virtual double getBX () const override;
        virtual double getBY () const override;
        virtual double getCX () const override;
        virtual double getCY () const override;

        virtual void setAX (double _x) override;
        virtual void setAY (double _y) override;
        virtual void setBX (double _x) override;
        virtual void setBY (double _y) override;
        virtual void setCX (double _x) override;
        virtual void setCY (double _y) override;


        virtual double distFromPoint(const Point&) const override;
        //virtual void draw(drawingClass* drawer) const override;
        //virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;
        TriangleShapeImpl(const Point&, const Point&, const Point&);
        TriangleShapeImpl (double, double, double, double, double, double);
        //virtual void addToConstructionElements (constructionElements& el) override;
        //virtual void removeFromConstructionElements (constructionElements& el) override;
        //virtual void addToCurrentConditions (uiOptionConditions& op, int c) override;
        virtual bool isHit (const Point& p, float scalingFactor) override;
        virtual unsigned int getHitPriority () override;

        virtual void getPreferredColor (color& c) override;

        virtual void acceptVisitor (ShapeVisitor* vis) override {vis->visitTriangle (this);}
};

//sf::Color getShapeColor (bool active, bool current, bool dependent);
