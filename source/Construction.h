/* file responsible for creating different constructions
 * */
#pragma once
#include "geo.h"
#include "shapeManager.h"
#include <memory>

class shapeHolderBase {
    public:
        virtual void addPoint (PointShape* ps) = 0;
        virtual void addLine (LineShape* ls) = 0;
        virtual void addCircle (CircleShape* cs) = 0;
        virtual void addSegment (SegmentShape* ss) = 0;
        virtual void addTriangle (TriangleShape* ts) = 0;
};

template <unsigned int N>
class zeroEvader {
    public:
        enum {num = N};
};
template <>
class zeroEvader<0> {
    public:
        enum {num = 1};
};

template <unsigned int POINTCNT, unsigned int LINECNT = 0, unsigned int CIRCLECNT = 0, unsigned int SEGMENTCNT = 0, unsigned int TRIANGLECNT = 0>
class shapeHolder : public shapeHolderBase {
    private:
        PointShape* points [zeroEvader<POINTCNT>::num];
        unsigned int pointCount;
        LineShape* lines [zeroEvader<LINECNT>::num];
        unsigned int lineCount;
        CircleShape* circles [zeroEvader<CIRCLECNT>::num];
        unsigned int circleCount;
        SegmentShape* segments [zeroEvader<SEGMENTCNT>::num];
        unsigned int segmentCount;
        TriangleShape* triangles [zeroEvader<TRIANGLECNT>::num];
        unsigned int triangleCount;
    protected:
        PointShape* getPoint (int n) {return points[n];}
        LineShape* getLine (int n) {return lines[n];}
        CircleShape* getCircle (int n) {return circles[n];}
        SegmentShape* getSegment (int n) {return segments[n];}
        TriangleShape* getTriangle (int n) {return triangles[n];}
    public:
        shapeHolder<POINTCNT, LINECNT, CIRCLECNT, SEGMENTCNT, TRIANGLECNT>()
            : pointCount (0), lineCount (0), circleCount (0), segmentCount (0), triangleCount(0) {}
        virtual void addPoint (PointShape* ps) override;
        virtual void addLine (LineShape* ls) override;
        virtual void addCircle (CircleShape* cs) override;
        virtual void addSegment (SegmentShape* ss) override;
        virtual void addTriangle (TriangleShape* ts) override;
};

template <unsigned int POINTCNT, unsigned int LINECNT, unsigned int CIRCLECNT, unsigned int SEGMENTCNT, unsigned int TRIANGLECNT>
void shapeHolder<POINTCNT, LINECNT, CIRCLECNT, SEGMENTCNT, TRIANGLECNT>::addPoint (PointShape* ps) {
    points [pointCount++] = ps;
}
template <unsigned int POINTCNT, unsigned int LINECNT, unsigned int CIRCLECNT, unsigned int SEGMENTCNT, unsigned int TRIANGLECNT>
void shapeHolder<POINTCNT, LINECNT, CIRCLECNT, SEGMENTCNT, TRIANGLECNT>::addLine (LineShape* ls) {
    lines [lineCount++] = ls;
}
template <unsigned int POINTCNT, unsigned int LINECNT, unsigned int CIRCLECNT, unsigned int SEGMENTCNT, unsigned int TRIANGLECNT>
void shapeHolder<POINTCNT, LINECNT, CIRCLECNT, SEGMENTCNT, TRIANGLECNT>::addCircle (CircleShape* cs) {
    circles [circleCount++] = cs;
}
template <unsigned int POINTCNT, unsigned int LINECNT, unsigned int CIRCLECNT, unsigned int SEGMENTCNT, unsigned int TRIANGLECNT>
void shapeHolder<POINTCNT, LINECNT, CIRCLECNT, SEGMENTCNT, TRIANGLECNT>::addSegment (SegmentShape* ss) {
    segments [segmentCount++] = ss;
}
template <unsigned int POINTCNT, unsigned int LINECNT, unsigned int CIRCLECNT, unsigned int SEGMENTCNT, unsigned int TRIANGLECNT>
void shapeHolder<POINTCNT, LINECNT, CIRCLECNT, SEGMENTCNT, TRIANGLECNT>::addTriangle (TriangleShape* ts) {
    triangles [triangleCount++] = ts;
}

