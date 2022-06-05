#include"Input.h"
#include <SFML/Graphics.hpp>

class inputSfmlWrapper {
    private:
        typedef std::unordered_map<uint32_t, inputManager::keyType> maptype;
        maptype mp;
        inputManager& manager;
    public:
        void onKeyEvent (sf::Event& event);
        inputSfmlWrapper (inputManager& _manager);
};
