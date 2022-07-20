#include "Geoapp.h"
#include "keyStates.h"
#include <SFML/Graphics.hpp>

constexpr double epsilon = 2;
constexpr int antialias = 4;

//Geoapp::Geoapp() : inManager (), inWrapper (inManager), mainGeoView (window, &world, uiTracker), testPtr (new int) {
Geoapp::Geoapp() : inManager (), inWrapper (inManager), mainGeoView (&world, uiTracker), sfmlDrawing (&window) {

    uiBarrier = 0.6;
    sf::ContextSettings settings;
    settings.antialiasingLevel = antialias;
    window.create(sf::VideoMode(500, 300), "Geo", sf::Style::Default, settings);
    scalingFactor=1.0;

    makeUiOption<segmentMiddle> (uiTracker, "resources/segmentMid.png", uiSegmentObject (1));
    makeUiOption<pointsMiddle> (uiTracker, "resources/pointsMid.png", uiPointObject (2));
    makeUiOption<parallelLine> (uiTracker, "resources/parallelLine.png", uiLineObject (1), uiPointObject (1));
    makeUiOption<orthogonalLine> (uiTracker, "resources/orthogonalLine.png", uiLineObject (1), uiPointObject (1));
    makeUiOption<lineThroughPoints> (uiTracker, "resources/lineThroughPoints.png", uiPointObject (2));
    makeUiOption<circleWithCenter> (uiTracker, "resources/circleWithCenter.png", uiPointObject (2));
    makeUiOption<segmentFromPoints> (uiTracker, "resources/segmentFromPoints.png", uiPointObject (2));
    makeUiOption<centerOfMass> (uiTracker, "resources/centerOfMass.png", uiPointObject (3));
    makeUiOption<circleThreePoints> (uiTracker, "resources/circleThreePoints.png", uiPointObject (3));
    makeUiOption<powerLine> (uiTracker, "resources/powerLine.png", uiCircleObject (2));
    makeUiOption<symmetricalOfPoints> (uiTracker, "resources/symmetricalOfPoints.png", uiPointObject (2));
    makeUiOption<symmetricalOfSegment> (uiTracker, "resources/symmetricalOfSegment.png", uiSegmentObject (1));
    makeUiOption<lineCircleIntersection> (uiTracker, "resources/lineCircleIntersection.png", uiLineObject(1), uiCircleObject(1));
    makeUiOption<circlesIntersection> (uiTracker, "resources/circleCircleIntersection.png", uiCircleObject (2));
    makeUiOption<bisectorThreePoints> (uiTracker, "resources/bisectorThreePoints.png", uiPointObject (3));
    makeUiOption<tangentCirclePoint> (uiTracker, "resources/tangentsThroughPoint.png", uiPointObject(1), uiCircleObject(1));
    makeUiOption<circleConstraint> (uiTracker, "resources/circleConstraint.png", uiPointObject (1), uiCircleObject (1));
    makeUiOption<lineConstraint> (uiTracker, "resources/lineConstraint.png", uiPointObject (1), uiLineObject (1));
    makeUiOption<Triangle> (uiTracker, "resources/segmentMid.png", uiPointObject (3));

    junctionInputState *mainState = new junctionInputState (&inManager);
    mainState->addState (inputManager::Key::Left,   new inputCameraMovementState (&inManager, &mainGeoView, -10,   0));
    mainState->addState (inputManager::Key::Right,  new inputCameraMovementState (&inManager, &mainGeoView,  10,   0));
    mainState->addState (inputManager::Key::Up,     new inputCameraMovementState (&inManager, &mainGeoView,   0, -10));
    mainState->addState (inputManager::Key::Down,   new inputCameraMovementState (&inManager, &mainGeoView,   0,  10));

    mainState->addState (inputManager::Key::Left,   new inputCameraMovementState (&inManager, &mainGeoView, -100,   0), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::Right,  new inputCameraMovementState (&inManager, &mainGeoView,  100,   0), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::Up,     new inputCameraMovementState (&inManager, &mainGeoView,   0, -100), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::Down,   new inputCameraMovementState (&inManager, &mainGeoView,   0,  100), inputManager::ctrlMod);

    mainState->addState (inputManager::Key::H, new inputPointMovementState (&inManager, &world, -10,   0));
    mainState->addState (inputManager::Key::J, new inputPointMovementState (&inManager, &world,   0,  10));
    mainState->addState (inputManager::Key::K, new inputPointMovementState (&inManager, &world,   0, -10));
    mainState->addState (inputManager::Key::L, new inputPointMovementState (&inManager, &world,  10,   0));

    mainState->addState (inputManager::Key::H, new inputPointMovementState (&inManager, &world, -100,   0), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::J, new inputPointMovementState (&inManager, &world,   0,  100), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::K, new inputPointMovementState (&inManager, &world,   0, -100), inputManager::ctrlMod);
    mainState->addState (inputManager::Key::L, new inputPointMovementState (&inManager, &world,  100,   0), inputManager::ctrlMod);

    mainState->addState (inputManager::Key::Q, new inputPointCreationState  (&inManager, &mainGeoView));
    mainState->addState (inputManager::Key::W, new inputPointSelectionState (&inManager, &mainGeoView));

    mainState->addState (inputManager::Key::M,      new inputSetMarkState  (&inManager, &mainGeoView, marks));
    mainState->addState (inputManager::Key::Quote,  new inputGoToMarkState (&inManager, &mainGeoView, marks));

    mainState->addState (inputManager::Key::U, new inputUIScrollState (&inManager, this,  10));
    mainState->addState (inputManager::Key::D, new inputUIScrollState (&inManager, this, -10));

    mainState->addState (inputManager::Key::Hyphen, new inputScalingState (&inManager, &mainGeoView, 2));
    mainState->addState (inputManager::Key::Equal, new inputScalingState (&inManager, &mainGeoView, 0.5), inputManager::shiftMod);

    mainState->addState (inputManager::Key::S, new inputSaveState (&inManager, &mainGeoView, "output.svg", &svgDrawing));

    inManager.setMainState (mainState);
    inManager.goToMainState();

    loop();
}

