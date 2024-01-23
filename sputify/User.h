#ifndef USER_H
#define USER_H
#include "Person.h"
#include "Playlist.h"
#include "MUSIC.h"
class User:public Person {

protected:
void introduce()override;
void introduceCompletely()override;
void sortPlaylists(std::vector<Playlist*>& userPlaylists) override;
void printYourProperties()override;
};
#endif 