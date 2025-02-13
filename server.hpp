/***************************************************************
  Student Name: Ari Palanjian
  Class Name: Systems and Networks II
  Project 1

  Server Header file to define Server class
***************************************************************/

#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <time.h>


#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
typedef int SOCKET;
#define INVALID_SOCKET ~0

class Server {
    char hostname[256];
    SOCKET serverSocket;
    sockaddr_in address{};
    bool running;
    bool debug;
    std::string DEFAULT_PORT;

    std::vector<std::thread> threads;
public:
    Server(bool debug, std::string portno);
    ~Server();

    void run();
    void serverThread(const SOCKET& socket);

    std::vector<std::string> parseRequest(const std::string&);
    std::vector<std::string> parseHeader(const std::string&);
    std::unordered_map<std::string,std::string> requestToMap(const std::vector<std::string>& request);

    static const std::string formGetResponse(std::string uri, std::string protocol);
    bool formPostResponse(std::unordered_map<std::string,std::string> &);
};



#endif //SERVER_HPP