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
#include "geoWorld.h"
#include "marks.h"

class Geoapp{

    private:
        uiOptionTracker uiTracker;

        inputManager inManager;
        inputSfmlWrapper inWrapper;

        double centerX, centerY, step=0.25;
        bool leftKeyDown=false, rightKeyDown=false, upKeyDown=false, downKeyDown=false;

        charMarks marks;
        //std::unordered_map <char, Point> markMap;

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

        mutable sfmlDrawingClass sfmlDrawing;
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
        //const Point * getMark (char c) const;

        //void setMark (char c, const Point& p);

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
