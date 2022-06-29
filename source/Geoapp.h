#pragma once
#include"geo.h"
//#include"Input.h"
#include"inputSFML.h"
#include<unordered_map>
#include<memory>
#include "Construction.h"
#include "drawers.h"

struct uiOptionConditions {
    uint8_t lineCount, pointCount, circleCount, segmentCount, triangleCount;
};

void resetUiOptionConditions (uiOptionConditions& op);

class uiOptionConditionsAdjusterShapeVisitor : public ShapeVisitor {
    private: 
        uiOptionConditions* conditions;
        int count;
    public:
        virtual ~uiOptionConditionsAdjusterShapeVisitor () {}
        void setConditions (uiOptionConditions* _conditions) {
            conditions = _conditions;
        }
        void setCount (int _count) {
            count = _count;
        }
        virtual void visitSegment (SegmentShape*) {
            conditions->segmentCount += count;
        }
        virtual void visitTriangle (TriangleShape*) {
            conditions->triangleCount += count;
        }
        virtual void visitLine (LineShape*) {
            conditions->lineCount += count;
        }
        virtual void visitCircle (CircleShape*) {
            conditions->circleCount += count;
        }
        virtual void visitPoint (PointShape*) {
            conditions->pointCount += count;
        }
};

class Geoapp{

    private:
        struct uiObject {
            sf::Texture image;
            constructionMaker creator;
        };


        std::unordered_map<uint32_t, std::vector<uiObject> > uiPages;

        uint32_t uiMapId (const uiOptionConditions& conditions) const;

        inputManager inManager;
        inputSfmlWrapper inWrapper;

        double centerX, centerY, step=0.25;
        bool leftKeyDown=false, rightKeyDown=false, upKeyDown=false, downKeyDown=false;

        struct point {
            double x, y;
        };

        std::unordered_map <char, Point> markMap;


        std::vector<std::unique_ptr<Shape> > shapes;
        std::vector<Shape*> hulledShapes;
        constructionElements hulledElements;

        std::vector<std::unique_ptr<Construction> > constructions;

        uiOptionConditions currentConditions;

        double uiBarrier;
        double scalingFactor=1;

        float uiTop = 0;

        Point lastMouseRightPosition;
        bool rightMoving;

        mutable sf::RenderWindow window;

        mutable sfmlDrawingClass sfmlDrawing;
        mutable svgDrawingClass svgDrawing;

        void loop();
        void update();
        void events(sf::Event);
        void UIhandling(const Point& point);
        void drawUI() const;
        void drawObjects() const;
        void whenClick(double,double);
        void changeMode(sf::Event);

        float findUIScrollMin () const;

        Shape* findObjectHit (const Point& p) const;

        void registerUiOption (uiObject obj, uiOptionConditions conditions);

        //TODO somehow move this classes outside geoapp
        class uiPointObject {
            private:
                unsigned int count;
            public:
                explicit uiPointObject (unsigned int _count) :count(_count) {}
                void pushToConditions (uiOptionConditions& op) const {
                    op.pointCount += count;
                }
        };
        class uiLineObject {
            private:
                unsigned int count;
            public:
                explicit uiLineObject (unsigned int _count) :count(_count) {}
                void pushToConditions (uiOptionConditions& op) const {
                    op.lineCount += count;
                }
        };
        class uiSegmentObject {
            private:
                unsigned int count;
            public:
                explicit uiSegmentObject (unsigned int _count) :count(_count) {}
                void pushToConditions (uiOptionConditions& op) const {
                    op.segmentCount += count;
                }
        };
        class uiCircleObject {
            private:
                unsigned int count;
            public:
                explicit uiCircleObject (unsigned int _count) :count(_count) {}
                void pushToConditions (uiOptionConditions& op) const {
                    op.circleCount += count;
                }
        };

        template <typename U, typename... T>
        void setUpCondition (uiOptionConditions& op, const U& obj, const T&... rest) {
            obj.pushToConditions(op);
            setUpCondition (op, rest...);
        }
        void setUpCondition (uiOptionConditions& op) {}

        template <typename U, typename... T>
        void makeOption (const char* fileName, const T&... con) {
            uiObject obj; 
            obj.creator = makeConstruction<U>;
            obj.image.loadFromFile (fileName);
            obj.image.setSmooth (true);
            uiOptionConditions opCond;
            resetUiOptionConditions (opCond);
            setUpCondition (opCond, con...);
            registerUiOption (obj, opCond);
        }

