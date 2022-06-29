#include "geoImpl.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "drawers.h"

void PointShapeImpl::setExistance (bool ex) {exists = ex;}
bool PointShapeImpl::getExistance () const {return exists;}
void PointShapeImpl::setActivity (bool ac) {isActive = ac;}
bool PointShapeImpl::getActivity () const {return isActive;}
void PointShapeImpl::setCurrent (bool cu) {isCurrent = cu;}
bool PointShapeImpl::getCurrent () const {return isCurrent;}
void PointShapeImpl::setDependent (bool de) {isDependent = de;}
bool PointShapeImpl::getDependent () const {return isDependent;}
double PointShapeImpl::getX () const {return coordinates.x;}
double PointShapeImpl::getY () const {return coordinates.y;}

void PointShapeImpl::setX (double newX) {coordinates.x = newX;}
void PointShapeImpl::setY (double newY) {coordinates.y = newY;}

void SegmentShapeImpl::setExistance (bool ex) {exists = ex;}
bool SegmentShapeImpl::getExistance () const {return exists;}
void SegmentShapeImpl::setActivity (bool ac) {isActive = ac;}
bool SegmentShapeImpl::getActivity () const {return isActive;}
void SegmentShapeImpl::setCurrent (bool cu) {isCurrent = cu;}
bool SegmentShapeImpl::getCurrent () const {return isCurrent;}
void SegmentShapeImpl::setDependent (bool de) {isDependent = de;}
bool SegmentShapeImpl::getDependent () const {return isDependent;}

double SegmentShapeImpl::getFromX () const {return p1.x;}
double SegmentShapeImpl::getToX () const {return p2.x;}
double SegmentShapeImpl::getFromY () const {return p1.y;}
double SegmentShapeImpl::getToY () const {return p2.y;}

void SegmentShapeImpl::setFromX (double newX) {p1.x = newX;}
void SegmentShapeImpl::setToX (double newX) {p2.x = newX;}
void SegmentShapeImpl::setFromY (double newY) {p1.y = newY;}
void SegmentShapeImpl::setToY (double newY) {p2.y = newY;}

void LineShapeImpl::setExistance (bool ex) {exists = ex;}
bool LineShapeImpl::getExistance () const {return exists;}
void LineShapeImpl::setActivity (bool ac) {isActive = ac;}
bool LineShapeImpl::getActivity () const {return isActive;}
void LineShapeImpl::setCurrent (bool cu) {isCurrent = cu;}
bool LineShapeImpl::getCurrent () const {return isCurrent;}
void LineShapeImpl::setDependent (bool de) {isDependent = de;}
bool LineShapeImpl::getDependent () const {return isDependent;}

double LineShapeImpl::getNormalX () const {return n.x;}
double LineShapeImpl::getNormalY () const {return n.y;}
double LineShapeImpl::getC () const {return c;}

void LineShapeImpl::setNormalX (double x) {n.x = x;}
void LineShapeImpl::setNormalY (double y) {n.y = y;}
void LineShapeImpl::setC (double _c) {c = _c;}

void CircleShapeImpl::setExistance (bool ex) {exists = ex;}
bool CircleShapeImpl::getExistance () const {return exists;}
void CircleShapeImpl::setActivity (bool ac) {isActive = ac;}
bool CircleShapeImpl::getActivity () const {return isActive;}
void CircleShapeImpl::setCurrent (bool cu) {isCurrent = cu;}
bool CircleShapeImpl::getCurrent () const {return isCurrent;}
void CircleShapeImpl::setDependent (bool de) {isDependent = de;}
bool CircleShapeImpl::getDependent () const {return isDependent;}

double CircleShapeImpl::getMiddleX () const {return middle.x;}
double CircleShapeImpl::getMiddleY () const {return middle.y;}
double CircleShapeImpl::getR () const {return r;}

void CircleShapeImpl::setMiddleX (double x) {middle.x = x;}
void CircleShapeImpl::setMiddleY (double y) {middle.y = y;}
void CircleShapeImpl::setR (double _r) {r = _r;}

