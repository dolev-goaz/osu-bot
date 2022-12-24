#include "fileHelper.h"

std::list<wstring> filesMatchingSubstr(const wstring& parentDirectory, const wstring& substring) 
{
	std::list<wstring> output;
	wstring pathString;
	for (auto& p : fs::directory_iterator(parentDirectory))
	{
		pathString = p.path().wstring();
		if (pathString.find(substring, 0) != wstring::npos) {
			output.push_back(pathString);
		}
	}

	return output;
}

std::list<wstring> directoriesMatchingSubstr(const wstring& parentDirectory, const wstring& substring) {
	std::list<wstring> files = filesMatchingSubstr(parentDirectory, substring);

	std::list<wstring> output;
	for (wstring& path : files) {
		if (fs::is_directory(path)) {
			output.push_back(path);
		}
	}

	return output;
}

wstring findMapFileByCandidateSongs(std::list<wstring>& candidates, wstring& difficulty) {
	wstring postFix = difficulty + L".osu";
	for (wstring candidatePath : candidates) {
		std::list<wstring> songFiles = filesMatchingSubstr(candidatePath, difficulty);

		for (wstring songFile : songFiles) {
			if (strUtil::endsWith(songFile, postFix)) {
				return songFile;
			}
		}

	}
	return L"";

	return L"";
}