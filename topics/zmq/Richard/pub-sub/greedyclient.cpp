//
//  Greedy Client - subscribes to all messages
//
#include <zmq.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);

    std::cout << "Client Connecting to socket loclhost:5555..." << std::endl;
    socket.connect("tcp://localhost:5555");

    socket.setsockopt(ZMQ_SUBSCRIBE, 0, 0);

    //  Get the reply.
    zmq::message_t reply;
    while (true) {
        if (socket.recv(&reply, ZMQ_NOBLOCK)) {
            std::string message = std::string(static_cast<char*> (reply.data()), reply.size());
            std::cout << "Client Received: " << message << std::endl;
        } else {
            std::cout << "idle\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    }
    return 0;
}