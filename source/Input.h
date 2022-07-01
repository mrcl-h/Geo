/* file responsible for managing input states and mapping specific keys to states
 * */
#pragma once
#include <map>
#include <cstddef>

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
        class Key {
            public:
            static constexpr int A=0,B=1,C=2,D=3,E=4,F=5,G=6,H=7,I=8,J=9,K=10,L=11,M=12,N=13,O=14,P=15,Q=16,R=17,S=18,T=19,U=20,V=21,W=22,X=23,Y=24,Z=25,
                             n1=26,n2=27,n3=28,n4=29,n5=30,n6=31,n7=32,n8=33,n9=34,n0=35,
                             Escape=36,LControl=37,LShift=38,LAlt=39,RControl=40,RShift=41,RAlt=42,
                             LBracket=43,RBracket=44,Semicolon=45,Comma=46,Period=47,Quote=48,Slash=49,Backslash=50,
                             Tilde=51,Equal=52,Hyphen=53,Space=54,Enter=55,Backspace=56,Tab=57,Delete=58,
                             Add=59,Subtract=60,Multiply=61,Divide=62,// numpad keys
                             Left=63,Right=64,Up=65,Down=66,
                             p1=67,p2=68,p3=69,p4=70,p5=71,p6=72,p7=73,p8=74,p9=75,p0=76,// numpad keys
                             f1=77,f2=78,f3=79,f4=80,f5=81,f6=82,f7=83,f8=84,f9=85,f10=86,f11=87,f12=88,
                             unknown=89;
        };
        typedef int keyType;
        static char keyToChar (keyType k) {
            if (k > 25) return 0;
            return k+'A';
        }
        enum action {
            pressed = 1, released
        };
        static constexpr unsigned int ctrlMod = 1;
        static constexpr unsigned int shiftMod = 2;
        static constexpr unsigned int altMod = 4;
        void onKey (keyType k, action a, unsigned int mods);
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
        virtual void onKey (inputManager::keyType k, inputManager::action a, unsigned int mods){

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
        struct keyComb {
            int key;
            unsigned int mods;
            bool operator < (const keyComb& r) const {
                if (key == r.key) return mods < r.mods;
                return key < r.key;
            }
        };
        typedef std::map<keyComb, stateObj> maptype;
        maptype stateMap;
    public:
        junctionInputState (inputManager* _manager) :inputState(_manager){}
        void addState (inputManager::keyType k, inputState* addedState, unsigned int mods = 0, bool responsible = true) {
            keyComb newComb;
            newComb.key = k; newComb.mods = mods;
            stateMap[newComb].set(addedState, responsible); 
        }
        virtual void onKey (inputManager::keyType k, inputManager::action a, unsigned int mods) {
            if (a != inputManager::action::pressed) return;
            keyComb newComb;
            newComb.key = k; newComb.mods = mods;
            maptype::iterator it = stateMap.find (newComb);
            if (it == stateMap.end()) { return; }
            changeState (it->second.getState());
        }
};
