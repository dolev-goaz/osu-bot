#pragma once
#include <string>
#include <vector>

using std::string;
using std::wstring;
using std::string_view;
using std::wstring_view;

namespace strUtil {
	wstring getDirectoryName(const wstring& path);

	wstring_view getMapDiff(const wstring& mapNameDiff);
	wstring_view getMapName(const wstring& mapNameDiff);

	wstring replace(const wstring& src, const wstring& substr, const wstring& newSubstr);

	std::vector<string> split(const string& s, const string& delim, size_t maxOccurances = SIZE_MAX);
	std::vector<string> split(const string& s, const string& delim, string& remainder, size_t maxOccurances = SIZE_MAX);

	bool endsWith(const wstring& str, const wstring& postfix);

	wstring formatMapName(const wstring& mapName);
}