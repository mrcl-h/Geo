#include"Geoapp.h"
#include<SFML/Graphics.hpp>

constexpr double epsilon = 2;
constexpr int antialias = 4;

Geoapp::Geoapp() : inManager (), inWrapper (inManager), testPtr (new int){
    //height=300.0;
    //width=300.0;
    //uiwidth=200.0;
    uiBarrier = 0.6;
    sf::ContextSettings settings;
    settings.antialiasingLevel = antialias;
    window.create(sf::VideoMode(500, 300), "Geo", sf::Style::Default, settings);
    scalingFactor=1.0;
    centerX = centerY = 0;
    //currentConditions.reset();
    resetUiOptionConditions (currentConditions);
    uiPages[uiMapId(currentConditions)];
    //currentConditions.segmentCount = 1;
    resetConstructionElements (hulledElements);

    uiOptionConditions cond;

    //segment mid point
    uiObject segMidObject;
    segMidObject.creator = makeConstruction<segmentMiddle>;
    segMidObject.image.loadFromFile ("resources/segmentMid.png");
    segMidObject.image.setSmooth(true);

    //cond.reset();
    resetUiOptionConditions (cond);
    cond.segmentCount = 1;
    registerUiOption (segMidObject, cond);

    //points mid point
    uiObject pointMidObject;
    pointMidObject.creator = makeConstruction<pointsMiddle>;
    pointMidObject.image.loadFromFile ("resources/pointsMid.png");
    pointMidObject.image.setSmooth(true);

    //cond.reset();
    resetUiOptionConditions (cond);
    cond.pointCount = 2;
    registerUiOption (pointMidObject, cond);

    //parallel line
    uiObject parallelLineObject;
    parallelLineObject.creator = makeConstruction<parallelLine>;
    parallelLineObject.image.loadFromFile ("resources/parallelLine.png");
    parallelLineObject.image.setSmooth(true);

    //cond.reset();
    resetUiOptionConditions (cond);
    cond.pointCount = 1;
    cond.lineCount = 1;
    registerUiOption (parallelLineObject, cond);

    //orthogonal line
    uiObject orthogonalLineObject;
    orthogonalLineObject.creator = makeConstruction<orthogonalLine>;
    orthogonalLineObject.image.loadFromFile ("resources/orthogonalLine.png");
    orthogonalLineObject.image.setSmooth (true);

    //cond.reset();
    resetUiOptionConditions (cond);
    cond.pointCount = 1;
    cond.lineCount = 1;
    registerUiOption (orthogonalLineObject, cond);

    uiObject lineThroughPointsObject;
    lineThroughPointsObject.creator = makeConstruction<lineThroughPoints>;
    lineThroughPointsObject.image.loadFromFile("resources/lineThroughPoints.png");
    lineThroughPointsObject.image.setSmooth(true);
    //cond.reset();
    resetUiOptionConditions (cond);
    cond.pointCount = 2;
    registerUiOption (lineThroughPointsObject, cond);

    uiObject circleWithCenterObject;
    circleWithCenterObject.creator = makeConstruction<circleWithCenter>;
    circleWithCenterObject.image.loadFromFile("resources/circleWithCenter.png");
    lineThroughPointsObject.image.setSmooth(true);
    //cond.reset();
    resetUiOptionConditions (cond);
    cond.pointCount = 2;
    registerUiOption (circleWithCenterObject, cond);

    uiObject segmentFromPointsObject;
    segmentFromPointsObject.creator = makeConstruction<segmentFromPoints>;
    segmentFromPointsObject.image.loadFromFile("resources/segmentFromPoints.png");
    segmentFromPointsObject.image.setSmooth(true);
    //cond.reset();
    resetUiOptionConditions (cond);
    cond.pointCount = 2;
    registerUiOption (segmentFromPointsObject, cond);

    uiObject centerOfMassObject;
    centerOfMassObject.creator = makeConstruction<centerOfMass>;
    centerOfMassObject.image.loadFromFile("resources/centerOfMass.png");
    centerOfMassObject.image.setSmooth(true);
    //cond.reset();
    resetUiOptionConditions (cond);
    cond.pointCount = 3;
    registerUiOption (centerOfMassObject, cond);

    uiObject circleThreePointsObject;
    circleThreePointsObject.creator = makeConstruction<circleThreePoints>;
    circleThreePointsObject.image.loadFromFile("resources/circleThreePoints.png");
    circleThreePointsObject.image.setSmooth(true);
    resetUiOptionConditions (cond);
    cond.pointCount = 3;
    registerUiOption (circleThreePointsObject, cond);

    uiObject powerLineObject;
    powerLineObject.creator = makeConstruction<powerLine>;
    powerLineObject.image.loadFromFile("resources/powerLine.png");
    powerLineObject.image.setSmooth(true);
    resetUiOptionConditions (cond);
    cond.circleCount = 2;
    registerUiOption (powerLineObject, cond);

    uiObject symmetricalOfPointsObject;
    symmetricalOfPointsObject.creator = makeConstruction<symmetricalOfPoints>;
    symmetricalOfPointsObject.image.loadFromFile("resources/symmetricalOfPoints.png");
    symmetricalOfPointsObject.image.setSmooth(true);
    resetUiOptionConditions (cond);
    cond.pointCount = 2;
    registerUiOption (symmetricalOfPointsObject, cond);

    uiObject symmetricalOfSegmentObject;
    symmetricalOfSegmentObject.creator = makeConstruction<symmetricalOfSegment>;
    symmetricalOfSegmentObject.image.loadFromFile("resources/symmetricalOfSegment.png");
    symmetricalOfSegmentObject.image.setSmooth(true);
    resetUiOptionConditions (cond);
    cond.segmentCount = 1;
    registerUiOption (symmetricalOfSegmentObject, cond);

    uiObject tangentCirclePointObject;
    tangentCirclePointObject.creator = makeConstruction<tangentCirclePoint>;
    tangentCirclePointObject.image.loadFromFile("resources/segmentMid.png");
    tangentCirclePointObject.image.setSmooth(true);
    resetUiOptionConditions (cond);
    cond.circleCount = 1;
    cond.pointCount = 1;
    registerUiOption (tangentCirclePointObject, cond);

    uiObject lineCircleIntersectionObject;
    lineCircleIntersectionObject.creator = makeConstruction<lineCircleIntersection>;
    lineCircleIntersectionObject.image.loadFromFile("resources/lineCircleIntersection.png");
    lineCircleIntersectionObject.image.setSmooth(true);
    resetUiOptionConditions (cond);
    cond.circleCount = 1;
    cond.lineCount = 1;
    registerUiOption (lineCircleIntersectionObject, cond);

    uiObject circlesIntersectionObject;
    circlesIntersectionObject.creator = makeConstruction<circlesIntersection>;
    circlesIntersectionObject.image.loadFromFile("resources/circleCircleIntersection.png");
    circlesIntersectionObject.image.setSmooth(true);
    resetUiOptionConditions (cond);
    cond.circleCount = 2;
    registerUiOption (circlesIntersectionObject, cond);

    uiObject bisectorThreePointsObject;
    bisectorThreePointsObject.creator = makeConstruction<bisectorThreePoints>;
    bisectorThreePointsObject.image.loadFromFile("resources/bisectorThreePoints.png");
    bisectorThreePointsObject.image.setSmooth(true);
    resetUiOptionConditions (cond);
    cond.pointCount = 3;
    registerUiOption (bisectorThreePointsObject, cond);
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

    inManager.setMainState (mainState);
    inManager.goToMainState();

    loop();
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

Shape* Geoapp::findObjectHit (const Point& p) const {
    Shape *shapeHit = NULL;
    for (auto& i : shapes) {
        if (i->isHit (p)) {
            if (shapeHit == NULL || shapeHit->getHitPriority() < i->getHitPriority()) {
                shapeHit = i.get();
            }
        }
    }
    return shapeHit;
}

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
    //centerX = p.getX();
    //centerY = p.getY();
    centerX = p.x;
    centerY = p.y;
}
const Point Geoapp::getCamera () {
    //return Point (centerX, centerY);
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

void Geoapp::moveHulledPoints (double x, double y) {
    for (auto& i : hulledShapes) {
        i->moveShape (x,y);
    }
    for (auto& i : constructions) {
        i->adjust();
    }
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
                //double x=(double)sf::Mouse::getPosition(window).x, y=(double)sf::Mouse::getPosition(window).y;
                Point mysz;
                mysz.x = sf::Mouse::getPosition(window).x; mysz.y=sf::Mouse::getPosition(window).y;
                if(mysz.x>uiBarrier*window.getSize().x){
                    UIhandling(mysz);
                } else {
                    whenClick(mysz.x,mysz.y);
                }
            } else if (event.type== sf::Event::Resized){
                resetUIPosition();
            } else if(event.type == sf::Event::KeyPressed){
                inWrapper.onKeyEvent (event);
            }
            else if(event.type == sf::Event::KeyReleased){
                inWrapper.onKeyEvent (event);
            }
        }
}

