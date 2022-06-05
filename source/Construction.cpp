#include"Construction.h"
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

void segmentMiddle::adjust() {
    midPoint->setX ((segment->getFromX() + segment->getToX())/2);
    midPoint->setY ((segment->getFromY() + segment->getToY())/2);
}

void pointsMiddle::adjust() {
    midPoint->setX ((pointA->getX()+pointB->getX())/2);
    midPoint->setY ((pointA->getY()+pointB->getY())/2);
}
void orthogonalLine::adjust() {
    orthogonal->setNormalX (-(line->getNormalY()));
    orthogonal->setNormalY (line->getNormalX());

    orthogonal->setC (-( point->getX() * orthogonal->getNormalX() + point->getY() * orthogonal->getNormalY()));
}
void parallelLine::adjust() {
    parallel->setNormalX (line->getNormalX());
    parallel->setNormalY (line->getNormalY());
    parallel->setC (-( point->getX() * parallel->getNormalX() + point->getY() * parallel->getNormalY()));
}
void lineThroughPoints::adjust() {
    line->goThroughPoints (pointA->getX(), pointA->getY(), pointB->getX(), pointB->getY());
}

void segmentFromPoints::adjust() {
    segment->setFromX (pointA->getX());
    segment->setFromY (pointA->getY());
    segment->setToX (pointB->getX());
    segment->setToY (pointB->getY());
}

void circleWithCenter::adjust() {
    circle->setMiddleX (center->getX());
    circle->setMiddleY (center->getY());
    circle->setR (dist(center->getX(), center->getY(), point->getX(), point->getY()));
}

void centerOfMass::adjust () {
    center->setX ((pointA->getX() + pointB->getX() + pointC->getX())/3);
    center->setY ((pointA->getY() + pointB->getY() + pointC->getY())/3);
}

void bisectorThreePoints::adjust () {
    double ratio = dist(pointA->getX(), pointA->getY(), pointC->getX(), pointC->getY())/dist(pointB->getX(), pointB->getY(), pointC->getX(), pointC->getY());    
    Point temp;
    temp.x=((pointA->getX()-pointB->getX())/(ratio+1)+pointB->getX());
    temp.y=((pointA->getY()-pointB->getY())/(ratio+1)+pointB->getY());
    line->goThroughPoints(pointC->getX(), pointC->getY(), temp.x, temp.y);

    
}

void circleThreePoints::adjust () {
    Point a, b;
    a.x = pointA->getX() - pointC->getX();
    a.y = pointA->getY() - pointC->getY();
    b.x = pointB->getX() - pointC->getX();
    b.y = pointB->getY() - pointC->getY();

    double aLen = length(a);
    double bLen = length(b);
    circle->setR (aLen*bLen*length(a-b)/2/(a%b));
    Point mid = b*(aLen*aLen)/(a%b)/2-a*(bLen*bLen/(a%b))/2;
    circle->setMiddleX (mid.y+pointC->getX());
    circle->setMiddleY (-mid.x+pointC->getY());

}
void powerLine::adjust() {
    Point c1Mid, c2Mid;
    c1Mid.x = circle1->getMiddleX();
    c1Mid.y = circle1->getMiddleY();
    c2Mid.x = circle2->getMiddleX();
    c2Mid.y = circle2->getMiddleY();
    power->setNormalX(2*c2Mid.x-2*c1Mid.x);
    power->setNormalY(2*c2Mid.y-2*c1Mid.y);

    
    power->setC (c1Mid*c1Mid-c2Mid*c2Mid-circle1->getR()*circle1->getR()+circle2->getR()*circle2->getR());
    
}
void symmetricalOfPoints::adjust() {
    line->setNormalX (pointA->getX() - pointB->getX());
    line->setNormalY (pointA->getY() - pointB->getY());
    line->setC (-0.5 * ((pointA->getX()+pointB->getX())*line->getNormalX() +
                        (pointA->getY()+pointB->getY())*line->getNormalY()));

}
void symmetricalOfSegment::adjust() {
    line->setNormalX (segment->getFromX() - segment->getToX());
    line->setNormalY (segment->getFromY() - segment->getToY());
    line->setC (-0.5 * ((segment->getFromX() + segment->getToX())*line->getNormalX() + 
                        (segment->getFromY() + segment->getToY())*line->getNormalY()));
}
void tangentCirclePoint::adjust() {
    Point p;
    p.x = point->getX() - circle->getMiddleX();
    p.y = point->getY() - circle->getMiddleY();
    double cosin = circle->getR() / length(p);;
    double sinus = sqrt(1 - cosin * cosin);
    line1->setNormalX ((p.x * cosin - p.y * sinus)*sinus);
    line1->setNormalY ((p.x * sinus + p.y * cosin)*sinus);
    line1->setC (-(line1->getNormalX()*point->getX() + line1->getNormalY()*point->getY()));

    line2->setNormalX ((p.x * cosin + p.y * sinus)*sinus);
    line2->setNormalY ((- p.x * sinus + p.y * cosin)*sinus);
    line2->setC (-(line2->getNormalX()*point->getX()+line2->getNormalY()*point->getY()));
}

