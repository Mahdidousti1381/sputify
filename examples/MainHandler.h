#ifndef MAINHANDLER_H 
#define MAINHANDLER_H
#include "../server/server.hpp"
#include "handlers.hpp"
class MainHandler{
public:
void mapServerPaths(Server& server);
MainHandler(Sputify* sputify , Server& server);
Sputify* sp;
};
#endif