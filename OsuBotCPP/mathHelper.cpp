#include "mathHelper.h"
namespace mathUtil {
	float calculateDistance(const Point& a, const Point& b) {
		return sqrtf(powf(a.y - b.y, 2) + powf(a.x - b.x, 2));
	}

	// Using 3 points, calculate the circle's center
	Point circleCenterByPoints(const std::vector<Point>& points) {
		float ma = (points[1].y - points[0].y + .0f) / (points[1].x - points[0].x);
		float mb = (points[2].y - points[1].y + .0f) / (points[2].x - points[1].x);

		Point center;
		center.x = (ma * mb * (points[0].y - points[2].y) + mb * (points[0].x + points[1].x) - ma * (points[1].x + points[2].x)) / (2 * (mb - ma));
		center.y = (-1.0 / ma) * (center.x - (points[0].x + points[1].x) / 2.0) + (points[0].y + points[1].y) / 2.0;
		return center;
	}

	float getAngleFromCenter(const Point& pointOnCircle, const Point& center) {
		float angle = atan2(center.y - pointOnCircle.y, pointOnCircle.x - center.x);
		if (angle < 0) angle += 2 * PI;
		return angle;
	}
}