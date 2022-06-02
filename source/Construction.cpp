#include"Construction.h"
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

void segmentMiddle::adjust() {
    midPoint->setX ((segment->p1.getX() + segment->p2.getX())/2);
    midPoint->setY ((segment->p1.getY() + segment->p2.getY())/2);
}

void pointsMiddle::adjust() {
    midPoint->setX ((pointA->getX()+pointB->getX())/2);
    midPoint->setY ((pointA->getY()+pointB->getY())/2);
}
void orthogonalLine::adjust() {
    orthogonal->n.setX (-(line->n.getY()));
    orthogonal->n.setY (line->n.getX());
    orthogonal->c = -( point->getX() * orthogonal->n.getX() + point->getY() * orthogonal->n.getY());
}
void parallelLine::adjust() {
    parallel->n = line->n;
    parallel->c = -( point->getX() * parallel->n.getX() + point->getY() * parallel->n.getY());
}
void lineThroughPoints::adjust() {
    line->goThroughPoints (*pointA, *pointB);
}

void segmentFromPoints::adjust() {
    segment->p1.setX (pointA->getX());
    segment->p1.setY (pointA->getY());
    segment->p2.setX (pointB->getX());
    segment->p2.setY (pointB->getY());
}

void circleWithCenter::adjust() {
    circle->middle.setX (center->getX());
    circle->middle.setY (center->getY());
    circle->r = center->dist (*point);
}

void centerOfMass::adjust () {
    center->setX ((pointA->getX() + pointB->getX() + pointC->getX())/3);
    center->setY ((pointA->getY() + pointB->getY() + pointC->getY())/3);
}

void bisectorThreePoints::adjust () {
    Point tmpPoint (pointB->getX()+pointC->getX()-pointA->getX(), pointB->getY()+pointC->getY()-pointA->getY());
    if (tmpPoint.abs() < 0.01) {

    }
}

void circleThreePoints::adjust () {
    Point a = *pointA-*pointC, b=*pointB-*pointC;
    circle->r=a.abs()*b.abs()*(a-b).abs()/(2*(a%b));
    circle->middle=b*(a.abs()*a.abs())/(a%b)/2-a*(b.abs()*b.abs()/(a%b))/2;
    circle->middle= Point(circle->middle.getY(),-circle->middle.getX())+*pointC;

}
void powerLine::adjust() {
    power->n = circle2->middle-circle1->middle;
    power->c = (circle1->middle*circle1->middle-circle2->middle*circle2->middle-circle1->r*circle1->r+circle2->r*circle2->r)/2;
}
void symmetricalOfPoints::adjust() {
    line->n = *pointA-*pointB;
    line->c = -((*pointA + *pointB)*line->n)/2;
}
void symmetricalOfSegment::adjust() {
    line->n = segment->p1 - segment->p2;
    line->c = -((segment->p1 + segment->p2)*line->n)/2;
}
void tangentCirclePoint::adjust() {
    Point p = *point - circle->middle;
    double cosin = circle->r / p.abs();
    double sinus = sqrt(1 - cosin * cosin);
    line1->n = Point(p.getX() * cosin - p.getY() * sinus, p.getX() * sinus + p.getY() * cosin) * sinus;
    line1->c = -(line1->n*(*point));
    line2->n = Point(p.getX() * cosin + p.getY() * sinus, - p.getX() * sinus + p.getY() * cosin) * sinus;
    line2->c = -(line2->n*(*point));
}

void lineCircleIntersection::adjust() {
    Line l = Line(line->n.getX(), line->n.getY(), line->c+(line->n*circle->middle));
    double sqrtdelta = l.n.getX() * sqrt( circle->r * circle->r * ( l.n * l.n ) - l.c * l.c);
    double y = ( - l.n.getY() * l.c + sqrtdelta)/( l.n * l.n );
    double x = -( l.c + l.n.getY() * y)/l.n.getX();
    *pointA = Point(x,y) + circle->middle;

    y = ( - l.n.getY()*l.c-sqrtdelta)/(l.n*l.n);
    x = -(l.c+l.n.getY()*y)/l.n.getX();
    *pointB = Point(x,y) + circle->middle;
}
