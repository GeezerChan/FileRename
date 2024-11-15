#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void renameMp3Files(const wstring& folderPath, int removeChars) {
    wstring searchPath = folderPath + L"\\*.mp3";

    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        wcout << L"No MP3 files found in the specified folder." << endl;
        return;
    }

    vector<wstring> mp3Files;
    do {
        mp3Files.push_back(findFileData.cFileName);
    } while (FindNextFileW(hFind, &findFileData) != 0);
    FindClose(hFind);

    for (const auto& mp3File : mp3Files) {
        wstring oldFilePath = folderPath + L"\\" + mp3File;
        wstring newFileName = mp3File.substr(removeChars);
        wstring newFilePath = folderPath + L"\\" + newFileName;

        if (MoveFileW(oldFilePath.c_str(), newFilePath.c_str()) == 0) {
            wcout << L"Failed to rename file: " << mp3File << endl;
        }
        else {
            wcout << L"Renamed '" << mp3File << L"' to '" << newFileName << L"'" << endl;
        }
    }
}

int main() {
    wstring folderPath;
    int removeChars;

    wcout << L"Enter the folder path where MP3 files are located: ";
    wcin >> folderPath;

    wcout << L"Enter the number of characters to remove from the beginning of each filename: ";
    wcin >> removeChars;

    renameMp3Files(folderPath, removeChars);

    return 0;
}
