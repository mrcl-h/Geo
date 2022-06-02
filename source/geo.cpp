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
Point::Point(double x1, double y2){
	x=x1;
	y=y2;
}
const double Point::dist(Point v) const {
    Point temp=*this-v;
    return temp.abs();
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

void Point::draw(sf::RenderWindow *window, sf::FloatRect visible, sf::FloatRect box) const{
    sf::CircleShape shape (radiusOfDrawing);
    float alpha = (x-visible.left)/visible.width;
    float beta = (y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= radiusOfDrawing;
    v.y -= radiusOfDrawing;
    shape.setPosition(v);
    shape.setFillColor (getShapeColor (isActive, isCurrent, isDependent));
    window->draw(shape);
}
void Point::hull_draw(sf::RenderWindow *window, sf::FloatRect visible, sf::FloatRect box) const{

    sf::CircleShape shape (2*radiusOfDrawing);
    float alpha = (x-visible.left)/visible.width;
    float beta = (y-visible.top)/visible.height;
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
Point::Point(Line l,Line m){
	/*if(l||m){

	} else*/ if((m.c==0)&&(l.c==0)){
		x=0;
		y=0;
	} else {
		x=(l.c*m.n.y-m.c*l.n.y)/(m.n%l.n);
		y=(-l.c*m.n.x+m.c*l.n.x)/(m.n*l.n);
	}
}

//----------------------------------------------

Segment::Segment(Point A, Point B){
    p1=A;
    p1=B;
}
void Segment::draw(sf::RenderWindow* window, sf::FloatRect visible, sf::FloatRect box) const{
    //float alpha = (x-visible.left)/visible.width;
    //float beta = (y-visible.top)/visible.height;
    //sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    //v.x -= radiusOfDrawing;
    //v.y -= radiusOfDrawing;
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
const double Segment::dist(Point v) const{
    Point D=p2-p1;

    if((v-p1)*D<0){
        return v.dist(p1);
    }
    if((v-p2)*D>0){
        return v.dist(p2);
    }
    return std::abs(((v-p2)%D)/(p1.dist(p2)));
}
//----------------------------------------------------
Line::Line(double a1, double b1, double c1){
    if((a1==0)&&(b1==0))
        throw std::invalid_argument("First two arguments can not be zero at the same time");
    n.x = a1; n.y = b1;
    //Point n(a1, b1);
    c=c1;
}
Line::Line(Point p,Point q){
    goThroughPoints (p,q);
}
Line::Line(Segment s){
    *this=Line(s.p1,s.p2);
}
const double Line::dist(Point v) const{
    return doubleAbs((n*v+c)/n.abs());
}
void Line::draw(sf::RenderWindow *window, sf::FloatRect visible, sf::FloatRect box) const{


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
Line::Line(Circle o1, Circle o2){
    n=(o1.middle-o2.middle)*2;
    c=o1.middle*o1.middle-o2.middle*o2.middle+o2.r*o2.r-o1.r*o1.r;
}

//--------------------------------

const double Circle::dist(Point v) const {
    return std::abs(middle.dist(v)-r);
}
void Circle::draw(sf::RenderWindow* window, sf::FloatRect visible, sf::FloatRect box) const{
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
void Circle::hull_draw(sf::RenderWindow* window, sf::FloatRect visible, sf::FloatRect box) const{
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
Circle::Circle(Point mid, double radius){
    middle=mid;
    r=radius;
}
Circle::Circle(Point mid, Point A){
    middle=mid;
    r=mid.dist(A);
}
Circle::Circle(Point A, Point B, Point C){
    Point a = A-C, b=B-C;
    r=a.abs()*b.abs()*(a-b).abs()/(2*(a%b));
    middle=b*(a.abs()*a.abs())/(a%b)/2-a*(b.abs()*b.abs()/(a%b))/2;
    middle= Point(middle.y,-middle.x);
    middle=middle+C;
}
