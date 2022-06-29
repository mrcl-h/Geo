#include "drawers.h"
#include <iomanip>

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

void sfmlDrawingClass::drawHullPoint (const Point& p) {
    const double radiusOfDrawing = 3;
    sf::CircleShape shape (2*radiusOfDrawing);
    float alpha = (p.x-visible.left)/visible.width;
    float beta = (p.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= 2*radiusOfDrawing;
    v.y -= 2*radiusOfDrawing;
    shape.setPosition(v);
    shape.setFillColor(sf::Color(0,0,0,100));

    window->draw(shape);
}
void sfmlDrawingClass::drawHullSegment (const Point& from, const Point& to) {
}
void sfmlDrawingClass::drawHullCircle (const Point& center, const double radius) {
    float scaling = box.width/visible.width;
    sf::CircleShape shape (radius*scaling-2, 400);
    float alpha = (center.x-visible.left)/visible.width;
    float beta = (center.y-visible.top)/visible.height;
    sf::Vector2f v(box.left + alpha*box.width, box.top + beta*box.height);
    v.x -= radius*scaling-2;
    v.y -= radius*scaling-2;
    shape.setPosition(v);
    shape.setOutlineColor(sf::Color(0,0,0,128));
    shape.setOutlineThickness(5);
    shape.setFillColor(sf::Color(255,255,255,0));
    //shape.setPointCount (400);
    window->draw(shape);
}
void sfmlDrawingClass::drawHullTriangle (const Point& a, const Point& b, const Point& c) {
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
    
    shape.setFillColor(sf::Color(0,255,255,40));
    window->draw(shape);
}
void sfmlDrawingClass::drawHullLine (const double a, const double b, const double c) {
}

void svgDrawingClass::startDrawing () {
    curStream << ""
        "<svg\n"
        "   width= \"" << visible.width << "\"\n"
        "   height= \"" << visible.height << "\">\n"
        "  <g>\n";
}
void svgDrawingClass::endDrawing () {
    curStream << ""
        "  </g>\n"
        "</svg>";
}
void svgDrawingClass::saveToFile (const std::string& filename) {
    std::ofstream of (filename);
    of << curStream.rdbuf();
    of.close();
}

svgDrawingClass::svgDrawingClass() {}

void svgDrawingClass::setVisible (const floatRect& _visible) {
    visible = _visible;
}
void svgDrawingClass::setBox (const floatRect& _box) {
    box = _box;
}
void svgDrawingClass::setColor (unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    currentR = r;
    currentG = g;
    currentB = b;
}
void svgDrawingClass::drawPoint (const Point& p) {
    const double radiusOfDrawing = 3;
    float alpha = (p.x-visible.left)/visible.width;
    float beta = (p.y-visible.top)/visible.height;
    float vx = box.left + alpha*box.width;
    float vy = box.top + beta*box.height;
    curStream << std::hex << ""
    "    <circle\n"
    "       style=\""
    "fill:#" <<
    std::setw (2) << std::setfill ('0') << currentR <<
    std::setw (2) << std::setfill ('0') << currentG <<
    std::setw (2) << std::setfill ('0') << currentB << ";"
    "stroke:none;"
    "stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stop-color:#000000\"\n"
    << std::dec << ""
    "       cx=\"" << vx << "\"\n"
    "       cy=\"" << vy << "\"\n"
    "       r=\"" << radiusOfDrawing << "\" />\n";
}
void svgDrawingClass::drawSegment (const Point& from, const Point& to) {
    float tp1x = box.left + (from.x-visible.left)/visible.width*box.width;
    float tp2x = box.left + (to.x-visible.left)/visible.width*box.width;

    float tp1y = box.top + (from.y-visible.top)/visible.height*box.height;
    float tp2y = box.top + (to.y-visible.top)/visible.height*box.height;
    curStream << std::hex << ""
    "    <path\n"
    "       style=\""
    "fill:none;"
    "stroke:#" <<
    std::setw (2) << std::setfill ('0') << currentR <<
    std::setw (2) << std::setfill ('0') << currentG <<
    std::setw (2) << std::setfill ('0') << currentB << ";"
    "stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stop-color:#000000\"\n"
    << std::dec << ""
    "       d=\"M " << tp1x << "," << tp1y << " " << tp2x << " " << tp2y << "\"/>\n";

}
void svgDrawingClass::drawCircle (const Point& center, const double radius) {
    double cx, cy, rx, ry;
    rx = radius * box.width / visible.width;
    ry = radius * box.height / visible.height;
    float alpha = (center.x-visible.left)/visible.width;
    float beta = (center.y-visible.top)/visible.height;
    cx = box.left + alpha*box.width;
    cy = box.top + beta*box.height;
    curStream << std::hex << ""
        "    <ellipse\n"
        "       style=\""
        "fill:none;"
        "stroke:#" <<
        std::setw (2) << std::setfill ('0') << currentR <<
        std::setw (2) << std::setfill ('0') << currentG <<
        std::setw (2) << std::setfill ('0') << currentB << ";"
        "stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stop-color:#000000\"\n"
    << std::dec << ""
    "       cx=\"" << cx << "\"\n"
    "       cy=\"" << cy << "\"\n"
    "       rx=\"" << rx << "\"\n"
    "       ry=\"" << ry << "\" />\n";
}
void svgDrawingClass::drawTriangle (const Point& a, const Point& b, const Point& c) {

}
void svgDrawingClass::drawLine (const double a, const double b, const double c) {
    double fromX, fromY, toX, toY;

    unsigned int cond1 = (b+a)>=0;
    unsigned int cond2 = (b-a)<0;
    if (cond1^cond2) { //draw horizontally
        fromX = (box.left);
        fromY = box.top+box.height/visible.height*((-c-a*visible.left)/b-visible.top);


        toX = (box.left+box.width);
        toY = box.top+box.height/visible.height*((-c-a*(visible.left+visible.width))/b-visible.top);
    } else { //draw vertically
        fromY = (box.top);
        fromX = box.left+box.width/visible.width*((-c-b*visible.top)/a-visible.left);

        toY = (box.top+box.height);
        toX = box.left+box.width/visible.width*((-c-b*(visible.top+visible.height))/a-visible.left);
    }

    curStream << std::hex << ""
    "    <path\n"
    "       style=\""
    "fill:none;"
    "stroke:#" <<
    std::setw (2) << std::setfill ('0') << currentR <<
    std::setw (2) << std::setfill ('0') << currentG <<
    std::setw (2) << std::setfill ('0') << currentB << ";"
    "stroke-width:1;stroke-linecap:round;stroke-linejoin:round;stop-color:#000000\"\n"
    << std::dec << ""
    "       d=\"M " << fromX << "," << fromY << " " << toX << " " << toY << "\"/>\n";

}
