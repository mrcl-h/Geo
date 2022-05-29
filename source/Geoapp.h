#pragma once
#include"geo.h"
#include<unordered_map>

//#include<SFML/Graphics.hpp>

class Geoapp{

    struct uiObject {
        sf::Texture image;
        constructionMaker creator;
    };
    std::unordered_map<uint32_t, std::vector<uiObject> > uiPages;

    struct uiOptionConditions {
        uint8_t lineCount, pointCount, circleCount, segmentCount;
        void reset () {lineCount = pointCount = circleCount = segmentCount = 0;}
    };
    uint32_t uiMapId (uiOptionConditions conditions) {
        uint32_t mapId = conditions.segmentCount;
        mapId <<= 8;
        mapId += conditions.circleCount;
        mapId <<= 8;
        mapId += conditions.pointCount;
        mapId <<= 8;
        mapId += conditions.lineCount;
        return mapId;
    }

    double centerX, centerY, step=0.25;
    int mode=0;
    bool leftKeyDown=false, rightKeyDown=false, upKeyDown=false, downKeyDown=false;

    std::vector<Shape*> shapes;
    std::vector<Shape*> hulledShapes;
    constructionElements hulledElements;

    std::vector<Construction*> constructions;

    uiOptionConditions currentConditions;

    double uiBarrier;
    double scalingFactor=1;

    sf::RenderWindow window;

    void loop();
    void update();
    void events(sf::Event);
    void UIhandling(Point);
    void drawUI();
    void drawObjects();
    void whenClick(double,double);
    void changeMode(sf::Event);

    int FTCO(Point); //find object closest to mouse
    int FTCP(Point); //find point closest to mouse
    int FTCL(Point); //find line closest to mouse
    int FTCS(Point); //find segment closest to mouse
    int FTCC(Point); //find circle closest to mouse
    int FTCT(Point); //find triangle closest to mouse

    void registerUiOption (uiObject obj, uiOptionConditions conditions) {
        uint32_t mapId = uiMapId (conditions);
        uiPages[mapId].push_back(obj);
    }

public:
    template<typename T>
    void pushToShapes(T);

    //void pushToConstructions(Construction);
    Geoapp();
    ~Geoapp () {
        for (auto i : shapes) {
            delete i;
        }
        for (auto i : constructions) {
            delete i;
        }
    }
};
