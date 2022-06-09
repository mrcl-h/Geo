#include"Geoapp.h"
#include<SFML/Graphics.hpp>

constexpr double epsilon = 2;
constexpr int antialias = 4;

Geoapp::Geoapp() : inManager (), inWrapper (inManager), testPtr (new int){
    uiBarrier = 0.6;
    sf::ContextSettings settings;
    settings.antialiasingLevel = antialias;
    window.create(sf::VideoMode(500, 300), "Geo", sf::Style::Default, settings);
    scalingFactor=1.0;
    centerX = centerY = 0;
    resetUiOptionConditions (currentConditions);
    uiPages[uiMapId(currentConditions)];
    //resetConstructionElements (hulledElements);
    hulledElements.clear();
    rightMoving = false;

    makeOption<segmentMiddle> ("resources/segmentMid.png", uiSegmentObject (1));
    makeOption<pointsMiddle> ("resources/pointsMid.png", uiPointObject (2));
    makeOption<parallelLine> ("resources/parallelLine.png", uiLineObject (1), uiPointObject (1));
    makeOption<orthogonalLine> ("resources/orthogonalLine.png", uiLineObject (1), uiPointObject (1));
    makeOption<lineThroughPoints> ("resources/lineThroughPoints.png", uiPointObject (2));
    makeOption<circleWithCenter> ("resources/circleWithCenter.png", uiPointObject (2));
    makeOption<segmentFromPoints> ("resources/segmentFromPoints.png", uiPointObject (2));
    makeOption<centerOfMass> ("resources/centerOfMass.png", uiPointObject (3));
    makeOption<circleThreePoints> ("resources/circleThreePoints.png", uiPointObject (3));
    makeOption<powerLine> ("resources/powerLine.png", uiCircleObject (2));
    makeOption<symmetricalOfPoints> ("resources/symmetricalOfPoints.png", uiPointObject (2));
    makeOption<symmetricalOfSegment> ("resources/symmetricalOfSegment.png", uiSegmentObject (1));
    makeOption<lineCircleIntersection> ("resources/lineCircleIntersection.png", uiLineObject(1), uiCircleObject(1));
    makeOption<circlesIntersection> ("resources/circleCircleIntersection.png", uiCircleObject (2));
    makeOption<bisectorThreePoints> ("resources/bisectorThreePoints.png", uiPointObject (3));
    makeOption<tangentCirclePoint> ("resources/tangentsThroughPoint.png", uiPointObject(1), uiCircleObject(1));
    makeOption<Triangle> ("resources/segmentMid.png", uiPointObject (3));

    junctionInputState *mainState = new junctionInputState (&inManager);
    mainState->addState (inputManager::Key::Left,   new inputCameraMovementState (&inManager, this, -10,   0));
    mainState->addState (inputManager::Key::Right,  new inputCameraMovementState (&inManager, this,  10,   0));
    mainState->addState (inputManager::Key::Up,     new inputCameraMovementState (&inManager, this,   0, -10));
    mainState->addState (inputManager::Key::Down,   new inputCameraMovementState (&inManager, this,   0,  10));

    mainState->addState (inputManager::Key::Left,   new inputCameraMovementState (&inManager, this, -100,   0), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::Right,  new inputCameraMovementState (&inManager, this,  100,   0), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::Up,     new inputCameraMovementState (&inManager, this,   0, -100), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::Down,   new inputCameraMovementState (&inManager, this,   0,  100), inputManager::ctrlMod);

    mainState->addState (inputManager::Key::H, new inputPointMovementState (&inManager, this, -10,   0));
    mainState->addState (inputManager::Key::J, new inputPointMovementState (&inManager, this,   0,  10));
    mainState->addState (inputManager::Key::K, new inputPointMovementState (&inManager, this,   0, -10));
    mainState->addState (inputManager::Key::L, new inputPointMovementState (&inManager, this,  10,   0));

    mainState->addState (inputManager::Key::H, new inputPointMovementState (&inManager, this, -100,   0), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::J, new inputPointMovementState (&inManager, this,   0,  100), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::K, new inputPointMovementState (&inManager, this,   0, -100), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::L, new inputPointMovementState (&inManager, this,  100,   0), inputManager::ctrlMod);

    mainState->addState (inputManager::Key::Q, new inputPointCreationState  (&inManager, this));
    mainState->addState (inputManager::Key::W, new inputPointSelectionState (&inManager, this));

    mainState->addState (inputManager::Key::M,      new inputSetMarkState  (&inManager, this));
    mainState->addState (inputManager::Key::Quote,  new inputGoToMarkState (&inManager, this));

    mainState->addState (inputManager::Key::U, new inputUIScrollState (&inManager, this,  10));
    mainState->addState (inputManager::Key::D, new inputUIScrollState (&inManager, this, -10));

    mainState->addState (inputManager::Key::Hyphen, new inputScalingState (&inManager, this, 2));
    mainState->addState (inputManager::Key::Equal, new inputScalingState (&inManager, this, 0.5), inputManager::shiftMod);

    inManager.setMainState (mainState);
    inManager.goToMainState();

    loop();
}