void Geoapp::update(){
    drawObjects();
    drawUI();
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

void Geoapp::drawObjects() const{
    float windowWidth = window.getSize().x, windowHeight = window.getSize().y;
    sf::FloatRect visible (centerX - uiBarrier*windowWidth/2, centerY-windowHeight/2,uiBarrier*windowWidth,windowHeight);
    sf::FloatRect box (0,0,window.getSize().x*uiBarrier,window.getSize().y);
    for(unsigned int i=0;i<hulledShapes.size();i++){
        hulledShapes[i]->hull_draw(&window, visible, box);
    }
    for(unsigned int i=0;i<shapes.size();i++){
        //if (shapes[i]->exists)
        if (shapes[i]->getExistance())
            shapes[i]->draw(&window, visible, box);
    }
}

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
    //Construction* constructionMade = currentPage[clickedOption].creator (hulledShapes, shapes);
    Construction *constructionMade = currentPage[clickedOption].creator (hulledElements, shapes);
    constructions.emplace_back (constructionMade);

    if (hulledShapes.size() > 0) {
        //hulledShapes.back()->isCurrent = false;
        hulledShapes.back()->setCurrent (false);
    }
    for (auto i : hulledShapes) {
        //i->isActive = false;
        i->setActivity (false);
    }
    hulledShapes.clear();
    resetUIPosition();
    //currentConditions.reset();
    resetUiOptionConditions (currentConditions);
    resetConstructionElements (hulledElements);
}