void TriangleShapeImpl::setExistance (bool ex) {exists = ex;}
bool TriangleShapeImpl::getExistance () const {return exists;}
void TriangleShapeImpl::setActivity (bool ac) {isActive = ac;}
bool TriangleShapeImpl::getActivity () const {return isActive;}
void TriangleShapeImpl::setCurrent (bool cu) {isCurrent = cu;}
bool TriangleShapeImpl::getCurrent () const {return isCurrent;}
void TriangleShapeImpl::setDependent (bool de) {isDependent = de;}
bool TriangleShapeImpl::getDependent () const {return isDependent;}

void TriangleShapeImpl::setAX (double x) {A.x=x;}
void TriangleShapeImpl::setAY (double y) {A.y=y;}
void TriangleShapeImpl::setBX (double x) {B.x=x;}
void TriangleShapeImpl::setBY (double y) {B.y=y;}
void TriangleShapeImpl::setCX (double x) {C.x=x;}
void TriangleShapeImpl::setCY (double y) {C.y=y;}

double TriangleShapeImpl::getAX () const {return A.x;}
double TriangleShapeImpl::getAY () const {return A.y;}
double TriangleShapeImpl::getBX () const {return B.x;}
double TriangleShapeImpl::getBY () const {return B.y;}
double TriangleShapeImpl::getCX () const {return C.x;}
double TriangleShapeImpl::getCY () const {return C.y;}

PointShape* makePointShape (double x, double y) {
    return new PointShapeImpl (x, y);
}
PointShape* makePointShape (const LineShape& l1, const LineShape& l2) {
    return new PointShapeImpl (l1, l2);
}

SegmentShape* makeSegmentShape () {
    return new SegmentShapeImpl;
}
SegmentShape* makeSegmentShape (const Point& p1, const Point& p2) {
    return new SegmentShapeImpl (p1, p2);
}

LineShape* makeLineShape (double a, double b, double c) {
    return new LineShapeImpl (a,b,c);
}
LineShape* makeLineShape (const SegmentShape& s) {
    return new LineShapeImpl (s); 
}
LineShape* makeLineShape (const Point& l, const Point& r) {
    return new LineShapeImpl (l, r);
}
CircleShape* makeCircleShape (const Point& p, double r) {
    return new CircleShapeImpl (p, r);
}
CircleShape* makeCircleShape (const Point& p, const Point& r) {
    return new CircleShapeImpl (p, r);
}
CircleShape* makeCircleShape (double x, double y, double r) {
    return new CircleShapeImpl (x, y, r);
}
CircleShape* makeCircleShape (const Point& a, const Point& b, const Point& c) {
    return new CircleShapeImpl (a,b,c);
}
TriangleShape* makeTriangleShape (const Point& p1, const Point& p2, const Point& p3){
    return new TriangleShapeImpl(p1, p2, p3);
}
TriangleShape* makeTriangleShape (double ax, double ay, double bx, double by, double cx, double cy){
    return new TriangleShapeImpl(ax, ay, bx, by, cx, cy);
}

double PointShapeImpl::abs() const {
    return std::sqrt (coordinates.x*coordinates.x+coordinates.y*coordinates.y);
}
//void PointShapeImpl::addToConstructionElements (constructionElements& el) {
//    //el.points.push_back(this);
//    el.getVector<PointShape*>().push_back(this);
//}
//void PointShapeImpl::removeFromConstructionElements (constructionElements& el) {
//    //el.points.erase (std::find (el.points.begin(), el.points.end(), static_cast<Shape*>(this)));
//    el.getVector<PointShape*>().erase (std::find (el.getVector<PointShape*>().begin(), el.getVector<PointShape*>().end(), static_cast<Shape*>(this)));
//}
void PointShapeImpl::addToCurrentConditions (uiOptionConditions& op, int c) {
    op.pointCount += c;
}
bool PointShapeImpl::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}

unsigned int PointShapeImpl::getHitPriority () {return 10;}

