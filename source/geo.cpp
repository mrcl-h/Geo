#include"geo.h"
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

//----------------------------------------
Point::Point(double x1, double y2){
	x=x1;
	y=y2;
}
double Point::dist(Point v){
    Point temp=*this-v;
    return temp.abs();
}
void Point::draw(sf::RenderWindow *window, sf::FloatRect visible, sf::FloatRect box){
        //sf::CircleShape shape(radiusOfDrawing);
        //sf::Vector2f v(x-radiusOfDrawing,y-radiusOfDrawing);
        //shape.setPosition(v);
        //shape.setFillColor(sf::Color::Black);
        //window->draw(shape);
    sf::CircleShape shape (radiusOfDrawing);
    float alpha = (x-visible.left)/visible.width;
    float beta = (y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= radiusOfDrawing;
    v.y -= radiusOfDrawing;
    shape.setPosition(v);
    if (isActive) {
        shape.setFillColor(sf::Color::Blue);
    } else {
        shape.setFillColor(sf::Color::Black);
    }
    window->draw(shape);
}
std::string Point::what_is(){
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
void Segment::draw(sf::RenderWindow* window, sf::FloatRect visible, sf::FloatRect box){
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
std::string Segment::what_is(){
    return "Segment";
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
    return doubleAbs((n*v+c)/n.abs());
}
void Line::draw(sf::RenderWindow *window, sf::FloatRect visible, sf::FloatRect box){


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
    if (isActive) {
        line[0].color=sf::Color::Blue;
        line[1].color=sf::Color::Blue;
    } else {
        line[0].color=sf::Color(0,0,0);
        line[1].color=sf::Color(0,0,0);
    }
    window->draw(line, 2, sf::Lines);

    //double w = window->getSize().x, h = window->getSize().y;

    //double  x1= -c/n.x,
    //        y1= -c/n.y,
    //        x2= -(c+n.y*h)/n.x,
    //        y2= -(c+n.x*w)/n.y;
    //vector<sf::Vertex> v;
    //if((x1>0)&&(x1<w)){
    //    v.push_back(sf::Vertex(sf::Vector2f(x1, 0)));
    //}
    //if((y1>=0)&&(y1<=h)){
    //    v.push_back(sf::Vertex(sf::Vector2f(0, y1)));
    //}
    //if((x2>0)&&(x2<w)){
    //    v.push_back(sf::Vertex(sf::Vector2f(x2, h)));
    //}
    //if((y2>=0)&&(y2<=h)){
    //    v.push_back(sf::Vertex(sf::Vector2f(w, y2)));
    //}
    //if(v.size()<2){
    //    return;
    //}
    //sf::Vertex line[] =
    //{
    //    v[0],
    //    v[1]
    //};
    //line[0].color=sf::Color(0,0,0);
    //line[1].color=sf::Color(0,0,0);
    //window->draw(line, 2, sf::Lines);
}
std::string Line::what_is(){
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
void Circle::draw(sf::RenderWindow* window, sf::FloatRect visible, sf::FloatRect box){
    sf::CircleShape shape(r);
    sf::Vector2f v(middle.x-r,middle.y-r);
    shape.setPosition(v);
    shape.setOutlineColor(sf::Color(0,0,0,255));
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color(255,255,255,0));
    window->draw(shape);
}
std::string Circle::what_is(){
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

/*
Point Construction::lengthen(Point A, Point B, double a){
    double b = a/A.dist(B);
    return (B-A)*b+A;
}

Point Construction::middle(Point A, Point B){
    return (A+B)/2;
}
*/
Construction *makeSegmentMiddle(std::vector<Shape*> &segment,
        std::vector<Shape*> &shapes) {
    if (segment.size() != 1 || segment[0]->what_is()=="segment")
        return NULL;
    shapes.push_back (new Point ());
    Construction *segmid = new segmentMiddle(static_cast<Segment*>(segment[0]), static_cast<Point*>(shapes.back()));
    segmid->adjust();
    return segmid;
}
void segmentMiddle::adjust() {
    midPoint->x = (segment->p1.x + segment->p2.x)/2;
    midPoint->y = (segment->p1.y + segment->p2.y)/2;
}

Construction *makePointsMiddle(std::vector<Shape*> &points,
        std::vector<Shape*> &shapes) {
    if (points.size() != 2 || points[0]->what_is() != "Point" || points[1]->what_is() != "Point")
        return NULL;
    shapes.push_back (new Point());
    Construction *pointMid = new pointsMiddle (static_cast<Point*>(points[0]), static_cast<Point*>(points[1]), static_cast<Point*>(shapes.back()));
    pointMid->adjust();
    return pointMid;
}
void pointsMiddle::adjust() {
    midPoint->x = (pointA->x+pointB->x)/2;
    midPoint->y = (pointA->y+pointB->y)/2;
}

Construction *makeOrthogonal(std::vector<Shape*> &input,
        std::vector<Shape*> &shapes) {
    std::cout << "make orthogonal" << std::endl;
    if (input.size() != 2)
        return NULL;
    shapes.push_back (new Line(1,0,0));
    Construction *orthogonal = NULL;
    if (input[0]->what_is() == "Line" && input[1]->what_is() == "Point") {
        orthogonal = new orthogonalLine(static_cast<Line*>(input[0]), static_cast<Point*>(input[1]), static_cast<Line*>(shapes.back()));
    } else if (input[0]->what_is() == "Point" && input[1]->what_is() == "Line")
        orthogonal = new orthogonalLine(static_cast<Line*>(input[1]), static_cast<Point*>(input[0]), static_cast<Line*>(shapes.back()));
    if (orthogonal != NULL) 
        orthogonal->adjust();
    return orthogonal;
}
void orthogonalLine::adjust() {
    orthogonal->n.x = -(line->n.y);
    orthogonal->n.y = line->n.x;
    orthogonal->c = -( point->x * orthogonal->n.x + point->y * orthogonal->n.y);
}

Construction *makeParallel(std::vector<Shape*> &input,
        std::vector<Shape*> &shapes) {
    std::cout << "make parallel" << std::endl;
    if (input.size() != 2)
        return NULL;
    shapes.push_back (new Line(1,0,0));
    Construction *parallel = NULL;
    if (input[0]->what_is() == "Line" && input[1]->what_is() == "Point") {
        parallel = new parallelLine(static_cast<Line*>(input[0]), static_cast<Point*>(input[1]), static_cast<Line*>(shapes.back()));
    } else if (input[0]->what_is() == "Point" && input[1]->what_is() == "Line")
        parallel = new parallelLine(static_cast<Line*>(input[1]), static_cast<Point*>(input[0]), static_cast<Line*>(shapes.back()));
    if (parallel != NULL) 
        parallel->adjust();
    return parallel;
}
void parallelLine::adjust() {
    parallel->n = line->n;
    parallel->c = -( point->x * parallel->n.x + point->y * parallel->n.y);
    //parallel->c=0;
}
