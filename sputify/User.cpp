#include "User.h"

void User::introduce(){
    std::cout<<this->id<<commaSpaceStr<<this->mode<<commaSpaceStr<<this->name<<commaSpaceStr<<this->userPlaylists.size()<<std::endl;
}
void User::introduceCompletely(){
    std::cout<<idColon<<id<<std::endl;
    std::cout<<modeColon<<mode<<std::endl;
    std::cout<< usernameColon<<name<<std::endl;
    
    std::cout<< followingsColon;
if(this->followings.size() == 0 )    
        std::cout<<std::endl;
for(size_t i=0;i<this->followings.size();i++){
        if(i == this->followings.size()-1){
            std::cout<< this->followings[i]->name<<std::endl;
        }
        else 
            std::cout<< this->followings[i]->name<<commaSpaceStr;
    }
    std::cout<< followersColon;
    if(this->followers.size() == 0 )    
        std::cout<<std::endl;
    
for(size_t i=0;i<this->followers.size();i++){
        if(i == this->followers.size()-1){
            std::cout<< this->followers[i]->name<<std::endl;
        }
        else
            std::cout<< this->followers[i]->name<<commaSpaceStr;
    }
    std::cout<<playlistsColon;
    if(this->userPlaylists.size() == 0 )    
        std::cout<<std::endl;
    for(size_t i=0;i<this->userPlaylists.size();i++){
        if(i == this->userPlaylists.size()-1){
            std::cout<< this->userPlaylists[i]->name<<std::endl;
            return;
        }
        std::cout<< this->userPlaylists[i]->name<<commaSpaceStr;
    }
}
bool sortPlaylistsByName(const Playlist* a, const Playlist* b) {return a->name.compare(b->name) < 0;}
void User::sortPlaylists(std::vector<Playlist*>& userPlaylists) {
    std::sort(userPlaylists.begin(), userPlaylists.end(), sortPlaylistsByName);
}
void User::printYourProperties(){
    this->sortPlaylists(this->userPlaylists);
    std::cout<<getPlaylistsTitle<<std::endl;
    for(Playlist* p:this->userPlaylists){
        p->introduce();
    }
}