    public:
        template<typename T>
            void pushToShapes(T);

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

        void drawShapes (drawingClass* drawer) const {
            drawingShapeVisitor dv;
            dv.setDrawer (drawer);
            for(unsigned int i=0;i<shapes.size();i++){
                if (shapes[i]->getExistance())
                    shapes[i]->acceptVisitor (&dv);
            }
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


class inputCameraMovementState : public inputState {
    private:
        Geoapp* app;
        double x, y;
    public:
        inputCameraMovementState (inputManager* _manager, Geoapp* _app, double _x, double _y) : inputState(_manager), app(_app), x(_x), y(_y) {}
        virtual void onEnter () override {
            app->moveCamera (x,y);
            done();
        }
};

class inputPointMovementState : public inputState {
    private:
        Geoapp* app;
        double x, y;
    public:
        inputPointMovementState (inputManager* _manager, Geoapp* _app, double _x, double _y) : inputState (_manager), app(_app), x(_x), y(_y) {}
        virtual void onEnter () override {
            app->moveHulledPoints(x,y);
            done();
        }
};

class inputPointSelectionState : public inputState {
    private:
        Geoapp* app;
    public:
        inputPointSelectionState (inputManager* _manager, Geoapp* _app) :inputState(_manager), app(_app) {}
        virtual void onEnter () override {
            app->setCurrentMode (Geoapp::mode::selection);
            done();
        }
};

class inputPointCreationState : public inputState {
    private:
        Geoapp* app;
    public:
        inputPointCreationState (inputManager* _manager, Geoapp* _app) :inputState(_manager), app(_app) {}
        virtual void onEnter () override {
            app->setCurrentMode (Geoapp::mode::pointCreation);
            done();
        }
};

class inputSetMarkState : public inputState {
    private:
        Geoapp* app;
    public:
        inputSetMarkState (inputManager* _manager, Geoapp* _app) : inputState(_manager), app(_app) {}
        virtual void onKey (inputManager::keyType k, inputManager::action a, unsigned int mods){
            if (a == inputManager::released) return;
            char mk = inputManager::keyToChar(k);
            if (mk == 0) {
                done();
                return;
            }
            app->setMark (mk,app->getCamera());
            done();
        }
};

class inputGoToMarkState : public inputState {
    private:
        Geoapp* app;
    public:
        inputGoToMarkState (inputManager* _manager, Geoapp* _app) : inputState(_manager), app(_app) {}
        virtual void onKey (inputManager::keyType k, inputManager::action a, unsigned int mods){
            if (a == inputManager::released) return;
            char mk = inputManager::keyToChar(k);
            if (mk == 0) {
                done();
                return;
            }
            const Point * const pptr = app->getMark (mk);
            if (pptr != NULL) {
                app->setCamera (*pptr);
            }
            done();
        }
};

class inputUIScrollState : public inputState {
    private:
        Geoapp* app;
        double scrollValue;
    public:
        inputUIScrollState (inputManager* _manager, Geoapp* _app, double _scrollValue) : inputState(_manager), app(_app), scrollValue (_scrollValue){}
        virtual void onEnter () override {
            app->scrollUI (scrollValue);
            done();
        }
};

class inputScalingState : public inputState {
    private:
        Geoapp* app;
        double scaleValue;
    public:
        inputScalingState (inputManager* _manager, Geoapp* _app, double _scaleValue) : inputState (_manager), app(_app), scaleValue (_scaleValue) {}
        virtual void onEnter () override {
            app->changeScale (scaleValue);
            done();
        }
};

class inputSaveState : public inputState {
    private:
        Geoapp* app;
        const std::string filename;
        svgDrawingClass* drawer;
    public:
        inputSaveState (inputManager* _manager, Geoapp* _app, const std::string& _filename, svgDrawingClass* _drawer) :inputState (_manager), app(_app), filename(_filename), drawer(_drawer) {}
        virtual void onEnter () override {
            drawer->setVisible (app->getVisible());
            drawer->setBox (app->getBox());
            drawer->startDrawing();
            app->drawShapes (drawer);
            drawer->endDrawing();
            drawer->saveToFile (filename);
            done();
        }
};
