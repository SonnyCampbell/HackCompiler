// HackCompiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "JackTokenizer.h"

std::wstring string_to_wstring(const std::string&);

int main()
{

	std::vector<std::wstring> files;
	std::string search_path = "../../projects/10/Square/";
	WIN32_FIND_DATA fd;

	HANDLE hFind = ::FindFirstFile(string_to_wstring(search_path + "*.jack").c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				files.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	
	

	for (auto file : files)
	{
		std::ofstream outputFile;
		std::string f(file.begin(), file.end());
		JackTokenizer* tokenizer = new JackTokenizer(search_path + f);

		size_t ext = f.find_first_of(".");
		std::string fileNameStart = f.substr(0, ext);
		outputFile.open(search_path + "my" + fileNameStart + "T.xml");









		delete tokenizer;
	}

    return 0;
}


std::wstring string_to_wstring(const std::string& str) {
	return std::wstring(str.begin(), str.end());
}