class shapeHolderAdderVisitor : public ShapeVisitor {
    private:
        shapeHolderBase * sh;
    public:
        virtual ~shapeHolderAdderVisitor () {}
        void setBase (shapeHolderBase * _sh) {
            sh = _sh;
        }
        virtual void visitSegment (SegmentShape* ss) override;
        virtual void visitTriangle (TriangleShape* ts) override;
        virtual void visitLine (LineShape* ls) override;
        virtual void visitCircle (CircleShape* cs) override;
        virtual void visitPoint (PointShape* ps) override;
};


class Construction {
    public:
        virtual ~Construction () {}
        virtual void adjust () {}
};

typedef Construction* (*constructionMaker)(shapeManager*);

//------------------------------------------------

class segmentMiddle : public Construction, public
shapeHolder <1, 0, 0, 1, 0> { //constructs middle point from segment
    private:
        PointShape *midPoint () { return getPoint (0); }
        const SegmentShape * segment () { return getSegment (0); }
    public:
        segmentMiddle (shapeManager * manager) {
            PointShape * mp = makePointShape ();
            mp->setDependent (true);
            addPoint (mp);
            manager->addShape (mp);
        }
        virtual void adjust ();
};

class pointsMiddle : public Construction, public
shapeHolder <3, 0, 0, 0, 0> { //constructs middle point from two points
    private:
        PointShape * midPoint () { return getPoint (0); }
        const PointShape * pointA () { return getPoint (1); }
        const PointShape * pointB () { return getPoint (2); }
    public:
        pointsMiddle (shapeManager * manager) {
            PointShape * mp = makePointShape ();
            mp->setDependent (true);
            addPoint (mp);
            manager->addShape (mp);
        }
        virtual void adjust ();
};

class orthogonalLine : public Construction, public
shapeHolder <1, 2, 0, 0, 0> { //constructs orthogonal line from line and a point
    private:
        LineShape * orthogonal () { return getLine (0); }
        const LineShape * line () { return getLine (1); }
        const PointShape * point () { return getPoint (0); }
    public:
        orthogonalLine (shapeManager * manager) {
            LineShape * ort = makeLineShape (1,0,0);
            ort->setDependent (true);
            addLine (ort);
            manager->addShape (ort);
        }
        virtual void adjust ();
};

class parallelLine : public Construction, public
shapeHolder <1, 2, 0, 0, 0> { //constructs parallel line from line and a point
    private:
        LineShape * parallel () { return getLine (0); }
        const LineShape * line () { return getLine (1); }
        const PointShape * point () { return getPoint (0); }
    public:
        parallelLine (shapeManager * manager) {
            LineShape * prl = makeLineShape (1,0,0);
            prl->setDependent (true);
            addLine (prl);
            manager->addShape(prl);
        }
        virtual void adjust ();
};

class lineThroughPoints : public Construction, public
shapeHolder <2, 1, 0, 0, 0> {
    private:
        LineShape * line () { return getLine (0); }
        const PointShape * pointA () { return getPoint (0); }
        const PointShape * pointB () { return getPoint (1); }
    public:
        lineThroughPoints (shapeManager * manager) {
            LineShape * ln = makeLineShape (1,0,0);
            ln->setDependent (true);
            addLine (ln);
            manager->addShape(ln);
        }
        virtual void adjust ();
};

