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

typedef Construction* (*constructionMaker)(constructionElements&, std::vector<std::unique_ptr<Shape> >&);

//------------------------------------------------

class segmentMiddle : public Construction { //constructs middle point from segment
    private:
        SegmentShape * const segment;
        PointShape *midPoint;
    public:
        //segmentMiddle (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : segment(el.segments[0]), midPoint(NULL) {
        segmentMiddle (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : segment(el.getVector<SegmentShape*>()[0]), midPoint(NULL) {
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
        //pointsMiddle (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB (el.points[1]), midPoint(NULL) {
        pointsMiddle (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.getVector<PointShape*>()[0]), pointB (el.getVector<PointShape*>()[1]), midPoint(NULL) {
            midPoint = makePointShape();
            shapes.emplace_back (midPoint);
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
        //orthogonalLine (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : line(el.lines[0]), point(el.points[0]), orthogonal(NULL) {
        orthogonalLine (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : line(el.getVector<LineShape*>()[0]), point(el.getVector<PointShape*>()[0]), orthogonal(NULL) {
            orthogonal = makeLineShape (1,0,0);
            shapes.emplace_back (orthogonal);
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
        //parallelLine (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : line(el.lines[0]), point(el.points[0]), parallel(NULL) {
        parallelLine (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : line(el.getVector<LineShape*>()[0]), point(el.getVector<PointShape*>()[0]), parallel(NULL) {
            parallel = makeLineShape (1,0,0);
            shapes.emplace_back (parallel);
            parallel->setDependent (true);
        }
        virtual void adjust ();
};

class lineThroughPoints : public Construction {
    private:
        PointShape * const pointA, * const pointB;
        LineShape *line;
    public:
        //lineThroughPoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB (el.points[1]), line(NULL) {
        lineThroughPoints (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.getVector<PointShape*>()[0]), pointB (el.getVector<PointShape*>()[1]), line(NULL) {
            line = makeLineShape (1,0,0);
            shapes.emplace_back (line);
            line->setDependent (true);
        }
        virtual void adjust ();
};

class segmentFromPoints : public Construction {
    private:
        PointShape * const pointA, * const pointB;
        SegmentShape *segment;
    public:
        //segmentFromPoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB (el.points[1]), segment(NULL) {
        segmentFromPoints (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.getVector<PointShape*>()[0]), pointB (el.getVector<PointShape*>()[1]), segment(NULL) {
            segment = makeSegmentShape ();
            shapes.emplace_back (segment);
            segment->setDependent(true);
        }
        virtual void adjust ();
};

class circleWithCenter : public Construction {
    private:
        PointShape * const center, * const point;
        CircleShape *circle;
    public:
        //circleWithCenter (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : center(el.points[0]), point(el.points[1]), circle(NULL) {
        circleWithCenter (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : center(el.getVector<PointShape*>()[0]), point(el.getVector<PointShape*>()[1]), circle(NULL) {
            circle = makeCircleShape (0,0,0);
            shapes.emplace_back (circle);
            circle->setDependent(true);
        }
        virtual void adjust ();
};

class centerOfMass : public Construction {
    private:
        PointShape * const pointA, * const pointB, * const pointC;
        PointShape *center;
    public:
        //centerOfMass (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA(el.points[0]), pointB(el.points[1]), pointC (el.points[2]), center (NULL) {
        centerOfMass (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA(el.getVector<PointShape*>()[0]), pointB(el.getVector<PointShape*>()[1]), pointC (el.getVector<PointShape*>()[2]), center (NULL) {
            center = makePointShape ();
            shapes.emplace_back (center);
            center->setDependent(true);
        }
        virtual void adjust ();
};

class bisectorThreePoints : public Construction {
    private:
        PointShape * const pointA, * const pointB, * const pointC;
        LineShape *line;
    public:
        //bisectorThreePoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB(el.points[1]), pointC(el.points[2]), line (NULL) {
        bisectorThreePoints (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.getVector<PointShape*>()[0]), pointB(el.getVector<PointShape*>()[1]), pointC(el.getVector<PointShape*>()[2]), line (NULL) {
            line = makeLineShape (1,0,0);
            shapes.emplace_back (line);
            line->setDependent(true);
        }
        virtual void adjust ();
};


class circleThreePoints : public Construction {
    private:
        PointShape * const pointA, * const pointB, * const pointC;
        CircleShape *circle;
    public:
        //circleThreePoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.points[0]), pointB(el.points[1]), pointC(el.points[2]), circle (NULL) {
        circleThreePoints (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA (el.getVector<PointShape*>()[0]), pointB(el.getVector<PointShape*>()[1]), pointC(el.getVector<PointShape*>()[2]), circle (NULL) {
            circle = makeCircleShape (0,0,0);
            shapes.emplace_back (circle);
            circle->setDependent(true);
        }
        virtual void adjust ();
};

class circlesIntersection : public Construction {
    private:
        CircleShape * const circle1, * const circle2;
        PointShape *pointA, *pointB;
    public:
        //circlesIntersection (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle1(el.circles[0]), circle2(el.circles[1]), pointA(NULL), pointB(NULL) {
        circlesIntersection (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle1(el.getVector<CircleShape*>()[0]), circle2(el.getVector<CircleShape*>()[1]), pointA(NULL), pointB(NULL) {
            pointA = makePointShape ();
            shapes.emplace_back (pointA);
            pointA->setDependent(true);
            pointB = makePointShape ();
            shapes.emplace_back (pointB);
            pointB->setDependent(true);
        }
        virtual void adjust ();
};

class powerLine : public Construction {
    private:
        CircleShape * const circle1, * const circle2;
        LineShape *power;
    public:
        //powerLine (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle1(el.circles[0]), circle2(el.circles[1]), power(NULL) {
        powerLine (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle1(el.getVector<CircleShape*>()[0]), circle2(el.getVector<CircleShape*>()[1]), power(NULL) {
            power = makeLineShape (1,0,0);
            shapes.emplace_back (power);
            power->setDependent(true);
        }
        virtual void adjust ();
};

class lineCircleIntersection : public Construction {
    private:
        CircleShape * const circle;
        LineShape * const line;
        PointShape *pointA, *pointB;
    public:
        //lineCircleIntersection (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle(el.circles[0]), line(el.lines[0]), pointA(NULL), pointB(NULL) {
        lineCircleIntersection (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : circle(el.getVector<CircleShape*>()[0]), line(el.getVector<LineShape*>()[0]), pointA(NULL), pointB(NULL) {
            pointA = makePointShape ();
            shapes.emplace_back (pointA);
            pointA->setDependent(true);
            pointB = makePointShape ();
            shapes.emplace_back (pointB);
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
        //tangentCirclePoint (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : point(el.points[0]), circle(el.circles[0]), line1(NULL), line2(NULL) {
        tangentCirclePoint (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : point(el.getVector<PointShape*>()[0]), circle(el.getVector<CircleShape*>()[0]), line1(NULL), line2(NULL) {
            line1 = makeLineShape (1,0,0);
            shapes.emplace_back (line1);
            line1->setDependent(true);
            line2 = makeLineShape (1,0,0);
            shapes.emplace_back (line2);
            line2->setDependent(true);
        }
        virtual void adjust ();
};

class symmetricalOfSegment : public Construction {
    private:
        SegmentShape * const segment;
        LineShape *line;
    public:
        //symmetricalOfSegment (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : segment(el.segments[0]), line(NULL) {
        symmetricalOfSegment (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : segment(el.getVector<SegmentShape*>()[0]), line(NULL) {
            line = makeLineShape (1,0,0);
            shapes.emplace_back (line);
            line->setDependent(true);
        }
        virtual void adjust ();
};
class symmetricalOfPoints : public Construction {
    private:
        PointShape * const pointA, * const pointB;
        LineShape *line;
    public:
        //symmetricalOfPoints (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA(el.points[0]), pointB(el.points[1]), line(NULL) {
        symmetricalOfPoints (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) : pointA(el.getVector<PointShape*>()[0]), pointB(el.getVector<PointShape*>()[1]), line(NULL) {
            line = makeLineShape (1,0,0);
            shapes.emplace_back (line);
            line->setDependent(true);
        }
        virtual void adjust ();
};

//TODO: bisectors of two Lines
//TODO: described circle on triangle
//TODO: inscribed circle in triangle
//TODO: Orthocenter of triangle
//TODO: nine point circle
//TODO: Euler's line
//TODO: Symmedian
//TODO: Space transformations: HOMOTHETY, ROTATION, SYMMETRY about point/line, SHIFT, INVERSION, AFINIC

template <typename T>
//Construction *makeConstruction (const constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) {
Construction *makeConstruction (constructionElements& el, std::vector<std::unique_ptr<Shape> >& shapes) {
    T* newT = new T (el, shapes);
    if (newT == NULL) return NULL;
    newT->adjust();
    return newT;
}
