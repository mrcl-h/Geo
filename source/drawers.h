/* file responsible for drawing shapes
 * it is possible to draw shapes in different context, either on screen or to file
 * */
#pragma once
#include "geo.h"
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>

//interface for drawing shapes
class drawingClass {
    public:
        virtual void setVisible (const floatRect& _visible) = 0;
        virtual void setBox (const floatRect& _box) = 0;
        virtual void setColor (unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255) = 0;
        virtual void drawPoint (const Point& p) = 0;
        virtual void drawSegment (const Point& from, const Point& to) = 0;
        virtual void drawCircle (const Point& center, const double radius) = 0;
        virtual void drawTriangle (const Point& a, const Point& b, const Point& c) = 0;
        virtual void drawLine (const double a, const double b, const double c) = 0;

        virtual void drawHullPoint (const Point& p) {}
        virtual void drawHullSegment (const Point& from, const Point& to) {}
        virtual void drawHullCircle (const Point& center, const double radius) {}
        virtual void drawHullTriangle (const Point& a, const Point& b, const Point& c) {}
        virtual void drawHullLine (const double a, const double b, const double c) {}
};

//class for drawing shapes to svg file
class svgDrawingClass : public drawingClass {
    private:
        std::stringstream curStream;
        unsigned int currentR, currentG, currentB;
        floatRect visible, box;
    public:
        svgDrawingClass ();
        void startDrawing ();
        void endDrawing ();
        void saveToFile (const std::string& filename);
        virtual void setVisible (const floatRect& _visible) override;
        virtual void setBox (const floatRect& _box) override;
        virtual void setColor (unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255) override;
        virtual void drawPoint (const Point& p) override;
        virtual void drawSegment (const Point& from, const Point& to) override;
        virtual void drawCircle (const Point& center, const double radius) override;
        virtual void drawTriangle (const Point& a, const Point& b, const Point& c) override;
        virtual void drawLine (const double a, const double b, const double c) override;
};

//class for drawing shapes to sfml context
class sfmlDrawingClass : public drawingClass {
    private:
        floatRect visible, box;
        sf::RenderWindow *window;
        sf::Color drawingColor;
    public:
        sfmlDrawingClass (sf::RenderWindow *_window) :window(_window) {}
        virtual void setVisible (const floatRect& _visible) override;
        virtual void setBox (const floatRect& _box) override;
        virtual void setColor (unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255) override;
        virtual void drawPoint (const Point& p) override;
        virtual void drawSegment (const Point& from, const Point& to) override;
        virtual void drawCircle (const Point& center, const double radius) override;
        virtual void drawTriangle (const Point& a, const Point& b, const Point& c) override;
        virtual void drawLine (const double a, const double b, const double c) override;

        virtual void drawHullPoint (const Point& p) override;
        virtual void drawHullSegment (const Point& from, const Point& to) override;
        virtual void drawHullCircle (const Point& center, const double radius) override;
        virtual void drawHullTriangle (const Point& a, const Point& b, const Point& c) override;
        virtual void drawHullLine (const double a, const double b, const double c) override;
};

//shape visitor drawing shapes with chosen drawer
class drawingShapeVisitor : public ShapeVisitor {
    private:
        drawingClass * drawer;

        void setDrawerColorToShape (Shape* s) {
            color pointColor; 
            s->getPreferredColor(pointColor);
            drawer->setColor (pointColor.r, pointColor.g, pointColor.b, pointColor.a);
        }

    public:
        virtual ~drawingShapeVisitor () {}

        void setDrawer (drawingClass* _drawer) {
            drawer = _drawer;
        }

        virtual void visitSegment (SegmentShape* ss) {
            setDrawerColorToShape (ss);
            drawer->drawSegment (getSegmentFrom (*ss), getSegmentTo (*ss));
        }
        virtual void visitTriangle (TriangleShape* ts) {
            setDrawerColorToShape (ts);
            drawer->drawTriangle (getTrianglePointA (*ts), getTrianglePointB (*ts), getTrianglePointC (*ts));
        }
        virtual void visitLine (LineShape* ls) {
            setDrawerColorToShape (ls);
            drawer->drawLine (ls->getNormalX(), ls->getNormalY(), ls->getC());
        }
        virtual void visitCircle (CircleShape* cs) {
            setDrawerColorToShape (cs);
            drawer->drawCircle (getCircleCenter (*cs), cs->getR());
        }
        virtual void visitPoint (PointShape* ps) {
            setDrawerColorToShape (ps);
            drawer->drawPoint (getPointLocation (*ps));
        }
};

//shape visitor hull drawing shapes with chosen drawer
class hullDrawingShapeVisitor : public ShapeVisitor {
    private:
        drawingClass * drawer;

    public:
        virtual ~hullDrawingShapeVisitor () {}

        void setDrawer (drawingClass* _drawer) {
            drawer = _drawer;
        }
        virtual void visitSegment (SegmentShape* ss) {
            drawer->drawHullSegment (getSegmentFrom (*ss), getSegmentTo (*ss));
        }
        virtual void visitTriangle (TriangleShape* ts) {
            drawer->drawHullTriangle (getTrianglePointA (*ts), getTrianglePointB (*ts), getTrianglePointC (*ts));
        }
        virtual void visitLine (LineShape* ls) {
            drawer->drawHullLine (ls->getNormalX(), ls->getNormalY(), ls->getC());
        }
        virtual void visitCircle (CircleShape* cs) {
            drawer->drawHullCircle (getCircleCenter (*cs), cs->getR());
        }
        virtual void visitPoint (PointShape* ps) {
            drawer->drawHullPoint (getPointLocation (*ps));
        }
};
