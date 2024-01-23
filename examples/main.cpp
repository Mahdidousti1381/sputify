#include <iostream>
#include <string>

#include "../server/server.hpp"
#include "../sputify/Sputify.h"
#include "MainHandler.h"



int main(int argc, char** argv) {
    Sputify* sputify = new Sputify;
    try {
        int port = argc > 1 ? std::stoi(argv[1]) : 5000;
        Server server(port);
        MainHandler mainHandler(sputify , server);
        std::cout << "Server running on port: " << port << std::endl;
        server.run();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const Server::Exception& e) {
        std::cerr << e.getMessage() << std::endl;
    }
    return 0;
}
