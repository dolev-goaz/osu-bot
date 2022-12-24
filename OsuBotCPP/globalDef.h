#pragma once
#include <string>
using std::string;

 struct Point {
	int x;
	int y;
};

 struct PointF {
	 float x;
	 float y;
 };

struct MapInfo {
	int AudioLeadIn;
	float SliderMultiplier;
};

class TimingPoint {
public:
	float beatLength;
	bool uninherited;
	int time;
	TimingPoint(const string& fileLine, float latestNonInheritedBeatLength);
	// Returns the multiplier based on if the current timing point is inherited
	float getPracticalSliderMultiplier(float sliderMultiplier) const;
private:
	float latestNonInheritedBeatLength;
};