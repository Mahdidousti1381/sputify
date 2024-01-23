#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

#include "../server/server.hpp"
#include "../sputify/Sputify.h"


class LoginHandler : public RequestHandler
{
public:
    LoginHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class SignupHandler : public RequestHandler
{
public:
    SignupHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class LogoutHandler : public RequestHandler
{
public:
    LogoutHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class LibraryHandler : public RequestHandler
{
public:
    LibraryHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class MusicPostHandler : public RequestHandler
{
public:
    MusicPostHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};

class PlaylistPostHandler : public RequestHandler
{
public:
    PlaylistPostHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class DeleteMusicHandler : public RequestHandler
{
public:
    DeleteMusicHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class DeletePlaylistHandler : public RequestHandler{
    public:
    DeletePlaylistHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class AddToPlaylistHandler : public RequestHandler{
    public:
    AddToPlaylistHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class MusicSearchHandler : public RequestHandler{
    public:
    MusicSearchHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class FoundMusicsHandler: public RequestHandler{
    public:
    FoundMusicsHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class RecomendationsHandler: public RequestHandler{
    public:
    RecomendationsHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class FavoritesHandler: public RequestHandler{
    public:
    FavoritesHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class LikeSetter: public RequestHandler{
    public:
    LikeSetter(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class FollowUnfollow: public RequestHandler{
    public:
    FollowUnfollow(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class LikeHandler: public RequestHandler{
    public:
    LikeHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class ShowFavoritesHandler: public RequestHandler{
    public:
    ShowFavoritesHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};

class MusicIntroHandler: public RequestHandler{
    public:
    MusicIntroHandler(Sputify *sp , Server* serv);
    Sputify *sputify;
    Server* server;
    Response *callback(Request *);
    MUSIC* selectedSong;
};
class PlaylistIntroHandler: public RequestHandler{
    public:
    PlaylistIntroHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class ViewMusicSetter: public RequestHandler{
    public:
    ViewMusicSetter(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class ViewPlaylistSetter: public RequestHandler{
    public:
    ViewPlaylistSetter(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class WholeMusicsViewHandler: public RequestHandler{
    public:
    WholeMusicsViewHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class WholeUsersViewHandler: public RequestHandler{
    public:
    WholeUsersViewHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};

class ViewFollowSetter: public RequestHandler{
    public:
    ViewFollowSetter(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class FollowViewHandler: public RequestHandler{
    public:
    FollowViewHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};

class UserIntroHandler: public RequestHandler{
    public:
    UserIntroHandler(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};
class ViewUserSetter: public RequestHandler{
    public:
    ViewUserSetter(Sputify *sp);
    Sputify *sputify;
    Response *callback(Request *);
};

class UserWindowHandler : public RequestHandler
{
public:
    Sputify* sputify;
    UserWindowHandler(Sputify* sp);
    Response *callback(Request *);
};
class ArtistWindowHandler : public RequestHandler
{
public:
    Sputify* sputify;
    ArtistWindowHandler(Sputify* sp);
    Response *callback(Request *);
};

#endif // HANDLERS_HPP_INCLUDE
