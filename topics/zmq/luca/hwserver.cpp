//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <vector>
#include <iostream>

#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)	Sleep(n)
#endif

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUB);
    socket.bind ("tcp://*:5555");

    // make and init a group of addresses to be published
    std::vector<std::string> ids {"100", "200", "210", "235", "250", "300", "350"};
    
    for ( auto id : ids ) {

        //  Do some 'work'
    	sleep(2);

        // prepare the message
	std::string message = id + " \"that's the address!\"";
        zmq::message_t tempo_pub( message.size() );
        memcpy (tempo_pub.data(), message.data(), message.size() );

        //  Send message to all subscribers
        socket.send (tempo_pub);
	std::cout << "Sent message for ID: " << id << std::endl;
    }

    return 0;
}
