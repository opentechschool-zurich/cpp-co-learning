//
//  Client
//
#include <zmq.hpp>
#include <string>
#include <vector>
#include <iostream>

int main() {
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);

    std::cout << "Client Connecting to socket loclhost:5555..." << std::endl;
    socket.connect("tcp://localhost:5555");

    //  subscription list
    std::vector<std::string> subList{"200", "250", "350"};

    // subscribe to elements in the list
    for (auto subName : subList) {
        socket.setsockopt(ZMQ_SUBSCRIBE, subName.c_str(), subName.size());
        std::cout << "Subscribed to: " << subName << std::endl;
    }

    //  Get the reply.
    zmq::message_t reply;
    while (socket.recv(&reply)) {
        std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
        std::cout << "Client Received: " << message << std::endl;
    }
    return 0;
}