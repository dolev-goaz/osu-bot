#include "stringHelper.h"

namespace strUtil {
	wstring getDirectoryName(const wstring& path)
	{
		const int fileSepInd = path.rfind('\\');
		if (fileSepInd >= 0)
		{
			return path.substr(0, fileSepInd);
		}
		return L"";
	}

	wstring_view getMapName(const wstring& mapNameDiff)
	{
		const int length = mapNameDiff.find('[') - 1; // space before '['
		return wstring_view(mapNameDiff.c_str(), length);
		//return mapNameDiff.substr(0, length);
	}
	wstring_view getMapDiff(const wstring& mapNameDiff)
	{
		const int startInd = mapNameDiff.find_last_of('[');
		const int endInd = mapNameDiff.find_last_of(']') + 1; // including ']'
		const int length = endInd - startInd;
		return wstring_view(mapNameDiff.c_str() + startInd, length);
		//return mapNameDiff.substr(startInd, length);
	}
	wstring replace(const wstring& src, const wstring& substr, const wstring& newSubstr)
	{
		const int substrLength = substr.length();

		size_t startPos = 0;
		wstring target = src;
		while ((startPos = target.find(substr, startPos)) != string::npos)
		{
			target.replace(startPos, substrLength, newSubstr);
			startPos += substrLength;
		}

		return target;
	}

	std::vector<string> split(const string& s, const string& delim, size_t maxOccurances) {
		string temp;
		return split(s, delim, temp, maxOccurances);
	}

	std::vector<string> split(const string& s, const string& delim, string& remainder, size_t maxOccurances) {
		std::vector<string> result;

		const size_t fullLength = s.length();
		const size_t delimLength = delim.length();

		size_t pos, prevPos = 0;
		do {
			pos = s.find(delim, prevPos);
			if (pos == string::npos) pos = fullLength;

			string token = s.substr(prevPos, pos - prevPos); // current token
			result.push_back(token);
			prevPos = pos + delimLength;

		} while (pos < fullLength && prevPos < fullLength && result.size() < maxOccurances);


		if (prevPos < fullLength) {
			remainder = s.substr(prevPos);
		}

		return result;
	}

	bool endsWith(const wstring& str, const wstring& postfix) {
		const size_t strLen = str.size();
		const size_t postFixLen = postfix.size();
		if (postFixLen > strLen) return false;

		return str.rfind(postfix) == (strLen - postFixLen);
	}

	wstring formatMapName(const wstring& mapName) {
		wstring tempStr = replace(mapName, L"/", L"_");
		tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), ':'), tempStr.end());
		return tempStr;
	}
}