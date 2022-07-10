/* file with body of the program, class Geoapp responsible for the behaviour of the app
 * */
#pragma once
#include "geo.h"
#include "inputSFML.h"
#include <unordered_map>
#include <memory>
#include "Construction.h"
#include "drawers.h"
#include "uiOptions.h"

class geoWorld {
    private:
        std::vector<std::unique_ptr<Shape> > shapes;
        std::vector<Shape*> hulledShapes;

        std::vector<std::unique_ptr<Construction> > constructions;
        Shape* findObjectHit (const Point& p, float scalingFactor) const {
            Shape *shapeHit = NULL;
            for (auto& i : shapes) {
                if (i->isHit (p, scalingFactor)) {
                    if (shapeHit == NULL || shapeHit->getHitPriority() < i->getHitPriority()) {
                        shapeHit = i.get();
                    }
                }
            }
            return shapeHit;
        }
    public:
        void createConstruction (constructionMaker maker) {
            constructions.emplace_back (maker (hulledShapes, shapes));
            if (hulledShapes.size () > 0) {
                hulledShapes.back()->setCurrent (false);
            }
            for (auto& i : hulledShapes) {
                i->setActivity (false);
            }
            hulledShapes.clear();
        }
        void refreshConstructions () {
            for (auto& i : constructions) {
                i->adjust ();
            }
        }
        void visitShapes (ShapeVisitor * visitor) {
            for (auto& i : shapes) {
                i->acceptVisitor (visitor);
            }
        }
        void visitHulledShapes (ShapeVisitor * visitor) {
            for (auto& i : hulledShapes) {
                i->acceptVisitor (visitor);
            }
        }
        void addPoint (float x, float y) {
            shapes.emplace_back (makePointShape (x, y));
        }
        void selectClick (float x, float y, float scalingFactor, 
                ShapeVisitor * selectVisitor = NULL, ShapeVisitor * unselectVisitor = NULL) {
            Point clickPosition;
            clickPosition.x = x; clickPosition.y = y;
            Shape *hitShape = findObjectHit (clickPosition, scalingFactor);
            if(hitShape){
                if (hitShape->getActivity()) {
                    hitShape->setActivity (false);
                    hitShape->setCurrent (false);

                    hulledShapes.erase (std::find(hulledShapes.begin(), hulledShapes.end(), hitShape));

                    if (hulledShapes.size() > 0) {
                        hulledShapes.back()->setCurrent (true);
                    }

                    if (unselectVisitor) {
                        hitShape->acceptVisitor (unselectVisitor);
                    }
                } else {
                    hitShape->setActivity (true);

                    if (hulledShapes.size() > 0) {
                        hulledShapes.back()->setCurrent (false);
                    }

                    hulledShapes.push_back(hitShape);
                    hulledShapes.back()->setCurrent (true);

                    if (selectVisitor) {
                        hitShape->acceptVisitor (selectVisitor);
                    }
                }
            }
        }
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
        void changeScale (double rat) {
            scalingFactor *= rat;
        }
        void setBox (const floatRect& _box) {
            box = _box;
            sfmlDrawing.setBox (box);
        }
        void setSelectingMode () {
            selectingMode = true;
        }
        void setAddingMode () {
            selectingMode = false;
        }
        void click (float x, float y) {
            Point clickPosition;
            clickPosition.x = centerX+(x-box.width/2)*scalingFactor;
            clickPosition.y = centerY+(y-box.height/2)*scalingFactor;
            if (selectingMode) {
                uiOptionConditionsAdjusterShapeVisitor casv1;
                casv1.setTracker (&uiTracker);
                casv1.setCount (1);
                uiOptionConditionsAdjusterShapeVisitor casv2;
                casv2.setTracker (&uiTracker);
                casv2.setCount (-1);
                world->selectClick (clickPosition.x, clickPosition.y, scalingFactor, &casv1, &casv2);
            } else {
                world->addPoint (clickPosition.x, clickPosition.y);
            }
        }
        void startRightDragging (float x, float y) {
            beginDraggingX = x; beginDraggingY = y;
            oldCenterX = centerX; oldCenterY = centerY;
            isDragging = true;
        }
        void continueRightDragging (float x, float y) {
            if (!isDragging) return;
            float deltaX, deltaY;
            deltaX = (beginDraggingX - x)*scalingFactor;
            deltaY = (beginDraggingY - y)*scalingFactor;
            centerX = oldCenterX + deltaX;
            centerY = oldCenterY + deltaY;
        }
        void stopRightDragging () {
            isDragging = false;
        }
        void interruptDragging () {
            centerX = oldCenterX; centerY = oldCenterY;
            isDragging = false;
        }
        void draw () {
            floatRect visible (centerX - box.width/2*scalingFactor, centerY-box.height/2*scalingFactor,
                    box.width*scalingFactor, box.height*scalingFactor);
            sfmlDrawing.setVisible (visible);

            hullDrawingShapeVisitor hdv;
            hdv.setDrawer (&sfmlDrawing);
            world->visitHulledShapes (&hdv);

            drawingShapeVisitor dv;
            dv.setDrawer (&sfmlDrawing);
            world->visitShapes (&dv);
        }
};

