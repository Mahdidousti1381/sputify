#include "Sputify.h"
Sputify::Sputify()
{
    userState = false;
    artistState = false;
    lastMusicId = 0;
}
std::string Sputify::run(std::string inputLine)
{
        Demand *dem = new Demand(userState, artistState, inputLine);
        std::string ans;
        try
        {
            dem->handleStates();
            switch (dem->method)
            {
            case Demand::HttpMethod::POST:
                switch (dem->postCommand)
                {
                case Demand::PostCommand::login:
                    handlelogin(dem);
                    break;
                case Demand::PostCommand::signup:
                    handleSignup(dem);
                    break;
                case Demand::PostCommand::logout:
                    handleLogout(dem);
                    break;
                case Demand::PostCommand::music:
                    handleMusicPost(dem);
                    break;
                case Demand::PostCommand::like:
                    handleLikeMusic(dem);
                    break;
                case Demand::PostCommand::playlist:
                    handlePlaylistPost(dem);
                    break;
                case Demand::PostCommand::follow:
                    handleFollow(dem);
                    break;
                case Demand::PostCommand::unfollow:
                    handleUnfollow(dem);
                    break;
                }
                ans = Ok;
                std::cout << Ok << std::endl;
                break;
            case Demand::HttpMethod::GET:
                switch (dem->getCommand)
                {
                case Demand::GetCommand::users:
                    handleGettingUsers(dem);
                    break;
                case Demand::GetCommand::likes:
                    handleGetLikes(dem);
                    break;
                case Demand::GetCommand::musics:
                    handleGettingMusics(dem);
                    break;
                case Demand::GetCommand::search_music:
                    handleSearchMusics(dem);
                    break;
                case Demand::GetCommand::registered_musics:
                    handleGettingRegisteredMusics(dem);
                    break;
                case Demand::GetCommand::playlist:
                    handleGettingUserPlaylists(dem);
                    break;
                case Demand::GetCommand::recommendations:
                    handleGetRecommendations(dem);
                    break;
                }
                break;
            case Demand::HttpMethod::DELETE:
                switch (dem->deleteCommand)
                {
                case Demand::DeleteCommand::music:
                    handleDeletemusic(dem);
                    break;
                case Demand::DeleteCommand::playlist:
                    handleDeletePlaylist(dem);
                    break;
                }
                ans = Ok;
                std::cout << Ok << std::endl;
                break;
            case Demand::HttpMethod::PUT:
                handleAddingMusicsToPlaylists(dem);
                ans = Ok;
                std::cout << Ok << std::endl;
                break;
            }
        }
        catch (std::runtime_error &ex)
        {
            std::cout << ex.what() << std::endl;
            ans = ex.what();
        }
        return ans;
}

