#include <iostream>
#include <future>
#include "beatmapParser.h"
#include "osuLoader.h"

void closeCallBack() {
    winUtil::waitForKeyPress(VK_ESCAPE);
    winUtil::mouseRelease();
    std::cout << "Program Aborted" << std::endl;
    exit(-1);
}

void playBeatmap(std::list<OsuObject*>& objects, std::queue<TimingPoint>& timingPoints, MapInfo mapInfo) {
    clock_t startTime, endTime;
    int currentTime = 0;

    TimingPoint currentTimingPoint = timingPoints.front();
    timingPoints.pop();

    for (OsuObject* object : objects) {
        startTime = clock();

        // Get the current timing point
        while (!timingPoints.empty() && timingPoints.front().time <= object->time) {
            currentTimingPoint = timingPoints.front();
            timingPoints.pop();
        }

        object->Play(currentTime, currentTimingPoint, mapInfo);
        endTime = clock();

        currentTime = currentTime + (endTime - startTime);
    }
}

int main()
{
    beatmapParser parser(osuLoader::getCurrentMapPath());
    std::wcout << osuLoader::getCurrentMapName() << std::endl;
    std::wcout << osuLoader::getCurrentMapPath() << std::endl;
    parser.loadCurrentMap();
    std::cout << "Press LSHIFT to start playing the map." << std::endl;

    winUtil::waitForKeyPress(VK_LSHIFT);
    auto close = std::async(std::launch::async, closeCallBack);

    playBeatmap(parser.objects, parser.timingPoints, parser.mapInfo);
}