#include"geo.h"
#include<cmath>
#include<iostream>
using namespace std;
Punkt::Punkt(double x1=0, double y2=0){
	x=x1;
	y=y2;
}
double Punkt::abs(){
	return sqrt(x*x+y*y);
}
Punkt Punkt::operator+(Punkt p){
	return Punkt(x+p.x,y+p.y);
}
Punkt Punkt::operator-(Punkt p){
	return Punkt(x-p.x,y-p.y);
}
double Punkt::operator*(Punkt p){
	return x*p.x+y*p.y;
}
bool Punkt::operator==(Punkt p){
	return ((*this/p)<0.01);
}
double Punkt::operator%(Punkt p){
	return x*p.y-y*p.x;
}
double Punkt::operator/(Punkt p){
	Punkt q=*this-p;
	return q.abs();
}
Punkt Punkt::operator*(double a){
	return Punkt(a*x,a*y);
}
Punkt::Punkt(Prosta l,Prosta m){
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
Prosta::Prosta(double a1, double b1, double c1){
	a=a1;
	b=b1;
	c=c1;
}
bool Prosta::operator||(Prosta l){
	return abs(a*l.b-b*l.a)<=0.01;
}
Prosta::Prosta(Punkt p, Punkt q){
	if(p==q){

	} else {
		if(p==Punkt()){
			cout<<"a";
			c=0;
			a=q.y;
			b=-q.x;
		} else if(q==Punkt()){
			cout<<"b";
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
Prosta::Prosta(Odcinek AB){
	*this=Prosta(AB.p1,AB.p2);
}
Prosta Prosta::par(Punkt A){
	return Prosta(a,b,-a*A.x-b*A.y);
}
Prosta Prosta::orto(Punkt A){
	return Prosta(-b,a,b*A.x-a*A.y);
}
Punkt Prosta::operator*(Prosta l){
	return Punkt(*this,l);
}
Prosta::Prosta(Okrag o1, Okrag o2){
	double S=o1.r*o1.r-o2.r*o2.r;
}
//----------------------------------------------
Trojkat::Trojkat(Punkt Q, Punkt P, Punkt R){
	A=Q;
	B=P;
	C=R;
}
Trojkat::Trojkat(Prosta p, Prosta q, Prosta r){
	A= p*q;
	B= q*r;
	C= p*r;
}
double Trojkat::obwod(){
	return (A/B)+(B/C)+(C/A);
}
double Trojkat::pole(){
	return abs((B-A)%(C-A));
}
bool Trojkat::operator==(Trojkat T){
	double a=B/C, b=C/A, c=B/A, a1=T.A/T.B, b1=T.B/T.C, c1=T.C/T.A;
	return ((a+b+c == a1+b1+c1) && (a*b+b*c+a*c==a1*b1+b1*c1+c1*a1) && (a*b*c==a1*b1*c1));
}
bool Trojkat::operator!=(Trojkat T){
	Trojkat T2=jednokladnosc(Punkt(0,0),obwod()/T.obwod(),T);
	return *this==T2;
}

//----------------------------------------------
Odcinek::Odcinek(Punkt A, Punkt B){
	p1=A;
	p2=B;
}
double Odcinek::abs(){
	return (p1/p2);
}
//----------------------------------------------
Okrag::Okrag(Punkt o, double promien){
	srodek=o;
	r=promien;
}
Okrag::Okrag(Punkt o, Punkt A){
	srodek=o;
	r=A/o;
}
Okrag::Okrag(Punkt A, Punkt B, Punkt C){
	

}

//----------------------------------------------
Punkt Przedluzenie(Punkt A, Punkt B, double x){
	return (A+(B-A)*(x/(B/A)));
}
Punkt jednokladnosc(Punkt O, double x, Punkt A){
	return (A-O)*x+O;
}
Trojkat jednokladnosc(Punkt O, double x, Trojkat T){
	return Trojkat(jednokladnosc(O,x,T.A), jednokladnosc(O,x,T.B),jednokladnosc(O,x,T.C));
}

