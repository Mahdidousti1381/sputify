#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <exception>
const std::string badReq = "Bad Request";
const std::string notFound = "Not Found";
const std::string permissionDen = "Permission Denied";
const std::string emptyStr = "Empty";

const std::string getMusicsTitleStr = "ID, Name, Artist";
const std::string getRecommendationsTitleStr = "ID, Name, Artist, Likes";
const std::string getMusicTitleStr = "ID, Name, Artist, Year, Album, Tags, Duration";
const std::string getUsersTitleStr = "ID, Mode, Username, Playlists_number/Songs_number";
const std::string getPlaylistsTitle = "Playlist_name, Songs_number, Duration";
const std::string getRegisteredMusicsTitle = "ID, Name, Artist, Year, Album, Tags, Duration";
const std::string idColon = "ID: ";
const std::string modeColon = "Mode: ";
const std::string usernameColon = "Username: ";
const std::string playlistsColon = "Playlists: ";
const std::string songsColon = "Songs: ";
const std::string commaSpaceStr = ", ";
const std::string followingsColon = "Followings: ";
const std::string followersColon = "Followers: ";


const std::string usernameStr = "username";
const std::string passwordStr = "password";
const std::string playlistStr = "playlist";
const std::string Music = "music";
const std::string Mode = "mode";
const std::string Title = "title";
const std::string Path = "path";
const std::string Year = "year";
const std::string Album = "album";
const std::string Tags = "tags";
const std::string Duration = "duration";
const std::string Name = "name";
const std::string Ok = "OK";
const char colon = ':';


const std::string signupStr = "signup";
const std::string loginStr = "login";
const std::string musicStr = "music";
const std::string musicsStr = "musics";
const std::string logoutStr = "logout";
const std::string likeStr = "like";
const std::string likesStr = "likes";
const std::string recommendationsStr = "recommendations";
const std::string userStr = "user";
const std::string usersStr = "users";
const std::string artistStr = "artist";
const std::string searchMusicsStr = "search_music";
const std::string registeredMusicsStr = "registered_musics";
const std::string addPlaylistStr = "add_playlist";
const std::string nameStr = "name";
const std::string idStr = "id";
const std::string tagStr = "tag";
const std::string followStr = "follow";
const std::string unfollowStr = "unfollow";


const std::string not_a_valid_command = "This command is not valid in this http method";
const std::string arguments_doesnt_match = "arguments are not entered properly";
#endif
