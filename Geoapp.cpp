#include"Geoapp.h"
#include<SFML/Graphics.hpp>
using namespace std;


Geoapp::Geoapp(){
    height=300.0;
    width=300.0;
    uiwidth=200.0;
    window.create(sf::VideoMode(500, 300), "Geo");
    scalingFactor=1.0;
    loop();
}

void Geoapp::loop(){
    while (window.isOpen()){
        sf::Event event;
        events(event);
        update();

        window.display();
        window.clear(sf::Color(255,255,255,255));
    }
}

void Geoapp::events(sf::Event event){
    while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed){
                double x=(double)sf::Mouse::getPosition(window).x, y=(double)sf::Mouse::getPosition(window).y;
                Point *mysz = new Point(x,y);
                if(x>width){
                    UIhandling(*mysz);
                } else {
                    whenClick(x,y);
                }
            } else if (event.type== sf::Event::Resized){

            } else if(event.type == sf::Event::KeyPressed){
                changeMode(event);
            }
        }
}

void Geoapp::update(){
    drawObjects();
    drawUI();
}

void Geoapp::drawUI(){
    sf::RectangleShape rect(sf::Vector2f(uiwidth,height));
    rect.move(sf::Vector2f(300,0));
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(width, 0)),
        sf::Vertex(sf::Vector2f(width, height))
    };
    line[0].color=sf::Color(0,0,0);
    line[1].color=sf::Color(0,0,0);
    window.draw(line, 2, sf::Lines);
    window.draw(rect);
}

void Geoapp::drawObjects(){
    for(int i=0;i<hulledShapes.size();i++){
        hulledShapes[i]->hull_draw(&window);
    }
    for(int i=0;i<shapes.size();i++){
        shapes[i]->draw(&window);
    }
}

void Geoapp::UIhandling(Point mysz){

}

void Geoapp::whenClick(double x, double y){
    Point *mysz=new Point(x,y);
    if(mode==0){
        Shape &S=*mysz;
        shapes.push_back(&S);
        if(shapes.size()>1){
            if(shapes[shapes.size()-2]->what_is()=="Point"){
                Point* a=static_cast<Point*>(shapes[shapes.size()-2]);
                Line *l= new Line(*a,*mysz);
                Shape &L=*l;
                shapes.push_back(&L);
            }
        }
    } else if(mode==1){
        int a=FTCO(*mysz);
        cout<<a;
        if(a>-1){
            hulledShapes.push_back(shapes[a]);
        }
        /*Shape &s=shapes[a];
        if(findInObjects(&s)>-1){
            hulledShapes.erase(findInObjects(s));
        } else{
            hulledShapes.push_back(&s);
        }*/
    }

}

void Geoapp::changeMode(sf::Event e){
    if(e.key.code==sf::Keyboard::Q){
        mode=0;
    } else if(e.key.code==sf::Keyboard::W){
        mode=1;
    }
    //cout<<mode<<endl;
}



int Geoapp::FTCP(Point A){
    for(int i=0;i<shapes.size();i++){
        if((shapes[i]->what_is()=="Point")&&(shapes[i]->dist(A)<EPSILON)){
            return i;
        }
    }
    return -1;
}
int Geoapp::FTCL(Point A){
    for(int i=0;i<shapes.size();i++){
        if((shapes[i]->what_is()=="Line")&&(shapes[i]->dist(A)<EPSILON)){
            return i;
        }

    }
    return -1;
}
int Geoapp::FTCS(Point A){
    for(int i=0;i<shapes.size();i++){
        if((shapes[i]->what_is()=="Segment")&&(shapes[i]->dist(A)<EPSILON)){
            return i;
        }
    }
    return -1;
}
int Geoapp::FTCC(Point A){
    for(int i=0;i<shapes.size();i++){
        if((shapes[i]->what_is()=="Point")&&(shapes[i]->dist(A)<EPSILON)){
            return i;
        }
    }
    return -1;
}
int Geoapp::FTCT(Point A){
    return -1;
}

int Geoapp::FTCO(Point A){
    int temp=FTCP(A);
    if(temp>-1){
        return temp;
    }
    temp=FTCS(A);
    if(temp>-1){
        return temp;
    }
    temp=FTCL(A);
    if(temp>-1){
        return temp;
    }
    temp=FTCC(A);
    if(temp>-1){
        return temp;
    }
    return FTCT(A);
}
