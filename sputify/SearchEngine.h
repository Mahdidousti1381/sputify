#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "Constants.h"
#include "Person.h"
#include "MUSIC.h"
#include "Playlist.h"
class SearchEngine{
public:
SearchEngine();
bool findUserById();
Person* findPersonById(std::vector<Person*> accs, int const id);
Person* findPersonByName(std::vector<Person*> accs, std::string name);
MUSIC* findMusicById(std::vector<MUSIC*> allMusics , int const id);
Playlist* findPlaylistByName(std::vector<Playlist*> allPlaylists , std::string name);
Playlist* findPlaylistPro(std::vector<Playlist*> allPlaylists , std::string name , int CId);

std::vector<MUSIC*> superSearch(std::vector<MUSIC*> & musics,std::string name , std::string singer , std::string genre);
bool isWordInString(const std::string& sentence, const std::string& word) ;

};
#endif