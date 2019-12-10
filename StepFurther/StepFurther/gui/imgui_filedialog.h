#pragma once
#include <cstdio>
#include <cstring>
#include <string>

#ifdef _WIN32

#include <windows.h>
#include <Commdlg.h>
// for _getcwd
#include <direct.h>

#define GetCurrentDir _getcwd
#define SetCurrentDir _chdir
// solve collision with std::max()
#undef max
#undef min

#else
#include <unistd.h>
#define GetCurrentDir getcwd
#define SetCurrentDir chdir
#endif

std::string GetCurrentWorkingDir(void) {
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

void SetCurrentWorkingDir(const std::string& dir) {
	SetCurrentDir(dir.c_str());
}

namespace ImGui {
	std::string file_dialog_open();

	std::string file_dialog_save();

}

// see https://github.com/libigl/libigl/blob/master/include/igl/file_dialog_open.cpp
std::string ImGui::file_dialog_open() {
	const int FILE_DIALOG_MAX_BUFFER = 1024;
	char buffer[FILE_DIALOG_MAX_BUFFER];

#ifdef __APPLE__
	// For apple use applescript hack
	FILE* output = popen(
		"osascript -e \""
		"   tell application \\\"System Events\\\"\n"
		"           activate\n"
		"           set existing_file to choose file\n"
		"   end tell\n"
		"   set existing_file_path to (POSIX path of (existing_file))\n"
		"\" 2>/dev/null | tr -d '\n' ", "r");
	while (fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL)
	{
	}
#elif defined _WIN32

	// Use native windows file dialog box
	// (code contributed by Tino Weinkauf)

	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = new wchar_t[100];
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"*.*\0";//off\0*.off\0obj\0*.obj\0mp\0*.mp\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
	int pos = 0;
	if (GetOpenFileName(&ofn) == TRUE)
	{
		while (ofn.lpstrFile[pos] != '\0')
		{
			buffer[pos] = (char)ofn.lpstrFile[pos];
			pos++;
		}
	}
	buffer[pos] = 0;
#else

	// For linux use zenity
	FILE* output = popen("/usr/bin/zenity --file-selection", "r");
	while (fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL)
	{
	}

	if (strlen(buffer) > 0)
	{
		buffer[strlen(buffer) - 1] = 0;
	}
#endif
	return std::string(buffer);
}

std::string ImGui::file_dialog_save()
{
	const int FILE_DIALOG_MAX_BUFFER = 1024;
	char buffer[FILE_DIALOG_MAX_BUFFER];
#ifdef __APPLE__
	// For apple use applescript hack
	// There is currently a bug in Applescript that strips extensions off
	// of chosen existing files in the "choose file name" dialog
	// I'm assuming that will be fixed soon
	FILE* output = popen(
		"osascript -e \""
		"   tell application \\\"System Events\\\"\n"
		"           activate\n"
		"           set existing_file to choose file name\n"
		"   end tell\n"
		"   set existing_file_path to (POSIX path of (existing_file))\n"
		"\" 2>/dev/null | tr -d '\n' ", "r");
	while (fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL)
	{
	}
#elif defined _WIN32

	// Use native windows file dialog box
	// (code contributed by Tino Weinkauf)

	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;//hwnd;
	ofn.lpstrFile = new wchar_t[100];
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
	int pos = 0;
	if (GetSaveFileName(&ofn) == TRUE)
	{
		while (ofn.lpstrFile[pos] != '\0')
		{
			buffer[pos] = (char)ofn.lpstrFile[pos];
			pos++;
		}
		buffer[pos] = 0;
	}

#else
	// For every other machine type use zenity
	FILE* output = popen("/usr/bin/zenity --file-selection --save", "r");
	while (fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL)
	{
	}

	if (strlen(buffer) > 0)
	{
		buffer[strlen(buffer) - 1] = 0;
	}
#endif
	return std::string(buffer);
}
