#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h> // close(socket)

#include <string>
#include <vector>
#include <iostream>

bool connect(std::string ip, int port)
{
	int clientSock=socket(AF_INET,SOCK_STREAM, 0);

    // 192.168.180.96 luca
    // 192.168.180.107 ale
    // netcat -l <portnumber>
    // netcat <ipaddress> <portnumber>
	
	sockaddr_in serverAddress;
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port=htons(port);
	serverAddress.sin_addr.s_addr=inet_addr(ip.c_str());
	
	int result = connect(clientSock, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr));
    // std::cout << result << std::endl;
    if (result != 0) {
        if (errno != 111 && errno != 107 && errno != 9) {
            std::cout << "errno: " << errno << std::endl;
        }
        // shutdown(clientSock, SHUT_RDWR);
        shutdown(clientSock, SHUT_RDWR);
        close(clientSock);
    }
    return (result == 0);
}

int main()
{
    // ports:
    // well known: 0 through 1023
    // iana registered: 1024 through 49151
    // private: 49152 through 65535
    for (int i = 1; i < 65535; i++) {
    // for (int i = 1233; i < 1235; i++) {
        // if (connect ("192.168.180.96", i)) {
        if (connect ("192.168.81.105", i)) {
            std::cout << i << std::endl;
        }
    }
}
