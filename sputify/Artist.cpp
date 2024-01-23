#include "Artist.h"

void Artist::introduce(){
    std::cout<<this->id<<commaSpaceStr<<this->mode<<commaSpaceStr<<this->name<<commaSpaceStr<<this->artistMusics.size()<<std::endl;
}
void Artist::introduceCompletely(){

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
    
    std::cout<<songsColon;
    if(this->artistMusics.size() == 0 )    
        std::cout<<std::endl;

    for(size_t i=0;i<this->artistMusics.size();i++){
        if(i == this->artistMusics.size()-1){
            std::cout<< this->artistMusics[i]->get_name()<<std::endl;
        }
        else
            std::cout<< this->artistMusics[i]->get_name()<<commaSpaceStr;
    }
}
void Artist::sortPlaylists(std::vector<Playlist*>& userPlaylists) {}
void Artist::printYourProperties(){
    std::cout<<getRegisteredMusicsTitle<<std::endl;
    for(MUSIC* s:this->artistMusics){
        s->introduceCompletely();
    }
}

