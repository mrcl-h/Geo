/* file for tracking conditions and choosing appropriate options
 *
 * conditionTracker tracks n conditions and stores objects of type OP
 *
 * By using begin() and end() one can iterate through all options matching
 * current conditions.
 * */
#pragma once
#include <array>
#include <map>
#include <vector>

template <typename OP, unsigned int LEN>
class conditionTracker {
    private:
        std::vector<OP> emptyOptionVec;
        std::map<std::array<int, LEN>, std::vector<OP> > conditionToOptionMap;
        std::array<int, LEN> currentConditions;
    public:
        void resetConditions () {
            currentConditions.fill (0);
        }
        conditionTracker <OP, LEN> () {
            resetConditions();
        }
        unsigned int size () const {
            typename std::map<std::array<int, LEN>, std::vector<OP> >::const_iterator i = conditionToOptionMap.find(currentConditions);
            if (i == conditionToOptionMap.end()) {
                return 0;
            }
            return (*i).second.size();
        }
        //return n-th possible option satisfying current conditions
        const OP& getNthOption (unsigned int n) const {
            typename std::map<std::array<int, LEN>, std::vector<OP> >::const_iterator i = conditionToOptionMap.find(currentConditions);
            if (i == conditionToOptionMap.end()) {
                //throw
            }
            return (*i).second[n];
        }
        //add an option to possibilities to choose from
        template <typename ITER>
            void addOption (ITER conditionBeg, const OP& newOp) {
                std::array<int, LEN> optionConditions;
                for (unsigned int i = 0; i < LEN; i++) {
                    optionConditions[i] = *conditionBeg;
                    conditionBeg++;
                }
                conditionToOptionMap[optionConditions].push_back(newOp);
            }
        //change current conditions
        void adjustCondition (unsigned int conditionNumber, int count) {
            currentConditions[conditionNumber] += count;
        }
        //iterator to iterate through all options matching current conditions
        class iterator {
            private:
                typename std::vector<OP>::const_iterator it;
                iterator (const typename std::vector<OP>::const_iterator& _it) :it(_it) {}
            public:
                bool operator == (const iterator& r) {
                    return it == r.it;
                }
                bool operator != (const iterator& r) {
                    return it != r.it;
                }
                const iterator& operator = (const iterator& r) {
                    it = r.it;
                }
                const iterator& operator ++ () {
                    ++it;
                    return *this;
                }
                const iterator& operator ++ (int) {
                    it++;
                    return *this;
                }
                const OP& operator * () {
                    return *it;
                }
                friend class conditionTracker;
        };
        iterator begin () const {
            typename std::map<std::array<int, LEN>, std::vector<OP> >::const_iterator i = conditionToOptionMap.find(currentConditions);
            if (i == conditionToOptionMap.end()) {
                return iterator (emptyOptionVec.begin());
            }
            return iterator ((*i).second.begin());
        }
        iterator end () const {
            typename std::map<std::array<int, LEN>, std::vector<OP> >::const_iterator i = conditionToOptionMap.find(currentConditions);
            if (i == conditionToOptionMap.end()) {
                return iterator (emptyOptionVec.end());
            }
            return iterator ((*i).second.end());
        }
};
