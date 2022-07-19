#include "keyStates.h"

void inputCameraMovementState::onEnter () {
    gv->moveCamera (x,y);
    done();
}

inputCameraMovementState::inputCameraMovementState (inputManager* _manager, geoView * _gv, double _x, double _y) : inputState(_manager), gv(_gv), x(_x), y(_y) {}

void inputPointMovementState::onEnter () {
    app->moveHulledPoints(x,y);
    done();
}

inputPointMovementState::inputPointMovementState (inputManager* _manager, Geoapp* _app, double _x, double _y) : inputState (_manager), app(_app), x(_x), y(_y) {}

void inputPointSelectionState::onEnter () {
    //app->setCurrentMode (Geoapp::mode::selection);
    gv->setSelectingMode ();
    done();
}

inputPointSelectionState::inputPointSelectionState (inputManager* _manager, geoView* _gv) :inputState(_manager), gv(_gv) {}

void inputPointCreationState::onEnter () {
    //app->setCurrentMode (Geoapp::mode::pointCreation);
    gv->setAddingMode ();
    done();
}

inputPointCreationState::inputPointCreationState (inputManager* _manager, geoView* _gv) :inputState(_manager), gv(_gv) {}

void inputSetMarkState::onKey (inputManager::keyType k, inputManager::action a, unsigned int mods) {
    if (a == inputManager::released) return;
    char mk = inputManager::keyToChar(k);
    if (mk == 0) {
        done();
        return;
    }
    app->setMark (mk,app->getCamera());
    done();
}

inputSetMarkState::inputSetMarkState (inputManager* _manager, Geoapp* _app) : inputState(_manager), app(_app) {}

void inputGoToMarkState::onKey (inputManager::keyType k, inputManager::action a, unsigned int mods) {
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

inputGoToMarkState::inputGoToMarkState (inputManager* _manager, Geoapp* _app) : inputState(_manager), app(_app) {}

void inputUIScrollState::onEnter () {
    app->scrollUI (scrollValue);
    done();
}

inputUIScrollState::inputUIScrollState (inputManager* _manager, Geoapp* _app, double _scrollValue) : inputState(_manager), app(_app), scrollValue (_scrollValue){}

void inputScalingState::onEnter () {
    //app->changeScale (scaleValue);
    gv->changeScale (scaleValue);
    done();
}

inputScalingState::inputScalingState (inputManager* _manager, geoView* _gv, double _scaleValue) : inputState (_manager), gv(_gv), scaleValue (_scaleValue) {}

void inputSaveState::onEnter () {
    //drawer->setVisible (app->getVisible());
    //drawer->setBox (app->getBox());
    //drawer->startDrawing();
    //app->drawShapes (drawer);
    //drawer->endDrawing();
    //drawer->saveToFile (filename);
    //done();
    drawingClass * oldDrawer = gv->setDrawer (drawer);
    gv->setRects();
    drawer->startDrawing();
    gv->draw ();
    gv->setDrawer (oldDrawer);
    drawer->endDrawing();
    drawer->saveToFile (filename);

}

inputSaveState::inputSaveState (inputManager* _manager, geoView * _gv, const std::string& _filename, svgDrawingClass* _drawer) :inputState (_manager), gv(_gv), filename(_filename), drawer(_drawer) {}
