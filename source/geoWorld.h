#pragma once
#include "drawers.h"
#include "geo.h"
#include "uiOptions.h"
#include "shapeManager.h"

class geoWorld : public shapeManager {
    private:
        std::vector<std::unique_ptr<Shape> > shapes;
        std::vector<Shape*> hulledShapes;

        std::vector<std::unique_ptr<Construction> > constructions;
        Shape* findObjectHit (const Point& p, float scalingFactor) const;
    public:
        virtual void addShape (Shape * shape);
        virtual void visitShapes (ShapeVisitor * visitor);
        virtual void visitHulledShapes (ShapeVisitor * visitor);
        void createConstruction (constructionMaker maker);
        void refreshConstructions ();
        void addPoint (float x, float y);
        void selectClick (float x, float y, float scalingFactor, ShapeVisitor * selectVisitor = NULL, ShapeVisitor * unselectVisitor = NULL);
};

class geoView {
    private:
        Point lastMouseRightPosition;
        bool rightMoving;

        float centerX, centerY;

        double scalingFactor;

        //sf::RenderWindow& window;

        //sfmlDrawingClass sfmlDrawing;
        drawingClass * drawer;

        geoWorld * world;

        floatRect box;

        bool selectingMode;

        uiOptionTracker& uiTracker;

        float beginDraggingX, beginDraggingY;
        float oldCenterX, oldCenterY;
        bool isDragging;

    public:
        geoView (geoWorld * _world, uiOptionTracker& _uiTracker) 
            : centerX (0), centerY (0), scalingFactor (1), //window (_window), 
            //sfmlDrawing (&window), 
            world (_world), selectingMode (false), uiTracker (_uiTracker), isDragging(false) {}
        drawingClass * setDrawer (drawingClass * newDrawer);
        void changeScale (double rat);
        void moveCamera (double x, double y);
        void setCamera (double x, double y);
        void setCamera (const Point& p);
        const Point getCamera ();
        void setBox (const floatRect& _box);
        void setSelectingMode ();
        void setAddingMode ();
        void click (float x, float y);
        void startRightDragging (float x, float y);
        void continueRightDragging (float x, float y);
        void stopRightDragging ();
        void interruptDragging ();
        void setRects ();
        void draw ();
};
