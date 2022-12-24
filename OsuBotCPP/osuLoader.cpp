#include "osuLoader.h"

osuLoader osuLoader::s_instance;

osuLoader::osuLoader() {
	this->osuHandle = getOsuWindowHandle();
	if (!this->osuHandle) {
		std::cout << "Osu! Process not found." << std::endl;
		exit(-1);
	}
	const wstring execFile = winUtil::getExecutablePath(this->osuHandle);
	this->songsPath = strUtil::getDirectoryName(execFile) + L"\\Songs";
	this->initOsuCoordinates();
	this->loadOsuProcess();
}

void osuLoader::loadOsuProcess() {
	const wstring mapPrefix = L"osu!  - ";
	
	const wstring windowTitle = winUtil::getWindowTitle(this->osuHandle);

	if (windowTitle.rfind(mapPrefix, 0) != 0) {
		std::cout << "Osu! Map is not being played." << std::endl;
		exit(-1);
	}
	const wstring currentMapNameDiff = windowTitle.substr(mapPrefix.length());
	this->loadMapData(currentMapNameDiff);
}

void osuLoader::loadMapData(const wstring& mapNameDiff) {
	wstring nameDiffFormatted = strUtil::formatMapName(mapNameDiff);
	this->currentMapName = strUtil::getMapName(nameDiffFormatted);
	this->currentMapDiff = strUtil::getMapDiff(nameDiffFormatted);

	std::list<wstring> candidates = directoriesMatchingSubstr(this->songsPath, this->currentMapName);

	// TODO: should look for the current map while getting the candidates to potentially not go over the entire songs folder

	this->currentMapPath = findMapFileByCandidateSongs(candidates, this->currentMapDiff);
}

HWND osuLoader::getOsuWindowHandle() {
	return winUtil::getWindowHandleByPrefix("osu!");
}

void osuLoader::initOsuCoordinates() {
	const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	const float sheight = screenHeight;
	const float swidth = (sheight * 4) / 3;

	scale.x = swidth / BASE_SCREEN_WIDTH;
	scale.y = sheight / BASE_SCREEN_HEIGHT;

	playFieldDimensions.x = OSUPIXEL_WIDTH * scale.x;
	playFieldDimensions.y = OSUPIXEL_HEIGHT * scale.y;

	pixelScale = (float)playFieldDimensions.x / OSUPIXEL_WIDTH; // could also do .y / _HEIGHT

	offset.x = (screenWidth - playFieldDimensions.x) / 2;
	offset.y = (screenHeight - playFieldDimensions.y) / 2 + TOP_PADDING;
}
Point osuLoader::convertOsuCoordinates(const Point& src) {
	return s_instance.impl_convertOsuCoordinates(src);
}
Point osuLoader::impl_convertOsuCoordinates(const Point& src) {
	const int x = src.x * scale.x + offset.x;
	const int y = src.y * scale.y + offset.y;
	return { x, y };
}
int osuLoader::convertOsuLength(const int osuPixelLength) {
	return s_instance.impl_convertOsuLength(osuPixelLength);
}
int osuLoader::impl_convertOsuLength(const int osuPixelLength) {
	return osuPixelLength * pixelScale;
}

const wstring& osuLoader::getCurrentMapPath() {
	return s_instance.currentMapPath;
}
const wstring& osuLoader::getCurrentMapName() {
	return s_instance.currentMapName;
}
const wstring& osuLoader::getCurrentMapDiff() {
	return s_instance.currentMapDiff;
}