void PointShapeImpl::moveShape (double xMov, double yMov) {
    if (isDependent) return;
    coordinates.x += xMov; 
    coordinates.y += yMov;
}

void PointShapeImpl::getPreferredColor (color& col) { //COLOR
    col.a = 255;
    if (getDependent()) { col.r = 255; } else { col.r = 0; }
    if (getCurrent()) {
        col.g = 255;    
        col.b = 0;
    } else if (getActivity()) {
        col.g = 0;
        col.b = 255;
    } else {
        col.g = 0;
        col.b = 0;
    }
}

//void SegmentShapeImpl::addToConstructionElements (constructionElements& el) {
//    //el.segments.push_back(this);
//    el.getVector<SegmentShape*>().push_back(this);
//}
//void SegmentShapeImpl::removeFromConstructionElements (constructionElements& el) {
//    //el.segments.erase (std::find (el.segments.begin(), el.segments.end(), static_cast<Shape*>(this)));
//    el.getVector<SegmentShape*>().erase (std::find (el.getVector<SegmentShape*>().begin(), el.getVector<SegmentShape*>().end(), static_cast<Shape*>(this)));
//}
void SegmentShapeImpl::addToCurrentConditions (uiOptionConditions& op, int c) {
    op.segmentCount += c;
}
bool SegmentShapeImpl::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}
unsigned int SegmentShapeImpl::getHitPriority () {return 8;}

void SegmentShapeImpl::getPreferredColor (color& c) { //COLOR
    c.a = 255;
    c.r = 0;
    if (getCurrent()) {
        c.g = 255;
        c.b = 0;
    } else if (getActivity()) {
        c.g = 0;
        c.b = 255;
    } else {
        c.g = 0;
        c.b = 0;
    }
}

void LineShapeImpl::goThroughPoints (const Point& p, const Point& q) {
    if(p==q){
        throw std::invalid_argument("Points lay to close to each other");
    } else {
        if(p.x < 1 && p.x > -1 && p.y < 1 && p.y > -1){
            c=0;
            n.x = q.y; n.y = -q.x;
        } else if(q.x < 1 && q.x > -1 && q.y < 1 && q.y > -1){
            c=0;
            n.x = p.y; n.y = -p.x;
        } else {
            c=-1;
            n.x = (q.y-p.y)/(p%q);
            n.y = (-q.x+p.x)/(p%q);

        }
    }
}

void LineShapeImpl::goThroughPoints (const double px, const double py, const double qx, const double qy) {
    Point p, q;
    p.x = px; p.y = py;
    q.x = qx; q.y = qy;
    goThroughPoints (p, q);
}

//void LineShapeImpl::addToConstructionElements (constructionElements& el) {
//    //el.lines.push_back(this);
//    el.getVector<LineShape*>().push_back(this);
//}
//void LineShapeImpl::removeFromConstructionElements (constructionElements& el) {
//    //el.lines.erase (std::find (el.lines.begin(), el.lines.end(), static_cast<Shape*>(this)));
//    el.getVector<LineShape*>().erase (std::find (el.getVector<LineShape*>().begin(), el.getVector<LineShape*>().end(), static_cast<Shape*>(this)));
//}
void LineShapeImpl::addToCurrentConditions (uiOptionConditions& op, int m) {
    op.lineCount += m;
}
bool LineShapeImpl::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}

unsigned int LineShapeImpl::getHitPriority () {return 6;}

void LineShapeImpl::getPreferredColor (color& col) { //COLOR
    col.a = 255;
    col.r = 0;
    if (getCurrent()) {
        col.g = 255;
        col.b = 0;
    } else if (getActivity()) {
        col.g = 0;
        col.b = 255;
    } else {
        col.g = 0;
        col.b = 0;
    }
}

