#include"geo.h"
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>
using namespace std;

//----------------------------------------
Point::Point(double x1, double y2){
	x=x1;
	y=y2;
}
double Point::dist(Point v){
    Point temp=*this-v;
    return temp.abs();
}
void Point::draw(sf::RenderWindow *window){
        sf::CircleShape shape(radiusOfDrawing);
        sf::Vector2f v(x-radiusOfDrawing,y-radiusOfDrawing);
        shape.setPosition(v);
        shape.setFillColor(sf::Color::Black);
        window->draw(shape);
}
string Point::what_is(){
    return "Point";
}
double Point::abs(){
	return sqrt(x*x+y*y);
}
Point Point::operator+(Point p){
	return Point(x+p.x,y+p.y);
}
Point Point::operator-(Point p){
	return Point(x-p.x,y-p.y);
}
double Point::operator*(Point p){
	return x*p.x+y*p.y;
}
bool Point::operator==(Point p){
	return ((dist(p))<0.01);
}
double Point::operator%(Point p){
	return x*p.y-y*p.x;
}
Point Point::operator*(double a){
	return Point(a*x,a*y);
}
Point Point::operator/(double a){
	return Point(x/a, y/a);
}
Point Point::zero(){
    return Point(0,0);
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
void Segment::draw(sf::RenderWindow* window){
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(p1.x, p1.y)),
        sf::Vertex(sf::Vector2f(p2.x, p2.y))
    };
    line[0].color=sf::Color(0,0,0);
    line[1].color=sf::Color(0,0,0);
    window->draw(line, 2, sf::Lines);
}
double Segment::dist(Point v){
    Point D=p2-p1;

    if((v-p1)*D<0){
        return v.dist(p1);
    }
    if((v-p2)*D>0){
        return v.dist(p2);
    }
    return std::abs(((v-p2)%D)/(p1.dist(p2)));
}
string Segment::what_is(){
    return "Segment";
}
//----------------------------------------------------
Line::Line(double a1, double b1, double c1){
    if((a1==0)&&(b1==0))
        throw std::invalid_argument("First two arguments can not be zero at the same time");
    Point n(a1,b1);
    c=c1;
}
Line::Line(Point p,Point q){
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
Line::Line(Segment s){
    *this=Line(s.p1,s.p2);
}
double Line::dist(Point v){


    return (n*v+c)/n.abs();
}
void Line::draw(sf::RenderWindow *window){
    double w = window->getSize().x, h = window->getSize().y;

    double  x1= -c/n.x,
            y1= -c/n.y,
            x2= -(c+n.y*h)/n.x,
            y2= -(c+n.x*w)/n.y;
    vector<sf::Vertex> v;
    if((x1>0)&&(x1<w)){
        v.push_back(sf::Vertex(sf::Vector2f(x1, 0)));
    }
    if((y1>=0)&&(y1<=h)){
        v.push_back(sf::Vertex(sf::Vector2f(0, y1)));
    }
    if((x2>0)&&(x2<w)){
        v.push_back(sf::Vertex(sf::Vector2f(x2, h)));
    }
    if((y2>=0)&&(y2<=h)){
        v.push_back(sf::Vertex(sf::Vector2f(w, y2)));
    }
    if(v.size()<2){
        return;
    }
    sf::Vertex line[] =
    {
        v[0],
        v[1]
    };
    line[0].color=sf::Color(0,0,0);
    line[1].color=sf::Color(0,0,0);
    window->draw(line, 2, sf::Lines);
}
string Line::what_is(){
    return "Line";
}
Line::Line(Circle o1, Circle o2){
    n=(o1.middle-o2.middle)*2;
    c=o1.middle*o1.middle-o2.middle*o2.middle+o2.r*o2.r-o1.r*o1.r;
}

//--------------------------------

double Circle::dist(Point v){
    return std::abs(middle.dist(v)-r);
}
void Circle::draw(sf::RenderWindow* window){
    sf::CircleShape shape(r);
    sf::Vector2f v(middle.x-r,middle.y-r);
    shape.setPosition(v);
    shape.setOutlineColor(sf::Color(0,0,0,255));
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color(255,255,255,0));
    window->draw(shape);
}
string Circle::what_is(){
    return "Circle";
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

Point Construction::lengthen(Point A, Point B, double a){
    double b = a/A.dist(B);
    return (B-A)*b+A;
}

Point Construction::middle(Point A, Point B){
    return (A+B)/2;
}
