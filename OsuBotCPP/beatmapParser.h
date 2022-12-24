#pragma once
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include "objects.h"
#include "windowsHelper.h"
#include "globalDef.h"

using std::string;
using std::wstring;
class beatmapParser
{
public:
	wstring mapPath;
	std::list<OsuObject*> objects;
	std::queue<TimingPoint> timingPoints;

	beatmapParser(const wstring& path);
	~beatmapParser();

	void loadCurrentMap();
	void loadMap(const wstring& path);
	MapInfo mapInfo;

private:
	static const string AudioLeadIn;
	static const string SliderMultiplier;
	static const string TimingPointsSection;
	static const string HitObjectsSection;
};