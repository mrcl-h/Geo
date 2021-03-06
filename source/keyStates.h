/* file responsible for creating input states used by geoapp, for
 * example to move around or change states
 * */
#pragma once
#include "Geoapp.h"
#include "Input.h"
#include "marks.h"

class inputCameraMovementState : public inputState {
    private:
        geoView* gv;
        double x, y;
    public:
        inputCameraMovementState (inputManager* _manager, geoView * _gv, double _x, double _y);
        virtual void onEnter () override;
};

class inputPointMovementState : public inputState {
    private:
        geoWorld* world;
        double x, y;
    public:
        inputPointMovementState (inputManager* _manager, geoWorld * _world, double _x, double _y);
        virtual void onEnter () override;
};

class inputPointSelectionState : public inputState {
    private:
        geoView* gv;
    public:
        inputPointSelectionState (inputManager* _manager, geoView* _gv);
        virtual void onEnter () override;
};

class inputPointCreationState : public inputState {
    private:
        geoView* gv;
    public:
        inputPointCreationState (inputManager* _manager, geoView* _gv);
        virtual void onEnter () override;
};

class inputSetMarkState : public inputState {
    private:
        geoView* gv;
        charMarks& marks;
    public:
        inputSetMarkState (inputManager* _manager, geoView * _gv, charMarks& _marks);
        virtual void onKey (inputManager::keyType k, inputManager::action a, unsigned int mods) override;
};

class inputGoToMarkState : public inputState {
    private:
        geoView* gv;
        charMarks& marks;
    public:
        inputGoToMarkState (inputManager* _manager, geoView * _gv, charMarks& _marks);
        virtual void onKey (inputManager::keyType k, inputManager::action a, unsigned int mods) override;
};

class inputUIScrollState : public inputState {
    private:
        Geoapp* app;
        double scrollValue;
    public:
        inputUIScrollState (inputManager* _manager, Geoapp* _app, double _scrollValue);
        virtual void onEnter () override;
};

class inputScalingState : public inputState {
    private:
        geoView* gv;
        double scaleValue;
    public:
        inputScalingState (inputManager* _manager, geoView* _gv, double _scaleValue);
        virtual void onEnter () override;
};

class inputSaveState : public inputState {
    private:
        geoView* gv;
        const std::string filename;
        svgDrawingClass* drawer;
    public:
        inputSaveState (inputManager* _manager, geoView * _gv, const std::string& _filename, svgDrawingClass* _drawer);
        virtual void onEnter () override;
};
