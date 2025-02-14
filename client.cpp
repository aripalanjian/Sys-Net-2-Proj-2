#include "client.hpp"

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
}

void Client::run(){
    std::string templatesPath;
    std::string relativeTemplatesPath = "templates";
    realpath(relativeTemplatesPath.data(), templatesPath.data());
    char* args[] = {templatesPath.data()};

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
            getline(std::cin, input);

            //Split input into request options
            std::stringstream ss{input};
            std::vector<std::string> request;
            for (std::string tmp{}; std::getline(ss, tmp, ' '); request.push_back(tmp)) {}
            for(std::string s: request){
                std::cout << s << " ";
            }
            std::cout << '\n';

            if (request.at(0).compare("ls")){
                
                int child = fork();
                if (child == 0) {
                    std::cout << '\n';
                    execvp("ls", args);
                    std::cout << '\n';
                }
            } else {
                if (request.at(0).compare("GET")){
                    // request.clear();
                    // request = std::string("") + request.at(0) + request.at(1);// + DEFAULT_PROTOCOL;
                    input += std::string(" ") + DEFAULT_PROTOCOL;
                    send(tcp_client_socket, input.data(), input.size(), 0);
                    recv(tcp_client_socket, buffer.data(), buffer.size(), 0);
                }
            }
        }
    }
}

int main() {

    Client c(false, "51002");
    c.run();
}