//void CircleShapeImpl::addToConstructionElements (constructionElements& el) {
//    //el.circles.push_back(this);
//    el.getVector<CircleShape*>().push_back(this);
//}
//void CircleShapeImpl::removeFromConstructionElements (constructionElements& el) {
//    //el.circles.erase (std::find (el.circles.begin(), el.circles.end(), static_cast<Shape*>(this)));
//    el.getVector<CircleShape*>().erase (std::find (el.getVector<CircleShape*>().begin(), el.getVector<CircleShape*>().end(), static_cast<Shape*>(this)));
//}
void CircleShapeImpl::addToCurrentConditions (uiOptionConditions& op, int c) {
    op.circleCount += c;
}
bool CircleShapeImpl::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}
unsigned int CircleShapeImpl::getHitPriority () {return 4;}

void CircleShapeImpl::getPreferredColor (color& c) { //COLOR
    c.a = 255;
    c.r = 0;
    if (getCurrent()) {
        c.g = 255;
        c.b = 0;
    } else if (getActivity()) {
        c.g = 0;
        c.b = 255;
    } else {
        c.g = 0;
        c.b = 0;
    }
}

PointShapeImpl::PointShapeImpl(double x1, double y2){
	coordinates.x=x1;
	coordinates.y=y2;
}
double PointShapeImpl::distFromPoint(const Point& v) const {
    Point temp=coordinates-v;
    return length(temp); 
}



//void TriangleShapeImpl::addToConstructionElements (constructionElements& el) {
//    el.getVector<TriangleShape*>().push_back(this);
//}
//void TriangleShapeImpl::removeFromConstructionElements (constructionElements& el) {
//    //el.circles.erase (std::find (el.circles.begin(), el.circles.end(), static_cast<Shape*>(this)));
//    el.getVector<TriangleShape*>().erase (std::find (el.getVector<TriangleShape*>().begin(), el.getVector<TriangleShape*>().end(), static_cast<Shape*>(this)));
//}
void TriangleShapeImpl::addToCurrentConditions (uiOptionConditions& op, int c) {
    op.triangleCount += c;
}
bool TriangleShapeImpl::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}
unsigned int TriangleShapeImpl::getHitPriority () {return 5;}

void TriangleShapeImpl::getPreferredColor (color& c) { //COLOR
    c.r = 255;
    c.g = 0;
    c.b = 0;
    c.a = 125;
}

sf::Color getShapeColor (bool active, bool current, bool dependent) {
    if (dependent) {
        if (current) {
            return sf::Color::Yellow;
        } else if (active) {
            return sf::Color::Magenta;
        } else {
            return sf::Color::Red;
        }
    } else {
        if (current) {
            return sf::Color::Green;
        } else if (active) {
            return sf::Color::Blue;
        } else {
            return sf::Color::Black;
        }
    }
}

//void PointShapeImpl::draw(drawingClass* drawer) const{
//    sf::Color drawingColor = getShapeColor (isActive, isCurrent, isDependent);
//    drawer->setColor (drawingColor.r, drawingColor.g, drawingColor.b, 255);
//    drawer->drawPoint (coordinates);
//    /*
//    sf::CircleShape shape (radiusOfDrawing);
//    float alpha = (coordinates.x-visible.left)/visible.width;
//    float beta = (coordinates.y-visible.top)/visible.height;
//    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
//    v.x -= radiusOfDrawing;
//    v.y -= radiusOfDrawing;
//    shape.setPosition(v);
//    shape.setFillColor (getShapeColor (isActive, isCurrent, isDependent));
//    window->draw(shape);
//    */
//}
//void PointShapeImpl::hull_draw(sf::RenderWindow *window, const sf::FloatRect& visible, const sf::FloatRect& box) const{
//
//    sf::CircleShape shape (2*radiusOfDrawing);
//    float alpha = (coordinates.x-visible.left)/visible.width;
//    float beta = (coordinates.y-visible.top)/visible.height;
//    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
//    v.x -= 2*radiusOfDrawing;
//    v.y -= 2*radiusOfDrawing;
//    shape.setPosition(v);
//    shape.setFillColor(sf::Color(0,0,0,100));
//
//    window->draw(shape);
//}
PointShapeImpl::PointShapeImpl(const LineShape& l,const LineShape& m){

    if (m.getC() < 1 && m.getC() > -1 && l.getC() < 1 && l.getC() > -1) {
        coordinates.x=0;
        coordinates.y=0;
    } else {
        Point mNormal, lNormal;
        mNormal.x = m.getNormalX();
        mNormal.y = m.getNormalY();
        lNormal.x = l.getNormalX();
        lNormal.y = l.getNormalY();
        coordinates.x=(l.getC()*m.getNormalY()-m.getC()*l.getNormalY())/(mNormal%lNormal);
        coordinates.y=(-l.getC()*m.getNormalX()+m.getC()*l.getNormalX())/(mNormal*lNormal);
    }
}

