#include <iostream>
#include<vector>
#include"geo.h"


vector<Shape*> shapes;
void func(auto a){
    Shape &S=a;
    shapes.push_back(&S);
}
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
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed){
                double x=(double)sf::Mouse::getPosition(window).x, y=(double)sf::Mouse::getPosition(window).y;
                Point *mysz = new Point(x,y);
                Shape &S=*mysz;
                shapes.push_back(&S);
            } else if (event.type== sf::Event::Resized){

            }
        }
        for(int i=0;i<shapes.size();i++){
            shapes[i]->draw(&window);
        }
        window.display();
        window.clear(sf::Color(255,255,255,255));
    }
    return 0;
}
