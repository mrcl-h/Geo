#pragma once
#include"geo.h"
#include"Input.h"
#include<unordered_map>
#include<memory>

//#include<SFML/Graphics.hpp>

class inputSfmlWrapper {
    private:
        //typedef std::unordered_map<sf::Keyboard::Key, inputManager::Key> maptype; //CHANGED
        typedef std::unordered_map<uint32_t, inputManager::Key> maptype;
        maptype mp;
        inputManager& manager;
    public:
        void onKeyEvent (sf::Event& event) {
            inputManager::action a; 
            if (event.type == sf::Event::KeyPressed) {
                a = inputManager::pressed;
            } else if (event.type == sf::Event::KeyReleased) {
                a = inputManager::released;
            }

            unsigned int mods = (event.key.alt?inputManager::altMod:0) |
                (event.key.control?inputManager::ctrlMod:0) |
                (event.key.shift?inputManager::shiftMod:0);
            
            maptype::const_iterator i = mp.find(event.key.code);
            if (i == mp.end()) {return;}
            inputManager::Key k = i->second;

            manager.onKey (k, a, mods);
            
        }
        inputSfmlWrapper (inputManager& _manager) :manager (_manager){
            mp[sf::Keyboard::A] = inputManager::Key::A;
            mp[sf::Keyboard::B] = inputManager::Key::B;
            mp[sf::Keyboard::C] = inputManager::Key::C;
            mp[sf::Keyboard::D] = inputManager::Key::D;
            mp[sf::Keyboard::E] = inputManager::Key::E;
            mp[sf::Keyboard::F] = inputManager::Key::F;
            mp[sf::Keyboard::G] = inputManager::Key::G;
            mp[sf::Keyboard::H] = inputManager::Key::H;
            mp[sf::Keyboard::I] = inputManager::Key::I;
            mp[sf::Keyboard::J] = inputManager::Key::J;
            mp[sf::Keyboard::K] = inputManager::Key::K;
            mp[sf::Keyboard::L] = inputManager::Key::L;
            mp[sf::Keyboard::M] = inputManager::Key::M;
            mp[sf::Keyboard::N] = inputManager::Key::N;
            mp[sf::Keyboard::O] = inputManager::Key::O;
            mp[sf::Keyboard::P] = inputManager::Key::P;
            mp[sf::Keyboard::Q] = inputManager::Key::Q;
            mp[sf::Keyboard::R] = inputManager::Key::R;
            mp[sf::Keyboard::S] = inputManager::Key::S;
            mp[sf::Keyboard::T] = inputManager::Key::T;
            mp[sf::Keyboard::U] = inputManager::Key::U;
            mp[sf::Keyboard::V] = inputManager::Key::V;
            mp[sf::Keyboard::W] = inputManager::Key::W;
            mp[sf::Keyboard::X] = inputManager::Key::X;
            mp[sf::Keyboard::Y] = inputManager::Key::Y;
            mp[sf::Keyboard::Z] = inputManager::Key::Z;
            mp[sf::Keyboard::Num0] = inputManager::Key::n0;
            mp[sf::Keyboard::Num1] = inputManager::Key::n1;
            mp[sf::Keyboard::Num2] = inputManager::Key::n2;
            mp[sf::Keyboard::Num3] = inputManager::Key::n3;
            mp[sf::Keyboard::Num4] = inputManager::Key::n4;
            mp[sf::Keyboard::Num5] = inputManager::Key::n5;
            mp[sf::Keyboard::Num6] = inputManager::Key::n6;
            mp[sf::Keyboard::Num7] = inputManager::Key::n7;
            mp[sf::Keyboard::Num8] = inputManager::Key::n8;
            mp[sf::Keyboard::Num9] = inputManager::Key::n9;
            mp[sf::Keyboard::Escape] = inputManager::Key::Escape;
            mp[sf::Keyboard::LControl] = inputManager::Key::LControl;
            mp[sf::Keyboard::LShift] = inputManager::Key::LShift;
            mp[sf::Keyboard::LAlt] = inputManager::Key::LAlt;
            mp[sf::Keyboard::RControl] = inputManager::Key::RControl;
            mp[sf::Keyboard::RShift] = inputManager::Key::RShift;
            mp[sf::Keyboard::RAlt] = inputManager::Key::RAlt;
            mp[sf::Keyboard::LBracket] = inputManager::Key::LBracket;
            mp[sf::Keyboard::RBracket] = inputManager::Key::RBracket;
            mp[sf::Keyboard::Semicolon] = inputManager::Key::Semicolon;
            mp[sf::Keyboard::Comma] = inputManager::Key::Comma;
            mp[sf::Keyboard::Period] = inputManager::Key::Period;
            mp[sf::Keyboard::Quote] = inputManager::Key::Quote;
            mp[sf::Keyboard::Slash] = inputManager::Key::Slash;
            mp[sf::Keyboard::Backslash] = inputManager::Key::Backslash;
            mp[sf::Keyboard::Tilde] = inputManager::Key::Tilde;
            mp[sf::Keyboard::Equal] = inputManager::Key::Equal;
            mp[sf::Keyboard::Hyphen] = inputManager::Key::Hyphen;
            mp[sf::Keyboard::Space] = inputManager::Key::Space;
            mp[sf::Keyboard::Enter] = inputManager::Key::Enter;
            mp[sf::Keyboard::Backspace] = inputManager::Key::Backspace;
            mp[sf::Keyboard::Tab] = inputManager::Key::Tab;
            mp[sf::Keyboard::Delete] = inputManager::Key::Delete;
            mp[sf::Keyboard::Add] = inputManager::Key::Add;
            mp[sf::Keyboard::Subtract] = inputManager::Key::Subtract;
            mp[sf::Keyboard::Multiply] = inputManager::Key::Multiply;
            mp[sf::Keyboard::Divide] = inputManager::Key::Divide;
            mp[sf::Keyboard::Left] = inputManager::Key::Left;
            mp[sf::Keyboard::Right] = inputManager::Key::Right;
            mp[sf::Keyboard::Up] = inputManager::Key::Up;
            mp[sf::Keyboard::Down] = inputManager::Key::Down;
            mp[sf::Keyboard::Numpad0] = inputManager::Key::n0;
            mp[sf::Keyboard::Numpad1] = inputManager::Key::n1;
            mp[sf::Keyboard::Numpad2] = inputManager::Key::n2;
            mp[sf::Keyboard::Numpad3] = inputManager::Key::n3;
            mp[sf::Keyboard::Numpad4] = inputManager::Key::n4;
            mp[sf::Keyboard::Numpad5] = inputManager::Key::n5;
            mp[sf::Keyboard::Numpad6] = inputManager::Key::n6;
            mp[sf::Keyboard::Numpad7] = inputManager::Key::n7;
            mp[sf::Keyboard::Numpad8] = inputManager::Key::n8;
            mp[sf::Keyboard::Numpad9] = inputManager::Key::n9;
            mp[sf::Keyboard::F1] = inputManager::Key::f1;
            mp[sf::Keyboard::F2] = inputManager::Key::f2;
            mp[sf::Keyboard::F3] = inputManager::Key::f3;
            mp[sf::Keyboard::F4] = inputManager::Key::f4;
            mp[sf::Keyboard::F5] = inputManager::Key::f5;
            mp[sf::Keyboard::F6] = inputManager::Key::f6;
            mp[sf::Keyboard::F7] = inputManager::Key::f7;
            mp[sf::Keyboard::F8] = inputManager::Key::f8;
            mp[sf::Keyboard::F9] = inputManager::Key::f9;
            mp[sf::Keyboard::F10] = inputManager::Key::f10;
            mp[sf::Keyboard::F11] = inputManager::Key::f11;
            mp[sf::Keyboard::F12] = inputManager::Key::f12;
        }
};


