#include"geo.h"
//#include<SFML/Graphics.hpp>

class Geoapp{
    
    double centerX, centerY;

    int mode=0;

    vector<Shape*> shapes;

    vector<Shape*> hulledShapes;

    vector<Construction> constructions;

    //double height, width, uiwidth;
    double uiBarrier;

    double scalingFactor=1;

    //Point Of Left Up Corner
    Point PORUC();

    sf::RenderWindow window;

    void loop();

    void update();

    void events(sf::Event);

    void UIhandling(Point);

    void drawUI();

    void drawObjects();

    void whenClick(double,double);

    void changeMode(sf::Event);

    //finding objects that are the closest to mouse
    /*
    O-objects
    P-Points
    L-Line
    S-Segment
    C-Circle
    T-Triangles
    */
    int FTCO(Point);
    int FTCP(Point);
    int FTCL(Point);
    int FTCS(Point);
    int FTCC(Point);
    int FTCT(Point);

public:
    template<typename T>
    void pushToShapes(T);

    //void pushToConstructions(Construction);
    Geoapp();
    ~Geoapp () {
        for (auto i : shapes) {
            delete i;
        }
        for (auto i : hulledShapes) {
            delete i;
        }
    }
};
