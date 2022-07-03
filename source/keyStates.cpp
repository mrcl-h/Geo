#include "keyStates.h"

void inputCameraMovementState::onEnter () {
    app->moveCamera (x,y);
    done();
}

inputCameraMovementState::inputCameraMovementState (inputManager* _manager, Geoapp* _app, double _x, double _y) : inputState(_manager), app(_app), x(_x), y(_y) {}

void inputPointMovementState::onEnter () {
    app->moveHulledPoints(x,y);
    done();
}

inputPointMovementState::inputPointMovementState (inputManager* _manager, Geoapp* _app, double _x, double _y) : inputState (_manager), app(_app), x(_x), y(_y) {}

void inputPointSelectionState::onEnter () {
    app->setCurrentMode (Geoapp::mode::selection);
    done();
}

inputPointSelectionState::inputPointSelectionState (inputManager* _manager, Geoapp* _app) :inputState(_manager), app(_app) {}

void inputPointCreationState::onEnter () {
    app->setCurrentMode (Geoapp::mode::pointCreation);
    done();
}

inputPointCreationState::inputPointCreationState (inputManager* _manager, Geoapp* _app) :inputState(_manager), app(_app) {}

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
    app->changeScale (scaleValue);
    done();
}

inputScalingState::inputScalingState (inputManager* _manager, Geoapp* _app, double _scaleValue) : inputState (_manager), app(_app), scaleValue (_scaleValue) {}

void inputSaveState::onEnter () {
    drawer->setVisible (app->getVisible());
    drawer->setBox (app->getBox());
    drawer->startDrawing();
    app->drawShapes (drawer);
    drawer->endDrawing();
    drawer->saveToFile (filename);
    done();
}

inputSaveState::inputSaveState (inputManager* _manager, Geoapp* _app, const std::string& _filename, svgDrawingClass* _drawer) :inputState (_manager), app(_app), filename(_filename), drawer(_drawer) {}
