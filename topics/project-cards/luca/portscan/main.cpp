#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// needed to close() the socket
#include <unistd.h>

/**
 * Scann a single host:port 
 * Tries to open a TCP socket
 * @return true on success
*/
bool scanOne(const std::string &ip, int port, int timeout=1000) {

	int clientSock = socket(AF_INET,SOCK_STREAM, 0);
	
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons( port );
	serverAddress.sin_addr.s_addr = inet_addr( ip.c_str() );
	
	int result = connect(clientSock, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr));
	if (result==0) {
		// in case of successful connection close it greacefully
		close(clientSock);
		return true;
	}
	return false;
}

void scanTarget(const std::string &ip, std::vector<int> ports)
{
	std::cout << "Scanning target host: " << ip << std::endl;
	
	// 4. scan the ports

	for ( auto port : ports)  {
		std::cout << "checking " << port; std::cout << " .. ";
		if ( scanOne(ip, port) ) {

			std::cout << "got it!" << std::endl;
		}else{
			std::cout << "failed!" << std::endl;
		}
	}
	std::cout << std::endl; 
}
/*
std::pair< std::pair< std::vector<std::string>, std::vector<int> > checkInput()
{
	// 1.1 ip range
	std::vector<std::string> ips = {"192.168.180.107", "localhost"};
	// 1.2 port range
	std::vector<int> ports {22,80,1234};

	return std::pair< std::vector<std::string>, std::vector<int> >
}
*/

int main(int argc, char** aragv)
{
	// 1. get values from user
//	checkInput(argc, argv);

	// 1.1 ip range
	std::vector<std::string> ips = {"192.168.180.107", "127.0.0.1"};
	// 1.2 port range
	std::vector<int> ports {22,80,1234};

	// 1.3 timeout -- TODO

	// 2. ? prepare list of targets ???
	for ( auto ip : ips) {
		// 3. scan one target
		scanTarget(ip, ports);
	}
}
