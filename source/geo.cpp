#include"geo.h"
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

//void resetConstructionElements (constructionElements& el) {
//    el.points.clear();
//    el.lines.clear();
//    el.circles.clear();
//    el.segments.clear();
//}

void resetUiOptionConditions (uiOptionConditions& op) {
    op.lineCount = op.pointCount = op.circleCount = op.segmentCount = 0;
}

//----------------------------------------
double dist(const Point &p1, const Point &p2) {
  double diffX = p1.x - p2.x;
  double diffY = p1.y - p2.y;
  return sqrt(diffX * diffX + diffY * diffY);
}
double dist (double x1, double y1, double x2, double y2) {
  double diffX = x1 - x2;
  double diffY = y1 - y2;
  return sqrt(diffX * diffX + diffY * diffY);
}
double length(const Point &p) {
  return sqrt(p.x * p.x + p.y * p.y);
}


const Point operator+(const Point &p1, const Point &p2) {
  Point sum;
  sum.x = p1.x + p2.x;
  sum.y = p1.y + p2.y;
  return sum;
}
const Point operator-(const Point &p1, const Point &p2) {
  Point difference;
  difference.x = p1.x - p2.x;
  difference.y = p1.y - p2.y;
  return difference;
}
const Point operator*(const Point &p, double a) {
  Point product = p;
  product.x *= a;
  product.y *= a;
  return product;
}
const Point operator*(double a, const Point &p) {
  Point product = p;
  product.x *= a;
  product.y *= a;
  return product;
}
const Point operator/(const Point &p, double a) {
  Point quotient = p;
  quotient.x /= a;
  quotient.y /= a;
  return quotient;
}
double operator*(const Point &p1, const Point &p2) {
  return p1.x * p2.x + p1.y * p2.y;
}
double operator%(const Point &p1, const Point &p2) {
  return p1.x * p2.y - p1.y * p2.x;
}
bool operator==(const Point &p1, const Point &p2) {
  return dist(p1, p2) < 0.01;
}

void PointShape::setExistance (bool ex) {exists = ex;}
bool PointShape::getExistance () const {return exists;}
void PointShape::setActivity (bool ac) {isActive = ac;}
bool PointShape::getActivity () const {return isActive;}
void PointShape::setCurrent (bool cu) {isCurrent = cu;}
bool PointShape::getCurrent () const {return isCurrent;}
void PointShape::setDependent (bool de) {isDependent = de;}
bool PointShape::getDependent () const {return isDependent;}
double PointShape::getX () const {return coordinates.x;}
double PointShape::getY () const {return coordinates.y;}

void PointShape::setX (double newX) {coordinates.x = newX;}
void PointShape::setY (double newY) {coordinates.y = newY;}

void SegmentShape::setExistance (bool ex) {exists = ex;}
bool SegmentShape::getExistance () const {return exists;}
void SegmentShape::setActivity (bool ac) {isActive = ac;}
bool SegmentShape::getActivity () const {return isActive;}
void SegmentShape::setCurrent (bool cu) {isCurrent = cu;}
bool SegmentShape::getCurrent () const {return isCurrent;}
void SegmentShape::setDependent (bool de) {isDependent = de;}
bool SegmentShape::getDependent () const {return isDependent;}

double SegmentShape::getFromX () const {return p1.x;}
double SegmentShape::getToX () const {return p2.x;}
double SegmentShape::getFromY () const {return p1.y;}
double SegmentShape::getToY () const {return p2.y;}

void SegmentShape::setFromX (double newX) {p1.x = newX;}
void SegmentShape::setToX (double newX) {p2.x = newX;}
void SegmentShape::setFromY (double newY) {p1.y = newY;}
void SegmentShape::setToY (double newY) {p2.y = newY;}

void LineShape::setExistance (bool ex) {exists = ex;}
bool LineShape::getExistance () const {return exists;}
void LineShape::setActivity (bool ac) {isActive = ac;}
bool LineShape::getActivity () const {return isActive;}
void LineShape::setCurrent (bool cu) {isCurrent = cu;}
bool LineShape::getCurrent () const {return isCurrent;}
void LineShape::setDependent (bool de) {isDependent = de;}
bool LineShape::getDependent () const {return isDependent;}

double LineShape::getNormalX () const {return n.x;}
double LineShape::getNormalY () const {return n.y;}
double LineShape::getC () const {return c;}