void Sputify::handleSignup(Demand *req)
{
    if (req->mode == userStr)
    {
        if (browser->findPersonByName(allUsers, req->username) == nullptr)
        {
            Person *user = new User;
            if (allUsers.size() == 0)
                user->id = 1;
            else
                user->id = allUsers[allUsers.size() - 1]->id + 1;
            user->name = req->username;
            user->password = req->password;
            user->mode = req->mode;
            users.push_back(user);
            allUsers.push_back(user);
            userState = true;
            artistState = false;
            currentUser = user;
        }
        else
            throw std::runtime_error(badReq);
    }
    else
    {
        if (browser->findPersonByName(allUsers, req->username) == nullptr)
        {
            Person *artist = new Artist;
            if (allUsers.size() == 0)
                artist->id = 1;
            else
                artist->id = allUsers[allUsers.size() - 1]->id + 1;
            artist->name = req->username;
            artist->password = req->password;
            artist->mode = req->mode;
            artists.push_back(artist);
            allUsers.push_back(artist);
            artistState = true;
            userState = false;
            currentUser = artist;
        }
        else
            throw std::runtime_error(badReq);
    }
}
void Sputify::handleLogout(Demand *req)
{
    userState = false;
    artistState = false;
}
void Sputify::handlelogin(Demand *req)
{

    if (browser->findPersonByName(users, req->username) == nullptr && browser->findPersonByName(artists, req->username) == nullptr)
    {
        throw std::runtime_error(notFound);
    }
    else if (browser->findPersonByName(users, req->username) == nullptr)
    {
        currentUser = browser->findPersonByName(artists, req->username);
        if (currentUser->password == req->password)
        {
            artistState = true;
            userState = false;
            return;
        }
        else
        {
            currentUser = nullptr;
            throw std::runtime_error(permissionDen);
        }
    }
    else if (browser->findPersonByName(artists, req->username) == nullptr)
    {
        currentUser = browser->findPersonByName(users, req->username);
        if (currentUser->password == req->password)
        {
            artistState = false;
            userState = true;
            return;
        }
        else
        {
            currentUser = nullptr;
            throw std::runtime_error(permissionDen);
        }
    }
}
void Sputify::handlePlaylistPost(Demand *req)
{
    if (currentUser->userPlaylists.size() != 0)
    {
        for (Playlist *p : currentUser->userPlaylists)
        {
            if (p->name == req->playlistName)
            {
                throw std::runtime_error(badReq);
            }
        }
    }
    Playlist *newPlaylist = new Playlist(req->playlistName);
    newPlaylist->creatorId = currentUser->id;
    currentUser->userPlaylists.push_back(newPlaylist);
    playlists.push_back(newPlaylist);
}
void Sputify::handleMusicPost(Demand *req)
{
    //this part checks if the posted music is repeated in same album. but because of project demands it is commented
    /* currentArtistMusics = currentUser->artistMusics;
    if (currentArtistMusics.size() != 0)
    {
        for (MUSIC *m : currentUser->artistMusics)
        {
            if (m->get_name() == req->title && m->get_AlbumName() == req->albumName)
                throw std::runtime_error(badReq);
        }
    } */
    lastMusicId++;
    MUSIC *newMusic = new MUSIC(req->title, currentUser->name,currentUser->id, req->albumName, req->path, req->tagsString, req->year, lastMusicId, req->hours, req->minutes, req->seconds, req->durationStr);
    currentUser->artistMusics.push_back(newMusic);
    musics.push_back(newMusic);
}
void Sputify::handleFollow(Demand *req)
{
    Person *followedUser = browser->findPersonById(allUsers, req->userId);
    if (followedUser == nullptr)
        throw std::runtime_error(notFound);
    if (currentUser->id == followedUser->id)
        throw std::runtime_error(badReq);
    for (size_t i = 0; i < currentUser->followings.size(); i++)
    {
        if (currentUser->followings[i]->id == followedUser->id)
            throw std::runtime_error(badReq);
    }
    currentUser->followings.push_back(followedUser);
    followedUser->followers.push_back(currentUser);
}
void Sputify::handleUnfollow(Demand *req)
{
    Person *unfollowedUser = browser->findPersonById(allUsers, req->userId);
    if (unfollowedUser == nullptr)
        throw std::runtime_error(notFound);
    if (currentUser->id == unfollowedUser->id)
        throw std::runtime_error(badReq);
    auto it = std::find(currentUser->followings.begin(), currentUser->followings.end(), unfollowedUser);
    if (it != currentUser->followings.end())
        currentUser->followings.erase(it);
    else
        throw std::runtime_error(badReq);
    auto iter = std::find(unfollowedUser->followers.begin(), unfollowedUser->followers.end(), currentUser);
    if (iter != unfollowedUser->followers.end())
        unfollowedUser->followers.erase(iter);
    else
        throw std::runtime_error(badReq);
}
void Sputify::handleLikeMusic(Demand *req)
{
    MUSIC *likedSong = browser->findMusicById(musics, req->musicId);
    if (likedSong == nullptr)
        throw std::runtime_error(notFound);
    for (size_t i = 0; i < currentUser->likedSongs.size(); i++)
    {
        if (likedSong->id == currentUser->likedSongs[i]->id)
            throw std::runtime_error(badReq);
    }
    likedSong->likesCount++;
    currentUser->likedSongs.push_back(likedSong);
}

void Sputify::handleDeletemusic(Demand *req)
{
    MUSIC *deleteThis = browser->findMusicById(musics, req->musicId);
    if (deleteThis == nullptr)
        throw std::runtime_error(notFound);
    if (deleteThis->get_creatorName() != currentUser->name)
        throw std::runtime_error(permissionDen);
    for (size_t i = 0; i < users.size(); i++)
    {
        users[i]->eraseFromPlaylist(deleteThis);
        users[i]->deleteFromFavorites(deleteThis);
    }
    std::vector<MUSIC *>::iterator it = std::find(musics.begin(), musics.end(), deleteThis);
    musics.erase(it);
    std::vector<MUSIC *>::iterator iter = std::find(currentUser->artistMusics.begin(), currentUser->artistMusics.end(), deleteThis);
    currentUser->artistMusics.erase(iter);
    delete deleteThis;
}
void Sputify::handleDeletePlaylist(Demand *req)
{
    Playlist *deleteIt = browser->findPlaylistByName(currentUser->userPlaylists, req->playlistName);
    if (deleteIt == nullptr)
        throw std::runtime_error(notFound);
    auto it = std::find(currentUser->userPlaylists.begin(), currentUser->userPlaylists.end(), deleteIt);
    currentUser->userPlaylists.erase(it);
    auto iter = std::find(this->playlists.begin(), this->playlists.end(), deleteIt);
    this->playlists.erase(iter);
    delete deleteIt;
}