class segmentFromPoints : public Construction, public
shapeHolder <2, 0, 0, 1, 0> {
    private:
        SegmentShape * segment () { return getSegment (0); }
        const PointShape * pointA () { return getPoint (0); }
        const PointShape * pointB () { return getPoint (1); }
    public:
        segmentFromPoints (shapeManager * manager) {
            SegmentShape * sg = makeSegmentShape ();
            sg->setDependent (true);
            addSegment (sg);
            manager->addShape(sg);
        }
        virtual void adjust ();
};

class circleWithCenter : public Construction, public
shapeHolder <2, 0, 1, 0, 0> {
    private:
        CircleShape * circle () { return getCircle (0); }
        const PointShape * center () { return getPoint (0); }
        const PointShape * point () { return getPoint (1); }
    public:
        circleWithCenter (shapeManager * manager) {
            CircleShape * cr = makeCircleShape (0,0,0);
            cr->setDependent (true);
            addCircle (cr);
            manager->addShape(cr);
        }
        virtual void adjust ();
};

class centerOfMass : public Construction, public
shapeHolder <4, 0, 0, 0, 0> {
    private:
        PointShape * center () { return getPoint (0); }
        const PointShape * pointA () { return getPoint (1); }
        const PointShape * pointB () { return getPoint (2); }
        const PointShape * pointC () { return getPoint (3); }
    public:
        centerOfMass (shapeManager * manager) {
            PointShape * cntr = makePointShape ();
            cntr->setDependent (true);
            addPoint (cntr);
            manager->addShape(cntr);
        }
        virtual void adjust ();
};

class bisectorThreePoints : public Construction, public
shapeHolder <3, 1, 0, 0, 0> {
    private:
        LineShape * line () { return getLine (0); }
        const PointShape * pointA () { return getPoint (0); }
        const PointShape * pointB () { return getPoint (1); }
        const PointShape * pointC () { return getPoint (2); }
    public:
        bisectorThreePoints (shapeManager * manager) {
            LineShape * bis = makeLineShape (1,0,0);
            bis->setDependent (true);
            addLine (bis);
            manager->addShape(bis);
        }
        virtual void adjust ();
};


class circleThreePoints : public Construction, public
shapeHolder <3, 0, 1, 0, 0> {
    private:
        CircleShape * circle () { return getCircle (0); }
        const PointShape * pointA () { return getPoint (0); }
        const PointShape * pointB () { return getPoint (1); }
        const PointShape * pointC () { return getPoint (2); }
    public:
        circleThreePoints (shapeManager * manager) {
            CircleShape * cir = makeCircleShape (0,0,0);
            cir->setDependent (true);
            addCircle (cir);
            manager->addShape(cir);
        }
        virtual void adjust ();
};

class circlesIntersection : public Construction, public
shapeHolder <2, 0, 2, 0, 0> {
    private:
        const CircleShape * circle1 () { return getCircle (0); }
        const CircleShape * circle2 () { return getCircle (1); }
        PointShape * pointA () { return getPoint (0); }
        PointShape * pointB () { return getPoint (1); }
    public:
        circlesIntersection (shapeManager * manager) {
            PointShape * pta = makePointShape ();
            pta->setDependent (true);
            PointShape * ptb = makePointShape ();
            ptb->setDependent (true);
            addPoint (pta);
            manager->addShape(pta);
            addPoint (ptb);
            manager->addShape(ptb);
        }
        virtual void adjust ();
};

class powerLine : public Construction, public
shapeHolder <0, 1, 2, 0, 0> {
    private:
        LineShape * power () { return getLine (0); }
        const CircleShape * circle1 () { return getCircle (0); }
        const CircleShape * circle2 () { return getCircle (1); }
    public:
        powerLine (shapeManager * manager) {
            LineShape * pwr = makeLineShape (1,0,0);
            pwr->setDependent (true);
            addLine (pwr);
            manager->addShape(pwr);
        }
        virtual void adjust ();
};