float Geoapp::findUIScrollMin () const {
    unsigned int windowWidth = window.getSize().x, windowHeight = window.getSize().y;
    float uiWidth = windowWidth*(1-uiBarrier);
    std::unordered_map<uint32_t, std::vector<uiObject> >::const_iterator it;
    float objectHeight = uiWidth/2;
    return -(objectHeight*uiTracker.size()-windowHeight);
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

void Geoapp::loop(){
    sf::Event event;
    while (window.waitEvent(event)){
        events (event);

        window.clear(sf::Color(255,255,255,255));
        drawApp ();
        window.display();
    }
}

void Geoapp::events(const sf::Event& event){
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
                //lastMouseRightPosition = mysz;
                //rightMoving = true;
                mainGeoView.startRightDragging (mysz.x, mysz.y);
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased){

        if (event.mouseButton.button == sf::Mouse::Right) {
            //rightMoving = false;
            mainGeoView.stopRightDragging ();

        }

    } else if (event.type== sf::Event::Resized){
        floatRect box;
        box.left = box.top = 0;
        box.height = getWindowHeight ();
        box.width = getWindowWidth () * uiBarrier;
        mainGeoView.setBox (box);
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
                //scalingFactor *= (1.25-event.mouseWheelScroll.delta*0.75);
                mainGeoView.changeScale (1.25-event.mouseWheelScroll.delta*0.75);
            }
        }
    } else if (event.type == sf::Event::MouseMoved) {
        Point mysz;
        mysz.x = sf::Mouse::getPosition(window).x; mysz.y=sf::Mouse::getPosition(window).y;
        mainGeoView.continueRightDragging (mysz.x, mysz.y);
    }
}

void Geoapp::drawApp(){
    drawObjects();
    drawUI();
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

    //const std::vector<uiObject>& currentObjects = uiPages.find(uiMapId (currentConditions))->second;
    float objectHeight = uiWidth/2;

    sf::Sprite currentIcon;
    currentIcon.setPosition (uiLeft+uiWidth*0.3, uiTop+objectHeight*0.1);

    sf::Vector2f leftSeparator (uiLeft, uiTop+objectHeight);
    sf::Vector2f rightSeparator (windowWidth, uiTop+objectHeight);
    //for (auto& i : currentObjects) {
    for (auto& i : uiTracker) {
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

void Geoapp::drawObjects() {
    drawingClass * oldDrawer = mainGeoView.setDrawer (&sfmlDrawing);
    mainGeoView.setRects();
    mainGeoView.draw();
    mainGeoView.setDrawer (oldDrawer);
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
    if (clickedOption >= uiTracker.size()) {
        return;
    }
    world.createConstruction (uiTracker.getNthOption(clickedOption).creator);


    resetUIPosition();
    uiTracker.resetConditions();
}

void Geoapp::whenClick(double x, double y){
    mainGeoView.click (x, y);
}
