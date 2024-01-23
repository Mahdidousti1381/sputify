#include "SearchEngine.h"
SearchEngine::SearchEngine(){

}
Person* SearchEngine::findPersonById(std::vector<Person*> accs , int const id){
    for(size_t i=0;i<accs.size();i++){
        if(accs[i]->id == id){
            return accs[i];
        }
    }
    return nullptr;
}
Person* SearchEngine::findPersonByName(std::vector<Person*> accs , std::string name){
    for(size_t i=0;i<accs.size();i++){
        if(accs[i]->name == name){
            return accs[i];
        }
    }
    return nullptr;
}
MUSIC* SearchEngine::findMusicById(std::vector<MUSIC*> allMusics , int const id){
for(size_t i=0;i<allMusics.size();i++){
        if(allMusics[i]->id == id){
            return allMusics[i];
        }
    }
    return nullptr;
}
Playlist* SearchEngine::findPlaylistByName(std::vector<Playlist*> allPlaylists , std::string name){
for(size_t i=0;i<allPlaylists.size();i++){
        if(allPlaylists[i]->name == name){
            return allPlaylists[i];
        }
    }
    return nullptr;
}
Playlist* SearchEngine::findPlaylistPro(std::vector<Playlist*> allPlaylists , std::string name , int CId){
for(size_t i=0;i<allPlaylists.size();i++){
        if(allPlaylists[i]->name == name || allPlaylists[i]->creatorId == CId){
            return allPlaylists[i];
        }
    }
    return nullptr;
}

std::vector<MUSIC*> SearchEngine::superSearch(std::vector<MUSIC*> &musics, std::string name , std::string singer , std::string genre){
    std::vector<MUSIC*> foundMusics;
    for(MUSIC* s : musics){
            if(isWordInString(s->get_name(),name)&&isWordInString(s->get_creatorName(),singer) && isWordInString(s->get_tagsString(),genre)){
                foundMusics.push_back(s);
            }
    }
    return foundMusics;
}
bool SearchEngine::isWordInString(const std::string& sentence, const std::string& word) {
    if (sentence.find(word) != std::string::npos) {
        return true;
    } else {
        return false;
    }
}