//----------------------------------------------

SegmentShapeImpl::SegmentShapeImpl(const Point& A, const Point& B){
    p1=A;
    p1=B;
}
//void SegmentShapeImpl::draw(drawingClass* drawer) const{
//    drawer->setColor (0,0,0);
//    drawer->drawSegment (p1, p2);
//    /*
//    float tp1x = box.left + (p1.x-visible.left)/visible.width*box.width;
//    float tp2x = box.left + (p2.x-visible.left)/visible.width*box.width;
//
//    float tp1y = box.top + (p1.y-visible.top)/visible.height*box.height;
//    float tp2y = box.top + (p2.y-visible.top)/visible.height*box.height;
//    sf::Vertex line[] =
//    {
//        sf::Vertex(sf::Vector2f(tp1x, tp1y)),
//        sf::Vertex(sf::Vector2f(tp2x, tp2y))
//    };
//    line[0].color=sf::Color(0,0,0);
//    line[1].color=sf::Color(0,0,0);
//    window->draw(line, 2, sf::Lines);
//    */
//}
double SegmentShapeImpl::distFromPoint(const Point& v) const{
    Point D=p2-p1;

    if((v-p1)*D<0){
        return dist (v, p1);
    }
    if((v-p2)*D>0){
        return dist (v, p2);
    }
    return std::abs(((v-p2)%D)/(dist(p1,p2)));
}
double SegmentShapeImpl::abs() const {
    return dist (p1, p2);
}
//----------------------------------------------------
LineShapeImpl::LineShapeImpl(double a1, double b1, double c1){
    if(a1 < 1 && a1 > -1 && b1 < 1 && b1 > -1)
        throw std::invalid_argument("First two arguments can not be zero at the same time");
    n.x = a1; n.y = b1;
    c=c1;
}
LineShapeImpl::LineShapeImpl(const Point& p,const Point& q){
    goThroughPoints (p,q);
}
LineShapeImpl::LineShapeImpl(const SegmentShape& s){
    Point p1, p2;
    p1.x = s.getFromX(); p1.y = s.getFromY();
    p2.x = s.getToX(); p2.y = s.getToY();
    goThroughPoints (p1, p2);
}

