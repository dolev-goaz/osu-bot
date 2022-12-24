#pragma once
#include <string>
#include <iostream>
#include "windowsHelper.h"
#include "fileHelper.h"
#include "globalDef.h"

#define OSUPIXEL_WIDTH 512
#define OSUPIXEL_HEIGHT 384
#define BASE_SCREEN_WIDTH 640
#define BASE_SCREEN_HEIGHT 480
#define TOP_PADDING 15

using std::string;
class osuLoader {
public:
	osuLoader(const osuLoader& loader) = delete;
	static int convertOsuLength(const int osuPixelLength);
	static Point convertOsuCoordinates(const Point&);
	static const wstring& getCurrentMapPath();
	static const wstring& getCurrentMapName();
	static const wstring& getCurrentMapDiff();
private:
	static osuLoader s_instance;
	Point offset;
	Point playFieldDimensions;
	PointF scale;
	float pixelScale;
	wstring currentMapName;
	wstring currentMapDiff;
	wstring currentMapPath;
	wstring songsPath;
	HWND osuHandle;

	osuLoader();
	Point impl_convertOsuCoordinates(const Point&);
	int impl_convertOsuLength(const int osuPixelLength);
	void loadOsuProcess();
	void loadMapData(const wstring& mapNameDiff);
	void initOsuCoordinates();
	static HWND getOsuWindowHandle();
};