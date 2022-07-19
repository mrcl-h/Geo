#pragma once
#include <unordered_map>
#include "geo.h"

class charMarks {
    private:
        typedef std::unordered_map <char, Point> maptype;
        maptype marks;
        Point cachedPoint;
    public:
        bool findMark (const char c) {
            maptype::const_iterator iter = marks.find (c);
            if (iter == marks.end()) { return false; }

            cachedPoint = iter->second;
            return true;
        }
        Point getFoundMark () {
            return cachedPoint;
        }
        void setMark (const char c, double x, double y) {
            Point& p = marks[c];
            p.x = x; p.y = y;
        }
        void setMark (const char c, const Point& p) {
            marks[c] = p;
        }
};