double LineShapeImpl::distFromPoint(const Point& v) const{
    return doubleAbs((n*v+c)/length(n));
}
//void LineShapeImpl::draw(drawingClass* drawer) const{
//    
//    sf::Color lineColor;
//    if (isCurrent) {
//        lineColor = sf::Color::Green;
//    } else if (isActive) {
//        lineColor = sf::Color::Blue;
//    } else {
//        lineColor = sf::Color::Black;
//    }
//    drawer->setColor (lineColor.r, lineColor.g, lineColor.b);
//    drawer->drawLine (n.x, n.y, c);
//    /*
//    sf::Vector2f from;
//    sf::Vector2f to;
//
//    unsigned int cond1 = (n.y+n.x)>=0;
//    unsigned int cond2 = (n.y-n.x)<0;
//    if (cond1^cond2) { //draw horizontally
//        from.x = (box.left);
//        from.y = box.top+box.height/visible.height*((-c-n.x*visible.left)/n.y-visible.top);
//
//
//        to.x = (box.left+box.width);
//        to.y = box.top+box.height/visible.height*((-c-n.x*(visible.left+visible.width))/n.y-visible.top);
//    } else { //draw vertically
//        from.y = (box.top);
//        from.x = box.left+box.width/visible.width*((-c-n.y*visible.top)/n.x-visible.left);
//
//        to.y = (box.top+box.height);
//        to.x = box.left+box.width/visible.width*((-c-n.y*(visible.top+visible.height))/n.x-visible.left);
//    }
//    sf::Vertex line[] = { from, to };
//    sf::Color lineColor;
//    if (isCurrent) {
//        lineColor = sf::Color::Green;
//    } else if (isActive) {
//        lineColor = sf::Color::Blue;
//    } else {
//        lineColor = sf::Color::Black;
//    }
//
//    line[0].color = line[1].color = lineColor;
//
//    window->draw(line, 2, sf::Lines);
//    */
//
//}
LineShapeImpl::LineShapeImpl(const CircleShape& o1, const CircleShape& o2){
    Point o1Mid, o2Mid;
    o1Mid.x = o1.getMiddleX(); o1Mid.y = o1.getMiddleY();
    o2Mid.x = o2.getMiddleX(); o2Mid.y = o2.getMiddleY();
    n=(o1Mid-o2Mid)*2;
    c=o1Mid*o1Mid-o2Mid*o2Mid+o2.getR()*o2.getR()-o1.getR()*o1.getR();
}

//--------------------------------

