#include"Construction.h"
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

void segmentMiddle::adjust() {
    //midPoint->setX ((segment->p1.getX() + segment->p2.getX())/2);
    //midPoint->setY ((segment->p1.getY() + segment->p2.getY())/2);
    midPoint->setX ((segment->getFromX() + segment->getToX())/2);
    midPoint->setY ((segment->getFromY() + segment->getToY())/2);
}

void pointsMiddle::adjust() {
    midPoint->setX ((pointA->getX()+pointB->getX())/2);
    midPoint->setY ((pointA->getY()+pointB->getY())/2);
}
void orthogonalLine::adjust() {
    //orthogonal->n.setX (-(line->n.getY()));
    //orthogonal->n.setY (line->n.getX());
    //orthogonal->n.x = (-(line->n.y));
    //orthogonal->n.y = (line->n.x);
    orthogonal->setNormalX (-(line->getNormalY()));
    orthogonal->setNormalY (line->getNormalX());

    //orthogonal->c = -( point->getX() * orthogonal->n.getX() + point->getY() * orthogonal->n.getY());
    //orthogonal->c = -( point->getX() * orthogonal->n.x + point->getY() * orthogonal->n.y);
    orthogonal->setC (-( point->getX() * orthogonal->getNormalX() + point->getY() * orthogonal->getNormalY()));
}
void parallelLine::adjust() {
    parallel->setNormalX (line->getNormalX());
    parallel->setNormalY (line->getNormalY());
    //parallel->n = line->n;
    //parallel->c = -( point->getX() * parallel->n.x + point->getY() * parallel->n.y);
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
    //circle->middle.setX (center->getX());
    //circle->middle.setY (center->getY());
    //circle->r = center->dist (*point);
    circle->setMiddleX (center->getX());
    circle->setMiddleY (center->getY());
    //circle->setR (center->dist (*point));
    circle->setR (dist(center->getX(), center->getY(), point->getX(), point->getY()));
}

void centerOfMass::adjust () {
    center->setX ((pointA->getX() + pointB->getX() + pointC->getX())/3);
    center->setY ((pointA->getY() + pointB->getY() + pointC->getY())/3);
}

void bisectorThreePoints::adjust () {
    //Point tmpPoint (pointB->getX()+pointC->getX()-pointA->getX(), pointB->getY()+pointC->getY()-pointA->getY());
    //if (tmpPoint.abs() < 0.01) {

    //}
}

void circleThreePoints::adjust () {
    //Point a = *pointA-*pointC, b=*pointB-*pointC;
    Point a, b;
    a.x = pointA->getX() - pointC->getX();
    a.y = pointA->getY() - pointC->getY();
    b.x = pointB->getX() - pointC->getX();
    b.y = pointB->getY() - pointC->getY();

    //circle->r=a.abs()*b.abs()*(a-b).abs()/(2*(a%b));
    //circle->middle=b*(a.abs()*a.abs())/(a%b)/2-a*(b.abs()*b.abs()/(a%b))/2;
    //circle->middle= Point(circle->middle.getY(),-circle->middle.getX())+*pointC;
    double aLen = length(a);
    double bLen = length(b);
    circle->setR (aLen*bLen*length(a-b)/2/(a%b));
    Point mid = b*(aLen*aLen)/(a%b)/2-a*(bLen*bLen/(a%b))/2;
    circle->setMiddleX (mid.y+pointC->getX());
    circle->setMiddleY (-mid.x+pointC->getY());

}
void powerLine::adjust() {
    //power->n = circle2->middle-circle1->middle;
    //power->c = (circle1->middle*circle1->middle-circle2->middle*circle2->middle-circle1->r*circle1->r+circle2->r*circle2->r)/2;
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
    //line->setC (-((*pointA + *pointB)*line->n)/2);
    line->setC (-0.5 * ((pointA->getX()+pointB->getX())*line->getNormalX() +
                        (pointA->getY()+pointB->getY())*line->getNormalY()));

    //line->n = *pointA-*pointB;
    //line->c = -((*pointA + *pointB)*line->n)/2;
}
void symmetricalOfSegment::adjust() {
    //line->n = segment->p1 - segment->p2;
    line->setNormalX (segment->getFromX() - segment->getToX());
    line->setNormalY (segment->getFromY() - segment->getToY());
    //line->c = -((segment->p1 + segment->p2)*line->n)/2;
    line->setC (-0.5 * ((segment->getFromX() + segment->getToX())*line->getNormalX() + 
                        (segment->getFromY() + segment->getToY())*line->getNormalY()));
}
void tangentCirclePoint::adjust() {
    //Point p = *point - circle->middle;
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
    //line1->n = Point(p.getX() * cosin - p.getY() * sinus, p.getX() * sinus + p.getY() * cosin) * sinus;
    //line1->c = -(line1->n*(*point));
    //line2->n = Point(p.getX() * cosin + p.getY() * sinus, - p.getX() * sinus + p.getY() * cosin) * sinus;
    //line2->c = -(line2->n*(*point));
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
