// fileExplorer.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "fileExplorer.h"

CHAR fileList[MAX_FILE_LIST];

#pragma warning(disable:4996)

extern "C"
{
	__declspec(dllexport) char * fileExplorer(const char * dir) {
		HANDLE hFind;
		WIN32_FIND_DATA findData;
		char dirTmp[100];
		memset(dirTmp, 0, sizeof(dirTmp));
		memset(fileList, 0, MAX_FILE_LIST);
		strcpy(dirTmp, dir);
		strcat(dirTmp, "*.*");
		hFind = FindFirstFile(dirTmp, &findData);
		if (hFind == INVALID_HANDLE_VALUE)
		{
			return 0;
		}
		do {
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// is directory
				strcat(fileList, findData.cFileName);
				strcat(fileList, " ");
				strcat(fileList, "0\n");
			}
			else
			{
				// is file
				strcat(fileList, findData.cFileName);
				strcat(fileList, " ");
				strcat(fileList, "1\n");
			}
		} while (FindNextFile(hFind, &findData));
		return fileList;
	}
}