#include <iostream>
#include <string>
#include <zmq.hpp>


#ifndef _WIN32
#include <unistd.h>
#include <pthread.h>
#else
#include <windows.h>
#define sleep(n)	Sleepo(n)
//#include <threads windows ??>
#endif


void* writer_worker(void* arg)
{
	std::cout << "Starting writer.." << std::endl;
	zmq::context_t *context = (zmq::context_t *) arg;

	zmq::socket_t socket (*context, ZMQ_PAIR);
	socket.connect ("inproc://my_comm_channel");

	std::cout << "now loop.." << std::endl;
	while (1) {
		std::string message { "hello inproc :)" };

		zmq::message_t msg( message.size() );
		memcpy( msg.data(), message.data(), message.size() );

		socket.send( msg );

		sleep(1);
	}
	return nullptr;
}

void* reader_worker(void* arg)
{
	std::cout << "Starting reader.." << std::endl;
	zmq::context_t *context = (zmq::context_t *) arg;

	zmq::socket_t socket (*context, ZMQ_PAIR);
	socket.bind ("inproc://my_comm_channel");

	zmq::message_t msg;
	while (socket.recv (&msg) ) {
		std::string message = std::string(static_cast<char*>(msg.data()), msg.size());
        	std::cout << "reader: " << message << std::endl;
	}
	return nullptr;
}

int main() {

	zmq::context_t context (1);
	//zmq::socket_t workers (context, ZMQ_);
	//workers.bind ("inproc://my_comm_channel");
 
	pthread_t writer;
	pthread_t reader;

	// if the writer connects to ZMQ_PAIR before the reader binds it an error occurs
	// but using threads it's not possible to be sure the reader actually binds before the writer tries to connect 
	pthread_create(&reader, NULL, reader_worker, (void*) &context);
	pthread_create(&writer, NULL, writer_worker, (void*) &context);

	pthread_join(writer, NULL);
	pthread_join(reader, NULL);
	
}

