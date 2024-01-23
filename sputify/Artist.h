#ifndef ARTIST_H
#define ARTIST_H
#include "MUSIC.h"
#include "Person.h"
#include "Playlist.h"
class Artist : public Person
{
protected:
void introduce()override;
void introduceCompletely()override;
void sortPlaylists(std::vector<Playlist*>& userPlaylists) override;
void printYourProperties()override;
};
#endif