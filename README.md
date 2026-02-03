# Osu! Bot

## Preview
https://github.com/user-attachments/assets/005ab042-0d8e-4a4e-9369-6f9bdc2f41be

## File Structure
```
.
│   beatmapParser.cpp
│   beatmapParser.h
│   beatmapPlayer.cpp
│   beatmapPlayer.h
│   fileHelper.cpp
│   fileHelper.h
│   globalDef.h
│   mathHelper.cpp
│   mathHelper.h
│   objects.cpp
│   objects.h
│   objects_play.cpp
│   OsuBotCPP.cpp
│   osuLoader.cpp
│   osuLoader.h
│   stringHelper.cpp
│   stringHelper.h
│   windowsHelper.cpp
│   windowsHelper.h
```

## Short explanation
1. Extracts the Currently playing song and difficulty from the osu! process' window title
2. Finds the relevant folder containing the map's data
3. Loads it into memory
4. Starts playing.

Doesn't support bezier curves.