void LineShape::setNormalX (double x) {n.x = x;}
void LineShape::setNormalY (double y) {n.y = y;}
void LineShape::setC (double _c) {c = _c;}

void CircleShape::setExistance (bool ex) {exists = ex;}
bool CircleShape::getExistance () const {return exists;}
void CircleShape::setActivity (bool ac) {isActive = ac;}
bool CircleShape::getActivity () const {return isActive;}
void CircleShape::setCurrent (bool cu) {isCurrent = cu;}
bool CircleShape::getCurrent () const {return isCurrent;}
void CircleShape::setDependent (bool de) {isDependent = de;}
bool CircleShape::getDependent () const {return isDependent;}

double CircleShape::getMiddleX () const {return middle.x;}
double CircleShape::getMiddleY () const {return middle.y;}
double CircleShape::getR () const {return r;}

void CircleShape::setMiddleX (double x) {middle.x = x;}
void CircleShape::setMiddleY (double y) {middle.y = y;}
void CircleShape::setR (double _r) {r = _r;}

void TriangleShape::setExistance (bool ex) {exists = ex;}
bool TriangleShape::getExistance () const {return exists;}
void TriangleShape::setActivity (bool ac) {isActive = ac;}
bool TriangleShape::getActivity () const {return isActive;}
void TriangleShape::setCurrent (bool cu) {isCurrent = cu;}
bool TriangleShape::getCurrent () const {return isCurrent;}
void TriangleShape::setDependent (bool de) {isDependent = de;}
bool TriangleShape::getDependent () const {return isDependent;}

void TriangleShape::setAX (double x) {A.x=x;}
void TriangleShape::setAY (double y) {A.y=y;}
void TriangleShape::setBX (double x) {B.x=x;}
void TriangleShape::setBY (double y) {B.y=y;}
void TriangleShape::setCX (double x) {C.x=x;}
void TriangleShape::setCY (double y) {C.y=y;}

double TriangleShape::getAX () const {return A.x;}
double TriangleShape::getAY () const {return A.y;}
double TriangleShape::getBX () const {return B.x;}
double TriangleShape::getBY () const {return B.y;}
double TriangleShape::getCX () const {return C.x;}
double TriangleShape::getCY () const {return C.y;}

PointShape* makePointShape (double x, double y) {
    return new PointShape (x, y);
}
PointShape* makePointShape (const LineShape& l1, const LineShape& l2) {
    return new PointShape (l1, l2);
}

SegmentShape* makeSegmentShape () {
    return new SegmentShape;
}
SegmentShape* makeSegmentShape (const Point& p1, const Point& p2) {
    return new SegmentShape (p1, p2);
}

LineShape* makeLineShape (double a, double b, double c) {
    return new LineShape (a,b,c);
}
LineShape* makeLineShape (const SegmentShape& s) {
    return new LineShape (s); 
}
LineShape* makeLineShape (const Point& l, const Point& r) {
    return new LineShape (l, r);
}
CircleShape* makeCircleShape (const Point& p, double r) {
    return new CircleShape (p, r);
}
CircleShape* makeCircleShape (const Point& p, const Point& r) {
    return new CircleShape (p, r);
}
CircleShape* makeCircleShape (double x, double y, double r) {
    return new CircleShape (x, y, r);
}
CircleShape* makeCircleShape (const Point& a, const Point& b, const Point& c) {
    return new CircleShape (a,b,c);
}
TriangleShape* makeTriangleShape (const Point& p1, const Point& p2, const Point& p3){
    return new TriangleShape(p1, p2, p3);
}
TriangleShape* makeTriangleShape (double ax, double ay, double bx, double by, double cx, double cy){
    return new TriangleShape(ax, ay, bx, by, cx, cy);
}

double PointShape::abs() const {
    return std::sqrt (coordinates.x*coordinates.x+coordinates.y*coordinates.y);
}
void PointShape::addToConstructionElements (constructionElements& el) {
    //el.points.push_back(this);
    el.getVector<PointShape*>().push_back(this);
}
void PointShape::removeFromConstructionElements (constructionElements& el) {
    //el.points.erase (std::find (el.points.begin(), el.points.end(), static_cast<Shape*>(this)));
    el.getVector<PointShape*>().erase (std::find (el.getVector<PointShape*>().begin(), el.getVector<PointShape*>().end(), static_cast<Shape*>(this)));
}
void PointShape::addToCurrentConditions (uiOptionConditions& op, int c) {
    op.pointCount += c;
}
bool PointShape::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}

