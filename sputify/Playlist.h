#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "Constants.h"
#include "MUSIC.h"
class Playlist
{
public:
    Playlist(std::string name_);
    int creatorId;
    std::string name;
    std::vector<MUSIC *> containingMusics;
    void eraseMusic(MUSIC *deleteIt);
    void introduce();
    void updateDuration();
    std::string durationStr;

private:
    int totalSeconds;
    void updateDurationString();

};

#endif