void Geoapp::changeScale (double rat) {
    scalingFactor *= rat;
}

float Geoapp::findUIScrollMin () const {
    unsigned int windowWidth = window.getSize().x, windowHeight = window.getSize().y;
    float uiWidth = windowWidth*(1-uiBarrier);
    std::unordered_map<uint32_t, std::vector<uiObject> >::const_iterator it;
    it = uiPages.find(uiMapId (currentConditions));
    if (it == uiPages.end()) return 0;
    float objectHeight = uiWidth/2;
    return -(objectHeight*it->second.size()-windowHeight);
}

uint32_t Geoapp::uiMapId (const uiOptionConditions& conditions) const {
    uint32_t mapId = conditions.segmentCount;
    mapId <<= 8;
    mapId += conditions.circleCount;
    mapId <<= 8;
    mapId += conditions.pointCount;
    mapId <<= 8;
    mapId += conditions.lineCount;
    return mapId;
}

//Shape* Geoapp::findObjectHit (const Point& p) const {
//    Shape *shapeHit = NULL;
//    /*for (auto& i : shapes) {
//        if (i->isHit (p)) {
//            if (shapeHit == NULL || shapeHit->getHitPriority() < i->getHitPriority()) {
//                shapeHit = i.get();
//            }
//        }
//    }
//    */
//    //TODO 4th step
//    for (auto& i : shapes.getVector<std::unique_ptr<PointShape> >()) { if (i->isHit (p)) { if (shapeHit == NULL || shapeHit->getHitPriority() < i->getHitPriority()) { shapeHit = i.get(); } } }
//    for (auto& i : shapes.getVector<std::unique_ptr<LineShape> >()) { if (i->isHit (p)) { if (shapeHit == NULL || shapeHit->getHitPriority() < i->getHitPriority()) { shapeHit = i.get(); } } }
//    for (auto& i : shapes.getVector<std::unique_ptr<SegmentShape> >()) { if (i->isHit (p)) { if (shapeHit == NULL || shapeHit->getHitPriority() < i->getHitPriority()) { shapeHit = i.get(); } } }
//    for (auto& i : shapes.getVector<std::unique_ptr<CircleShape> >()) { if (i->isHit (p)) { if (shapeHit == NULL || shapeHit->getHitPriority() < i->getHitPriority()) { shapeHit = i.get(); } } }
//    for (auto& i : shapes.getVector<std::unique_ptr<TriangleShape> >()) { if (i->isHit (p)) { if (shapeHit == NULL || shapeHit->getHitPriority() < i->getHitPriority()) { shapeHit = i.get(); } } }
//    return shapeHit;
//}

void Geoapp::registerUiOption (uiObject obj, uiOptionConditions conditions) {
    uint32_t mapId = uiMapId (conditions);
    uiPages[mapId].push_back(obj);
}

const Point * Geoapp::getMark (char c) const {
    decltype(markMap)::const_iterator it = markMap.find (c);
    if (it == markMap.end()) { return NULL; }
    return &it->second;
}