unsigned int PointShape::getHitPriority () {return 10;}

void PointShape::moveShape (double xMov, double yMov) {
    if (isDependent) return;
    coordinates.x += xMov; 
    coordinates.y += yMov;
}

void SegmentShape::addToConstructionElements (constructionElements& el) {
    //el.segments.push_back(this);
    el.getVector<SegmentShape*>().push_back(this);
}
void SegmentShape::removeFromConstructionElements (constructionElements& el) {
    //el.segments.erase (std::find (el.segments.begin(), el.segments.end(), static_cast<Shape*>(this)));
    el.getVector<SegmentShape*>().erase (std::find (el.getVector<SegmentShape*>().begin(), el.getVector<SegmentShape*>().end(), static_cast<Shape*>(this)));
}
void SegmentShape::addToCurrentConditions (uiOptionConditions& op, int c) {
    op.segmentCount += c;
}
bool SegmentShape::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}
unsigned int SegmentShape::getHitPriority () {return 8;}

void LineShape::goThroughPoints (const Point& p, const Point& q) {
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

void LineShape::goThroughPoints (const double px, const double py, const double qx, const double qy) {
    Point p, q;
    p.x = px; p.y = py;
    q.x = qx; q.y = qy;
    goThroughPoints (p, q);
}

void LineShape::addToConstructionElements (constructionElements& el) {
    //el.lines.push_back(this);
    el.getVector<LineShape*>().push_back(this);
}
void LineShape::removeFromConstructionElements (constructionElements& el) {
    //el.lines.erase (std::find (el.lines.begin(), el.lines.end(), static_cast<Shape*>(this)));
    el.getVector<LineShape*>().erase (std::find (el.getVector<LineShape*>().begin(), el.getVector<LineShape*>().end(), static_cast<Shape*>(this)));
}
void LineShape::addToCurrentConditions (uiOptionConditions& op, int m) {
    op.lineCount += m;
}
bool LineShape::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}

unsigned int LineShape::getHitPriority () {return 6;}

void CircleShape::addToConstructionElements (constructionElements& el) {
    //el.circles.push_back(this);
    el.getVector<CircleShape*>().push_back(this);
}
void CircleShape::removeFromConstructionElements (constructionElements& el) {
    //el.circles.erase (std::find (el.circles.begin(), el.circles.end(), static_cast<Shape*>(this)));
    el.getVector<CircleShape*>().erase (std::find (el.getVector<CircleShape*>().begin(), el.getVector<CircleShape*>().end(), static_cast<Shape*>(this)));
}
void CircleShape::addToCurrentConditions (uiOptionConditions& op, int c) {
    op.circleCount += c;
}
bool CircleShape::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}
unsigned int CircleShape::getHitPriority () {return 4;}

PointShape::PointShape(double x1, double y2){
	coordinates.x=x1;
	coordinates.y=y2;
}
double PointShape::distFromPoint(const Point& v) const {
    Point temp=coordinates-v;
    return length(temp); 
}



void TriangleShape::addToConstructionElements (constructionElements& el) {
    el.getVector<TriangleShape*>().push_back(this);
}
void TriangleShape::removeFromConstructionElements (constructionElements& el) {
    //el.circles.erase (std::find (el.circles.begin(), el.circles.end(), static_cast<Shape*>(this)));
    el.getVector<TriangleShape*>().erase (std::find (el.getVector<TriangleShape*>().begin(), el.getVector<TriangleShape*>().end(), static_cast<Shape*>(this)));
}
void TriangleShape::addToCurrentConditions (uiOptionConditions& op, int c) {
    op.triangleCount += c;
}
bool TriangleShape::isHit (const Point& p) {
    return distFromPoint(p) < hitEpsilon;
}
unsigned int TriangleShape::getHitPriority () {return 5;}


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

