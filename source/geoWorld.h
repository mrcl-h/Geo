#pragma once
#include "drawers.h"
#include "geo.h"
#include "uiOptions.h"

class geoWorld {
    private:
        std::vector<std::unique_ptr<Shape> > shapes;
        std::vector<Shape*> hulledShapes;

        std::vector<std::unique_ptr<Construction> > constructions;
        Shape* findObjectHit (const Point& p, float scalingFactor) const;
    public:
        void createConstruction (constructionMaker maker);
        void refreshConstructions ();
        void visitShapes (ShapeVisitor * visitor);
        void visitHulledShapes (ShapeVisitor * visitor);
        void addPoint (float x, float y);
        void selectClick (float x, float y, float scalingFactor, ShapeVisitor * selectVisitor = NULL, ShapeVisitor * unselectVisitor = NULL);
};

class geoView {
    private:
        Point lastMouseRightPosition;
        bool rightMoving;

        float centerX, centerY;

        double scalingFactor;

        sf::RenderWindow& window;

        sfmlDrawingClass sfmlDrawing;

        geoWorld * world;

        floatRect box;

        bool selectingMode;

        uiOptionTracker& uiTracker;

        float beginDraggingX, beginDraggingY;
        float oldCenterX, oldCenterY;
        bool isDragging;

    public:
        geoView (sf::RenderWindow& _window, geoWorld * _world, uiOptionTracker& _uiTracker) 
            : centerX (0), centerY (0), scalingFactor (1), window (_window), 
            sfmlDrawing (&window), world (_world), selectingMode (false), uiTracker (_uiTracker) {}
        void changeScale (double rat);
        void setBox (const floatRect& _box);
        void setSelectingMode ();
        void setAddingMode ();
        void click (float x, float y);
        void startRightDragging (float x, float y);
        void continueRightDragging (float x, float y);
        void stopRightDragging ();
        void interruptDragging ();
        void draw ();
};
