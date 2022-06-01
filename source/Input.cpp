#include "Input.h"

inputManager::~inputManager () {
    delete mainState;
}

void inputManager::onKey (keyType k, action a, unsigned int mods) {
    currentState->onKey (k, a, mods);
}

void inputManager::onChar (unsigned int unicode) {
    currentState->onChar (unicode);
}

void inputState::done () {
    manager->goToMainState();
}
void inputState::changeState (inputState *state) {
    manager->setCurrentState (state);
    state->onEnter();
}

