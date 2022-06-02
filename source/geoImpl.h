#include "geo.h"
#include <algorithm>
#include <stdexcept>

class PointShapeImpl : public PointShape {
    private:
        static constexpr double radiusOfDrawing=3;
        //double x,y;
        Point coordinates;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:
        virtual ~PointShapeImpl () {}

        virtual void setExistance (bool ex) override {exists = ex;}
        const virtual bool getExistance () const override {return exists;}
        virtual void setActivity (bool ac) override {isActive = ac;}
        const virtual bool getActivity () const override {return isActive;}
        virtual void setCurrent (bool cu) override {isCurrent = cu;}
        const virtual bool getCurrent () const override {return isCurrent;}
        virtual void setDependent (bool de) override {isDependent = de;}
        const virtual bool getDependent () const override {return isDependent;}
        virtual const double getX () const override {return coordinates.x;}
        virtual const double getY () const override {return coordinates.y;}

        virtual void setX (double newX) override {coordinates.x = newX;}
        virtual void setY (double newY) override {coordinates.y = newY;}
        //static Point zero();

        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;

        virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;

        virtual const double distFromPoint(const Point&) const override;

        PointShapeImpl(double=0, double=0);

        //długość do (0,0) +
        virtual const double abs() const override {
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

        PointShapeImpl (const LineShape&,const LineShape&);
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

        virtual void setExistance (bool ex) override {exists = ex;}
        const virtual bool getExistance () const override {return exists;}
        virtual void setActivity (bool ac) override {isActive = ac;}
        const virtual bool getActivity () const override {return isActive;}
        virtual void setCurrent (bool cu) override {isCurrent = cu;}
        const virtual bool getCurrent () const override {return isCurrent;}
        virtual void setDependent (bool de) override {isDependent = de;}
        const virtual bool getDependent () const override {return isDependent;}
        virtual const double getFromX () const override {return p1.x;}
        virtual const double getToX () const override {return p2.x;}
        virtual const double getFromY () const override {return p1.y;}
        virtual const double getToY () const override {return p2.y;}

        virtual void setFromX (double newX) override {p1.x = newX;}
        virtual void setToX (double newX) override {p2.x = newX;}
        virtual void setFromY (double newY) override {p1.y = newY;}
        virtual void setToY (double newY) override {p2.y = newY;}

        SegmentShapeImpl(const Point&, const Point&);
        SegmentShapeImpl () {}

        virtual const double distFromPoint(const Point&) const override;

        //virtual void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;
        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;

        //dlugosc odcinka +
        virtual const double abs() const override;
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

class LineShapeImpl : public LineShape{
    private:
        Point n;
        double c;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
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
        virtual ~LineShapeImpl () {}
        virtual void setExistance (bool ex) override {exists = ex;}
        const virtual bool getExistance () const override {return exists;}
        virtual void setActivity (bool ac) override {isActive = ac;}
        const virtual bool getActivity () const override {return isActive;}
        virtual void setCurrent (bool cu) override {isCurrent = cu;}
        const virtual bool getCurrent () const override {return isCurrent;}
        virtual void setDependent (bool de) override {isDependent = de;}
        const virtual bool getDependent () const override {return isDependent;}

        virtual const double getNormalX () const override {return n.x;}
        virtual const double getNormalY () const override {return n.y;}
        virtual const double getC () const override {return c;}

        virtual void setNormalX (double x) override {n.x = x;}
        virtual void setNormalY (double y) override {n.y = y;}
        virtual void setC (double _c) override {c = _c;}

        LineShapeImpl(double,double,double); //line ax+by+c=0
        LineShapeImpl(const Point&,const Point&); //line through two points
        LineShapeImpl(const SegmentShape&);

        const double distFromPoint(const Point&) const override;
        //void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;
        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;


        //void goThroughPoints (const Point& p, const Point& q) {
        virtual void goThroughPoints (const double px, const double py, const double qx, const double qy) override {
            Point p, q;
            p.x = px; p.y = py;
            q.x = qx; q.y = qy;
            goThroughPoints (p, q);
        }

        LineShapeImpl(const CircleShape&,const CircleShape&);
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

class CircleShapeImpl : public CircleShape {
        Point middle;
        double r;
        bool exists = true;
        bool isActive = false;
        bool isCurrent = false;
        bool isDependent = false;
    public:

        virtual ~CircleShapeImpl () {}
        
        virtual void setExistance (bool ex) override {exists = ex;}
        const virtual bool getExistance () const override {return exists;}
        virtual void setActivity (bool ac) override {isActive = ac;}
        const virtual bool getActivity () const override {return isActive;}
        virtual void setCurrent (bool cu) override {isCurrent = cu;}
        const virtual bool getCurrent () const override {return isCurrent;}
        virtual void setDependent (bool de) override {isDependent = de;}
        const virtual bool getDependent () const override {return isDependent;}
        virtual const double getMiddleX () const override {return middle.x;}
        virtual const double getMiddleY () const override {return middle.y;}
        virtual const double getR () const override {return r;}

        virtual void setMiddleX (double x) override {middle.x = x;}
        virtual void setMiddleY (double y) override {middle.y = y;}
        virtual void setR (double _r) override {r = _r;}

        virtual const double distFromPoint(const Point&) const override;
        //virtual void draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;
        virtual void draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;
        //virtual void hull_draw(sf::RenderWindow*, sf::FloatRect visible, sf::FloatRect box) const override;
        virtual void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const override;
        CircleShapeImpl(const Point&, const Point&, const Point&);
        CircleShapeImpl(const Point&, double);
        CircleShapeImpl(const Point&, const Point&);
        CircleShapeImpl (double, double, double);
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
