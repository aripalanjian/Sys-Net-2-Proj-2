#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <time.h>
// #include <stdlib.h>


#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
typedef int SOCKET;
#define INVALID_SOCKET ~0

class Client{
    SOCKET tcp_client_socket;
    struct sockaddr_in tcp_server_address;
    std::string DEFAULT_PORT;
    std::string DEFAULT_PROTOCOL;
    bool debug;
    bool running;

public:
    Client(bool debug, std::string portno);
    ~Client();

    void run();
};

#endif