void Sputify::handleAddingMusicsToPlaylists(Demand *req)
{
    int musicID = req->musicId;
    if (browser->findPlaylistByName(currentUser->userPlaylists, req->playlistName) == nullptr || browser->findMusicById(musics, musicID) == nullptr)
        throw std::runtime_error(notFound);

    Playlist *chosenPlaylist = browser->findPlaylistByName(currentUser->userPlaylists, req->playlistName);
    MUSIC *chosenMusic = browser->findMusicById(musics, musicID);
    chosenPlaylist->containingMusics.push_back(chosenMusic);
    chosenPlaylist->updateDuration();
    return;
}

void Sputify::handleGettingMusics(Demand *req)
{

    if (req->command == musicsStr && req->musicIdStr.empty())
    {
        if (musics.size() == 0)
        {
            throw std::runtime_error(emptyStr);
        }
        std::cout << getMusicsTitleStr << std::endl;
        for (MUSIC *s : musics)
        {
            s->introduce();
        }
    }
    else if (req->command == musicsStr && !req->musicIdStr.empty())
    {
        MUSIC *theMusic = browser->findMusicById(musics, req->musicId);
        if (theMusic == nullptr)
            throw std::runtime_error(notFound);
        std::cout << getMusicTitleStr << std::endl;
        theMusic->introduceCompletely();
    }
}
void Sputify::handleGettingUsers(Demand *req)
{
    if (req->command == usersStr && req->userIdStr.empty())
    {
        std::cout << getUsersTitleStr << std::endl;
        for (Person *u : allUsers)
        {
            u->introduce();
        }
    }
    else if (req->command == usersStr && !req->userIdStr.empty())
    {
        Person *theUser = browser->findPersonById(allUsers, req->userId);
        if (theUser == nullptr)
            throw std::runtime_error(notFound);
        theUser->introduceCompletely();
    }
}
void Sputify::handleGettingUserPlaylists(Demand *req)
{
    Person *theUser = browser->findPersonById(allUsers, req->userId);
    if (theUser == nullptr)
    {
        throw std::runtime_error(notFound);
    }
    if (theUser->mode == artistStr)
    {
        throw std::runtime_error(badReq);
    }
    if (req->playlistName.empty())
    {
        theUser->printYourProperties();
    }
    else
    {
        Playlist *chosenPlaylist = browser->findPlaylistByName(theUser->userPlaylists, req->playlistName);
        if (chosenPlaylist == nullptr)
            throw std::runtime_error(notFound);
        std::cout << getMusicsTitleStr << std::endl;
        for (size_t i = 0; i < chosenPlaylist->containingMusics.size(); i++)
        {
            chosenPlaylist->containingMusics[i]->introduce();
        }
    }
}
void Sputify::handleGettingRegisteredMusics(Demand *req)
{
    if (currentUser->artistMusics.size() == 0)
    {
        throw std::runtime_error(emptyStr);
    }
    currentUser->printYourProperties();
}
void Sputify::handleSearchMusics(Demand *req)
{
    foundMusics.empty();
    foundMusics = browser->superSearch(musics, req->musicName, req->singer, req->albumName);
    if (foundMusics.size() == 0)
        throw std::runtime_error(emptyStr);
    else
    {
        std::cout << getMusicsTitleStr << std::endl;
        for (MUSIC *song : foundMusics)
        {
            song->introduce();
        }
    }
}
void Sputify::handleGetRecommendations(Demand *req)
{
    currentUser->recommendations.clear();
    if (musics.size() == 0)
        throw std::runtime_error(emptyStr);
    std::vector<MUSIC *> allLikedSongs;
    for (size_t i = 0; i < musics.size(); i++)
    {
        if (musics[i]->likesCount >= 1)
            allLikedSongs.push_back(musics[i]);
    }
    for (MUSIC *song : allLikedSongs)
    {
        if (std::find(currentUser->likedSongs.begin(), currentUser->likedSongs.end(), song) == currentUser->likedSongs.end())
            currentUser->recommendations.push_back(song);
    }
    if (currentUser->recommendations.size() == 0)
        throw std::runtime_error(emptyStr);

    std::sort(currentUser->recommendations.begin(), currentUser->recommendations.end(), [](const MUSIC *a, const MUSIC *b)
              { return std::make_tuple(-a->likesCount, a->id) < std::make_tuple(-b->likesCount, b->id); });

    if (currentUser->recommendations.size() > 5)
        currentUser->recommendations.erase(currentUser->recommendations.begin() + 5, currentUser->recommendations.end());

    std::cout << getRecommendationsTitleStr << std::endl;
    for (MUSIC *m : currentUser->recommendations)
    {
        m->recommendYourself();
    }
}
void Sputify::handleGetLikes(Demand *req){
    std::cout<<getMusicsTitleStr<<std::endl;
    if(currentUser->likedSongs.size()==0)
        throw std::runtime_error(emptyStr);
    for(MUSIC* song : currentUser->likedSongs){
        song->introduce();
    }
}