class lineCircleIntersection : public Construction, public
shapeHolder <2, 1, 1, 0, 0> {
    private:
        PointShape * pointA () { return getPoint (0); }
        PointShape * pointB () { return getPoint (1); }
        const CircleShape * circle () { return getCircle (0); }
        const LineShape * line () { return getLine (0); }
    public:
        lineCircleIntersection (shapeManager * manager) {
            PointShape * pta = makePointShape ();
            pta->setDependent (true);
            PointShape * ptb = makePointShape ();
            ptb->setDependent (true);
            addPoint (pta);
            manager->addShape(pta);
            addPoint (ptb);
            manager->addShape(ptb);
        }
        virtual void adjust ();
};

class tangentCirclePoint : public Construction, public
shapeHolder <1, 2, 1, 0, 0> {
    private:
        LineShape * line1 () { return getLine (0); }
        LineShape * line2 () { return getLine (1); }
        const PointShape * point () { return getPoint (0); }
        const CircleShape * circle () { return getCircle (0); }
    public:
        tangentCirclePoint (shapeManager * manager) {
            LineShape * ln1 = makeLineShape (1,0,0);
            ln1->setDependent (true);
            LineShape * ln2 = makeLineShape (1,0,0);
            ln2->setDependent (true);
            addLine (ln1);
            manager->addShape(ln1);
            addLine (ln2);
            manager->addShape(ln2);
        }
        virtual void adjust ();
};

class symmetricalOfSegment : public Construction, public
shapeHolder <0, 1, 0, 1, 0> {
    private:
        LineShape *line () { return getLine (0); }
        const SegmentShape * segment ()  { return getSegment (0); }
    public:
        symmetricalOfSegment (shapeManager * manager) {
            LineShape * sym = makeLineShape (1,0,0);
            sym->setDependent (true);
            addLine (sym);
            manager->addShape(sym);
        }
        virtual void adjust ();
};
class symmetricalOfPoints : public Construction, public
shapeHolder <2, 1, 0, 0, 0> {
    private:
        LineShape * line () { return getLine (0); }
        const PointShape * pointA () { return getPoint (0); }
        const PointShape * pointB () { return getPoint (1); }
    public:
        symmetricalOfPoints (shapeManager * manager) {
            LineShape * sym = makeLineShape (1,0,0);
            sym->setDependent (true);
            addLine (sym);
            manager->addShape(sym);
        }
        virtual void adjust ();
};

class lineConstraint : public Construction, public
shapeHolder <1, 1, 0, 0, 0> {
    private:
        const LineShape * line () {
            return getLine (0);
        }
        PointShape * point () {
            return getPoint (0);
        }
    public:
        lineConstraint (shapeManager * manager) {}
        virtual void adjust ();
};

class circleConstraint : public Construction, public
shapeHolder <1, 0, 1, 0, 0> {
    private:
        const CircleShape * circle () {
            return getCircle (0);
        }
        PointShape * point () {
            return getPoint (0);
        }
    public:
        circleConstraint (shapeManager * manager) {}
        virtual void adjust ();
};

class Triangle : public Construction, public
shapeHolder <3, 0, 0, 0, 1> {
    private:
        TriangleShape * triangle () { return getTriangle (0); }
        const PointShape * pointA () { return getPoint (0); }
        const PointShape * pointB () { return getPoint (1); }
        const PointShape * pointC () { return getPoint (2); }
    public:
        Triangle (shapeManager * manager) {
            TriangleShape * tri = makeTriangleShape (0,0,0,0,0,0);
            tri->setDependent (true);
            addTriangle (tri);
            manager->addShape(tri);
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
Construction *makeConstruction (shapeManager * manager) {
    T * newT = new T (manager);
    shapeHolderAdderVisitor hav;
    hav.setBase (newT);
    manager->visitHulledShapes (&hav);
    newT->adjust ();
    return newT;
    //T * newT = new T (shapes);
    //shapeHolderAdderVisitor hav;
    //hav.setBase (newT);
    //for (auto& i : hulledShapes) {
    //    i->acceptVisitor (&hav);
    //}
    //newT->adjust ();
    //return newT;
}
