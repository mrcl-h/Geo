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
    gv->setSelectingMode ();
    done();
}

inputPointSelectionState::inputPointSelectionState (inputManager* _manager, geoView* _gv) :inputState(_manager), gv(_gv) {}

void inputPointCreationState::onEnter () {
    gv->setAddingMode ();
    done();
}

inputPointCreationState::inputPointCreationState (inputManager* _manager, geoView* _gv) :inputState(_manager), gv(_gv) {}

void inputSetMarkState::onKey (inputManager::keyType k, inputManager::action a, unsigned int mods) {
    if (a != inputManager::pressed) return;
    char mk = inputManager::keyToChar(k);
    if (mk == 0) {
        done();
        return;
    }
    marks.setMark (mk, gv->getCamera());
    done();
}

inputSetMarkState::inputSetMarkState (inputManager* _manager, geoView * _gv, charMarks & _marks) : inputState(_manager), gv(_gv), marks(_marks) {}

void inputGoToMarkState::onKey (inputManager::keyType k, inputManager::action a, unsigned int mods) {
    if (a != inputManager::pressed) return;
    char mk = inputManager::keyToChar(k);
    if (mk == 0) {
        done();
        return;
    }
    if (marks.findMark (mk)) {
        gv->setCamera (marks.getFoundMark());
    }
    done();
}

inputGoToMarkState::inputGoToMarkState (inputManager* _manager, geoView * _gv, charMarks & _marks) : inputState(_manager), gv(_gv), marks(_marks) {}

void inputUIScrollState::onEnter () {
    app->scrollUI (scrollValue);
    done();
}

inputUIScrollState::inputUIScrollState (inputManager* _manager, Geoapp* _app, double _scrollValue) : inputState(_manager), app(_app), scrollValue (_scrollValue){}

void inputScalingState::onEnter () {
    gv->changeScale (scaleValue);
    done();
}

inputScalingState::inputScalingState (inputManager* _manager, geoView* _gv, double _scaleValue) : inputState (_manager), gv(_gv), scaleValue (_scaleValue) {}

void inputSaveState::onEnter () {
    drawingClass * oldDrawer = gv->setDrawer (drawer);
    gv->setRects();
    drawer->startDrawing();
    gv->draw ();
    gv->setDrawer (oldDrawer);
    drawer->endDrawing();
    drawer->saveToFile (filename);

}

inputSaveState::inputSaveState (inputManager* _manager, geoView * _gv, const std::string& _filename, svgDrawingClass* _drawer) :inputState (_manager), gv(_gv), filename(_filename), drawer(_drawer) {}
