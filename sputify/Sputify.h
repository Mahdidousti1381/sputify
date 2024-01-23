#ifndef SPUTIFY_H
#define SPUTIFY_H
#include "Artist.h"
#include "User.h"
#include "MUSIC.h"
#include "Playlist.h"
#include "Demand.h"
#include "Constants.h"
#include "SearchEngine.h"
class Sputify
{
public:
Sputify();
Person* currentUser;
std::string run(std::string inputLine);
bool userState;
bool artistState;
std::vector<MUSIC *> foundMusics;
std::vector<MUSIC*> musics;
std::vector<Playlist*> playlists;
std::vector<Person*> artists;
std::vector<Person*> users;
std::vector<Person*> allUsers;
std::string playingMusicPath;
SearchEngine* browser = new SearchEngine;

private:


void handleSignup(Demand* req);
void handleLogout(Demand* req);
void handlelogin(Demand* req);
void handleMusicPost(Demand* req);
void handlePlaylistPost(Demand* req);
void handleFollow(Demand* req);
void handleUnfollow(Demand* req);
void handleLikeMusic(Demand* req);

void handleDeletemusic(Demand* req);
void handleDeletePlaylist(Demand* req);

void handleGettingMusics(Demand* req);
void handleGettingUsers(Demand *req);
void handleGettingUserPlaylists(Demand* req);
void handleGettingRegisteredMusics(Demand* req);
void handleSearchMusics(Demand* req);
void handleGetRecommendations(Demand* req);
void handleGetLikes(Demand* req);

void handleAddingMusicsToPlaylists(Demand* req);




int lastMusicId;
std::vector<Playlist*> currentUserPlaylists;
std::vector<MUSIC*> currentArtistMusics;

};
#endif