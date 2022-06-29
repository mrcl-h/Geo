#include "Geoapp.h"
#include "Input.h"

class inputCameraMovementState : public inputState {
    private:
        Geoapp* app;
        double x, y;
    public:
        inputCameraMovementState (inputManager* _manager, Geoapp* _app, double _x, double _y);
        virtual void onEnter () override;
};

class inputPointMovementState : public inputState {
    private:
        Geoapp* app;
        double x, y;
    public:
        inputPointMovementState (inputManager* _manager, Geoapp* _app, double _x, double _y);
        virtual void onEnter () override;
};

class inputPointSelectionState : public inputState {
    private:
        Geoapp* app;
    public:
        inputPointSelectionState (inputManager* _manager, Geoapp* _app);
        virtual void onEnter () override;
};

class inputPointCreationState : public inputState {
    private:
        Geoapp* app;
    public:
        inputPointCreationState (inputManager* _manager, Geoapp* _app);
        virtual void onEnter () override;
};

class inputSetMarkState : public inputState {
    private:
        Geoapp* app;
    public:
        inputSetMarkState (inputManager* _manager, Geoapp* _app);
        virtual void onKey (inputManager::keyType k, inputManager::action a, unsigned int mods) override;
};

class inputGoToMarkState : public inputState {
    private:
        Geoapp* app;
    public:
        inputGoToMarkState (inputManager* _manager, Geoapp* _app);
        virtual void onKey (inputManager::keyType k, inputManager::action a, unsigned int mods) override;
};

class inputUIScrollState : public inputState {
    private:
        Geoapp* app;
        double scrollValue;
    public:
        inputUIScrollState (inputManager* _manager, Geoapp* _app, double _scrollValue);
        virtual void onEnter () override;
};

class inputScalingState : public inputState {
    private:
        Geoapp* app;
        double scaleValue;
    public:
        inputScalingState (inputManager* _manager, Geoapp* _app, double _scaleValue);
        virtual void onEnter () override;
};

class inputSaveState : public inputState {
    private:
        Geoapp* app;
        const std::string filename;
        svgDrawingClass* drawer;
    public:
        inputSaveState (inputManager* _manager, Geoapp* _app, const std::string& _filename, svgDrawingClass* _drawer);
        virtual void onEnter () override;
};
