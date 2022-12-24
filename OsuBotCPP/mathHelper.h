#pragma once
#include <vector>
#include "globalDef.h"
#define PI 3.141592653

namespace mathUtil {
	float calculateDistance(const Point& a, const Point& b);
	Point circleCenterByPoints(const std::vector<Point>& points);
	float getAngleFromCenter(const Point& pointOnCircle, const Point& center);
}