void Geoapp::setMark (char c, const Point& p) {
    markMap[c] = p;
}

void Geoapp::moveCamera (double x, double y) {
    centerX += x;
    centerY += y;
}
void Geoapp::setCamera (const Point& p) {
    centerX = p.x;
    centerY = p.y;
}
const Point Geoapp::getCamera () {
    Point camera;
    camera.x = centerX;
    camera.y = centerY;
    return camera;
}

void Geoapp::scrollUI (double s) {
    uiTop += s;
    float min = findUIScrollMin();
    if (uiTop > 0 || min > 0) {
        uiTop = 0;
        return;
    }
    if (uiTop < min) {
        uiTop = min; 
    }
}

void Geoapp::resetUIPosition () {
    uiTop = 0;
}

class hulledPointsMover {
    private:
        double x, y;
    public:
        hulledPointsMover (double _x, double _y) :x (_x), y(_y) {}
        template <typename T>
            void act (T& thing) {}
        void act (std::unique_ptr<PointShape>& ptr) {
            if (ptr->getActivity()) {
                ptr->moveShape (x, y);
            }
        }
};

void Geoapp::moveHulledPoints (double x, double y) {
    hulledPointsMover m (x, y);
    shapes.execute (m);
    for (auto& i : constructions) {
        i->adjust();
    }
}

//void Geoapp::moveHulledPoints (double x, double y) {
//    for (auto& i : hulledShapes) {
//        i->moveShape (x,y);
//    }
//    for (auto& i : constructions) {
//        i->adjust();
//    }
//}

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
            Point mysz;
            //mysz.x = sf::Mouse::getPosition(window).x; mysz.y=sf::Mouse::getPosition(window).y;
            mysz.x = event.mouseButton.x; mysz.y = event.mouseButton.y;
            if(mysz.x>uiBarrier*window.getSize().x){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    UIhandling(mysz);
                }
            } else {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    whenClick(mysz.x,mysz.y);
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    lastMouseRightPosition = mysz;
                    rightMoving = true;
                }
            }
        } else if (event.type == sf::Event::MouseButtonReleased){

            if (event.mouseButton.button == sf::Mouse::Right) {
                rightMoving = false;
            }

        } else if (event.type== sf::Event::Resized){
            resetUIPosition();
        } else if(event.type == sf::Event::KeyPressed){
            inWrapper.onKeyEvent (event);
        } else if(event.type == sf::Event::KeyReleased){
            inWrapper.onKeyEvent (event);
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                if (event.mouseWheelScroll.x > uiBarrier*window.getSize().x) {
                    scrollUI (10*event.mouseWheelScroll.delta);
                } else {
                    scalingFactor *= (1.25-event.mouseWheelScroll.delta*0.75);
                }
            }
        }
    }
    if (rightMoving) {
        Point mysz;
        mysz.x = sf::Mouse::getPosition(window).x; mysz.y=sf::Mouse::getPosition(window).y;
        centerX -= (mysz.x-lastMouseRightPosition.x)*scalingFactor;
        centerY -= (mysz.y-lastMouseRightPosition.y)*scalingFactor;

        lastMouseRightPosition = mysz;
    }
}

void Geoapp::update(){
    drawObjects();
    drawUI();
    /*
    if (leftKeyDown) {
        centerX -= step;
    }
    if (rightKeyDown) {
        centerX += step;
    }
    if (upKeyDown) {
        centerY -= step;
    }
    if (downKeyDown) {
        centerY += step;
    }
    */
}

