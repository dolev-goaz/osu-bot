#include "objects.h"

ObjectType OsuObject::GetObjectType(const int rawType) {
	if (rawType & HIT_CIRCLE) return HitCircleOType;
	if (rawType & SLIDER) return SliderOType;
	if (rawType & SPINNER) return SpinnerOType;
	return NoOType;
}
SliderType Slider::GetSliderType(const char rawType) {
	switch (rawType)
	{
	case SLIDER_BEZIER: return BezierSType;
	case SLIDER_CENTRIPETAL: return CentripetalSType;
	case SLIDER_LINEAR: return LinearSType;
	case SLIDER_PERFECT_CIRCLE: return CircleSType;
	default: return NoSType;
	}
}

OsuObject* OsuObject::CreateObject(const string& fileLine, const MapInfo& mapInfo) {
	OsuObject base;
	string lineRemainder;
	std::vector<string> objectParameters = strUtil::split(fileLine, ",", lineRemainder, 5);
	const int x = std::stoi(objectParameters[0]);
	const int y = std::stoi(objectParameters[1]);
	const int time = std::stoi(objectParameters[2]);
	const int typeRaw = std::stoi(objectParameters[3]);
	base.m_coord = osuLoader::convertOsuCoordinates({ x, y });
	base.time = time + mapInfo.AudioLeadIn;

	const ObjectType type = GetObjectType(typeRaw);

	OsuObject* output;

	if (type == HitCircleOType) {
		output = HitCircle::CreateHitCircle(base, lineRemainder);
	}
	else if (type == SliderOType) {
		output = Slider::CreateSlider(base, lineRemainder);
	}
	else if (type == SpinnerOType) {
		output = Spinner::CreateSpinner(base, lineRemainder);
	}
	else {
		throw std::logic_error("Invalid Data!");
	}

	return output;
}

HitCircle* HitCircle::CreateHitCircle(const OsuObject& base, const string& remainingData) {
	return new HitCircle(base);
}
Slider* Slider::CreateSlider(const OsuObject& base, const string& remainingData) {
	std::vector<string> sliderParameters = strUtil::split(remainingData, ",");
	const string curveData = sliderParameters[0];
	const int slides = std::stoi(sliderParameters[1]);
	const float osuPixelLength = std::stof(sliderParameters[2]);
	const int length = osuLoader::convertOsuLength(osuPixelLength);

	const SliderType curveType = GetSliderType(curveData[0]);
	const string pointsRaw = curveData.substr(2); // skip |
	std::vector<Point> points = ParsePoints(pointsRaw);

	points.insert(points.begin(), base.m_coord);

	return new Slider(base, curveType, points, slides, osuPixelLength, length);
}
Spinner* Spinner::CreateSpinner(const OsuObject& base, const string& remainingData) {
	std::vector<string> spinnerParameters = strUtil::split(remainingData, ",");
	const int endTime = std::stoi(spinnerParameters[0]);

	return new Spinner(base, endTime);
}

std::vector<Point> Slider::ParsePoints(const string& pointsRaw) {
	std::vector<Point> output;
	const std::vector<string> pointsSplit = strUtil::split(pointsRaw, "|");

	for (const string& pointRaw : pointsSplit) {
		const std::vector<string> coordRaw = strUtil::split(pointRaw, ":");
		const int x = std::stoi(coordRaw[0]);
		const int y = std::stoi(coordRaw[1]);
		output.push_back(osuLoader::convertOsuCoordinates({ x, y }));
	}
	return output;
}


// CONSTRUCTORS
OsuObject::OsuObject()
	: m_coord({ 0, 0 }), time(0) {}
OsuObject::OsuObject(const OsuObject& other)
	: m_coord(other.m_coord), time(other.time) {}
HitCircle::HitCircle(const OsuObject& other)
	: OsuObject(other) {}
Slider::Slider(const OsuObject& other, SliderType curveType, const std::vector<Point>& points, size_t slideCount, float osuPixelsLength, float length)
	: OsuObject(other), m_curveType(curveType),
	m_points(points), m_slideCount(slideCount),
	m_lengthOsuPixels(osuPixelsLength), m_length(length) {}
Spinner::Spinner(const OsuObject& other, int endTime)
	: OsuObject(other), m_endTime(endTime) {}