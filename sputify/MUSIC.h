#ifndef MUSIC_H
#define MUSIC_H
#include "Constants.h"
class MUSIC
{
public:
    MUSIC(std::string name_, std::string creatorName_, int creatorId_, std::string AlbumName_, std::string path_, std::string tagsString_,
          int year_, int id_, int h_, int m_, int s_, std::string durStr_);
    int get_length() { return length; }
    std::string get_AlbumName() { return AlbumName; }
    std::string get_name() { return name; }
    std::string get_path() { return path; }
    std::string get_creatorName() { return creatorName; }
    std::string get_tagsString() { return tagsString; }
    std::string get_durationString() { return durationString; }
    std::string get_yearString() { return std::to_string(year); }

    int likesCount;
    void introduce();
    void recommendYourself();
    void introduceCompletely();
    int id;
    int creatorId;


private:
    std::string name;
    std::string path;
    std::string creatorName;
    std::string AlbumName;
    std::string tagsString;
    std::vector<std::string> tags;
    int year;
    int length;
    int hours;
    int minutes;
    int seconds;
    std::string durationString;
    void calcLength();
};
#endif