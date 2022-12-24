#pragma once
#include <list>
#include <string>
#include <filesystem>
#include "stringHelper.h"
using std::string;
using std::wstring;
namespace fs = std::filesystem;

std::list<wstring> directoriesMatchingSubstr(const wstring& parentDirectory, const wstring& substring);
wstring findMapFileByCandidateSongs(std::list<wstring>& candidates, wstring& difficulty);