void PointShape::draw(sf::RenderWindow *window, const sf::FloatRect& visible, const sf::FloatRect& box) const{
    sf::CircleShape shape (radiusOfDrawing);
    float alpha = (coordinates.x-visible.left)/visible.width;
    float beta = (coordinates.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= radiusOfDrawing;
    v.y -= radiusOfDrawing;
    shape.setPosition(v);
    shape.setFillColor (getShapeColor (isActive, isCurrent, isDependent));
    window->draw(shape);
}
void PointShape::hull_draw(sf::RenderWindow *window, const sf::FloatRect& visible, const sf::FloatRect& box) const{

    sf::CircleShape shape (2*radiusOfDrawing);
    float alpha = (coordinates.x-visible.left)/visible.width;
    float beta = (coordinates.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= 2*radiusOfDrawing;
    v.y -= 2*radiusOfDrawing;
    shape.setPosition(v);
    shape.setFillColor(sf::Color(0,0,0,100));

    window->draw(shape);
}
PointShape::PointShape(const LineShape& l,const LineShape& m){

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

SegmentShape::SegmentShape(const Point& A, const Point& B){
    p1=A;
    p1=B;
}
void SegmentShape::draw(sf::RenderWindow* window, const sf::FloatRect& visible, const sf::FloatRect& box) const{
    float tp1x = box.left + (p1.x-visible.left)/visible.width*box.width;
    float tp2x = box.left + (p2.x-visible.left)/visible.width*box.width;

    float tp1y = box.top + (p1.y-visible.top)/visible.height*box.height;
    float tp2y = box.top + (p2.y-visible.top)/visible.height*box.height;
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(tp1x, tp1y)),
        sf::Vertex(sf::Vector2f(tp2x, tp2y))
    };
    line[0].color=sf::Color(0,0,0);
    line[1].color=sf::Color(0,0,0);
    window->draw(line, 2, sf::Lines);
}
double SegmentShape::distFromPoint(const Point& v) const{
    Point D=p2-p1;

    if((v-p1)*D<0){
        return dist (v, p1);
    }
    if((v-p2)*D>0){
        return dist (v, p2);
    }
    return std::abs(((v-p2)%D)/(dist(p1,p2)));
}
double SegmentShape::abs() const {
    return dist (p1, p2);
}
//----------------------------------------------------
LineShape::LineShape(double a1, double b1, double c1){
    if(a1 < 1 && a1 > -1 && b1 < 1 && b1 > -1)
        throw std::invalid_argument("First two arguments can not be zero at the same time");
    n.x = a1; n.y = b1;
    c=c1;
}
LineShape::LineShape(const Point& p,const Point& q){
    goThroughPoints (p,q);
}
LineShape::LineShape(const SegmentShape& s){
    Point p1, p2;
    p1.x = s.getFromX(); p1.y = s.getFromY();
    p2.x = s.getToX(); p2.y = s.getToY();
    goThroughPoints (p1, p2);
}

double LineShape::distFromPoint(const Point& v) const{
    return doubleAbs((n*v+c)/length(n));
}
void LineShape::draw(sf::RenderWindow *window, const sf::FloatRect& visible, const sf::FloatRect& box) const{


    sf::Vector2f from;
    sf::Vector2f to;

    unsigned int cond1 = (n.y+n.x)>=0;
    unsigned int cond2 = (n.y-n.x)<0;
    if (cond1^cond2) { //draw horizontally
        from.x = (box.left);
        from.y = box.top+box.height/visible.height*((-c-n.x*visible.left)/n.y-visible.top);


        to.x = (box.left+box.width);
        to.y = box.top+box.height/visible.height*((-c-n.x*(visible.left+visible.width))/n.y-visible.top);
    } else { //draw vertically
        from.y = (box.top);
        from.x = box.left+box.width/visible.width*((-c-n.y*visible.top)/n.x-visible.left);

        to.y = (box.top+box.height);
        to.x = box.left+box.width/visible.width*((-c-n.y*(visible.top+visible.height))/n.x-visible.left);
    }
    sf::Vertex line[] = { from, to };
    sf::Color lineColor;
    if (isCurrent) {
        lineColor = sf::Color::Green;
    } else if (isActive) {
        lineColor = sf::Color::Blue;
    } else {
        lineColor = sf::Color::Black;
    }

    line[0].color = line[1].color = lineColor;

    window->draw(line, 2, sf::Lines);

}
LineShape::LineShape(const CircleShape& o1, const CircleShape& o2){
    Point o1Mid, o2Mid;
    o1Mid.x = o1.getMiddleX(); o1Mid.y = o1.getMiddleY();
    o2Mid.x = o2.getMiddleX(); o2Mid.y = o2.getMiddleY();
    n=(o1Mid-o2Mid)*2;
    c=o1Mid*o1Mid-o2Mid*o2Mid+o2.getR()*o2.getR()-o1.getR()*o1.getR();
}

//--------------------------------

double CircleShape::distFromPoint(const Point& v) const {
    return std::abs(dist (middle,v)-r);
}
void CircleShape::draw(sf::RenderWindow* window, const sf::FloatRect& visible, const sf::FloatRect& box) const{
    // i hope this works.
    sf::CircleShape shape (r, 400);
    sf::Vector2f scaling;
    scaling.x = box.width/visible.width;
    scaling.y = box.height/visible.height;
    shape.scale (scaling);
    float alpha = (middle.x-visible.left)/visible.width;
    float beta = (middle.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= r*scaling.x;
    v.y -= r*scaling.y;
    shape.setPosition(v);
    shape.setOutlineColor(sf::Color(0,0,0,255));
    shape.setOutlineThickness(1/scaling.x);
    shape.setFillColor(sf::Color(255,255,255,0));
    //shape.setPointCount (400);
    window->draw(shape);
}
void CircleShape::hull_draw(sf::RenderWindow* window, const sf::FloatRect& visible, const sf::FloatRect& box) const{
    float scaling = box.width/visible.width;
    sf::CircleShape shape (r*scaling-2, 400);
    float alpha = (middle.x-visible.left)/visible.width;
    float beta = (middle.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= r*scaling-2;
    v.y -= r*scaling-2;
    shape.setPosition(v);
    shape.setOutlineColor(sf::Color(0,0,0,128));
    shape.setOutlineThickness(5);
    shape.setFillColor(sf::Color(255,255,255,0));
    //shape.setPointCount (400);
    window->draw(shape);
}
CircleShape::CircleShape(const Point& mid, double radius){
    middle=mid;
    r=radius;
}
CircleShape::CircleShape(const Point& mid, const Point& A){
    middle=mid;
    r = dist (mid, A);
}
CircleShape::CircleShape(double x, double y, double _r) {
    middle.x = x; middle.y = y;
    r = _r;
}
CircleShape::CircleShape(const Point& A, const Point& B, const Point& C){
    Point a = A-C, b=B-C;
    double aLen = length(a), bLen = length(b);
    r=aLen*bLen*length(a-b)/(2*(a%b));
    middle=b*(aLen*aLen)/(a%b)/2-a*(bLen*bLen/(a%b))/2;
    middle.x = middle.y+C.x; middle.y = -middle.x + C.y;
}
///////////////////////////////////////
double TriangleShape::distFromPoint(const Point& v) const {
    if(std::abs((v-A)%(B-A))+std::abs((v-B)%(C-B))+std::abs((v-C)%(A-C))<=(C-A)%(B-A)){
        return 0;
    } else {
        return 100;
    }
}
void TriangleShape::draw(sf::RenderWindow* window, const sf::FloatRect& visible, const sf::FloatRect& box) const{
    sf::ConvexShape shape(3);
    float alpha = (A.x-visible.left)/visible.width;
    float beta = (A.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    shape.setPoint(0, v);
    alpha = (B.x-visible.left)/visible.width;
    beta = (B.y-visible.top)/visible.height;
    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
    shape.setPoint(1, v);
    alpha = (C.x-visible.left)/visible.width;
    beta = (C.y-visible.top)/visible.height;
    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
    shape.setPoint(2, v);
    
    shape.setFillColor(sf::Color(255,0,0,125));
    window->draw(shape);
}
void TriangleShape::hull_draw(sf::RenderWindow* window, const sf::FloatRect& visible, const sf::FloatRect& box) const{
    sf::ConvexShape shape(3);
    float alpha = (A.x-visible.left)/visible.width;
    float beta = (A.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    shape.setPoint(0, v);
    alpha = (B.x-visible.left)/visible.width;
    beta = (B.y-visible.top)/visible.height;
    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
    shape.setPoint(1, v);
    alpha = (C.x-visible.left)/visible.width;
    beta = (C.y-visible.top)/visible.height;
    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
    shape.setPoint(2, v);
    
    shape.setFillColor(sf::Color(0,255,255,40));
    window->draw(shape);
}
TriangleShape::TriangleShape(const Point& _a, const Point& _b, const Point& _c){
    A = _a;
    B = _b;
    C = _c;
}
TriangleShape::TriangleShape (double ax, double ay, double bx, double by, double cx, double cy){
    A.x = ax;
    A.y = ay;
    B.x = bx;
    B.y = by;
    C.x = cx;
    C.y = cy;
}
//helper outside functions

Point getPointLocation (PointShape& ps) {
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

Point getCircleCenter (CircleShape& cs) {
    Point center;
    center.x = cs.getMiddleX(); center.y = cs.getMiddleY();
    return center;
}
