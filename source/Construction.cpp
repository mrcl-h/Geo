#include"Construction.h"
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

void segmentMiddle::adjust() {
    midPoint->x = (segment->p1.x + segment->p2.x)/2;
    midPoint->y = (segment->p1.y + segment->p2.y)/2;
}

void pointsMiddle::adjust() {
    midPoint->x = (pointA->x+pointB->x)/2;
    midPoint->y = (pointA->y+pointB->y)/2;
}
void orthogonalLine::adjust() {
    orthogonal->n.x = -(line->n.y);
    orthogonal->n.y = line->n.x;
    orthogonal->c = -( point->x * orthogonal->n.x + point->y * orthogonal->n.y);
}
void parallelLine::adjust() {
    parallel->n = line->n;
    parallel->c = -( point->x * parallel->n.x + point->y * parallel->n.y);
}
void lineThroughPoints::adjust() {
    line->goThroughPoints (*pointA, *pointB);
}

void segmentFromPoints::adjust() {
    segment->p1.x = pointA->x;
    segment->p1.y = pointA->y;
    segment->p2.x = pointB->x;
    segment->p2.y = pointB->y;
}

void circleWithCenter::adjust() {
    circle->middle.x = center->x;
    circle->middle.y = center->y;
    circle->r = center->dist (*point);
}

void centerOfMass::adjust () {
    center->x = (pointA->x + pointB->x + pointC->x)/3;
    center->y = (pointA->y + pointB->y + pointC->y)/3;
}

void bisectorThreePoints::adjust () {
    Point tmpPoint (pointB->x+pointC->x-pointA->x, pointB->y+pointC->y-pointA->y);
    if (tmpPoint.abs() < 0.01) {

    }
}

void circleThreePoints::adjust () {
    Point a = *pointA-*pointC, b=*pointB-*pointC;
    circle->r=a.abs()*b.abs()*(a-b).abs()/(2*(a%b));
    circle->middle=b*(a.abs()*a.abs())/(a%b)/2-a*(b.abs()*b.abs()/(a%b))/2;
    circle->middle= Point(circle->middle.y,-circle->middle.x)+*pointC;

}
void powerLine::adjust() {
    power->n = circle2->middle-circle1->middle;
    power->c = (circle1->middle*circle1->middle-circle2->middle*circle2->middle-circle1->r*circle1->r+circle2->r*circle2->r)/2;
    std::cout<<circle1->middle<<" "<<circle2->middle;
}
void symmetricalOfPoints::adjust() {
    line->n = *pointA-*pointB;
    line->c = -((*pointA + *pointB)*line->n)/2;
}
void symmetricalOfSegment::adjust() {
    line->n = segment->p1 - segment->p2;
    line->c = -((segment->p1 + segment->p2)*line->n)/2;
}
