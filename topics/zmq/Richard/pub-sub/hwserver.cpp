//
// Publisher
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
    zmq::socket_t socket(context, ZMQ_PUB);
    socket.bind("tcp://*:5555");

    std::vector<std::string> stuff{"100", "200", "210", "235", "250", "300", "350"};

    while (true) {
        for (auto item : stuff) {
            //  slow down
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            // prepare the message
            std::string message = item + " - message started with " + item;

            zmq::message_t tempo_pub(message.size());
            memcpy(tempo_pub.data(), message.data(), message.size());

            //  Send message to all subscribers
            socket.send(tempo_pub);
            std::cout << "Sent message: " << message << std::endl;
        }
    }

    return 0;
}

