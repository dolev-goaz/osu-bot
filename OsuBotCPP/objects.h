#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include "stringHelper.h"
#include "globalDef.h"
#include "beatmapPlayer.h"
#include "osuLoader.h"
#include "mathHelper.h"

#define HIT_CIRCLE 1
#define SLIDER 2
#define SPINNER 8

#define SLIDER_BEZIER 'B'
#define SLIDER_CENTRIPETAL 'C'
#define SLIDER_LINEAR 'L'
#define SLIDER_PERFECT_CIRCLE 'P'

enum ObjectType { NoOType, HitCircleOType, SliderOType, SpinnerOType };
enum SliderType { NoSType, BezierSType, CentripetalSType, LinearSType, CircleSType };

class OsuObject
{
public:
	OsuObject();
	OsuObject(const OsuObject& other);
	static OsuObject* CreateObject(const string& fileLine, const MapInfo& mapInfo);
	virtual void Play(int currentTime, const TimingPoint& currentTimingPoint, const MapInfo& mapInfo);
	int time;
	Point m_coord;
private:
	static ObjectType GetObjectType(const int rawType);
};

class HitCircle : public OsuObject 
{ 
public:
	HitCircle(const OsuObject& base);
	void Play(int currentTime, const TimingPoint& currentTimingPoint, const MapInfo& mapInfo);
	static HitCircle* CreateHitCircle(const OsuObject& base, const string& remainingData);
};

class Slider : public OsuObject
{
public:
	Slider(const OsuObject& other, SliderType curveType, const std::vector<Point>& points, size_t slideCount, float osuPixelsLength, float length);
	void Play(int currentTime, const TimingPoint& currentTimingPoint, const MapInfo& mapInfo);
	static Slider* CreateSlider(const OsuObject& base, const string& remainingData);
private:
	SliderType m_curveType;
	std::vector<Point> m_points; // curve points, including m_coord
	size_t m_slideCount; // how many times to repeat slider(minimum 1)
	float m_lengthOsuPixels; // osu pixels
	int m_length; // real pixels


	static void SlideSingle(const std::vector<Point>& points, SliderType type, int length, float slideDuration);
	static void SlideLinear(const std::vector<Point>& points, int length, float duration);
	static void SlideCircular(const std::vector<Point>& points, int length, float duration);
	static void SlideCentripetal(const std::vector<Point>& points, float duration);
	static void SlideBezier(const std::vector<Point>& points, float duration);

	static std::vector<Point> ParsePoints(const string& pointsRaw);
	static SliderType GetSliderType(const char rawType);
};

class Spinner : public OsuObject 
{
public:
	Spinner(const OsuObject& base, int endTime);
	void Play(int currentTime, const TimingPoint& currentTimingPoint, const MapInfo& mapInfo);
	static Spinner* CreateSpinner(const OsuObject& base, const string& remainingData);
	static const int spinRadius;
	static const float spinStep;
private:
	int m_endTime;
};