void Geoapp::whenClick(double x, double y){
    //Point clickPosition (centerX+x-float(window.getSize().x*uiBarrier)/2,centerY+y-float(window.getSize().y)/2);
    Point clickPosition;
    clickPosition.x = centerX+x-float(window.getSize().x*uiBarrier)/2;
    clickPosition.y = centerY+y-float(window.getSize().y)/2;
    if(currentMode == mode::pointCreation){
        //Shape *S = new Point (clickPosition);;
        //std::unique_ptr<Shape> S = std::make_unique<PointShape>(clickPosition.x, clickPosition.y);
        std::unique_ptr<Shape> S (makePointShape(clickPosition.x, clickPosition.y));
        shapes.push_back(std::move(S));
    } else if(currentMode == mode::selection){
        //int a=FTCO(clickPosition);
        Shape *hitShape = findObjectHit (clickPosition);
        //std::cout<<a;
        if(hitShape){
            int selectCount;
            //if (hitShape->isActive) {
            if (hitShape->getActivity()) {
                //hitShape->isActive = false;
                //hitShape->isCurrent = false;
                hitShape->setActivity (false);
                hitShape->setCurrent (false);

                hulledShapes.erase (std::find(hulledShapes.begin(), hulledShapes.end(), hitShape));

                hitShape->removeFromConstructionElements (hulledElements);


                if (hulledShapes.size() > 0) {
                    //hulledShapes.back()->isCurrent = true;
                    hulledShapes.back()->setCurrent (true);
                }
                selectCount = -1;
            } else {
                //hitShape->isActive = true;
                hitShape->setActivity (true);
                if (hulledShapes.size() > 0)
                    //hulledShapes.back()->isCurrent = false;
                    hulledShapes.back()->setCurrent (false);

                hulledShapes.push_back(hitShape);
                //hulledShapes.back()->isCurrent = true;
                hulledShapes.back()->setCurrent (true);

                hitShape->addToConstructionElements (hulledElements);
                selectCount = 1;
            }
            hitShape->addToCurrentConditions (currentConditions, selectCount);
            resetUIPosition();
        }
        uiPages[uiMapId(currentConditions)];
        /*Shape &s=shapes[a];
        if(findInObjects(&s)>-1){
            hulledShapes.erase(findInObjects(s));
        } else{
            hulledShapes.push_back(&s);
        }*/
    }

}
