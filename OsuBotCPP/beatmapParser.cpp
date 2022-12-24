#include "beatmapParser.h"

const string beatmapParser::AudioLeadIn = "AudioLeadIn";
const string beatmapParser::SliderMultiplier = "SliderMultiplier";
const string beatmapParser::TimingPointsSection = "[TimingPoints]";
const string beatmapParser::HitObjectsSection = "[HitObjects]";

beatmapParser::~beatmapParser() {
	while (!this->objects.empty()) {
		OsuObject* current = this->objects.front();
		this->objects.pop_front();
		delete current;
	}
}

beatmapParser::beatmapParser(const wstring& path) {
	this->mapPath = path;
}
void beatmapParser::loadMap(const wstring& path) {
	this->mapPath = path;
	loadCurrentMap();
}
void beatmapParser::loadCurrentMap() {
	std::fstream mapFile;
	mapFile.open(this->mapPath, std::ios::in);
	if (!mapFile.is_open()) {
		std::cout << "Couldn't open map file." << std::endl;
		std::wcout << this->mapPath << std::endl;
		exit(-1);
	}
	string line;
	string numValue;
	
	// Get Audio Lead In
	do {
		std::getline(mapFile, line);
	} while (line.rfind(beatmapParser::AudioLeadIn, 0) != 0);
	numValue = line.substr(beatmapParser::AudioLeadIn.length() + 1);
	mapInfo.AudioLeadIn = std::stoi(numValue);

	// Get Slider Multiplier
	do {
		std::getline(mapFile, line);
	} while (line.rfind(beatmapParser::SliderMultiplier, 0) != 0);
	numValue = line.substr(beatmapParser::SliderMultiplier.length() + 1);
	mapInfo.SliderMultiplier = std::stof(numValue);

	// Get to the TimingPoints tab
	do {
		std::getline(mapFile, line);
	} while (line.rfind(beatmapParser::TimingPointsSection, 0) != 0);


	float latestNonInheritedBeatLength = 0;
	while (std::getline(mapFile, line)) {
		if (line.empty()) break; // end of timing points tab
		TimingPoint tp = TimingPoint(line, latestNonInheritedBeatLength);
		if (tp.uninherited) latestNonInheritedBeatLength = tp.beatLength;
		
		this->timingPoints.push(tp);
	}

	// Get to the HitObjects tab
	do {
		std::getline(mapFile, line);
	} while (line.rfind(beatmapParser::HitObjectsSection, 0) != 0);

	while (std::getline(mapFile, line)) {
		if (line[0] == '\n') break; // end of hit objects tab
		OsuObject* object = OsuObject::CreateObject(line, mapInfo);
		this->objects.push_back(object);
	}
	mapFile.close();
}

TimingPoint::TimingPoint(const string& fileLine, float latestNonInheritedBeatLength) {
	std::vector<string> parameters = strUtil::split(fileLine, ",");
	this->time = std::stoi(parameters[0]);
	this->beatLength = std::stof(parameters[1]);
	this->uninherited = (bool)std::stoi(parameters[6]);

	if (this->uninherited) {
		this->latestNonInheritedBeatLength = this->beatLength;
	}
	else {
		this->latestNonInheritedBeatLength = latestNonInheritedBeatLength;
	}
}
float TimingPoint::getPracticalSliderMultiplier(float sliderMultiplier) const {
	const float SV = this->uninherited ? 1 : -100.0f / this->beatLength;
	return this->latestNonInheritedBeatLength / (sliderMultiplier * 100 * SV);
};