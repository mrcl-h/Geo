#include "geoWorld.h"

Shape* geoWorld::findObjectHit (const Point& p, float scalingFactor) const {
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

void geoWorld::createConstruction (constructionMaker maker) {
    constructions.emplace_back (maker (hulledShapes, shapes));
    if (hulledShapes.size () > 0) {
        hulledShapes.back()->setCurrent (false);
    }
    for (auto& i : hulledShapes) {
        i->setActivity (false);
    }
    hulledShapes.clear();
}

void geoWorld::refreshConstructions () {
    for (auto& i : constructions) {
        i->adjust ();
    }
}

void geoWorld::visitShapes (ShapeVisitor * visitor) {
    for (auto& i : shapes) {
        i->acceptVisitor (visitor);
    }
}

void geoWorld::visitHulledShapes (ShapeVisitor * visitor) {
    for (auto& i : hulledShapes) {
        i->acceptVisitor (visitor);
    }
}

void geoWorld::addPoint (float x, float y) {
    shapes.emplace_back (makePointShape (x, y));
}

void geoWorld::selectClick (float x, float y, float scalingFactor, ShapeVisitor * selectVisitor, ShapeVisitor * unselectVisitor) {
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

void geoView::changeScale (double rat) {
    scalingFactor *= rat;
}

void geoView::setBox (const floatRect& _box) {
    box = _box;
    sfmlDrawing.setBox (box);
}

void geoView::setSelectingMode () {
    selectingMode = true;
}
void geoView::setAddingMode () {
    selectingMode = false;
}
void geoView::click (float x, float y) {
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
void geoView::startRightDragging (float x, float y) {
    beginDraggingX = x; beginDraggingY = y;
    oldCenterX = centerX; oldCenterY = centerY;
    isDragging = true;
}
void geoView::continueRightDragging (float x, float y) {
    if (!isDragging) return;
    float deltaX, deltaY;
    deltaX = (beginDraggingX - x)*scalingFactor;
    deltaY = (beginDraggingY - y)*scalingFactor;
    centerX = oldCenterX + deltaX;
    centerY = oldCenterY + deltaY;
}
void geoView::stopRightDragging () {
    isDragging = false;
}
void geoView::interruptDragging () {
    centerX = oldCenterX; centerY = oldCenterY;
    isDragging = false;
}
void geoView::draw () {
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
