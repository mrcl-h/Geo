#include"geo.h"
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

void resetConstructionElements (constructionElements& el) {
    el.points.clear();
    el.lines.clear();
    el.circles.clear();
    el.segments.clear();
}

void resetUiOptionConditions (uiOptionConditions& op) {
    op.lineCount = op.pointCount = op.circleCount = op.segmentCount = 0;
}

//----------------------------------------
PointShape::PointShape(double x1, double y2){
	coordinates.x=x1;
	coordinates.y=y2;
}
const double PointShape::distFromPoint(const Point& v) const {
    Point temp=coordinates-v;
    return length(temp); 
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

void PointShape::draw(sf::RenderWindow *window, sf::FloatRect visible, sf::FloatRect box) const{
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
void PointShape::hull_draw(sf::RenderWindow *window, sf::FloatRect visible, sf::FloatRect box) const{

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
std::ostream& operator<<(std::ostream& os, const Point& obj){
        return os <<"("<<obj.x<<", "<<obj.y<<")";
}
PointShape::PointShape(const LineShape& l,const LineShape& m){

	 //if((m.c==0)&&(l.c==0)){
    if (m.getC()==0 && l.getC() == 0) {
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

SegmentShape::SegmentShape(Point A, Point B){
    p1=A;
    p1=B;
}
void SegmentShape::draw(sf::RenderWindow* window, sf::FloatRect visible, sf::FloatRect box) const{
    //float alpha = (x-visible.left)/visible.width;
    //float beta = (y-visible.top)/visible.height;
    //sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    //v.x -= radiusOfDrawing;
    //v.y -= radiusOfDrawing;
    //float tp1x = box.left + (p1.getX()-visible.left)/visible.width*box.width;
    float tp1x = box.left + (p1.x-visible.left)/visible.width*box.width;
    //float tp2x = box.left + (p2.getX()-visible.left)/visible.width*box.width;
    float tp2x = box.left + (p2.x-visible.left)/visible.width*box.width;

    //float tp1y = box.top + (p1.getY()-visible.top)/visible.height*box.height;
    float tp1y = box.top + (p1.y-visible.top)/visible.height*box.height;
    //float tp2y = box.top + (p2.getY()-visible.top)/visible.height*box.height;
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
const double SegmentShape::distFromPoint(const Point& v) const{
    Point D=p2-p1;

    if((v-p1)*D<0){
        return dist (v, p1);
    }
    if((v-p2)*D>0){
        return dist (v, p2);
    }
    return std::abs(((v-p2)%D)/(dist(p1,p2)));
}
//----------------------------------------------------
LineShape::LineShape(double a1, double b1, double c1){
    if((a1==0)&&(b1==0))
        throw std::invalid_argument("First two arguments can not be zero at the same time");
    //n.setX (a1); n.setY (b1);
    n.x = a1; n.y = b1;
    //Point n(a1, b1);
    c=c1;
}
LineShape::LineShape(const Point& p,const Point& q){
    goThroughPoints (p,q);
}
LineShape::LineShape(const SegmentShape& s){
    //*this=Line(s.p1,s.p2);
    Point p1, p2;
    p1.x = s.getFromX(); p1.y = s.getFromY();
    p2.x = s.getToX(); p2.y = s.getToY();
    goThroughPoints (p1, p2);
}
const double LineShape::distFromPoint(const Point& v) const{
    return doubleAbs((n*v+c)/length(n));
}
void LineShape::draw(sf::RenderWindow *window, sf::FloatRect visible, sf::FloatRect box) const{


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
    //sf::Color lineColor = getShapeColor (isActive, isCurrent, isDependent);
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

const double CircleShape::distFromPoint(const Point& v) const {
    return std::abs(dist (middle,v)-r);
}
void CircleShape::draw(sf::RenderWindow* window, sf::FloatRect visible, sf::FloatRect box) const{
    sf::CircleShape shape (r);
    float alpha = (middle.x-visible.left)/visible.width;
    float beta = (middle.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= r;
    v.y -= r;
    shape.setPosition(v);
    //shape.setFillColor (getShapeColor (isActive, isCurrent, isDependent));
    shape.setOutlineColor(sf::Color(0,0,0,255));
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color(255,255,255,0));
    shape.setPointCount (400);
    window->draw(shape);
}
void CircleShape::hull_draw(sf::RenderWindow* window, sf::FloatRect visible, sf::FloatRect box) const{
    sf::CircleShape shape (r-2);
    float alpha = (middle.x-visible.left)/visible.width;
    float beta = (middle.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= r-2;
    v.y -= r-2;
    shape.setPosition(v);
    //shape.setFillColor (getShapeColor (isActive, isCurrent, isDependent));
    shape.setOutlineColor(sf::Color(0,0,0,128));
    shape.setOutlineThickness(5);
    shape.setFillColor(sf::Color(255,255,255,0));
    shape.setPointCount (400);
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
const double dist(const Point &p1, const Point &p2) {
  double diffX = p1.x - p2.x;
  double diffY = p1.y - p2.y;
  return sqrt(diffX * diffX + diffY * diffY);
}
const double dist (double x1, double y1, double x2, double y2) {
  double diffX = x1 - x2;
  double diffY = y1 - y2;
  return sqrt(diffX * diffX + diffY * diffY);
}
const double length(const Point &p) {
  return sqrt(p.x * p.x + p.y * p.y);
}

//Point::Point (double _x, double _y) :x(_x), y(_y) {}

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
const double operator*(const Point &p1, const Point &p2) {
  return p1.x * p2.x + p1.y * p2.y;
}
const double operator%(const Point &p1, const Point &p2) {
  return p1.x * p2.y - p1.y * p2.x;
}
const bool operator==(const Point &p1, const Point &p2) {
  return dist(p1, p2) < 0.01;
}
const double abs(const Point &p) { return sqrt(p.x * p.x + p.y * p.y); }
