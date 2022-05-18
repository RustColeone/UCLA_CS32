#ifndef UTILS
#define UTILS

#include <iostream>
#include "globals.h"
#include <string>

using namespace std;

bool isNumber(string str) {
    for (char const& c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool pointComparison(Point a, Point b) {
    if (a.r == b.r && a.c == b.c) {
        return true;
    }
    return false;
}

bool containsPoint(vector<Point> points, Point point) {
    for (int i = 0; i < points.size(); i++) {
        if (pointComparison(points[i], point)) {
            return true;
        }
    }
    return false;
}

#endif