void lineCircleIntersection::adjust() {
    LineShape *l = makeLineShape(line->getNormalX(), line->getNormalY(), circle->getMiddleX() * line->getNormalX() + circle->getMiddleY() * line->getNormalY() +  line->getC());
    double sqrtdelta = l->getNormalX() * sqrt( circle->getR() * circle->getR() * ( l->getNormalX() * l->getNormalX() + l->getNormalY() * l->getNormalY() ) - l->getC() * l->getC());
    double y = (-l->getNormalY() * l->getC() + sqrtdelta) / (l->getNormalX() * l->getNormalX() + l->getNormalY() * l->getNormalY());
    double x = - ( l->getC() + l->getNormalY() * y)/l->getNormalX();
    pointA->setX(x + circle->getMiddleX());
    pointA->setY(y + circle->getMiddleY());

    y = (- l->getNormalY() * l->getC() - sqrtdelta)/(l->getNormalX() * l->getNormalX() + l->getNormalY() * l->getNormalY());
    x = - (l->getC() + l->getNormalY() * y) / l->getNormalX();
    pointB->setX(x + circle->getMiddleX());
    pointB->setY(y + circle->getMiddleY());
    
}

void circlesIntersection::adjust() {
    LineShape * l = makeLineShape(1,0,1); 
    Point c1Mid, c2Mid;
    c1Mid.x = circle1->getMiddleX();
    c1Mid.y = circle1->getMiddleY();
    c2Mid.x = circle2->getMiddleX();
    c2Mid.y = circle2->getMiddleY();
    l->setNormalX(2*c2Mid.x-2*c1Mid.x);
    l->setNormalY(2*c2Mid.y-2*c1Mid.y);
    l->setC (c1Mid*c1Mid-c2Mid*c2Mid-circle1->getR()*circle1->getR()+circle2->getR()*circle2->getR() + circle1->getMiddleX() * l->getNormalX() + circle1->getMiddleY() * l->getNormalY()); 
    
    
    double sqrtdelta = l->getNormalX() * sqrt( circle1->getR() * circle1->getR() * ( l->getNormalX() * l->getNormalX() + l->getNormalY() * l->getNormalY() ) - l->getC() * l->getC());
    double y = (-l->getNormalY() * l->getC() + sqrtdelta) / (l->getNormalX() * l->getNormalX() + l->getNormalY() * l->getNormalY());
    double x = - ( l->getC() + l->getNormalY() * y)/l->getNormalX();
    pointA->setX(x + circle1->getMiddleX());
    pointA->setY(y + circle1->getMiddleY());

    y = (- l->getNormalY() * l->getC() - sqrtdelta)/(l->getNormalX() * l->getNormalX() + l->getNormalY() * l->getNormalY());
    x = - (l->getC() + l->getNormalY() * y) / l->getNormalX();
    pointB->setX(x + circle1->getMiddleX());
    pointB->setY(y + circle1->getMiddleY());
}
