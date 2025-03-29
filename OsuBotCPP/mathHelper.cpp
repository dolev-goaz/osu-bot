#include "mathHelper.h"
namespace mathUtil {
	float calculateDistance(const Point& a, const Point& b) {
		return sqrtf(powf(a.y - b.y, 2) + powf(a.x - b.x, 2));
	}

	// Source: https://paulbourke.net/geometry/circlesphere/
	Point _circleCenterBy3Points(const Point& p0, const Point& p1, const Point& p2) {
		Point center;

		float ma = (p1.y - p0.y + .0f) / (p1.x - p0.x);
		float mb = (p2.y - p1.y + .0f) / (p2.x - p1.x);

		center.x = (ma * mb * (p0.y - p2.y) + mb * (p0.x + p1.x) - ma * (p1.x + p2.x)) / (2 * (mb - ma));
		center.y = (-1.0 / ma) * (center.x - (p0.x + p1.x) / 2.0) + (p0.y + p1.y) / 2.0;
		return center;
	}

	Point circleCenterByPoints(const std::vector<Point>& points) {
		// Don't use a vertical/horizontal line formed by two points that have the same x/y value
		// TODO: doesn't handle the case there's one vertical line and one horizontal line
		if (points[1].x == points[0].x || points[1].y == points[0].y) {
			// separate 1 and 0
			return _circleCenterBy3Points(points[1], points[2], points[0]);
		}
		else if (points[1].x == points[2].x || points[1].y == points[2].y) {
			// separate 1 and 2
			return _circleCenterBy3Points(points[2], points[0], points[1]);
		}
		// separate 0 and 2
		return _circleCenterBy3Points(points[0], points[1], points[2]);
	}

	float getAngleFromCenter(const Point& pointOnCircle, const Point& center) {
		float angle = atan2(center.y - pointOnCircle.y, pointOnCircle.x - center.x);
		if (angle < 0) angle += 2 * PI;
		return angle;
	}
}