#include"geo.h"
#include<cmath>
#include<iostream>
using namespace std;
Point::Point(double x1=0, double y2=0){
	x=x1;
	y=y2;
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
	return ((*this/p)<0.01);
}
double Point::operator%(Point p){
	return x*p.y-y*p.x;
}
double Point::operator/(Point p){
	Point q=*this-p;
	return q.abs();
}
Point Point::operator*(double a){
	return Point(a*x,a*y);
}
Point::Point(Line l,Line m){
	if(l||m){

	} else if((m.c==0)&&(l.c==0)){
		x=0;
		y=0;
	} else {
		x=(l.c*m.b-m.c*m.a)/(-l.a*m.b+m.a*l.b);
		y=(-l.c*l.b+m.c*l.a)/(-l.a*m.b+m.a*l.b);
	}
}
//------------------------------------------------
Line::Line(double a1, double b1, double c1){
	a=a1;
	b=b1;
	c=c1;
}
bool Line::operator||(Line l){
	return abs(a*l.b-b*l.a)<=0.01;
}
Line::Line(Point p, Point q){
	if(p==q){

	} else {
		if(p==Point()){
			c=0;
			a=q.y;
			b=-q.x;
		} else if(q==Point()){
			c=0;
			a=p.y;
			b=-p.x;
		} else {
			c=-1;
			a=(q.y-p.y)/(p%q);
			b=(-q.x+p.x)/(p%q);
		}
	}
}
Line::Line(Segment AB){
	*this=Line(AB.p1,AB.p2);
}
Line Line::par(Point A){
	return Line(a,b,-a*A.x-b*A.y);
}
Line Line::ortho(Point A){
	return Line(-b,a,b*A.x-a*A.y);
}
Point Line::operator*(Line l){
	return Point(*this,l);
}
Line::Line(Circle o1, Circle o2){
	double S=o1.r*o1.r-o2.r*o2.r;
}
//----------------------------------------------
Triangle::Triangle(Point Q, Point P, Point R){
	A=Q;
	B=P;
	C=R;
}
Triangle::Triangle(Line p, Line q, Line r){
	A= p*q;
	B= q*r;
	C= p*r;
}
double Triangle::perimeter(){
	return (A/B)+(B/C)+(C/A);
}
double Triangle::area(){
	return abs((B-A)%(C-A));
}
bool Triangle::operator==(Triangle T){
	double a=B/C, b=C/A, c=B/A, a1=T.A/T.B, b1=T.B/T.C, c1=T.C/T.A;
	return ((a+b+c == a1+b1+c1) && (a*b+b*c+a*c==a1*b1+b1*c1+c1*a1) && (a*b*c==a1*b1*c1));
}
bool Triangle::operator!=(Triangle T){
	Triangle T2=homothety(Point(0,0),perimeter()/T.perimeter(),T);
	return *this==T2;
}

//----------------------------------------------
Segment::Segment(Point A, Point B){
	p1=A;
	p2=B;
}
double Segment::abs(){
	return (p1/p2);
}
//----------------------------------------------
Circle::Circle(Point o, double radius){
	middle=o;
	r=radius;
}
Circle::Circle(Point o, Point A){
	middle=o;
	r=A/o;
}
Circle::Circle(Point A, Point B, Point C){


}
//----------------------------------------------

//----------------------------------------------
Point Przedluzenie(Point A, Point B, double x){
	return (A+(B-A)*(x/(B/A)));
}
Point homothety(Point O, double x, Point A){
	return (A-O)*x+O;
}
Triangle homothety(Point O, double x, Triangle T){
	return Triangle(homothety(O,x,T.A), homothety(O,x,T.B),homothety(O,x,T.C));
}