void Geoapp::drawUI() const {
    unsigned int windowWidth = window.getSize().x, windowHeight = window.getSize().y;

    float uiWidth = windowWidth*(1-uiBarrier);
    float uiLeft = windowWidth * uiBarrier;

    window.setView (sf::View(sf::FloatRect(0,0,windowWidth, windowHeight)));
    sf::RectangleShape rect (sf::Vector2f(uiWidth,windowHeight));
    rect.move(sf::Vector2f(uiLeft,0));
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(uiLeft, 0)),
        sf::Vertex(sf::Vector2f(uiLeft, windowHeight))
    };
    line[0].color=sf::Color(0,0,0);
    line[1].color=sf::Color(0,0,0);
    rect.setFillColor (sf::Color(0,255,255));
    window.draw(rect);
    window.draw(line, 2, sf::Lines);

    const std::vector<uiObject>& currentObjects = uiPages.find(uiMapId (currentConditions))->second;
    float objectHeight = uiWidth/2;

    sf::Sprite currentIcon;
    currentIcon.setPosition (uiLeft+uiWidth*0.3, uiTop+objectHeight*0.1);

    sf::Vector2f leftSeparator (uiLeft, uiTop+objectHeight);
    sf::Vector2f rightSeparator (windowWidth, uiTop+objectHeight);
    for (auto& i : currentObjects) {
        currentIcon.setTexture (i.image);
        float texWidth = i.image.getSize().x, texHeight = i.image.getSize().y;
        currentIcon.setScale (objectHeight*0.8/texWidth, objectHeight*0.8/texHeight);
        window.draw (currentIcon);
        sf::Vertex separator [] = { sf::Vertex (leftSeparator), sf::Vertex (rightSeparator) };
        separator[0].color=sf::Color(0,0,0);
        separator[1].color=sf::Color(0,0,0);
        window.draw (separator, 2, sf::Lines);

        leftSeparator.y += objectHeight;
        rightSeparator.y += objectHeight;
        currentIcon.move(0,objectHeight);
    }
}

class hulledDrawer {
    private:
//        void hull_draw(sf::RenderWindow*, const sf::FloatRect& visible, const sf::FloatRect& box) const {}
        sf::RenderWindow& window;
        const sf::FloatRect visible; 
        const sf::FloatRect box;
    public:
        hulledDrawer (sf::RenderWindow& _window, const sf::FloatRect& _visible, const sf::FloatRect& _box) :window (_window), visible (_visible), box(_box) {}
        template <typename T>
            void act (T& thing) const {
                thing->hull_draw (&window, visible, box);
            }
};

void Geoapp::drawObjects() const{
    float windowWidth = window.getSize().x, windowHeight = window.getSize().y;
    sf::FloatRect visible (centerX - uiBarrier*windowWidth/2*scalingFactor, centerY-windowHeight/2*scalingFactor,uiBarrier*windowWidth*scalingFactor,windowHeight*scalingFactor);
    sf::FloatRect box (0,0,windowWidth*uiBarrier,windowHeight);

    //for(unsigned int i=0;i<hulledShapes.size();i++){
    //    hulledShapes[i]->hull_draw(&window, visible, box);
    //}

    hulledDrawer hd (window, visible, box);
    hulledElements.execute (hd);

    //for(unsigned int i=0;i<shapes.size();i++){
    //    if (shapes[i]->getExistance())
    //        shapes[i]->draw(&window, visible, box);
    //}
    for(auto& i : shapes.getVector<std::unique_ptr<PointShape> >()){
        if (i->getExistance())
            i->draw(&window, visible, box);
    }
    for(auto& i : shapes.getVector<std::unique_ptr<CircleShape> >()){
        if (i->getExistance())
            i->draw(&window, visible, box);
    }
    for(auto& i : shapes.getVector<std::unique_ptr<LineShape> >()){
        if (i->getExistance())
            i->draw(&window, visible, box);
    }
    for(auto& i : shapes.getVector<std::unique_ptr<SegmentShape> >()){
        if (i->getExistance())
            i->draw(&window, visible, box);
    }
    for(auto& i : shapes.getVector<std::unique_ptr<TriangleShape> >()){
        if (i->getExistance())
            i->draw(&window, visible, box);
    }
}

class inactiveSetter {
    public:
        template <typename T>
            void act (T& thing) {
                thing->setActivity(false); 
            }
};

