#pragma once
#include "geo.h"



class drawingClass {
    public:
        virtual void setVisible (const floatRect& _visible) = 0;
        virtual void setBox (const floatRect& _box) = 0;
        virtual void setColor (unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255) = 0;
        virtual void drawPoint (const Point& p) = 0;
        virtual void drawSegment (const Point& from, const Point& to) = 0;
        virtual void drawCircle (const Point& center, const double radius) = 0;
        virtual void drawTriangle (const Point& a, const Point& b, const Point& c) = 0;
        virtual void drawLine (const double a, const double b, const double c) = 0;
};

class sfmlDrawingClass : public drawingClass {
    private:
        floatRect visible, box;
        sf::RenderWindow *window;
        sf::Color drawingColor;
    public:
        sfmlDrawingClass (sf::RenderWindow *_window) :window(_window) {}
        virtual void setVisible (const floatRect& _visible) override;
        virtual void setBox (const floatRect& _box) override;
        virtual void setColor (unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255) override;
        virtual void drawPoint (const Point& p) override;
        virtual void drawSegment (const Point& from, const Point& to) override;
        virtual void drawCircle (const Point& center, const double radius) override;
        virtual void drawTriangle (const Point& a, const Point& b, const Point& c) override;
        virtual void drawLine (const double a, const double b, const double c) override;
};
