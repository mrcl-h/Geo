#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<cmath>
#include<memory>


//lista figur geometrycznych
class Segment;
class Triangle;
class Line;
class Circle;
class PointShape;
class Shape;

inline double doubleAbs (double r) {
    return r >= 0 ? r : -r;
}

struct constructionElements {
    std::vector<PointShape*> points;
    std::vector<Line*> lines;
    std::vector<Circle*> circles;
    std::vector<Segment*> segments;
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
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
        //std::string name;
        virtual const double distFromPoint(const Point&) const =0;
        virtual void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const {}
        virtual void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const {}
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
    private:
        static constexpr double radiusOfDrawing=3;
        //double x,y;
        Point coordinates;
    public:

        const double getX () const {return coordinates.x;}
        const double getY () const {return coordinates.y;}

        void setX (double newX) {coordinates.x = newX;}
        void setY (double newY) {coordinates.y = newY;}
        //static Point zero();

        void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;

        void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;

        const double distFromPoint(const Point&) const override;


        friend std::ostream& operator<<(std::ostream&, const Point&);

        PointShape(double=0, double=0);



        //długość do (0,0) +
        const double abs() const {
            return std::sqrt (coordinates.x*coordinates.x+coordinates.y*coordinates.y);
        }

        virtual void addToConstructionElements (constructionElements& el) override {
            el.points.push_back(this);
        }
        virtual void removeFromConstructionElements (constructionElements& el) override {
            el.points.erase (std::find (el.points.begin(), el.points.end(), this));
        }

        virtual void addToCurrentConditions (uiOptionConditions& op, int c) override {
            op.pointCount += c;
        }
        virtual bool isHit (const Point& p) override {
            return distFromPoint(p) < hitEpsilon;
        }

        virtual unsigned int getHitPriority () override {return 10;}

        virtual void moveShape (double xMov, double yMov) override {
            if (isDependent) return;
            coordinates.x += xMov; 
            coordinates.y += yMov;
        }

        PointShape(const Line&,const Line&);
};


class Segment : public Shape{
    private:
        Point p1, p2;
    public:
        const double getFromX () const {return p1.x;}
        const double getToX () const {return p2.x;}
        const double getFromY () const {return p1.y;}
        const double getToY () const {return p2.y;}

        void setFromX (double newX) {p1.x = newX;}
        void setToX (double newX) {p2.x = newX;}
        void setFromY (double newY) {p1.y = newY;}
        void setToY (double newY) {p2.y = newY;}

        Segment(Point,Point);
        Segment () {}

        const double distFromPoint(const Point&) const override;

        void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;


        friend std::ostream& operator<<(std::ostream&, const Segment&);

        //dlugosc odcinka +
        const double abs();
        virtual void addToConstructionElements (constructionElements& el) override {
            el.segments.push_back(this);
        }
        virtual void removeFromConstructionElements (constructionElements& el) override {
            el.segments.erase (std::find (el.segments.begin(), el.segments.end(), this));
        }
        virtual void addToCurrentConditions (uiOptionConditions& op, int c) override {
            op.segmentCount += c;
        }
        virtual bool isHit (const Point& p) override {
            return distFromPoint(p) < hitEpsilon;
        }
        virtual unsigned int getHitPriority () override {return 8;}

};


class Line : public Shape{
    private:
        Point n;
        double c;
        void goThroughPoints (const Point& p, const Point& q) {
            if(p==q){
                throw std::invalid_argument("Points lay to close to each other");
            } else {
                if(p.x == 0 && p.y == 0){
                    c=0;
                    //n=Point(q.getY(), -q.getX());
                    n.x = q.y; n.y = -q.x;
                } else if(q.x == 0 && q.y == 0){
                    c=0;
                    //n=Point(p.getY(), -p.getX());
                    n.x = p.y; n.y = -p.x;
                } else {
                    c=-1;
                    //n=Point((q.getY()-p.getY())/(p%q), (-q.getX()+p.getX())/(p%q));
                    n.x = (q.y-p.y)/(p%q);
                    n.y = (-q.x+p.x)/(p%q);

                }
            }
        }
    public:

        const double getNormalX () const {return n.x;}
        const double getNormalY () const {return n.y;}
        const double getC () const {return c;}

        void setNormalX (double x) {n.x = x;}
        void setNormalY (double y) {n.y = y;}
        void setC (double _c) {c = _c;}

        Line(double,double,double); //line ax+by+c=0
        Line(const Point&,const Point&); //line through two points
        Line(const Segment&);

        const double distFromPoint(const Point&) const override;
        void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;


        //void goThroughPoints (const Point& p, const Point& q) {
        void goThroughPoints (const double px, const double py, const double qx, const double qy) {
            Point p, q;
            p.x = px; p.y = py;
            q.x = qx; q.y = qy;
            goThroughPoints (p, q);
        }

        friend std::ostream& operator<<(std::ostream&, const Line&);

        Line(const Circle&,const Circle&);
        virtual void addToConstructionElements (constructionElements& el) override {
            el.lines.push_back(this);
        }
        virtual void removeFromConstructionElements (constructionElements& el) override {
            el.lines.erase (std::find (el.lines.begin(), el.lines.end(), this));
        }
        virtual void addToCurrentConditions (uiOptionConditions& op, int c) override {
            op.lineCount += c;
        }
        virtual bool isHit (const Point& p) override {
            return distFromPoint(p) < hitEpsilon;
        }

        virtual unsigned int getHitPriority () override {return 6;}
};


class Circle: public Shape {
        Point middle;
        double r;
    public:
        const double getMiddleX () const {return middle.x;}
        const double getMiddleY () const {return middle.y;}
        const double getR () const {return r;}

        void setMiddleX (double x) {middle.x = x;}
        void setMiddleY (double y) {middle.y = y;}
        void setR (double _r) {r = _r;}

        const double distFromPoint(const Point&) const override;
        void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;
        void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;
        friend std::ostream& operator<<(std::ostream&, const Circle&);
        Circle(const Point&, const Point&, const Point&);
        Circle(const Point&, double);
        Circle(const Point&, const Point&);
        Circle (double, double, double);
        virtual void addToConstructionElements (constructionElements& el) override {
            el.circles.push_back(this);
        }
        virtual void removeFromConstructionElements (constructionElements& el) override {
            el.circles.erase (std::find (el.circles.begin(), el.circles.end(), this));
        }
        virtual void addToCurrentConditions (uiOptionConditions& op, int c) override {
            op.circleCount += c;
        }
        virtual bool isHit (const Point& p) override {
            return distFromPoint(p) < hitEpsilon;
        }
        virtual unsigned int getHitPriority () override {return 4;}
};

//TODO: Triangle class
