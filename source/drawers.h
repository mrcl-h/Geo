#include "geo.h"

class drawingClass {
    public:
        virtual void setVisible (const floatRect& _visible);
        virtual void setBox (const floatRect& _box);
        virtual void drawPoint (const Point& p);
        virtual void drawSegment (const Point& from, const Point& to);
        virtual void drawCircle (const Point& center, const double radius);
        virtual void drawTriangle (const Point& a, const Point& b, const Point& c);
        virtual void drawLine (const double a, const double b, const double c);
};

class sfmlDrawingClass : public drawingClass {
    private:
        floatRect visible, box;
        sf::RenderWindow *window;
    public:
        sfmlDrawingClass (sf::RenderWindow *_window) :window(_window) {}
        virtual void setVisible (const floatRect& _visible) override;
        virtual void setBox (const floatRect& _box) override;
        virtual void drawPoint (const Point& p) override;
        virtual void drawSegment (const Point& from, const Point& to) override;
        virtual void drawCircle (const Point& center, const double radius) override;
        virtual void drawTriangle (const Point& a, const Point& b, const Point& c) override;
        virtual void drawLine (const double a, const double b, const double c) override;
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
    double nx, ny, c;
    nx = ls->getNormalX(); ny = ls->getNormalY();
    c = ls->getC();
    drawingTool->drawLine (nx, ny, c);
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

void sfmlDrawingClass::drawPoint (const Point& p) {
    
    const double radiusOfDrawing = 3;
    sf::CircleShape shape (radiusOfDrawing);
    float alpha = (p.x-visible.left)/visible.width;
    float beta = (p.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= radiusOfDrawing;
    v.y -= radiusOfDrawing;
    shape.setPosition(v);
    //shape.setFillColor (getShapeColor (isActive, isCurrent, isDependent));
    shape.setFillColor (sf::Color::Black);
    window->draw(shape);
}

void sfmlDrawingClass::drawSegment (const Point& from, const Point& to) {
    float tp1x = box.left + (from.x-visible.left)/visible.width*box.width;
    float tp2x = box.left + (to.x-visible.left)/visible.width*box.width;

    float tp1y = box.top + (from.y-visible.top)/visible.height*box.height;
    float tp2y = box.top + (to.y-visible.top)/visible.height*box.height;
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(tp1x, tp1y)),
        sf::Vertex(sf::Vector2f(tp2x, tp2y))
    };
    line[0].color=sf::Color(0,0,0);
    line[1].color=sf::Color(0,0,0);
    window->draw(line, 2, sf::Lines);

}
void sfmlDrawingClass::drawCircle (const Point& center, const double radius) {
    // i hope this works.
    sf::CircleShape shape (radius, 400);
    sf::Vector2f scaling;
    scaling.x = box.width/visible.width;
    scaling.y = box.height/visible.height;
    shape.scale (scaling);
    float alpha = (center.x-visible.left)/visible.width;
    float beta = (center.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= radius*scaling.x;
    v.y -= radius*scaling.y;
    shape.setPosition(v);
    shape.setOutlineColor(sf::Color(0,0,0,255));
    shape.setOutlineThickness(1/scaling.x);
    shape.setFillColor(sf::Color(255,255,255,0));
    //shape.setPointCount (400);
    window->draw(shape);

}
void sfmlDrawingClass::drawTriangle (const Point& a, const Point& b, const Point& c) {
    sf::ConvexShape shape(3);
    float alpha = (a.x-visible.left)/visible.width;
    float beta = (a.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    shape.setPoint(0, v);
    alpha = (b.x-visible.left)/visible.width;
    beta = (b.y-visible.top)/visible.height;
    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
    shape.setPoint(1, v);
    alpha = (c.x-visible.left)/visible.width;
    beta = (c.y-visible.top)/visible.height;
    v = sf::Vector2f(box.left + alpha*box.width, box.top + beta*box.height);
    shape.setPoint(2, v);
    
    shape.setFillColor(sf::Color(255,0,0,125));
    window->draw(shape);
}

void sfmlDrawingClass::drawLine (const double a, const double b, const double c) {

    sf::Vector2f from;
    sf::Vector2f to;

    unsigned int cond1 = (b+a)>=0;
    unsigned int cond2 = (b-a)<0;
    if (cond1^cond2) { //draw horizontally
        from.x = (box.left);
        from.y = box.top+box.height/visible.height*((-c-a*visible.left)/b-visible.top);


        to.x = (box.left+box.width);
        to.y = box.top+box.height/visible.height*((-c-a*(visible.left+visible.width))/b-visible.top);
    } else { //draw vertically
        from.y = (box.top);
        from.x = box.left+box.width/visible.width*((-c-b*visible.top)/a-visible.left);

        to.y = (box.top+box.height);
        to.x = box.left+box.width/visible.width*((-c-b*(visible.top+visible.height))/a-visible.left);
    }
    sf::Vertex line[] = { from, to };
    sf::Color lineColor;
    //if (isCurrent) {
    //    lineColor = sf::Color::Green;
    //} else if (isActive) {
    //    lineColor = sf::Color::Blue;
    //} else {
    //    lineColor = sf::Color::Black;
    //}
    lineColor = sf::Color::Black;

    line[0].color = line[1].color = lineColor;

    window->draw(line, 2, sf::Lines);
}