class Geoapp{

    private:
        struct uiObject {
            sf::Texture image;
            constructionMaker creator;
        };
        std::unordered_map<uint32_t, std::vector<uiObject> > uiPages;

        struct uiOptionConditions {
            uint8_t lineCount, pointCount, circleCount, segmentCount;
            void reset () {lineCount = pointCount = circleCount = segmentCount = 0;}
        };
        const uint32_t uiMapId (uiOptionConditions conditions) const {
            uint32_t mapId = conditions.segmentCount;
            mapId <<= 8;
            mapId += conditions.circleCount;
            mapId <<= 8;
            mapId += conditions.pointCount;
            mapId <<= 8;
            mapId += conditions.lineCount;
            return mapId;
        }

        inputManager inManager;
        inputSfmlWrapper inWrapper;

        double centerX, centerY, step=0.25;
        bool leftKeyDown=false, rightKeyDown=false, upKeyDown=false, downKeyDown=false;

        std::vector<std::unique_ptr<Shape> > shapes;
        std::vector<Shape*> hulledShapes;
        constructionElements hulledElements;

        std::vector<std::unique_ptr<Construction> > constructions;

        uiOptionConditions currentConditions;

        double uiBarrier;
        double scalingFactor=1;

        mutable sf::RenderWindow window;

