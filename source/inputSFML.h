/* file responsible for interpreting sfml key inputs and passing them to input class
 * */
#include "Input.h"
#include <unordered_map>
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
