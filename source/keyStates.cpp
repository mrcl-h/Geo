#include "keyStates.h"

void inputCameraMovementState::onEnter () {
    gv->moveCamera (x,y);
    done();
}

inputCameraMovementState::inputCameraMovementState (inputManager* _manager, geoView * _gv, double _x, double _y) : inputState(_manager), gv(_gv), x(_x), y(_y) {}

class shapeMovingVisitor : public ShapeVisitor {
    private:
        float x, y;
    public:
        void setMovement (float _x, float _y) {
            x = _x; y = _y;
        }
        virtual void visitSegment (SegmentShape* ss) {
            ss->moveShape (x,y);
        }
        virtual void visitTriangle (TriangleShape* ts) {
            ts->moveShape (x,y);
        }
        virtual void visitLine (LineShape* ls) {
            ls->moveShape (x,y);
        }
        virtual void visitCircle (CircleShape* cs) {
            cs->moveShape (x,y);
        }
        virtual void visitPoint (PointShape* ps) {
            ps->moveShape (x,y);
        }
};

void inputPointMovementState::onEnter () {
    //app->moveHulledPoints(x,y);
    //done();
    shapeMovingVisitor mv;
    mv.setMovement (x, y);
    world->visitHulledShapes (&mv);
    world->refreshConstructions ();

    done();
}

inputPointMovementState::inputPointMovementState (inputManager* _manager, geoWorld * _world, double _x, double _y) : inputState (_manager), world(_world), x(_x), y(_y) {}

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
