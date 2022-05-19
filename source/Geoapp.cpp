#include"Geoapp.h"
#include<SFML/Graphics.hpp>
using namespace std;
constexpr double epsilon = 2;
constexpr int antialias = 4;

Geoapp::Geoapp(){
    //height=300.0;
    //width=300.0;
    //uiwidth=200.0;
    uiBarrier = 0.6;
    sf::ContextSettings settings;
    settings.antialiasingLevel = antialias;
    window.create(sf::VideoMode(500, 300), "Geo", sf::Style::Default, settings);
    scalingFactor=1.0;
    centerX = centerY = 0;
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
                if(x>uiBarrier*window.getSize().x){
                    UIhandling(*mysz);
                } else {
                    whenClick(x,y);
                }
            } else if (event.type== sf::Event::Resized){

            } else if(event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Left) {
                    centerX -= 10; 
                } else if (event.key.code == sf::Keyboard::Right) {
                    centerX += 10;
                } else if (event.key.code == sf::Keyboard::Up) {
                    centerY -= 10;
                } else if (event.key.code == sf::Keyboard::Down) {
                    centerY += 10;
                }
                changeMode(event);
            }
        }
}

void Geoapp::update(){
    drawObjects();
    drawUI();
}

void Geoapp::drawUI(){
    unsigned int windowWidth = window.getSize().x, windowHeight = window.getSize().y;
    window.setView (sf::View(sf::FloatRect(0,0,windowWidth, windowHeight)));
    sf::RectangleShape rect (sf::Vector2f(windowWidth*(1-uiBarrier),windowHeight));
    rect.move(sf::Vector2f(windowWidth*uiBarrier,0));
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(windowWidth*uiBarrier, 0)),
        sf::Vertex(sf::Vector2f(windowWidth*uiBarrier, windowHeight))
    };
    line[0].color=sf::Color(0,0,0);
    line[1].color=sf::Color(0,0,0);
    rect.setFillColor (sf::Color(0,255,255));
    window.draw(rect);
    window.draw(line, 2, sf::Lines);
}

void Geoapp::drawObjects(){
    float windowWidth = window.getSize().x, windowHeight = window.getSize().y;
    sf::FloatRect visible (centerX - uiBarrier*windowWidth/2, centerY-windowHeight/2,uiBarrier*windowWidth,windowHeight);
    sf::FloatRect box (0,0,window.getSize().x*uiBarrier,window.getSize().y);
    for(unsigned int i=0;i<hulledShapes.size();i++){
        hulledShapes[i]->hull_draw(&window, visible, box);
    }
    for(unsigned int i=0;i<shapes.size();i++){
        shapes[i]->draw(&window, visible, box);
    }
}

void Geoapp::UIhandling(Point mysz){

}

void Geoapp::whenClick(double x, double y){
    Point *mysz=new Point(centerX+x-float(window.getSize().x*uiBarrier)/2,centerY+y-float(window.getSize().y)/2);
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
    for(unsigned int i=0;i<shapes.size();i++){
        if((shapes[i]->what_is()=="Point")&&(shapes[i]->dist(A)<epsilon)){
            return i;
        }
    }
    return -1;
}
int Geoapp::FTCL(Point A){
    for(unsigned int i=0;i<shapes.size();i++){
        if((shapes[i]->what_is()=="Line")&&(shapes[i]->dist(A)<epsilon)){
            return i;
        }

    }
    return -1;
}
int Geoapp::FTCS(Point A){
    for(unsigned int i=0;i<shapes.size();i++){
        if((shapes[i]->what_is()=="Segment")&&(shapes[i]->dist(A)<epsilon)){
            return i;
        }
    }
    return -1;
}
int Geoapp::FTCC(Point A){
    for(unsigned int i=0;i<shapes.size();i++){
        if((shapes[i]->what_is()=="Point")&&(shapes[i]->dist(A)<epsilon)){
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
