#include"geo.h"
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

void resetConstructionElements (constructionElements& el) {
    el.points.clear();
    el.lines.clear();
    el.circles.clear();
    el.segments.clear();
}

void resetUiOptionConditions (uiOptionConditions& op) {
    op.lineCount = op.pointCount = op.circleCount = op.segmentCount = 0;
}

//----------------------------------------
const double dist(const Point &p1, const Point &p2) {
  double diffX = p1.x - p2.x;
  double diffY = p1.y - p2.y;
  return sqrt(diffX * diffX + diffY * diffY);
}
const double dist (double x1, double y1, double x2, double y2) {
  double diffX = x1 - x2;
  double diffY = y1 - y2;
  return sqrt(diffX * diffX + diffY * diffY);
}
const double length(const Point &p) {
  return sqrt(p.x * p.x + p.y * p.y);
}

//Point::Point (double _x, double _y) :x(_x), y(_y) {}

const Point operator+(const Point &p1, const Point &p2) {
  Point sum;
  sum.x = p1.x + p2.x;
  sum.y = p1.y + p2.y;
  return sum;
}
const Point operator-(const Point &p1, const Point &p2) {
  Point difference;
  difference.x = p1.x - p2.x;
  difference.y = p1.y - p2.y;
  return difference;
}
const Point operator*(const Point &p, double a) {
  Point product = p;
  product.x *= a;
  product.y *= a;
  return product;
}
const Point operator*(double a, const Point &p) {
  Point product = p;
  product.x *= a;
  product.y *= a;
  return product;
}
const Point operator/(const Point &p, double a) {
  Point quotient = p;
  quotient.x /= a;
  quotient.y /= a;
  return quotient;
}
const double operator*(const Point &p1, const Point &p2) {
  return p1.x * p2.x + p1.y * p2.y;
}
const double operator%(const Point &p1, const Point &p2) {
  return p1.x * p2.y - p1.y * p2.x;
}
const bool operator==(const Point &p1, const Point &p2) {
  return dist(p1, p2) < 0.01;
}
const double abs(const Point &p) { return sqrt(p.x * p.x + p.y * p.y); }
