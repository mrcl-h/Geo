/* file responsible for creating different constructions
 * */
#pragma once
#include <vector>
#include "geo.h"
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

typedef Construction* (*constructionMaker)(const std::vector<Shape*>&, std::vector<std::unique_ptr<Shape> >&);

//------------------------------------------------

class segmentMiddle : public Construction, public
shapeHolder <1, 0, 0, 1, 0> { //constructs middle point from segment
    private:
        PointShape *midPoint () { return getPoint (0); }
        const SegmentShape * segment () { return getSegment (0); }
    public:
        segmentMiddle (std::vector<std::unique_ptr<Shape> >& shapes) {
            PointShape * mp = makePointShape ();
            mp->setDependent (true);
            addPoint (mp);
            shapes.emplace_back (mp);
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
        pointsMiddle (std::vector<std::unique_ptr<Shape> >& shapes) {
            PointShape * mp = makePointShape ();
            mp->setDependent (true);
            addPoint (mp);
            shapes.emplace_back (mp);
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
        orthogonalLine (std::vector<std::unique_ptr<Shape> >& shapes) {
            LineShape * ort = makeLineShape (1,0,0);
            ort->setDependent (true);
            addLine (ort);
            shapes.emplace_back (ort);
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
        parallelLine (std::vector<std::unique_ptr<Shape> >& shapes) {
            LineShape * prl = makeLineShape (1,0,0);
            prl->setDependent (true);
            addLine (prl);
            shapes.emplace_back (prl);
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
        lineThroughPoints (std::vector<std::unique_ptr<Shape> >& shapes) {
            LineShape * ln = makeLineShape (1,0,0);
            ln->setDependent (true);
            addLine (ln);
            shapes.emplace_back (ln);
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
        segmentFromPoints (std::vector<std::unique_ptr<Shape> >& shapes) {
            SegmentShape * sg = makeSegmentShape ();
            sg->setDependent (true);
            addSegment (sg);
            shapes.emplace_back (sg);
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
        circleWithCenter (std::vector<std::unique_ptr<Shape> >& shapes) {
            CircleShape * cr = makeCircleShape (0,0,0);
            cr->setDependent (true);
            addCircle (cr);
            shapes.emplace_back (cr);
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
        centerOfMass (std::vector<std::unique_ptr<Shape> >& shapes) {
            PointShape * cntr = makePointShape ();
            cntr->setDependent (true);
            addPoint (cntr);
            shapes.emplace_back (cntr);
        }
        virtual void adjust ();
};

class bisectorThreePoints : public Construction, public
shapeHolder <3, 1, 0, 0, 0> {
    private:
        LineShape * line () { return getLine (0); }
        const PointShape * pointA () { return getPoint (0); }
        const PointShape * pointB () { return getPoint (2); }
        const PointShape * pointC () { return getPoint (3); }
    public:
        bisectorThreePoints (std::vector<std::unique_ptr<Shape> >& shapes) {
            LineShape * bis = makeLineShape (1,0,0);
            bis->setDependent (true);
            addLine (bis);
            shapes.emplace_back (bis);
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
        circleThreePoints (std::vector<std::unique_ptr<Shape> >& shapes) {
            CircleShape * cir = makeCircleShape (0,0,0);
            cir->setDependent (true);
            addCircle (cir);
            shapes.emplace_back (cir);
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
        circlesIntersection (std::vector<std::unique_ptr<Shape> >& shapes) {
            PointShape * pta = makePointShape ();
            pta->setDependent (true);
            PointShape * ptb = makePointShape ();
            ptb->setDependent (true);
            addPoint (pta);
            shapes.emplace_back (pta);
            addPoint (ptb);
            shapes.emplace_back (ptb);
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
        powerLine (std::vector<std::unique_ptr<Shape> >& shapes) {
            LineShape * pwr = makeLineShape (1,0,0);
            pwr->setDependent (true);
            addLine (pwr);
            shapes.emplace_back (pwr);
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
        lineCircleIntersection (std::vector<std::unique_ptr<Shape> >& shapes) {
            PointShape * pta = makePointShape ();
            pta->setDependent (true);
            PointShape * ptb = makePointShape ();
            ptb->setDependent (true);
            addPoint (pta);
            shapes.emplace_back (pta);
            addPoint (ptb);
            shapes.emplace_back (ptb);
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
        tangentCirclePoint (std::vector<std::unique_ptr<Shape> >& shapes) {
            LineShape * ln1 = makeLineShape (1,0,0);
            ln1->setDependent (true);
            LineShape * ln2 = makeLineShape (1,0,0);
            ln2->setDependent (true);
            addLine (ln1);
            shapes.emplace_back (ln1);
            addLine (ln2);
            shapes.emplace_back (ln2);
        }
        virtual void adjust ();
};

class symmetricalOfSegment : public Construction, public
shapeHolder <0, 1, 0, 1, 0> {
    private:
        LineShape *line () { return getLine (0); }
        const SegmentShape * segment ()  { return getSegment (0); }
    public:
        symmetricalOfSegment (std::vector<std::unique_ptr<Shape> >& shapes) {
            LineShape * sym = makeLineShape (1,0,0);
            sym->setDependent (true);
            addLine (sym);
            shapes.emplace_back (sym);
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
        symmetricalOfPoints (std::vector<std::unique_ptr<Shape> >& shapes) {
            LineShape * sym = makeLineShape (1,0,0);
            sym->setDependent (true);
            addLine (sym);
            shapes.emplace_back (sym);
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
        lineConstraint (std::vector<std::unique_ptr<Shape> >& shapes) {}
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
        circleConstraint (std::vector<std::unique_ptr<Shape> >& shapes) {}
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
        Triangle (std::vector<std::unique_ptr<Shape> >& shapes) {
            TriangleShape * tri = makeTriangleShape (0,0,0,0,0,0);
            tri->setDependent (true);
            addTriangle (tri);
            shapes.emplace_back (tri);
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
Construction *makeConstruction (const std::vector<Shape*>& hulledShapes, std::vector<std::unique_ptr<Shape> >& shapes) {
    T * newT = new T (shapes);
    shapeHolderAdderVisitor hav;
    hav.setBase (newT);
    for (auto& i : hulledShapes) {
        i->acceptVisitor (&hav);
    }
    newT->adjust ();
    return newT;
}
