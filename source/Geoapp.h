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

        charMarks marks;

        double uiBarrier;
        double scalingFactor=1;

        float uiTop = 0;

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

    public:
        void scrollUI (double s);

        void resetUIPosition ();

        void moveHulledPoints (double x, double y);

        float getWindowWidth () const {
            return window.getSize().x;
        }
        float getWindowHeight () const {
            return window.getSize().y;
        }

        Geoapp();
        ~Geoapp () { }
};