        void loop();
        void update();
        void events(sf::Event);
        void UIhandling(Point);
        void drawUI() const;
        void drawObjects() const;
        void whenClick(double,double);
        void changeMode(sf::Event);


        int FTCO(Point) const; //find object closest to mouse
        int FTCP(Point) const; //find point closest to mouse
        int FTCL(Point) const; //find line closest to mouse
        int FTCS(Point) const; //find segment closest to mouse
        int FTCC(Point) const; //find circle closest to mouse
        int FTCT(Point) const; //find triangle closest to mouse

        void registerUiOption (uiObject obj, uiOptionConditions conditions) {
            uint32_t mapId = uiMapId (conditions);
            uiPages[mapId].push_back(obj);
        }

    public:
        template<typename T>
            void pushToShapes(T);

        void moveCamera (double x, double y) {
            centerX += x;
            centerY += y;
        }
        void setCamera (double x, double y) {
            centerX = x;
            centerY = y;
        }

        void moveHulledPoints (double x, double y) {
            for (auto i : hulledShapes) {
                if (i->what_is() == shapeTypeId<Point>::typeId && i->isDependent == false) {
                    Point *pt = static_cast<Point*> (i);
                    pt->x += x;
                    pt->y += y;
                }
            }
            for (auto& i : constructions) {
                i->adjust();
            }
        }
        enum mode {pointCreation = 1, selection = 2};

        //void pushToConstructions(Construction);
        std::unique_ptr<int> testPtr;
        Geoapp();
        ~Geoapp () {
            //for (auto i : shapes) { delete i; }
            //for (auto i : constructions) { delete i; }
        }

    private:
        mode currentMode = pointCreation;
    public:
        void setCurrentMode (mode m) {
            currentMode = m;
        }
};

//TODO
//move camera left
//move camera right
//move camera up
//move camera down
//
//move points left
//move points right
//move points up
//move points down
//

class inputCameraMovementState : public inputState {
    private:
        Geoapp* app;
        double x, y;
    public:
        inputCameraMovementState (inputManager* manager, Geoapp* _app, double _x, double _y) : inputState(manager), app(_app), x(_x), y(_y) {}
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
        inputPointMovementState (inputManager* manager, Geoapp* _app, double _x, double _y) : inputState (manager), app(_app), x(_x), y(_y) {}
        virtual void onEnter () override {
            app->moveHulledPoints(x,y);
            done();
        }
};

class inputPointSelectionState : public inputState {
    private:
        Geoapp* app;
    public:
        inputPointSelectionState (inputManager* manager, Geoapp* _app) :inputState(manager), app(_app) {}
        virtual void onEnter () override {
            app->setCurrentMode (Geoapp::mode::selection);
            done();
        }
};

class inputPointCreationState : public inputState {
    private:
        Geoapp* app;
    public:
        inputPointCreationState (inputManager* manager, Geoapp* _app) :inputState(manager), app(_app) {}
        virtual void onEnter () override {
            app->setCurrentMode (Geoapp::mode::pointCreation);
            done();
        }
};