class Geoapp{

    private:
        uiOptionTracker uiTracker;

        inputManager inManager;
        inputSfmlWrapper inWrapper;

        double centerX, centerY, step=0.25;
        bool leftKeyDown=false, rightKeyDown=false, upKeyDown=false, downKeyDown=false;

        std::unordered_map <char, Point> markMap;

        //std::vector<std::unique_ptr<Shape> > shapes;
        //std::vector<Shape*> hulledShapes;

        //std::vector<std::unique_ptr<Construction> > constructions;

        double uiBarrier;
        double scalingFactor=1;

        float uiTop = 0;

        //Point lastMouseRightPosition;
        //bool rightMoving;

        mutable sf::RenderWindow window;

        geoWorld world;
        geoView mainGeoView;

        //mutable sfmlDrawingClass sfmlDrawing;
        mutable svgDrawingClass svgDrawing;

        void loop();
        void drawApp();
        void events(const sf::Event&);
        void UIhandling(const Point& point);
        void drawUI() const;
        void drawObjects();
        void whenClick(double,double);
        void changeMode(sf::Event);

        float findUIScrollMin () const;

        //Shape* findObjectHit (const Point& p) const;

    public:
        const Point * getMark (char c) const;

        void setMark (char c, const Point& p);

        void moveCamera (double x, double y);
        void setCamera (double x, double y);
        void setCamera (const Point& p);
        const Point getCamera ();

        void changeScale (double rat);

        void scrollUI (double s);

        void resetUIPosition ();

        void moveHulledPoints (double x, double y);
        enum mode {pointCreation = 1, selection = 2};

        floatRect getVisible () {
            float windowWidth = getWindowWidth();
            float windowHeight = getWindowHeight();
            floatRect visible (centerX - uiBarrier*windowWidth/2*scalingFactor, centerY-windowHeight/2*scalingFactor,uiBarrier*windowWidth*scalingFactor,windowHeight*scalingFactor);
            return visible;
        }
        floatRect getBox () {
            float windowWidth = getWindowWidth();
            float windowHeight = getWindowHeight();
            floatRect box (0,0,windowWidth*uiBarrier,windowHeight);
            return box;
        }

        float getWindowWidth () const {
            return window.getSize().x;
        }
        float getWindowHeight () const {
            return window.getSize().y;
        }

        void drawShapes (drawingClass* drawer) {
            drawingShapeVisitor dv;
            dv.setDrawer (drawer);
            world.visitShapes (&dv);
            //for(unsigned int i=0;i<shapes.size();i++){
            //    if (shapes[i]->getExistance())
            //        shapes[i]->acceptVisitor (&dv);
            //}
        }

        std::unique_ptr<int> testPtr;
        Geoapp();
        ~Geoapp () {
        }

    private:
        mode currentMode = pointCreation;
    public:
        void setCurrentMode (mode m) {
            currentMode = m;
        }
};
