#include <iostream>
#include "source/Geoapp.h"

int main () {
    Geoapp g;
}

/*
#include <iostream>
#include<vector>
#include"source/geo.h"


vector<Shape*> shapes;

template <typename T>
void func(T& a){
    Shape &S=a;
    shapes.push_back(&S);
}

void draw (sf::RenderWindow& window) {
        window.clear(sf::Color(255,255,255,255));
        for(unsigned int i=0;i<shapes.size();i++){
            shapes[i]->draw(&window);
        }
        window.display();
};

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(200,200), "GEO");

    Point A(20,20);
    Point B(50,50);
    Point C(20,50);
    Line l(C,B);
    Circle Omega(A,B,C);
    func(A);
    func(B);
    func(C);
    func(l);
    func(Omega);
    while (window.isOpen()){
        sf::Event event;
        window.waitEvent (event);
        if (event.type == sf::Event::Closed){
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed){
            double x=(double)sf::Mouse::getPosition(window).x, y=(double)sf::Mouse::getPosition(window).y;
            Point *mysz = new Point(x,y);
            Shape &S=*mysz;
            shapes.push_back(&S);
        } else if (event.type== sf::Event::Resized){

        }
        draw(window);
    }
    return 0;
}

*/