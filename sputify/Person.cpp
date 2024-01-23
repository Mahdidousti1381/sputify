#include "Person.h"
void Person::eraseFromPlaylist(MUSIC *deleteThis)
{
    for (Playlist *p : userPlaylists)
    {
        p->eraseMusic(deleteThis);
    }
}

void Person::deletePlaylist(Playlist *deleteIt)
{
    auto it = std::find(this->userPlaylists.begin(), this->userPlaylists.end(), deleteIt);
    if (it != this->userPlaylists.end())
        this->userPlaylists.erase(it);
    else 
        throw std::runtime_error(notFound);
}
void Person::deleteFromFavorites(MUSIC *deleteIt)
{
    auto it = std::find(this->likedSongs.begin() , this->likedSongs.end(),deleteIt);
    this->likedSongs.erase(it);
}
