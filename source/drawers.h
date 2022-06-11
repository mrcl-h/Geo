#include "geo.h"

class drawingClass {
    public:
        virtual void setVisible (const floatRect& _visible);
        virtual void setBox (const floatRect& _box);
        virtual void drawPoint (const Point& p);
        virtual void drawSegment (const Point& from, const Point& to);
        virtual void drawCircle (const Point& center, const double radius);
        virtual void drawTriangle (const Point& a, const Point& b, const Point& c);
};

class sfmlDrawingClass : public drawingClass {
    private:
        floatRect visible, box;
    public:
        virtual void setVisible (const floatRect& _visible) override;
        virtual void setBox (const floatRect& _box) override;
        virtual void drawPoint (const Point& p) override;
        virtual void drawSegment (const Point& from, const Point& to) override;
        virtual void drawCircle (const Point& center, const double radius) override;
        virtual void drawTriangle (const Point& a, const Point& b, const Point& c) override;
};

class shapeDrawer {
    private:
        drawingClass* drawingTool;
    public:
        void setDrawingTool (drawingClass* tool);
        void setVisible (const floatRect& visible);
        void setBox (const floatRect& box);
        void drawShape (PointShape* ps);
        void drawShape (SegmentShape* ss);
        void drawShape (LineShape* ls);
        void drawShape (CircleShape* cs);
        void drawShape (TriangleShape* ts);
};

void shapeDrawer::setDrawingTool (drawingClass* tool) {
    drawingTool = tool;
}
void shapeDrawer::setVisible (const floatRect& visible) {
    drawingTool->setVisible (visible);
}
void shapeDrawer::setBox (const floatRect& box) {
    drawingTool->setBox (box);
}
void shapeDrawer::drawShape (PointShape* ps) {
    Point p;
    p.x = ps->getX(); p.y = ps->getY();
    drawingTool->drawPoint (p);
}
void shapeDrawer::drawShape (SegmentShape* ss) {
    Point from, to;
    from.x = ss->getFromX(); from.y = ss->getFromY();
    to.x = ss->getToX(); to.y = ss->getToY();
    drawingTool->drawSegment (from, to);
}
void shapeDrawer::drawShape (CircleShape* cs) {
    Point center;
    center.x = cs->getMiddleX();
    center.y = cs->getMiddleY();
    drawingTool->drawCircle (center, cs->getR());
}

void shapeDrawer::drawShape (LineShape* ls) {
    //TODO
}

void shapeDrawer::drawShape (TriangleShape* ts) {
    Point a, b, c;
    a.x = ts->getAX(); a.y = ts->getAY();
    b.x = ts->getBX(); b.y = ts->getBY();
    c.x = ts->getCX(); c.y = ts->getCY();
    drawingTool->drawTriangle (a, b, c);
}

void sfmlDrawingClass::setVisible (const floatRect& _visible) {
    visible = _visible; 
}

void sfmlDrawingClass::setBox (const floatRect& _box) {
    box = _box;
}
void sfmlDrawingClass::drawSegment (const Point& from, const Point& to) {

}
void sfmlDrawingClass::drawCircle (const Point& center, const double radius) {

}
void sfmlDrawingClass::drawTriangle (const Point& a, const Point& b, const Point& c) {

}

