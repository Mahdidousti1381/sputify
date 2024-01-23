#ifndef PERSON_H
#define PERSON_H
#include "Constants.h"
#include "MUSIC.h"
#include "Playlist.h"
class Person
{
public:
    int id;
    std::string name;
    std::string password;
    std::string mode;
    std::vector<MUSIC *> artistMusics;
    std::vector<Playlist *> userPlaylists;
    std::vector<Person*> followers;
    std::vector<Person*> followings;
    std::vector<MUSIC*> likedSongs;
    std::vector<MUSIC *> recommendations;
    void eraseFromPlaylist(MUSIC *deleteThis);
    void deleteFromFavorites(MUSIC* deleteIt);
    void deletePlaylist(Playlist* deleteIt);
    virtual void introduce()=0;
    virtual void introduceCompletely()=0;
    virtual void sortPlaylists(std::vector<Playlist *> &userPlaylists)=0;
    virtual void printYourProperties()=0;

};
#endif