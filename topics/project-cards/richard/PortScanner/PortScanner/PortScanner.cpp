// PortScanner.cpp : Defines the entry point for the console application.
// @see http://members.tripod.com/frenchwhales_site/winsockt/Lesson1.htm
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <winsock2.h>
#include <atlstr.h>

#pragma comment(lib, "ws2_32.lib")

WSADATA wsda;        // Structure to store info returned from WSAStartup

struct hostent *host;     // Used to store information retreived about the server

char szMessage[80];
int iMessageLen;
int ret;


char szInBuffer[128];
int iBufferLen;

char szAddress[64];
int iPort;

SOCKET tcpSocket;       // Our TCP socket handle

#define MESSAGE         "Hello, Server!\n"

std::string getErrorDescription(DWORD err) {
LPWSTR errString = NULL;
int size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
	FORMAT_MESSAGE_FROM_SYSTEM, // use windows internal message table
	0,       // 0 since source is internal message table
	err, // this is the error code returned by WSAGetLastError()
		 // Could just as well have been an error code from generic
		 // Windows errors from GetLastError()
	0,       // auto-determine language to use
	(LPWSTR)&errString, // this is WHERE we want FormatMessage
						// to plunk the error string.  Note the
						// peculiar pass format:  Even though
						// errString is already a pointer, we
						// pass &errString (which is really type LPSTR* now)
						// and then CAST IT to (LPSTR).  This is a really weird
						// trip up.. but its how they do it on msdn:
						// http://msdn.microsoft.com/en-us/library/ms679351(VS.85).aspx
	0,                 // min size for buffer
	0);               // 0, since getting message from system tables

std::string errMsg = CW2A(errString);



LocalFree(errString); // if you don't do this, you will get an
					  // ever so slight memory leak, since we asked
					  // FormatMessage to FORMAT_MESSAGE_ALLOCATE_BUFFER,
					  // and it does so using LocalAlloc
					  // Gotcha!  I guess.
return errMsg;
}

void scanPort(std::string ip, int port) {
	std::cout << "Scanning: " << ip << " port: " << port << std::endl;

	// Copy the pre-defined message into a buffer
	strcpy(szMessage, MESSAGE);

	iMessageLen = strlen(szMessage);

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	
		tcpSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (tcpSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		//freeaddrinfo(result);
		WSACleanup();
		return;
	}
	else {
		std::cout << "Got socket\n";
	}

	SOCKADDR_IN serverAddress; // The host's address
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr(ip.c_str());

	{
		host = NULL;
		printf("Resolving host...");
		host = gethostbyname(szAddress); // Get the IP address of the server
										 // and store it in host
		if (host == NULL)
		{
			printf("Error\nUnknown host: %s\n", szAddress);
			exit(1);
		}
		memcpy(&serverAddress.sin_addr, host->h_addr_list[0],
			host->h_length);
		printf("OK\n");
		std::string hostaddr = inet_ntoa(serverAddress.sin_addr);
		std::cout << "Resolved to: " << hostaddr << std::endl;
	}

	int con = connect(tcpSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr));
	if (con == SOCKET_ERROR) {
		DWORD err = GetLastError();

		std::cout << "Error " << err << ": " << getErrorDescription(err) << std::endl;


	}
	else {
		std::cout << "Connection OK\n";
	}

	closesocket(tcpSocket);
}

void scanPorts(std::string ip, int lowPort, int highPort) {
	for (int port = lowPort; port <= highPort; port++) {
		scanPort(ip, port);
	}
}

int main()
{
	// Load version 2.0 of Winsock
	WSAStartup(MAKEWORD(2, 0), &wsda);
	scanPorts("localhost", 135, 142);
	WSACleanup();
}

