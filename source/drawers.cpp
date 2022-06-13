#include "drawers.h"

void sfmlDrawingClass::setColor (unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    drawingColor = sf::Color (r,g,b,a); 
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
    shape.setFillColor (drawingColor);
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
    /*
    line[0].color=sf::Color(0,0,0);
    line[1].color=sf::Color(0,0,0);
    */
    line[0].color=drawingColor;
    line[1].color=drawingColor;
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
    shape.setOutlineColor(drawingColor);
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
    
    /*
    shape.setFillColor(sf::Color(255,0,0,125));
    */
    shape.setFillColor(drawingColor);
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
    lineColor = drawingColor;

    line[0].color = line[1].color = lineColor;

    window->draw(line, 2, sf::Lines);
}
