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
        SegmentShape * const segment;
        PointShape *midPoint;
    public:
        segmentMiddle (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : segment(el.segments[0]), midPoint(NULL) {
            //midPoint = new PointShape;
            midPoint = makePointShape();
            shapes.emplace_back (midPoint);
            midPoint->setDependent (true);
        }
        virtual void adjust ();
};

class pointsMiddle : public Construction { //constructs middle point from two points
    private:
        PointShape * const pointA, * const pointB;
        PointShape *midPoint;
    public:
        pointsMiddle (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB (el.points[1]), midPoint(NULL) {
            //midPoint = new PointShape;
            midPoint = makePointShape();
            shapes.emplace_back (midPoint);
            //midPoint->isDependent = true;
            midPoint->setDependent (true);
        }
        virtual void adjust ();
};

class orthogonalLine : public Construction { //constructs orthogonal line from line and a point
    private:
        LineShape * const line;
        PointShape * const point;
        LineShape *orthogonal;
    public:
        orthogonalLine (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : line(el.lines[0]), point(el.points[0]), orthogonal(NULL) {
            //orthogonal = new LineShape (1,0,0);
            orthogonal = makeLineShape (1,0,0);
            shapes.emplace_back (orthogonal);
            //orthogonal->isDependent = true;
            orthogonal->setDependent (true);
        }
        virtual void adjust ();
};

class parallelLine : public Construction { //constructs parallel line from line and a point
    private:
        LineShape * const line;
        PointShape * const point;
        LineShape *parallel;
    public:
        parallelLine (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : line(el.lines[0]), point(el.points[0]), parallel(NULL) {
            //parallel = new LineShape (1,0,0);
            parallel = makeLineShape (1,0,0);
            shapes.emplace_back (parallel);
            //parallel->isDependent = true;
            parallel->setDependent (true);
        }
        virtual void adjust ();
};

class lineThroughPoints : public Construction {
    private:
        PointShape * const pointA, * const pointB;
        LineShape *line;
    public:
        lineThroughPoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB (el.points[1]), line(NULL) {
            //line = new LineShape (1,0,0);
            line = makeLineShape (1,0,0);
            shapes.emplace_back (line);
            //line->isDependent = true;
            line->setDependent (true);
        }
        virtual void adjust ();
};

class segmentFromPoints : public Construction {
    private:
        PointShape * const pointA, * const pointB;
        SegmentShape *segment;
    public:
        segmentFromPoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB (el.points[1]), segment(NULL) {
            //segment = new SegmentShape;
            segment = makeSegmentShape ();
            shapes.emplace_back (segment);
            //segment->isDependent = true;
            segment->setDependent(true);
        }
        virtual void adjust ();
};

class circleWithCenter : public Construction {
    private:
        PointShape * const center, * const point;
        CircleShape *circle;
    public:
        circleWithCenter (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : center(el.points[0]), point(el.points[1]), circle(NULL) {
            //circle = new CircleShape (0,0,0);
            circle = makeCircleShape (0,0,0);
            shapes.emplace_back (circle);
            //circle->isDependent = true;
            circle->setDependent(true);
        }
        virtual void adjust ();
};

class centerOfMass : public Construction {
    private:
        PointShape * const pointA, * const pointB, * const pointC;
        PointShape *center;
    public:
        centerOfMass (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA(el.points[0]), pointB(el.points[1]), pointC (el.points[2]), center (NULL) {
            //center = new PointShape;
            center = makePointShape ();
            shapes.emplace_back (center);
            //center->isDependent = true;
            center->setDependent(true);
        }
        virtual void adjust ();
};

class bisectorThreePoints : public Construction {
    private:
        PointShape * const pointA, * const pointB, * const pointC;
        LineShape *line;
    public:
        bisectorThreePoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB(el.points[1]), pointC(el.points[2]), line (NULL) {
            //line = new LineShape (1,0,0);
            line = makeLineShape (1,0,0);
            shapes.emplace_back (line);
            //line->isDependent = true;
            line->setDependent(true);
        }
        virtual void adjust ();
};


class circleThreePoints : public Construction {
    private:
        PointShape * const pointA, * const pointB, * const pointC;
        CircleShape *circle;
    public:
        circleThreePoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB(el.points[1]), pointC(el.points[2]), circle (NULL) {
            //circle = new CircleShape (0,0,0);
            circle = makeCircleShape (0,0,0);
            shapes.emplace_back (circle);
            //circle->isDependent = true;
            circle->setDependent(true);
        }
        virtual void adjust ();
};

//TODO: Intersections of two circles

class circlesIntersection : public Construction {
    private:
        CircleShape * const circle1, * const circle2;
        PointShape *pointA, *pointB;
    public:
        circlesIntersection (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle1(el.circles[0]), circle2(el.circles[1]), pointA(NULL), pointB(NULL) {
            //pointA = new PointShape ();
            pointA = makePointShape ();
            shapes.emplace_back (pointA);
            //pointA->isDependent = true;
            pointA->setDependent(true);
            //pointB = new PointShape ();
            pointB = makePointShape ();
            shapes.emplace_back (pointB);
            //pointB->isDependent = true;
            pointB->setDependent(true);
        }
        virtual void adjust ();
};

class powerLine : public Construction {
    private:
        CircleShape * const circle1, * const circle2;
        LineShape *power;
    public:
        powerLine (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle1(el.circles[0]), circle2(el.circles[1]), power(NULL) {
            //power = new LineShape (1,0,0);
            power = makeLineShape (1,0,0);
            shapes.emplace_back (power);
            //power->isDependent = true;
            power->setDependent(true);
        }
        virtual void adjust ();
};
//TODO: Intersections of circle and line

class lineCircleIntersection : public Construction {
    private:
        CircleShape * const circle;
        LineShape * const line;
        PointShape *pointA, *pointB;
    public:
        lineCircleIntersection (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle(el.circles[0]), line(el.lines[0]), pointA(NULL), pointB(NULL) {
            //pointA = new PointShape ();
            pointA = makePointShape ();
            shapes.emplace_back (pointA);
            //pointA->isDependent = true;
            pointA->setDependent(true);
            //pointB = new PointShape ();
            pointB = makePointShape ();
            shapes.emplace_back (pointB);
            //pointB->isDependent = true;
            pointB->setDependent(true);
        }
        virtual void adjust ();
};

class tangentCirclePoint : public Construction {
    private:
        PointShape * const point;
        CircleShape * const circle;
        LineShape *line1, *line2;
    public:
        tangentCirclePoint (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : point(el.points[0]), circle(el.circles[0]), line1(NULL), line2(NULL) {
            //line1 = new LineShape (1,0,0);
            line1 = makeLineShape (1,0,0);
            shapes.emplace_back (line1);
            //line1->isDependent = true;
            line1->setDependent(true);
            //line2 = new LineShape (1,0,0);
            line2 = makeLineShape (1,0,0);
            shapes.emplace_back (line2);
            //line2->isDependent = true;
            line2->setDependent(true);
        }
        virtual void adjust ();
};

class symmetricalOfSegment : public Construction {
    private:
        SegmentShape * const segment;
        LineShape *line;
    public:
        symmetricalOfSegment (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : segment(el.segments[0]), line(NULL) {
            //line = new LineShape (1,0,0);
            line = makeLineShape (1,0,0);
            shapes.emplace_back (line);
            //line->isDependent = true;
            line->setDependent(true);
        }
        virtual void adjust ();
};
class symmetricalOfPoints : public Construction {
    private:
        PointShape * const pointA, * const pointB;
        LineShape *line;
    public:
        symmetricalOfPoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA(el.points[0]), pointB(el.points[1]), line(NULL) {
            //line = new LineShape (1,0,0);
            line = makeLineShape (1,0,0);
            shapes.emplace_back (line);
            //line->isDependent = true;
            line->setDependent(true);
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
