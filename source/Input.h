#include <unordered_map>
#include <cstddef>
#include <cstdint>
#include <iostream>

class inputManager;
class inputState;

class inputManager {
    private:
        inputState * mainState, *currentState;
    public:
        ~inputManager ();
        void setMainState (inputState *state) {
            mainState = state;
        }
        void goToMainState () {
            currentState = mainState;
        }
        void setCurrentState (inputState *newCurrent) {
            currentState = newCurrent;
        }
        enum Key {
            A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            n1, n2, n3, n4, n5, n6, n7, n8, n9, n0,
            Escape, LControl, LShift, LAlt, RControl, RShift, RAlt,
            LBracket, RBracket, Semicolon, Comma, Period, Quote, Slash, Backslash,
            Tilde, Equal, Hyphen, Space, Enter, Backspace, Tab, Delete,
            Add, Subtract, Multiply, Divide, // numpad keys
            Left, Right, Up, Down,
            p1, p2, p3, p4, p5, p6, p7, p8, p9, p0, // numpad keys
            f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12
        };
        enum action {
            pressed = 1, released
        };
        static constexpr unsigned int ctrlMod = 1;
        static constexpr unsigned int shiftMod = 2;
        static constexpr unsigned int altMod = 4;
        void onKey (Key k, action a, unsigned int mods);
        void onChar (unsigned int unicode);
};

class inputState {
    private: 
        inputManager * const manager;
    protected:
        void done ();
        void changeState (inputState* state);
    public:
        inputState (inputManager * _manager) :manager (_manager) {}
        virtual ~inputState () {}
        virtual void onKey (inputManager::Key k, inputManager::action a, unsigned int mods){

        }
        virtual void onChar (unsigned int unicode){}
        virtual void onEnter () {}
};

class junctionInputState : public inputState {
    private:
        class stateObj {
            private:
                inputState *state;
                bool responsible;
            public:
                stateObj () : state(NULL), responsible(false) {}
                void set (inputState* _state, bool _responsible) {
                    state = _state;
                    responsible = _responsible;
                }
                inputState* getState () {
                    return state;
                }
                stateObj (inputState * _state, bool _responsible) : state(_state), responsible(_responsible) {}
                ~stateObj () {
                    if (responsible) delete state;
                }
        };
        //typedef std::unordered_map<inputManager::Key, stateObj> maptype; CHANGED
        typedef std::unordered_map<uint32_t, stateObj> maptype; 
        maptype stateMap;
    public:
        junctionInputState (inputManager* _manager) :inputState(_manager){}
        void addState (inputManager::Key k, inputState* addedState, bool responsible) {
            stateMap[k].set(addedState, responsible); // = stateObj(addedState, responsible);
            //stateMap.emplace(std::make_pair(k, stateObj(addedState, responsible)));
        }
        virtual void onKey (inputManager::Key k, inputManager::action a, unsigned int mods) {
            if (a != inputManager::action::pressed) return;
            maptype::iterator it = stateMap.find (k);
            if (it == stateMap.end()) { return; }
            changeState (it->second.getState());
        }
};
