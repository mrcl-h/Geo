#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<cmath>
#include<memory>
#include"geo.h"



class Construction {
    public:
    virtual ~Construction () {}
    virtual void adjust () {}
};

typedef Construction* (*constructionMaker)(const constructionElements&, std::vector<std::unique_ptr<Shape> >&);

//------------------------------------------------

class segmentMiddle : public Construction { //constructs middle point from segment
    private:
        Segment * const segment;
        Point *midPoint;
    public:
        segmentMiddle (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : segment(el.segments[0]), midPoint(NULL) {
            midPoint = new Point;
            shapes.emplace_back (midPoint);
            midPoint->isDependent = true;
        }
        virtual void adjust ();
};

class pointsMiddle : public Construction { //constructs middle point from two points
    private:
        Point * const pointA, * const pointB;
        Point *midPoint;
    public:
        pointsMiddle (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB (el.points[1]), midPoint(NULL) {
            midPoint = new Point;
            shapes.emplace_back (midPoint);
            midPoint->isDependent = true;
        }
        virtual void adjust ();
};

class orthogonalLine : public Construction { //constructs orthogonal line from line and a point
    private:
        Line * const line;
        Point * const point;
        Line *orthogonal;
    public:
        orthogonalLine (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : line(el.lines[0]), point(el.points[0]), orthogonal(NULL) {
            orthogonal = new Line (1,0,0);
            shapes.emplace_back (orthogonal);
            orthogonal->isDependent = true;
        }
        virtual void adjust ();
};

class parallelLine : public Construction { //constructs parallel line from line and a point
    private:
        Line * const line;
        Point * const point;
        Line *parallel;
    public:
        parallelLine (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : line(el.lines[0]), point(el.points[0]), parallel(NULL) {
            parallel = new Line (1,0,0);
            shapes.emplace_back (parallel);
            parallel->isDependent = true;
        }
        virtual void adjust ();
};

class lineThroughPoints : public Construction {
    private:
        Point * const pointA, * const pointB;
        Line *line;
    public:
        lineThroughPoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB (el.points[1]), line(NULL) {
            line = new Line (1,0,0);
            shapes.emplace_back (line);
            line->isDependent = true;
        }
        virtual void adjust ();
};

class segmentFromPoints : public Construction {
    private:
        Point * const pointA, * const pointB;
        Segment *segment;
    public:
        segmentFromPoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB (el.points[1]), segment(NULL) {
            segment = new Segment;
            shapes.emplace_back (segment);
            segment->isDependent = true;
        }
        virtual void adjust ();
};

class circleWithCenter : public Construction {
    private:
        Point * const center, * const point;
        Circle *circle;
    public:
        circleWithCenter (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : center(el.points[0]), point(el.points[1]), circle(NULL) {
            circle = new Circle (0,0,0);
            shapes.emplace_back (circle);
            circle->isDependent = true;
        }
        virtual void adjust ();
};

class centerOfMass : public Construction {
    private:
        Point * const pointA, * const pointB, * const pointC;
        Point *center;
    public:
        centerOfMass (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA(el.points[0]), pointB(el.points[1]), pointC (el.points[2]), center (NULL) {
            center = new Point;
            shapes.emplace_back (center);
            center->isDependent = true;
        }
        virtual void adjust ();
};

class bisectorThreePoints : public Construction {
    private:
        Point * const pointA, * const pointB, * const pointC;
        Line *line;
    public:
        bisectorThreePoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB(el.points[1]), pointC(el.points[2]), line (NULL) {
            line = new Line (1,0,0);
            shapes.emplace_back (line);
            line->isDependent = true;
        }
        virtual void adjust ();
};


class circleThreePoints : public Construction {
    private:
        Point * const pointA, * const pointB, * const pointC;
        Circle *circle;
    public:
        circleThreePoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB(el.points[1]), pointC(el.points[2]), circle (NULL) {
            circle = new Circle (0,0,0);
            shapes.emplace_back (circle);
            circle->isDependent = true;
        }
        virtual void adjust ();
};

//TODO: Intersections of two circles


class powerLine : public Construction {
    private:
        Circle * const circle1, * const circle2;
        Line *power;
    public:
        powerLine (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle1(el.circles[0]), circle2(el.circles[1]), power(NULL) {
            power = new Line (1,0,0);
            shapes.emplace_back (power);
            power->isDependent = true;
        }
        virtual void adjust ();
};
//TODO: Intersections of circle and line

class lineCircleIntersection : public Construction {
    private:
        Circle * const circle;
        Line * const line;
        Point *pointA, *pointB;
    public:
        lineCircleIntersection (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle(el.circles[0]), line(el.lines[0]), pointA(NULL), pointB(NULL) {
            pointA = new Point ();
            shapes.emplace_back (pointA);
            pointA->isDependent = true;
            pointB = new Point ();
            shapes.emplace_back (pointB);
            pointB->isDependent = true;
        }
        virtual void adjust ();
};

class tangentCirclePoint : public Construction {
    private:
        Point * const point;
        Circle * const circle;
        Line *line1, *line2;
    public:
        tangentCirclePoint (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : point(el.points[0]), circle(el.circles[0]), line1(NULL), line2(NULL) {
            line1 = new Line (1,0,0);
            shapes.emplace_back (line1);
            line1->isDependent = true;
            line2 = new Line (1,0,0);
            shapes.emplace_back (line2);
            line2->isDependent = true;
        }
        virtual void adjust ();
};

class symmetricalOfSegment : public Construction {
    private:
        Segment * const segment;
        Line *line;
    public:
        symmetricalOfSegment (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : segment(el.segments[0]), line(NULL) {
            line = new Line (1,0,0);
            shapes.emplace_back (line);
            line->isDependent = true;
        }
        virtual void adjust ();
};
class symmetricalOfPoints : public Construction {
    private:
        Point * const pointA, * const pointB;
        Line *line;
    public:
        symmetricalOfPoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA(el.points[0]), pointB(el.points[1]), line(NULL) {
            line = new Line (1,0,0);
            shapes.emplace_back (line);
            line->isDependent = true;
        }
        virtual void adjust ();
};
//TODO: tangents to circle through point

//TODO: bisector of 3 points / bisectors of two Lines
//TODO: described circle on triangle
//TODO: inscribed circle in triangle
//TODO: Orthocenter of triangle
//TODO: nine point circle
//TODO: Euler's line
//TODO: Symmedian
//TODO: Space transformations: HOMOTHETY, ROTATION, SYMMETRY about point/line, SHIFT, INVERSION, AFINIC

template <typename T>
Construction *makeConstruction (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) {
    T* newT = new T (el, shapes);
    if (newT == NULL) return NULL;
    newT->adjust();
    return newT;
}