double CircleShapeImpl::distFromPoint(const Point& v) const {
    return std::abs(dist (middle,v)-r);
}
//void CircleShapeImpl::draw(drawingClass* drawer) const{
//
//    sf::Color lineColor;
//    if (isCurrent) {
//        lineColor = sf::Color::Green;
//    } else if (isActive) {
//        lineColor = sf::Color::Blue;
//    } else {
//        lineColor = sf::Color::Black;
//    }
//    drawer->setColor (lineColor.r, lineColor.g, lineColor.b);
//    drawer->drawCircle (middle, r);
//    /*
//    sf::CircleShape shape (r, 400);
//    sf::Vector2f scaling;
//    scaling.x = box.width/visible.width;
//    scaling.y = box.height/visible.height;
//    shape.scale (scaling);
//    float alpha = (middle.x-visible.left)/visible.width;
//    float beta = (middle.y-visible.top)/visible.height;
//    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
//    v.x -= r*scaling.x;
//    v.y -= r*scaling.y;
//    shape.setPosition(v);
//    shape.setOutlineColor(sf::Color(0,0,0,255));
//    shape.setOutlineThickness(1/scaling.x);
//    shape.setFillColor(sf::Color(255,255,255,0));
//    //shape.setPointCount (400);
//    window->draw(shape);
//    */
//}
//void CircleShapeImpl::hull_draw(sf::RenderWindow* window, const sf::FloatRect& visible, const sf::FloatRect& box) const{
//    float scaling = box.width/visible.width;
//    sf::CircleShape shape (r*scaling-2, 400);
//    float alpha = (middle.x-visible.left)/visible.width;
//    float beta = (middle.y-visible.top)/visible.height;
//    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
//    v.x -= r*scaling-2;
//    v.y -= r*scaling-2;
//    shape.setPosition(v);
//    shape.setOutlineColor(sf::Color(0,0,0,128));
//    shape.setOutlineThickness(5);
//    shape.setFillColor(sf::Color(255,255,255,0));
//    //shape.setPointCount (400);
//    window->draw(shape);
//}
CircleShapeImpl::CircleShapeImpl(const Point& mid, double radius){
    middle=mid;
    r=radius;
}
CircleShapeImpl::CircleShapeImpl(const Point& mid, const Point& A){
    middle=mid;
    r = dist (mid, A);
}
CircleShapeImpl::CircleShapeImpl(double x, double y, double _r) {
    middle.x = x; middle.y = y;
    r = _r;
}
CircleShapeImpl::CircleShapeImpl(const Point& A, const Point& B, const Point& C){
    Point a = A-C, b=B-C;
    double aLen = length(a), bLen = length(b);
    r=aLen*bLen*length(a-b)/(2*(a%b));
    middle=b*(aLen*aLen)/(a%b)/2-a*(bLen*bLen/(a%b))/2;
    middle.x = middle.y+C.x; middle.y = -middle.x + C.y;
}
///////////////////////////////////////
double TriangleShapeImpl::distFromPoint(const Point& v) const {
    if(abs((v-A)%(B-A))+abs((v-B)%(C-B))+abs((v-C)%(A-C))<=(C-A)%(B-A)){
        return 0;
    } else {
        return 100;
    }
}
//void TriangleShapeImpl::draw(drawingClass* drawer) const{
//    drawer->setColor (255,0,0,125);
//    drawer->drawTriangle (A, B, C);
//    /*
//    sf::ConvexShape shape(3);
//    float alpha = (A.x-visible.left)/visible.width;
//    float beta = (A.y-visible.top)/visible.height;
//    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
//    shape.setPoint(0, v);
//    alpha = (B.x-visible.left)/visible.width;
//    beta = (B.y-visible.top)/visible.height;
//    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
//    shape.setPoint(1, v);
//    alpha = (C.x-visible.left)/visible.width;
//    beta = (C.y-visible.top)/visible.height;
//    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
//    shape.setPoint(2, v);
//    
//    shape.setFillColor(sf::Color(255,0,0,125));
//    window->draw(shape);
//    */
//}
//void TriangleShapeImpl::hull_draw(sf::RenderWindow* window, const sf::FloatRect& visible, const sf::FloatRect& box) const{
//    sf::ConvexShape shape(3);
//    float alpha = (A.x-visible.left)/visible.width;
//    float beta = (A.y-visible.top)/visible.height;
//    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
//    shape.setPoint(0, v);
//    alpha = (B.x-visible.left)/visible.width;
//    beta = (B.y-visible.top)/visible.height;
//    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
//    shape.setPoint(1, v);
//    alpha = (C.x-visible.left)/visible.width;
//    beta = (C.y-visible.top)/visible.height;
//    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
//    shape.setPoint(2, v);
//    
//    shape.setFillColor(sf::Color(0,255,255,40));
//    window->draw(shape);
//}
TriangleShapeImpl::TriangleShapeImpl(const Point& _a, const Point& _b, const Point& _c){
    A = _a;
    B = _b;
    C = _c;
}
TriangleShapeImpl::TriangleShapeImpl (double ax, double ay, double bx, double by, double cx, double cy){
    A.x = ax;
    A.y = ay;
    B.x = bx;
    B.y = by;
    C.x = cx;
    C.y = cy;
}
//helper outside functions

Point getPointLocation (const PointShape& ps) {
    Point p;
    p.x = ps.getX(); p.y = ps.getY();
    return p;
}

Point getSegmentFrom (const SegmentShape& seg) {
    Point p;
    p.x = seg.getFromX(); p.y = seg.getFromY();
    return p;
}

Point getSegmentTo (const SegmentShape& seg) {
    Point p;
    p.x = seg.getToX(); p.y = seg.getToY();
    return p;
}

Point getLineNormal (const LineShape& ls) {
    Point n;
    n.x = ls.getNormalX (); n.y = ls.getNormalY();
    return n;
}

Point getCircleCenter (const CircleShape& cs) {
    Point center;
    center.x = cs.getMiddleX(); center.y = cs.getMiddleY();
    return center;
}

Point getTrianglePointA (const TriangleShape& ts) {
    Point A;
    A.x = ts.getAX(); A.y = ts.getAY();
    return A;
}

Point getTrianglePointB (const TriangleShape& ts) {
    Point B;
    B.x = ts.getBX(); B.y = ts.getBY();
    return B;
}

Point getTrianglePointC (const TriangleShape& ts) {
    Point C;
    C.x = ts.getCX(); C.y = ts.getCY();
    return C;
}