void Geoapp::UIhandling(const Point& mysz){
    unsigned int windowWidth = window.getSize().x;
    float uiWidth = windowWidth*(1-uiBarrier);
    float top = 0;
    float objectHeight = uiWidth/2;
    if (mysz.y < uiTop) {
        return;
    }
    unsigned int clickedOption = (mysz.y-uiTop)/objectHeight;
    std::vector<uiObject>& currentPage = uiPages[uiMapId (currentConditions)];
    if (clickedOption >= currentPage.size()) {
        return;
    }
    Construction *constructionMade = currentPage[clickedOption].creator (hulledElements, shapes);
    constructions.emplace_back (constructionMade);

    //if (hulledShapes.size() > 0) {
    //    hulledShapes.back()->setCurrent (false);
    //}
    //for (auto i : hulledShapes) {
    //    i->setActivity (false);
    //}
    //hulledShapes.clear();
    resetUIPosition();
    resetUiOptionConditions (currentConditions);
    //resetConstructionElements (hulledElements);
    
    inactiveSetter is;
    hulledElements.execute (is);

    hulledElements.clear();


}

/*
class hulledPointsMover {
    private:
        double x, y;
    public:
        hulledPointsMover (double _x, double _y) :x (_x), y(_y) {}
        template <typename T>
            void act (T& thing) {}
        void act (std::unique_ptr<PointShape>& ptr) {
            ptr->moveShape (x, y);
        }
};
*/

class objectSelecter {
    private:
        const Point clickPosition;
        constructionElements & hulledElements;
        uiOptionConditions & currentConditions;
    public:
        objectSelecter (const Point& _clickPosition, constructionElements& _hulledElements, uiOptionConditions& _currentConditions) :clickPosition (_clickPosition), hulledElements (_hulledElements), currentConditions (_currentConditions) {}
        template <typename T>
            bool act (T& thing) {
                if (thing->isHit (clickPosition)) {
                    if (thing->getActivity()) {

                        thing->setActivity(false); 
                        thing->removeFromConstructionElements (hulledElements);
                        thing->addToCurrentConditions (currentConditions, -1);

                    } else {

                        thing->setActivity(true); 
                        thing->addToConstructionElements (hulledElements);
                        thing->addToCurrentConditions (currentConditions, 1);

                    }
                    return true;
                } 
                return false;
            }
};

void Geoapp::whenClick(double x, double y){
    Point clickPosition;
    clickPosition.x = centerX+(x-float(window.getSize().x*uiBarrier)/2)*scalingFactor;
    clickPosition.y = centerY+(y-float(window.getSize().y)/2)*scalingFactor;
    if(currentMode == mode::pointCreation){
        std::unique_ptr<PointShape> S (makePointShape(clickPosition.x, clickPosition.y));
        //shapes.push_back(std::move(S));
        shapes.getVector<std::unique_ptr<PointShape> >().push_back (std::move(S));
    } else if(currentMode == mode::selection){
        objectSelecter os (clickPosition, hulledElements, currentConditions);
        shapes.executeTillTrue (os);
        /*
        Shape *hitShape = findObjectHit (clickPosition);
        if(hitShape){
            int selectCount;
            if (hitShape->getActivity()) {
                hitShape->setActivity (false);
                hitShape->setCurrent (false);

                hulledShapes.erase (std::find(hulledShapes.begin(), hulledShapes.end(), hitShape));

                hitShape->removeFromConstructionElements (hulledElements);


                if (hulledShapes.size() > 0) {
                    hulledShapes.back()->setCurrent (true);
                }
                selectCount = -1;
            } else {
                hitShape->setActivity (true);
                if (hulledShapes.size() > 0)
                    hulledShapes.back()->setCurrent (false);

                hulledShapes.push_back(hitShape);
                hulledShapes.back()->setCurrent (true);

                hitShape->addToConstructionElements (hulledElements);
                selectCount = 1;
            }
            hitShape->addToCurrentConditions (currentConditions, selectCount);
            resetUIPosition();
        }
        uiPages[uiMapId(currentConditions)];
        */
        uiPages[uiMapId(currentConditions)];
    }

}
