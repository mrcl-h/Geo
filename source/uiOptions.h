#include "geo.h"
#include "conditionTracker.h"
#include "Construction.h"
#include <SFML/Graphics.hpp>
#include <array>

struct uiObject {
    sf::Texture image;
    constructionMaker creator;
};

template <typename T>
class ShapeIdGetter {};
template <> class ShapeIdGetter <PointShape> {public: enum {id = 0};};
template <> class ShapeIdGetter <CircleShape> {public: enum {id = 1};};
template <> class ShapeIdGetter <LineShape> {public: enum {id = 2};};
template <> class ShapeIdGetter <SegmentShape> {public: enum {id = 3};};
template <> class ShapeIdGetter <TriangleShape> {public: enum {id = 4};};

typedef conditionTracker <uiObject, 5> uiOptionTracker;
typedef std::array <int, 5> uiOptionConditions;

template <typename T>
void adjustUiOptionTrackerCount (uiOptionTracker& tracker, int count) {
    tracker.adjustCondition (ShapeIdGetter<T>::id, count);
}

inline void resetUiOptionConditions (uiOptionConditions& op) {op.fill(0);}

class uiPointObject {
    private:
        int count;
    public:
        explicit uiPointObject (int _count) :count(_count) {}
        void pushToConditions (uiOptionConditions& op) const {
            op[ShapeIdGetter<PointShape>::id] += count;
        }
};
class uiLineObject {
    private:
        int count;
    public:
        explicit uiLineObject (int _count) :count(_count) {}
        void pushToConditions (uiOptionConditions& op) const {
            op[ShapeIdGetter<LineShape>::id] += count;
        }
};
class uiSegmentObject {
    private:
        int count;
    public:
        explicit uiSegmentObject (int _count) :count(_count) {}
        void pushToConditions (uiOptionConditions& op) const {
            op[ShapeIdGetter<SegmentShape>::id] += count;
        }
};
class uiCircleObject {
    private:
        int count;
    public:
        explicit uiCircleObject (int _count) :count(_count) {}
        void pushToConditions (uiOptionConditions& op) const {
            op[ShapeIdGetter<CircleShape>::id] += count;
        }
};

class uiTriangleObject {
    private:
        int count;
    public:
        explicit uiTriangleObject (int _count) :count(_count) {}
        void pushToConditions (uiOptionConditions& op) const {
            op[ShapeIdGetter<TriangleShape>::id] += count;
        }
};

template <typename U, typename... T>
void setUpUiCondition (uiOptionConditions& op, const U& obj, const T&... rest) {
    obj.pushToConditions(op);
    setUpUiCondition (op, rest...);
}
template <typename U>
void setUpUiCondition (uiOptionConditions& op, const U& obj) {
    obj.pushToConditions(op);
}

template <typename U, typename... T>
void makeUiOption (uiOptionTracker& tracker, const char* fileName, const T&... con) {

    uiOptionConditions opCond;
    opCond.fill (0);
    setUpUiCondition (opCond, con...);

    uiObject obj; 
    obj.creator = makeConstruction<U>;
    obj.image.loadFromFile (fileName);
    obj.image.setSmooth (true);

    tracker.addOption (opCond.begin(), obj);
}

class uiOptionConditionsAdjusterShapeVisitor : public ShapeVisitor {
    private: 
        uiOptionTracker *tracker;
        int count;
    public:
        virtual ~uiOptionConditionsAdjusterShapeVisitor () {}
        void setTracker (uiOptionTracker *_tracker) {
            tracker = _tracker; 
        }
        void setCount (int _count) {
            count = _count;
        }
        virtual void visitSegment (SegmentShape*) {
            adjustUiOptionTrackerCount<SegmentShape> (*tracker, count);
        }
        virtual void visitTriangle (TriangleShape*) {
            adjustUiOptionTrackerCount<TriangleShape> (*tracker, count);
        }
        virtual void visitLine (LineShape*) {
            adjustUiOptionTrackerCount<LineShape> (*tracker, count);
        }
        virtual void visitCircle (CircleShape*) {
            adjustUiOptionTrackerCount<CircleShape> (*tracker, count);
        }
        virtual void visitPoint (PointShape*) {
            adjustUiOptionTrackerCount<PointShape> (*tracker, count);
        }
};
