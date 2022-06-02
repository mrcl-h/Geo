#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<cmath>
#include<memory>

template <typename T>
class shapeTypeId {
    public:
        enum {typeId = 0};
};

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

struct constructionElements {
    std::vector<Point*> points;
    std::vector<Line*> lines;
    std::vector<Circle*> circles;
    std::vector<Segment*> segments;
};

void resetConstructionElements (constructionElements& el);

struct uiOptionConditions {
    uint8_t lineCount, pointCount, circleCount, segmentCount;
};

void resetUiOptionConditions (uiOptionConditions& op);

class Shape {
    protected:
        constexpr static double hitEpsilon = 4;
    public:
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
        //std::string name;
        virtual const double dist(Point) const =0;
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



class Point : public Shape {
    private:
        static constexpr double radiusOfDrawing=3;
    public:
        double x,y;

        //static Point zero();

        void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;

        void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;

        const double dist(Point) const override;


        friend std::ostream& operator<<(std::ostream&, const Point&);

        Point(double=0, double=0);

        const bool operator==(Point p) const {
            return ((dist(p))<0.01);
        }

        const Point operator+(Point p) const {
            return Point(x+p.x,y+p.y);
        }
        const Point operator-(Point p) const {
            return Point(x-p.x,y-p.y);
        }
        const Point operator*(double a) const {
            return Point(a*x,a*y);
        }
        const Point operator/(double a) const {
            return Point(x/a, y/a);
        }
        const double operator*(Point p) const {
            return x*p.x+y*p.y;
        }
        const double operator%(Point p) const {
            return x*p.y-y*p.x;
        }

        //długość do (0,0) +
        const double abs() const {
            return std::sqrt (x*x+y*y);
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
            return dist(p) < hitEpsilon;
        }

        virtual unsigned int getHitPriority () override {return 10;}

        virtual void moveShape (double xMov, double yMov) override {
            if (isDependent) return;
            x += xMov; 
            y += yMov;
        }

        Point(Line,Line);
};


class Segment : public Shape{
    public:
        Point p1, p2;

        Segment(Point,Point);
        Segment () {}

        const double dist(Point) const override;

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
            return dist(p) < hitEpsilon;
        }
        virtual unsigned int getHitPriority () override {return 8;}

};


class Line : public Shape{
    public:

        Point n;
        double c;

        Line(double,double,double); //line ax+by+c=0
        Line(Point,Point); //line through two points
        Line(Segment);

        const double dist(Point) const override;
        void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;


        void goThroughPoints (const Point& p, const Point& q) {
            if(p==q){
                throw std::invalid_argument("Points lay to close to each other");
            } else {
                if(p==Point(0,0)){
                    c=0;
                    n=Point(q.y, -q.x);
                } else if(q==Point(0,0)){
                    c=0;
                    n=Point(p.y, -p.x);
                } else {
                    c=-1;
                    n=Point((q.y-p.y)/(p%q), (-q.x+p.x)/(p%q));
                }
            }
        }

        friend std::ostream& operator<<(std::ostream&, const Line&);

        Line(Circle,Circle);
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
            return dist(p) < hitEpsilon;
        }

        virtual unsigned int getHitPriority () override {return 6;}
};


class Circle: public Shape {
    public:
        Point middle;
        double r;
        const double dist(Point) const override;
        void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;
        void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;
        friend std::ostream& operator<<(std::ostream&, const Circle&);
        Circle(Point, Point, Point);
        Circle(Point, double);
        Circle(Point, Point);
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
            return dist(p) < hitEpsilon;
        }
        virtual unsigned int getHitPriority () override {return 4;}
};

//TODO: Triangle class
