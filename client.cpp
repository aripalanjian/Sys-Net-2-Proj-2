#include "client.hpp"
#include <sys/wait.h>
#include <errno.h>

Client::Client(bool debug, std::string portno){
    running = false;
    tcp_client_socket = INVALID_SOCKET;
    this->debug = debug;
    DEFAULT_PORT = portno;
    DEFAULT_PROTOCOL = "HTTP/1.1";

    tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0);

    tcp_server_address.sin_family = AF_INET;
    tcp_server_address.sin_addr.s_addr = INADDR_ANY;
    tcp_server_address.sin_port = htons(std::stoi(DEFAULT_PORT));
}

Client::~Client(){
    close(tcp_client_socket);
    int status;
    wait(&status);
}

void Client::run(){

    std::cout << "  Options: \n    ls\t\t\t  list of html files found in templates"
                << "\n    GET /<file_name>\t  show HTML code for give file"
                << "\n    POST <message>\t  send message to server\n\n";
    // execvp("ls", args);
    
    int connection_status = connect(tcp_client_socket, reinterpret_cast<struct sockaddr *>(&tcp_server_address), sizeof(tcp_server_address));     //params: which socket, cast for address to the specific structure type, size of address
    if (connection_status == -1) {                                                                                         //return value of 0 means all okay, -1 means a problem
        std::cout << "Problem connecting to the socket! Sorry!! \n";
    } else {
        //start client loop
        running = true;
        std::string buffer(1024,'\0');
        std::string request;
        std::string input;

        while (running) {
            std::cout << "client$ ";
            getline(std::cin, input);

            if (input.compare("quit") == 0 || input.compare("exit") == 0) break;

            //Split input into request options
            std::stringstream ss{input};
            std::vector<std::string> request;
            for (std::string tmp{}; std::getline(ss, tmp, ' '); request.push_back(tmp)) {}
            if (debug) {
                for(std::string s: request){
                    std::cout << s << " ";
                }
                std::cout << '\n';
            }

            if (request.at(0).compare("exit") == 0){
                running = false;
            } else if (request.at(0).compare("ls") == 0){
                int child = fork();
                
                if (child == 0) {
                    std::string relativeTemplatesPath = "templates";
                    
                    char* args[] = {"ls", relativeTemplatesPath.data()};
                    
                    if (debug)       
                        std::cout << " **child** searching path: " << relativeTemplatesPath <<'\n';
                    
                    execvp("ls", args);
                    exit(0);
                }
                sleep(1); //ensure input is on same line as prompt
            } else {
                if (request.at(0).compare("GET") == 0){
                    input += std::string(" ") + DEFAULT_PROTOCOL;

                    int conn = send(tcp_client_socket, input.data(), input.size(), 0);
                    std::cout << "Connection Error: " << conn << '\n';
                    if (conn == -1){
                        connection_status = connect(tcp_client_socket, reinterpret_cast<struct sockaddr *>(&tcp_server_address), sizeof(tcp_server_address));
                        conn = send(tcp_client_socket, input.data(), input.size(), 0);
                        if (connection_status == -1 || conn == -1){
                            std::cout << "Error: Couldn't maintain server connection.";
                            break;
                        }
                        
                    }

                    std::cout << "  Response: [\n    " ;
                    std::string msg;
                    while (true) {
                        auto size = recv(tcp_client_socket, buffer.data(), buffer.size(), 0);
                        std::cout << "Msg size: " << size << "\n";
                        if (size == 0) {
                            msg += buffer;
                            break;
                        } else if (size == -1) {
                            std::cout << "Error: " << strerror(errno);
                        } else{
                            msg += buffer;
                        }
                        std::cout << buffer;
                    }
                    std::cout << "\n  ]\n";
                }
            }
        }
    }
}

int main(int argC, char** argV) {
    bool debug = false;
    std::string portno = "51002";
    if (argC > 1){
        for (int i = 1; i < argC; i++){
            if (strcmp(argV[i], "-d") == 0){
                debug = true;
                std::cout << "Debug Mode\n";
            } else {
                portno = argV[i];
            }
        }
    }
    Client c(debug , portno);
    c.run();
}