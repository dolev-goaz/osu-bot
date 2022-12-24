#include "objects.h"

#define MOUSE_ACTIONS 0

void OsuObject::Play(int currentTime, const TimingPoint& currentTimingPoint, const MapInfo& mapInfo) {}
void HitCircle::Play(int currentTime, const TimingPoint& currentTimingPoint, const MapInfo& mapInfo) {
	const int duration = time - currentTime;

	DragMouseTo(m_coord, duration);
#if MOUSE_ACTIONS
	winUtil::mouseClick();
#endif
}
void Slider::Play(int currentTime, const TimingPoint& currentTimingPoint, const MapInfo& mapInfo) {
	const int moveDuration = time - currentTime;
	const float multiplier = currentTimingPoint.getPracticalSliderMultiplier(mapInfo.SliderMultiplier);
	const float sliderDuration = m_lengthOsuPixels * multiplier;
	const float singleSlideDuration = sliderDuration;

	std::vector<Point> pointsReversed = m_points;
	std::reverse(pointsReversed.rbegin(), pointsReversed.rend());

	DragMouseTo(m_coord, moveDuration);

#if MOUSE_ACTIONS
	winUtil::mouseHold();
#endif

	std::vector<Point>* currentPoints;
	for (size_t i = 0; i < m_slideCount; i++)
	{
		bool reversed = (i % 2 != 0);
		if (reversed) currentPoints = &pointsReversed;
		else currentPoints = &m_points;
		SlideSingle(*currentPoints, m_curveType, m_length, singleSlideDuration);
	}
#if MOUSE_ACTIONS
	winUtil::mouseRelease();
#endif
}

void Slider::SlideSingle(const std::vector<Point>& points, SliderType type, int length, float slideDuration) {
	switch (type)
	{
	case LinearSType:
		Slider::SlideLinear(points, length, slideDuration);
		break;
	case BezierSType:
		Slider::SlideBezier(points, slideDuration);
		break;
	case CentripetalSType:
		Slider::SlideCentripetal(points, slideDuration);
		break;
	case CircleSType:
		Slider::SlideCircular(points, length, slideDuration);
		break;
	default:
		std::cout << "Unknown slider type" << std::endl;
		break;
	}

}

void Slider::SlideLinear(const std::vector<Point>& points, int length, float duration) {
	const Point source = points[0];
	const Point targetDirection = points[1];
	const float angle = mathUtil::getAngleFromCenter(targetDirection, source);

	const int dy = sin(angle) * length;
	const int dx = cos(angle) * length;

	const Point target = { source.x + dx, source.y - dy };

	DragMouseTo(target, duration);
}
void Slider::SlideCircular(const std::vector<Point>& points, int length, float duration) {
	float totalTime = 0;
	clock_t t = clock();
	float dt;

	Point center =  mathUtil::circleCenterByPoints(points);
	const float radius = mathUtil::calculateDistance(points[0], center);
	const float startAngle = mathUtil::getAngleFromCenter(points[0], center);
	const float midAngle = mathUtil::getAngleFromCenter(points[1], center);
	const float endAngle = mathUtil::getAngleFromCenter(points[2], center);

	float angle;
	int x, y;
	double percentage;

	int direction;
	float diff = startAngle - midAngle;
	if (diff < 0) diff += 2 * PI;

	if (diff < PI) direction = -1; // source: trust me bro
	else direction = 1;

	/*float da = endAngle - startAngle;
	if (da < 0) da += 2 * PI;
	if (direction == -1) da = 2 * PI - da;*/

	const float da = length / radius;

	while (totalTime < duration) {
		dt = (float)clock() - t;
		totalTime += dt;
		t = clock();

		percentage = min(totalTime / duration, 1);
		angle = startAngle + direction * percentage * da;
		x = center.x + radius * cos(angle);
		y = center.y - radius * sin(angle);
		SetCursorPos(x, y);
	}
}
void Slider::SlideCentripetal(const std::vector<Point>& points, float duration) {

}
void Slider::SlideBezier(const std::vector<Point>& points, float duration) {

}


const int Spinner::spinRadius = 100;
const float Spinner::spinStep = 0.06;
void Spinner::Play(int currentTime, const TimingPoint& currentTimingPoint, const MapInfo& mapInfo) {
	const int moveDuration = time - currentTime;
	const int spinDuration = m_endTime - time;
	
	DragMouseTo(this->m_coord, moveDuration);
#if MOUSE_ACTIONS
	winUtil::mouseHold();
#endif
	Spin(m_coord, spinDuration);
#if MOUSE_ACTIONS
	winUtil::mouseRelease();
#endif
}