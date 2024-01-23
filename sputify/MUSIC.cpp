#include "MUSIC.h"
#include "Constants.h"
MUSIC::MUSIC(std::string name_, std::string creatorName_,int creatorId_, std::string AlbumName_, std::string path_, std::string tagsString_,
             int year_, int id_, int h_, int m_, int s_ , std::string durStr_)
{
    this->name = name_;
    this->creatorName = creatorName_;
    this->creatorId = creatorId_;
    this->AlbumName = AlbumName_;
    this->path = path_;
    this->tagsString = tagsString_;
    this->year = year_;
    this->id = id_;
    this->hours = h_;
    this->minutes = m_;
    this->seconds = s_;
    this->durationString = durStr_;
    calcLength();
    likesCount =0;
}
void MUSIC::introduce()
{
    std::cout << id << commaSpaceStr << name << commaSpaceStr << creatorName << std::endl;
}
void MUSIC::recommendYourself(){
    std::cout << id << commaSpaceStr << name << commaSpaceStr << creatorName << commaSpaceStr <<likesCount << std::endl;
}
void MUSIC::introduceCompletely()
{
    std::cout << id << commaSpaceStr << name << commaSpaceStr << creatorName << commaSpaceStr << year << commaSpaceStr << AlbumName << commaSpaceStr << tagsString << commaSpaceStr << durationString << std::endl;
}
void MUSIC::calcLength()
{
    this->length = hours * 3600 + minutes * 60 + seconds;
}