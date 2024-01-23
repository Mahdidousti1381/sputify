#include "handlers.hpp"
#include "../sputify/Constants.h"
using namespace std;


LoginHandler::LoginHandler(Sputify *sp)
{
    sputify = sp;
}
Response *LoginHandler::callback(Request *req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    if (username == "root")
        throw Server::Exception("Remote root access has been disabled.");
    cout << "username: " << username << ",\tpassword: " << password << endl;
    string demand = "POST login ? username <" + username + "> password <" + password + ">";
    Response *res;
    string ans = sputify->run(demand);
    if ( ans== Ok)
    {
        if (sputify->currentUser->mode == userStr)
            res = Response::redirect("/userLibrary");
        else if (sputify->currentUser->mode == artistStr)
            res = Response::redirect("/artistLibrary");
    }
    else
    {
        throw Server::Exception(ans);
    }
    return res;
}
SignupHandler::SignupHandler(Sputify *sp)
{
    sputify = sp;
}
Response *SignupHandler::callback(Request *req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    string mode = req->getBodyParam("mode");
    if (username == "root")
        throw Server::Exception("Remote root access has been disabled.");
    cout << "username: " << username << ",\tpassword: " << password << ",\tmode: " << mode << endl;
    string demand = "POST signup ? username <" + username + "> password <" + password + "> mode <" + mode + ">";
    cout << demand << endl;
    Response *res;
    string ans = sputify->run(demand);
    if (ans == Ok)
    {
        if (mode == userStr)
            res = Response::redirect("/userLibrary");
        else
            res = Response::redirect("/artistLibrary");
    }
    else
    {
        throw Server::Exception(ans);
    }
    return res;
}

LogoutHandler::LogoutHandler(Sputify *sp)
{
    sputify = sp;
}
Response *LogoutHandler::callback(Request *req)
{
    string demand = "POST logout ? ";
    string ans = sputify->run(demand);
    Response *res;
    res = Response::redirect("/");
    res->setSessionId("0");
    return res;
}

LibraryHandler::LibraryHandler(Sputify *sp)
{
    sputify = sp;
}
Response *LibraryHandler::callback(Request *req)
{
    Response *res;
    if (sputify->artistState)
    {
        res = Response::redirect("/artistLibrary");
    }
    else if (sputify->userState)
    {
        res = Response::redirect("/userLibrary");
    }
    else
    {
        res = Response::redirect("/");
    }
    return res;
}

DeleteMusicHandler::DeleteMusicHandler(Sputify *sp)
{
    sputify = sp;
}
Response *DeleteMusicHandler::callback(Request *req){
    string musicId = req->getBodyParam("musicId");
    string demand = "DELETE music ? id <" + musicId + ">";
    string ans = sputify->run(demand);
    Response *res;
    if(ans == Ok){
        res = Response::redirect("/artistLibrary");
    }
    else
    {
        throw Server::Exception(ans);
    }
    return res;


}

DeletePlaylistHandler::DeletePlaylistHandler(Sputify *sp)
{
    sputify = sp;
}
Response *DeletePlaylistHandler::callback(Request *req){
    string playlistName = req->getBodyParam("playlistName");
    string playlistCreatorId = req->getBodyParam("playlistCreatorId");
    string demand = "DELETE playlist ? name <" + playlistName + ">";
    cout<<demand<<endl;
    string ans = sputify->run(demand);
    Response *res;
    if(ans == Ok){
        res = Response::redirect("/userLibrary");
    }
    else
    {
        throw Server::Exception(ans);
    }
    return res;
}

FollowUnfollow::FollowUnfollow(Sputify *sp)
{
    sputify = sp;
}
Response *FollowUnfollow::callback(Request *req){
    string opp = req->getBodyParam("opperation");
    string userId = req->getBodyParam("userId");
    string demand = "POST "+opp+" ? id <" + userId + ">";
    cout<<demand<<endl;
    string ans = sputify->run(demand);
    Response *res;
    if(ans == Ok){
        res = Response::redirect("/userIntro");
    }
    else
    {
        throw Server::Exception(ans);
    }
    return res;
}


LikeHandler::LikeHandler(Sputify *sp)
{
    sputify = sp;
}
Response *LikeHandler::callback(Request *req){
    string musicId = req->getBodyParam("musicId");
    string demand = "POST like ? id <" + musicId + ">";
    cout<<demand<<endl;
    string ans = sputify->run(demand);
    if(ans != Ok){
        throw Server::Exception(ans);
    }
    Response *res;
    res = Response::redirect("/musicIntro");
    return res;
}

AddToPlaylistHandler::AddToPlaylistHandler(Sputify *sp)
{
    sputify = sp;
}
Response *AddToPlaylistHandler::callback(Request *req){
    string playlistName = req->getBodyParam("playlistName");
    string musicId = req->getBodyParam("musicId");
    string demand = "PUT add_playlist ? name <" + playlistName + "> id <"+musicId+">";
        cout<<demand<<endl;
    string ans = sputify->run(demand);
    Response *res;
    if(ans == Ok){
        res = Response::redirect("/userLibrary");
    }
    else
    {
        throw Server::Exception(ans);
    }
    return res;
}

PlaylistPostHandler::PlaylistPostHandler(Sputify *sp)
{
    sputify = sp;
}
Response *PlaylistPostHandler::callback(Request *req){
    Response *res;
    string playlistName = req->getBodyParam("playlistName");
    if(playlistName == ""){throw invalid_argument(badReq);}
    string demand = "POST playlist ? name <" + playlistName + ">";
    string ans = sputify->run(demand);
    if(ans == Ok){
        res = Response::redirect("/userLibrary");
    }
    
    else
    {
        throw Server::Exception(ans);
    }
    return res;
}

MusicPostHandler::MusicPostHandler(Sputify *sp)
{
    sputify = sp;
}
Response *MusicPostHandler::callback(Request *req)
{
    string title = req->getBodyParam("musicName");
    string path = req->getBodyParam("musicName")+".mp3";
    string file = req->getBodyParam("path");
    string durationString = req->getBodyParam("duration");
    string album = req->getBodyParam("albumName");
    string tagsString = req->getBodyParam("tags");
    string yearStr = req->getBodyParam("year");
    utils::writeToFile(file, title+".mp3");

    string ans;
    string demand = "POST music ? title <" + title + "> path <" + path + "> year <"+yearStr+"> album <"+album+"> tags <"+tagsString+"> duration <"+durationString+">";
    Response *res;
    ans = sputify->run(demand);
    if (ans == Ok)
    {
        res = Response::redirect("/artistLibrary");
    }
    else
    {
        throw Server::Exception(ans);
    }
    return res;
}

MusicSearchHandler::MusicSearchHandler(Sputify *sp)
{
    sputify = sp;
}
Response *MusicSearchHandler::callback(Request *req){
    string musicName = req->getBodyParam("musicName");
    string singer = req->getBodyParam("singer");
    string genre = req->getBodyParam("genre");


    string demand = "GET search_music ? name <" + musicName + "> artist <"+singer+"> tag <"+genre+">";
    string ans = sputify->run(demand);
    Response *res;
    if(ans == badReq || ans == permissionDen ){
        res = Response::redirect("/userLibrary");
    }
    else if( ans == emptyStr){
        throw Server::Exception(ans);
    }
    else if(ans==Ok){
        res = Response::redirect("/foundMusics");
    }
    return res;
}

ViewMusicSetter::ViewMusicSetter(Sputify *sp)
{
    sputify = sp;
}
Response *ViewMusicSetter::callback(Request *req)
{
    string musicId = req->getBodyParam("musicId");
    Response *res;
    res = Response::redirect("/musicIntro");
    res->setSessionId(musicId);
    return res;
}

ViewPlaylistSetter::ViewPlaylistSetter(Sputify *sp)
{
    sputify = sp;
}
Response *ViewPlaylistSetter::callback(Request *req)
{
    string playlistName = req->getBodyParam("playlistName");
    Response *res;
    res = Response::redirect("/playlistIntro");
    res->setSessionId(playlistName);
    return res;
}
ViewUserSetter::ViewUserSetter(Sputify *sp)
{
    sputify = sp;
}
Response *ViewUserSetter::callback(Request *req)
{
    string userId = req->getBodyParam("userId");
    Response *res;
    res = Response::redirect("/userIntro");
    res->setSessionId(userId);
    return res;
}

ViewFollowSetter::ViewFollowSetter(Sputify *sp)
{
    sputify = sp;
}
Response *ViewFollowSetter::callback(Request *req)
{
    string list_userId = req->getBodyParam("list_userId");
    Response *res;
    res = Response::redirect("/followList");        
    res->setSessionId(list_userId);
    return res;
}

ArtistWindowHandler::ArtistWindowHandler(Sputify* sp){
    sputify = sp;
}
Response* ArtistWindowHandler::callback(Request * req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    stringstream str;
    str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #333;
        }

        .inline-form {
            display: flex;
            align-items: center;
            display: block;
            padding: 5px;
            width: 50%;
            box-sizing: border-box;
            border: 1px solid #333;
            border-radius: 5px;
            font-size: 16px;
        }
        input[name="musicId"] {
            margin-right: 10px;
            margin-left: 20px;
            padding: 10px;
            background-color: #ccc;
            border-radius: 5px;


        }
        #header {
            background-color: #2cae48;
            color: #333;
            padding: 10px;
            text-align: center;
        }

        #main-content {
            color: #333;
            display: flex;
            padding: 20px;
        }

        #left-sidebar {
            flex: 1;
            margin-left: 10px;

        }

        #user-info {
            background-color: #2cae48;
            padding: 10px;
            border-radius: 10px;
            margin-bottom: 20px;
            margin-right: 20px;
            margin-left: 10px;
        }

        #artist-musics {
            background-color: #2cae48;
            padding: 20px;
            border-radius: 10px;
            margin-right: 20px;
            margin-left: 10px;
        }


        #right-sidebar {
            flex: 0.3;
            width: 200px;
            margin-right: 10px;
        }

        #buttons-container {
            background-color: #2cae48;
            padding: 20px;
            border-radius: 10px;
            margin-bottom: 20px;
        }

        #music-table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #music-table th,
        #music-table td {
            border: 1px solid #333;
            padding: 8px;
            text-align: left;
        }

        #music-table th {
            background-color: #333;
            color: #2cae48;
        }

        #buttons-container button {
            background-color: #333;
            color: #2cae48;
            padding: 10px;
            margin-bottom: 10px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }

        #artist-musics button {
            background-color: #333;
            color: #2cae48;
            padding: 10px;
            margin-bottom: 10px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }

        #header button {
            background-color: #333;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>LIBRARY</h1>
        <button onclick="goHome() "></button>
    </div>

    <div id="main-content">

        <div id="left-sidebar">
            <div id="user-info">
                <h2>You</h2>
                <p> )"<<sputify->currentUser->name<<R"(
                    </p>
                        <a href="javascript:void(0);" onclick="submitFollowForm('e)"<<sputify->currentUser->id<<R"(') ">
                                        Followers: )"<<sputify->currentUser->followers.size()<<R"(
                                        <form id="followForme)"<<sputify->currentUser->id<<R"(" action="/viewFollow" method="post" style="display: none;">
                                            <input type="hidden" name="list_userId" value="e)"<<sputify->currentUser->id<<R"(">
                                        </form>
                        </a>
                    </p>
                    </p>
                        <a href="javascript:void(0);" onclick="submitFollowForm('i)"<<sputify->currentUser->id<<R"(') ">
                                        Followings: )"<<sputify->currentUser->followings.size()<<R"(
                                        <form id="followFormi)"<<sputify->currentUser->id<<R"(" action="/viewFollow" method="post" style="display: none;">
                                            <input type="hidden" name="list_userId" value="i)"<<sputify->currentUser->id<<R"(">
                                        </form>
                        </a>
                    </p>
            </div>

            <div id="artist-musics">
                <h2>Your Musics</h2>
                <form action="/postMusic" method="get">
                    <button type="submit" class="button">Publish Music</button>
                </form>
                <form action="/deleteMusic" method="post" class = "inline-form">
                    <button type="submit" class="button">Delete Music</button>
                    <label for="musicId">Select a Music:</label>
                    <select name="musicId" type="text" placeholder="Music Id">
)";
                for(MUSIC* s:sputify->currentUser->artistMusics){
                        str<<R"(<option value=")"<<s->id<<R"(">)"<<s->get_name()<<R"(</option>)";
                }
                    str<<R"(</select>
                </form>
                <table id="music-table">
                    <thead>
                        <tr>
                            <th>Music Id</th>
                            <th>Music Name</th>
                            <th>Artist</th>
                            <th>Year Published</th>
                            <th>Album Name</th>
                            <th>Genres</th>
                            <th>Duration</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(MUSIC* s:sputify->currentUser->artistMusics){
                    str<<R"(<tr>
                                <td>)"<<s->id<<R"(</td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitForm(')"<<s->id<<R"(') ">
                                        )"<<s->get_name()<<R"(
                                        <form id="musicForm)"<<s->id<<R"(" action="/viewMusic" method="post" style="display: none;">
                                            <input type="hidden" name="musicId" value=")"<<s->id<<R"(">
                                        </form>
                                    </a>
                                </td>
                                <td>)"<<s->get_creatorName()<<R"(</td>
                                <td>)"<<s->get_yearString()<<R"(</td>
                                <td>)"<<s->get_AlbumName()<<R"(</td>
                                <td>)"<<s->get_tagsString()<<R"(</td>
                                <td>)"<<s->get_durationString()<<R"(</td>
                            </tr> )";
                    }
                    str<<R"( 
                    </tbody>
                </table>
            </div>
        </div>

        <div id="right-sidebar">
            <div id="buttons-container">
                <h2>Navigation</h2>
                <a href="http://localhost:5000/allMusics"><button>Visit All Music</button></a><br>
                <a href="http://localhost:5000/allUsers"><button>Visit All Users</button></a><br>
            </div>
        </div>
    </div>

    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitFollowForm(list_userId) {
                    var form = document.getElementById('followForm' + list_userId);
                    form.submit();
        }
        function submitForm(musicId) {
            var form = document.getElementById('musicForm' + musicId);
            form.submit();
        }
        function showMessage(message, duration) {
    document.getElementById('message-text').innerText = message;
    document.getElementById('message-container').style.display = 'block';
    setTimeout(function() {
        document.getElementById('message-container').style.display = 'none';
    }, duration);
}
    </script>

</body>

</html>
)";
    res->setBody(str.str());
    return res;
}


UserWindowHandler::UserWindowHandler(Sputify* sp){
    sputify =sp;
}
Response* UserWindowHandler::callback(Request * req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    stringstream str;
    str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        input[type="text"],
        input[type="submit"],
        label {
            display: block;
            margin: auto;
            margin-bottom: 15px;
            padding: 5px;
            width: 70%;
            box-sizing: border-box;
            border: 1px solid #ccc;
            border-radius: 5px;
            font-size: 16px;
        }

        .inline-form {
            display: flex;
            align-items: center;
        }
        select[name="playlistName"] {
            margin-right: 10px;
            background-color: #ccc;

        }
        input[name="playlistName"] {
            margin-right: 10px;
            background-color: #ccc;

        }
        input[name="musicId"] {
            margin-right: 10px;
            margin-left: 10px;
            background-color: #ccc;

        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }

        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }

        #left-sidebar {
            flex: 1;
            margin-left: 10px;

        }

        #user-info {
            background-color: #333;
            padding: 20px;
            border-radius: 5px;
            margin-bottom: 20px;
            margin-right: 20px;
            margin-left: 10px;
        }

        #user-playlists {
            background-color: #333;
            padding: 20px;
            border-radius: 5px;
            margin-right: 20px;
            margin-left: 10px;

        }

        #right-sidebar {
            flex: 0.3;
            width: 200px;
            margin-right: 10px;
        }

        #buttons-container {
            background-color: #333;
            padding: 20px;
            border-radius: 5px;
            margin-bottom: 20px;
        }

        #playlist-table {
            margin: 20px auto;
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #playlist-table th,
        #playlist-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #playlist-table th {
            background-color: #1DB954;
            color: #000;
        }

        #buttons-container button {
            background-color: #1DB954;
            color: #333;
            padding: 10px;
            margin-bottom: 10px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            border: 1px solid #ccc;
        }

        #user-playlists button {
            background-color: #1DB954;
            color: #333;
            padding: 10px;
            margin-bottom: 10px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            border: 1px solid #ccc;
        }

        #header button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }

        #right-sidebar,
        #right-sidebar-2 {
            flex: 0.3;
            margin-right: 10px;
            margin-top: 10px;
            width: 200px;

        }


        #form-container {
            background-color: #333;
            padding: 20px;
            border-radius: 5px;
            margin-bottom: 20px;
            width: 70%;
            margin: auto;
        }

        #form-container input[type="text"]{
            display: block;
            margin: auto;
            margin-bottom: 15px;
            padding: 5px;
            width: 70%;
            box-sizing: border-box;
            border: 1px solid #ccc;
            border-radius: 5px;
            font-size: 16px;
            background-color: #ccc;
        }
        #form-container button {
            display: block;
            margin: auto;
            margin-bottom: 15px;
            padding: 5px;
            width: 70%;
            box-sizing: border-box;
            border: 1px solid #ccc;
            border-radius: 5px;
            font-size: 16px;
            background-color: #1DB954;
        }
            .dropdown {
            position: relative;
            display: inline-block;
        }

        .dropdown-content {
            display: none;
            position: absolute;
            background-color: #f9f9f9;
            min-width: 160px;
            box-shadow: 0 8px 16px rgba(0, 0, 0, 0.2);
            z-index: 1;
        }

        .dropdown-content select {
            padding: 12px 16px;
            text-decoration: none;
            display: block;
            color: #333;
        }

        .dropdown-content option:hover {
            background-color: #f1f1f1;
            cursor: pointer;
        }

        .dropdown:hover .dropdown-content {
            display: block;
            cursor: pointer;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>LIBRARY</h1>
        <button onclick= "goHome() "></button>
    </div>

    <div id="main-content">

        <div id="left-sidebar">
            <div id="user-info">
                <h2>You</h2>
                <p> )"<<sputify->currentUser->name<<R"(
                    </p>
                        <a href="javascript:void(0);" onclick="submitFollowForm('e)"<<sputify->currentUser->id<<R"(') ">
                                        Followers: )"<<sputify->currentUser->followers.size()<<R"(
                                        <form id="followForme)"<<sputify->currentUser->id<<R"(" action="/viewFollow" method="post" style="display: none;">
                                            <input type="hidden" name="list_userId" value="e)"<<sputify->currentUser->id<<R"(">
                                        </form>
                        </a>
                    </p>
                    </p>
                        <a href="javascript:void(0);" onclick="submitFollowForm('i)"<<sputify->currentUser->id<<R"(') ">
                                        Followings: )"<<sputify->currentUser->followings.size()<<R"(
                                        <form id="followFormi)"<<sputify->currentUser->id<<R"(" action="/viewFollow" method="post" style="display: none;">
                                            <input type="hidden" name="list_userId" value="i)"<<sputify->currentUser->id<<R"(">
                                        </form>
                        </a>
                    </p>
            </div>
            <div id="user-playlists">
                <h2>Manage Playlists</h2>
                <form action="/postPlaylist" method="post" class = "inline-form">
                    <button type="submit" class="button">Add Playlist</button>
                    <input name="playlistName" type="text" placeholder="Playlist Name">
                </form>
                <form action="/deletePlaylist" method="post" class = "inline-form">
                    <button type="submit" class="button">Delete Playlist</button>
                    <label for="playlistName">Select a Playlist:</label>
                    <select name="playlistName" type="text" placeholder="Playlist Name">
                    <option value=""></option>
)";
                for(Playlist* p:sputify->currentUser->userPlaylists){
                        str<<R"(<option value=")"<<p->name<<R"(">)"<<p->name<<R"(</option>)";
                }
                    str<<R"(</select></form>
                <form action="/addToPlaylist" method="post" class = "inline-form">
                    <button type="submit" class="button">Add Music to Playlist</button>
                    <label for="musicId">Select a Music:</label>
                    <select name="musicId" type="text" placeholder="Music Id">
                    <option value=""></option>
)";
                for(MUSIC* s:sputify->musics){
                        str<<R"(<option value=")"<<s->id<<R"(">)"<<s->get_name()<<R"(</option>)";
                }
                    str<<R"(</select>
                    <label for="playlistName">Select a Playlist:</label>
                    <select name="playlistName" type="text" placeholder="Playlist Name">
                    <option value=""></option>
                     )";
                for(Playlist* p:sputify->currentUser->userPlaylists){
                        str<<R"(<option value=")"<<p->name<<R"(">)"<<p->name<<R"(</option>)";
                }
                    str<<R"(</select>
                </form>
                <table id="playlist-table">
                    <thead>
                        <tr>
                            <th>Playlist Name</th>
                            <th>Duration</th>
                            <th>Songs Count</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(Playlist* p:sputify->currentUser->userPlaylists){
                        str<<R"(
                            <tr>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitPlaylistForm(')"<<p->name<<R"(') ">
                                    )"<<p->name<<R"(
                                        <form id="playlistForm)"<<p->name<<R"(" action="/viewPlaylist" method="post" style="display: none;">
                                            <input type="hidden" name="playlistName" value=")"<<p->name<<R"(">
                                        </form>
                                    </a>
                                </td>
                                <td>)"<<p->durationStr<<R"(</td>
                                <td>)"<<p->containingMusics.size()<<R"(</td>
                            </tr> )";
                    }
                        str<<R"(
                    </tbody>
                </table>
            </div>
        </div>
        <div id="right-sidebar-2">
            <div id="form-container">
                <h2>Discover Musics</h2>
                <form action="/search_music" method="post">
                    <input name="musicName" type="text" placeholder="Music Name">
                    <input name="singer" type="text" placeholder="Singer">
                    <input name="genre" type="text" placeholder="Genre">
                    <button type="submit" class="button">Search</button>
                </form>
            </div>
        </div>
        <div id="right-sidebar">
            <div id="buttons-container">
                <h2>Navigation</h2>
                <button onclick=show_all_musics()>Visit All Musics</button><br>
                    <button onclick=Show_recomendations()>Visit Recommendations</button><br>
                    <button onclick=show_all_users()>Visit All Users</button><br>
                    <button onclick=show_favorites()>Favorites</button><br>
            </div>
        </div>
    </div>

    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function show_all_musics() {
            window.location.href = 'http://localhost:5000/allMusics';
        }
        function show_all_users() {
            window.location.href = 'http://localhost:5000/allUsers';
        }
        function Show_recomendations() {
            window.location.href = 'http://localhost:5000/recommendations';
        }
        function show_favorites(){
            window.location.href = 'http://localhost:5000/favorites';
        }
        function submitPlaylistForm(playlistName) {
                    var form = document.getElementById('playlistForm' + playlistName);
                    form.submit();
        }
        function submitFollowForm(list_userId) {
                    var form = document.getElementById('followForm' + list_userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";
    res->setBody(str.str());
    return res;
}

WholeMusicsViewHandler::WholeMusicsViewHandler(Sputify* sp){
sputify = sp;
}
Response* WholeMusicsViewHandler::callback(Request * req){
    if(sputify->musics.size()==0){
        throw Server::Exception(emptyStr);
    }
Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    stringstream str;
str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }
        #header button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }


        #music-table {
            margin: 20px auto;
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #music-table th,
        #music-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #music-table th {
            background-color: #1DB954;
            color: #000;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>All Musics</h1>
        <button onclick= "goHome() "></button>
    </div>

    <div id="main-content">
                <table id="music-table">
                    <thead>
                        <tr>
                            <th>Music Id</th>
                            <th>Name</th>
                            <th>Singer</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(MUSIC* s:sputify->musics){
                        str<<R"(
                            <tr>
                                <td>)"<<s->id<<R"(</td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitForm(')"<<s->id<<R"(') ">
                                    )"<<s->get_name()<<R"(
                                        <form id="musicForm)"<<s->id<<R"(" action="/viewMusic" method="post" style="display: none;">
                                            <input type="hidden" name="musicId" value=")"<<s->id<<R"(">
                                        </form>
                                    </a>
                                </td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitUserForm(')"<<s->creatorId<<R"(') ">
                                    )"<<s->get_creatorName()<<R"(
                                        <form id="userForm)"<<s->creatorId<<R"(" action="/viewUser" method="post" style="display: none;">
                                            <input type="hidden" name="userId" value=")"<<s->creatorId<<R"(">
                                        </form>
                                    </a>
                                </td>
                                </tr> )";
                    }
                        str<<R"(
                    </tbody>
                </table>
    </div>
    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitForm(musicId) {
            var form = document.getElementById('musicForm' + musicId);
            form.submit();
        }
        function submitUserForm(userId) {
                    var form = document.getElementById('userForm' + userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";
    res->setBody(str.str());
    return res;

}

WholeUsersViewHandler::WholeUsersViewHandler(Sputify* sp){
sputify = sp;
}
Response* WholeUsersViewHandler::callback(Request * req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    stringstream str;
str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }
        #header button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }
        #main-content button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 15px;
            cursor: pointer;
            text-indent: 30px;
        }


        #users-table {
            margin: 20px auto;           
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #users-table th,
        #users-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #users-table th {
            background-color: #1DB954;
            color: #000;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>All Users</h1>
        <button onclick= "goHome() "></button>
    </div>

    <div id="main-content"> )";
                str<<R"(
                    <table id="users-table">
                    <thead>
                        <tr>
                            <th>User Id</th>
                            <th>Mode</th>
                            <th>Name</th>
                            <th>Playlists Number / Songs Number</th>
                            <th>Following / Not Following</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(Person* p:sputify->allUsers){
                        str<<R"(
                            <tr>
                                <td>)"<<p->id<<R"(</td> )";
                        if(p->mode == "artist"){
                                str<<R"(<td>Artist</td>)";
                        }else{
                                str<<R"(<td>User</td>)";
                        }
                                    str<<R"(<td>
                                    <a href="javascript:void(0);" onclick="submitUserForm(')"<<p->id<<R"(') ">
                                    )"<<p->name<<R"(
                                        <form id="userForm)"<<p->id<<R"(" action="/viewUser" method="post" style="display: none;">
                                            <input type="hidden" name="userId" value=")"<<p->id<<R"(">
                                        </form>
                                    </a>
                                </td>)";
                        if(p->mode == "artist"){
                                str<<R"(<td>)"<<p->artistMusics.size()<<R"(</td>)";
                        }else{
                                str<<R"(<td>)"<<p->userPlaylists.size()<<R"(</td>)";
                        }
                        auto it = std::find(sputify->currentUser->followings.begin(),sputify->currentUser->followings.end(),p);
                        if(it == sputify->currentUser->followings.end())
                        {
                                str<<R"(<td>Not Following</td>)";
                        }
                        else
                                str<<R"(<td>Following</td>)";
                        str<<R"(</tr> )";
                    }
                        str<<R"(
                    </tbody>
                </table>
    </div>
    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitForm(musicId) {
            var form = document.getElementById('musicForm' + musicId);
            form.submit();
        }
        function submitUserForm(userId) {
                    var form = document.getElementById('userForm' + userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";
    res->setBody(str.str());
    return res;

}

FollowViewHandler::FollowViewHandler(Sputify* sp){
sputify = sp;
}
Response* FollowViewHandler::callback(Request * req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    char listToShow = (req->getSessionId())[0];
    int userId =  stoi(req->getSessionId().substr(1));
    Person* selectedUser = sputify->browser->findPersonById(sputify->allUsers,userId);
    stringstream str;
str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }
        #header button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }


        #users-table {
            margin: 20px auto;           
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #users-table th,
        #users-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #users-table th {
            background-color: #1DB954;
            color: #000;
        }
    </style>
</head>

<body>

    <div id="header">)";
        if(listToShow == 'i'){
        str<<R"(<h1>)"<<selectedUser->name<<R"('s Followings</h1>)";
        }else{
        str<<R"(<h1>)"<<selectedUser->name<<R"('s Followers</h1>)";
        }
        str<<R"(<button onclick= "goHome() "></button>
    </div>

    <div id="main-content"> )";
                str<<R"(
                    <table id="users-table">
                    <thead>
                        <tr>
                            <th>User Id</th>
                            <th>Mode</th>
                            <th>Name</th>
                            <th>Playlists Number / Songs Number</th>
                            <th>Following / Not Following</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    if(listToShow == 'i'){
                    for(Person* p:selectedUser->followings){
                        str<<R"(
                            <tr>
                                <td>)"<<p->id<<R"(</td> )";
                        if(p->mode == "artist"){
                                str<<R"(<td>Artist</td>)";
                        }else{
                                str<<R"(<td>User</td>)";
                        }
                                    str<<R"(<td>
                                    <a href="javascript:void(0);" onclick="submitUserForm(')"<<p->id<<R"(') ">
                                    )"<<p->name<<R"(
                                        <form id="userForm)"<<p->id<<R"(" action="/viewUser" method="post" style="display: none;">
                                            <input type="hidden" name="userId" value=")"<<p->id<<R"(">
                                        </form>
                                    </a>
                                </td>)";
                        if(p->mode == "artist"){
                                str<<R"(<td>)"<<p->artistMusics.size()<<R"(</td>)";
                        }else{
                                str<<R"(<td>)"<<p->userPlaylists.size()<<R"(</td>)";
                        }
                        auto it = std::find(sputify->currentUser->followings.begin(),sputify->currentUser->followings.end(),p);
                        if(it == sputify->currentUser->followings.end())
                        {
                                str<<R"(<td>Not Following</td>)";
                        }
                        else
                                str<<R"(<td>Following</td>)";
                        str<<R"(</tr> )";
                    }
                    }
                    if(listToShow == 'e'){
                    for(Person* p:selectedUser->followers){
                        str<<R"(
                            <tr>
                                <td>)"<<p->id<<R"(</td> )";
                        if(p->mode == "artist"){
                                str<<R"(<td>Artist</td>)";
                        }else{
                                str<<R"(<td>User</td>)";
                        }
                                    str<<R"(<td>
                                    <a href="javascript:void(0);" onclick="submitUserForm(')"<<p->id<<R"(') ">
                                    )"<<p->name<<R"(
                                        <form id="userForm)"<<p->id<<R"(" action="/viewUser" method="post" style="display: none;">
                                            <input type="hidden" name="userId" value=")"<<p->id<<R"(">
                                        </form>
                                    </a>
                                </td>)";
                        if(p->mode == "artist"){
                                str<<R"(<td>)"<<p->artistMusics.size()<<R"(</td>)";
                        }else{
                                str<<R"(<td>)"<<p->userPlaylists.size()<<R"(</td>)";
                        }
                        auto it = std::find(sputify->currentUser->followings.begin(),sputify->currentUser->followings.end(),p);
                        if(it == sputify->currentUser->followings.end())
                        {
                                str<<R"(<td>Not Following</td>)";
                        }
                        else
                                str<<R"(<td>Following</td>)";
                        str<<R"(</tr> )";
                    }
                    }
                        str<<R"(
                    </tbody>
                </table>
    </div>
    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitForm(musicId) {
            var form = document.getElementById('musicForm' + musicId);
            form.submit();
        }
        function submitUserForm(userId) {
                    var form = document.getElementById('userForm' + userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";
    res->setBody(str.str());
    return res;

}

FoundMusicsHandler::FoundMusicsHandler(Sputify* sp){
    sputify =sp;
}
Response* FoundMusicsHandler::callback(Request * req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    stringstream str;
str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }
        #header button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }


        #music-table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #music-table th,
        #music-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #music-table th {
            background-color: #1DB954;
            color: #000;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>Search Results</h1>
        <button onclick= "goHome() "></button>
    </div>

    <div id="main-content">
                <table id="music-table">
                    <thead>
                        <tr>
                            <th>Music Id</th>
                            <th>Name</th>
                            <th>Singer</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(MUSIC* s:sputify->foundMusics){
                        str<<R"(
                            <tr>
                                <td>)"<<s->id<<R"(</td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitForm(')"<<s->id<<R"(') ">
                                    )"<<s->get_name()<<R"(
                                        <form id="musicForm)"<<s->id<<R"(" action="/viewMusic" method="post" style="display: none;">
                                            <input type="hidden" name="musicId" value=")"<<s->id<<R"(">
                                        </form>
                                    </a>
                                </td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitUserForm(')"<<s->creatorId<<R"(') ">
                                    )"<<s->get_creatorName()<<R"(
                                        <form id="userForm)"<<s->creatorId<<R"(" action="/viewUser" method="post" style="display: none;">
                                            <input type="hidden" name="userId" value=")"<<s->creatorId<<R"(">
                                        </form>
                                    </a>
                                </td>
                                </tr> )";
                    }
                        str<<R"(
                    </tbody>
                </table>
    </div>
    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitForm(musicId) {
            var form = document.getElementById('musicForm' + musicId);
            form.submit();
        }
        function submitUserForm(userId) {
                    var form = document.getElementById('userForm' + userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";
    res->setBody(str.str());
    return res;

}

ShowFavoritesHandler::ShowFavoritesHandler(Sputify* sp){
    sputify =sp;
}
Response* ShowFavoritesHandler::callback(Request * req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string demand = "GET likes ?";
    string ans= sputify->run(demand);
    if(ans == emptyStr){
        throw Server::Exception(ans);
    }
    stringstream str;
str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }
        #header button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }


        #music-table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #music-table th,
        #music-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #music-table th {
            background-color: #1DB954;
            color: #000;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>Your Favorites</h1>
        <button onclick= "goHome() "></button>
    </div>

    <div id="main-content">
                <table id="music-table">
                    <thead>
                        <tr>
                            <th>Music Id</th>
                            <th>Name</th>
                            <th>Singer</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(MUSIC* s:sputify->currentUser->likedSongs){
                        str<<R"(
                            <tr>
                                <td>)"<<s->id<<R"(</td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitForm(')"<<s->id<<R"(') ">
                                    )"<<s->get_name()<<R"(
                                        <form id="musicForm)"<<s->id<<R"(" action="/viewMusic" method="post" style="display: none;">
                                            <input type="hidden" name="musicId" value=")"<<s->id<<R"(">
                                        </form>
                                    </a>
                                </td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitUserForm(')"<<s->creatorId<<R"(') ">
                                    )"<<s->get_creatorName()<<R"(
                                        <form id="userForm)"<<s->creatorId<<R"(" action="/viewUser" method="post" style="display: none;">
                                            <input type="hidden" name="userId" value=")"<<s->creatorId<<R"(">
                                        </form>
                                    </a>
                                </td>
                                </tr> )";
                    }
                        str<<R"(
                    </tbody>
                </table>
    </div>
    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitForm(musicId) {
            var form = document.getElementById('musicForm' + musicId);
            form.submit();
        }
        function submitUserForm(userId) {
                    var form = document.getElementById('userForm' + userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";
    res->setBody(str.str());
    return res;
}

RecomendationsHandler::RecomendationsHandler(Sputify* sp){
    sputify =sp;
}
Response* RecomendationsHandler::callback(Request * req){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string demand = "GET recommendations ? ";
    string ans= sputify->run(demand);
    if(ans == emptyStr){
        throw Server::Exception(ans);
    }
    stringstream str;
str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }
        #header button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }


        #music-table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #music-table th,
        #music-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #music-table th {
            background-color: #1DB954;
            color: #000;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>Recommendations</h1>
        <button onclick= "goHome() "></button>
    </div>

    <div id="main-content">
                <table id="music-table">
                    <thead>
                        <tr>
                            <th>Music Id</th>
                            <th>Name</th>
                            <th>Singer</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(MUSIC* s:sputify->currentUser->recommendations){
                        str<<R"(
                            <tr>
                                <td>)"<<s->id<<R"(</td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitForm(')"<<s->id<<R"(') ">
                                    )"<<s->get_name()<<R"(
                                        <form id="musicForm)"<<s->id<<R"(" action="/viewMusic" method="post" style="display: none;">
                                            <input type="hidden" name="musicId" value=")"<<s->id<<R"(">
                                        </form>
                                    </a>
                                </td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitUserForm(')"<<s->creatorId<<R"(') ">
                                    )"<<s->get_creatorName()<<R"(
                                        <form id="userForm)"<<s->creatorId<<R"(" action="/viewUser" method="post" style="display: none;">
                                            <input type="hidden" name="userId" value=")"<<s->creatorId<<R"(">
                                        </form>
                                    </a>
                                </td>
                                </tr> )";
                    }
                        str<<R"(
                    </tbody>
                </table>
    </div>
    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitForm(musicId) {
            var form = document.getElementById('musicForm' + musicId);
            form.submit();
        }
        function submitUserForm(userId) {
                    var form = document.getElementById('userForm' + userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";
    res->setBody(str.str());
    return res;
}

MusicIntroHandler::MusicIntroHandler(Sputify* sp , Server* serv){
sputify = sp;
server = serv;
}
Response* MusicIntroHandler::callback(Request * req){
    Response *res = new Response;
    selectedSong =sputify->browser->findMusicById(sputify->musics,stoi(req->getSessionId()));
    string playingSong = selectedSong->get_path();
    sputify->playingMusicPath = playingSong;
    server->playingSong = playingSong;
    cout<<server->playingSong<<" musicintro"<<endl;
    res->setHeader("Content-Type", "text/html");
    stringstream str;
 str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }
        #audio {
            padding: 10px;
            text-align: center;
        }
        #likeBar {
            padding: 20px;
                        margin-right: 230px;
            text-align: center;
        }
        .home-button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
        .liked-button {
            background-color: #0c3208;
            border: none;
            color: #fff;
            padding: 0px 0px;
            width:0pk;
            height: 0px;
            font-size: 16px;
            cursor: pointer;
            border-radius: 50%;
            position: relative;
            margin-top: 10px; 
        }

        .liked-button::before{
            content: '';
            position: absolute;
            top: 0;
            width: 50px;
            height: 80px;
            background-color: #0c3208;
            border-radius: 50px 50px 0 0;
            transform: rotate(45deg);
            transform-origin: -10% 75%;
        }
        .liked-button::after {
            content: '';
            position: absolute;
            top: 0;
            width: 52px;
            height: 80px;
            background-color: #0c3208;
            border-radius: 50px 50px 0 0;
            transform: rotate(-45deg);
            transform-origin: 100% 100%;
        }

        .liked-button::before {
            left: 100px;
        }

        .liked-button::after {
            left: 100px;
        }
        .like-button {
            background-color: #f0f0f0;
            border: none;
            color: #fff;
            padding: 0px 0px;
            width:0pk;
            height: 0px;
            font-size: 16px;
            cursor: pointer;
            border-radius: 50%;
            position: relative;
            margin-top: 10px; 
        }

        .like-button::before{
            content: '';
            position: absolute;
            top: 0;
            width: 50px;
            height: 80px;
            background-color: #f0f0f0;
            border-radius: 50px 50px 0 0;
            transform: rotate(45deg);
            transform-origin: -10% 75%;
        }
        .like-button::after {
            content: '';
            position: absolute;
            top: 0;
            width: 52px;
            height: 80px;
            background-color: #f0f0f0;
            border-radius: 50px 50px 0 0;
            transform: rotate(-45deg);
            transform-origin: 100% 100%;
        }

        .like-button::before {
            left: 100px;
        }

        .like-button::after {
            left: 100px;
        }
        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }


        #playlist-table {
            margin: 20px auto;
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #playlist-table th,
        #playlist-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #playlist-table th {
            background-color: #1DB954;
            color: #000;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>Music Information</h1>
        <button class="home-button" onclick= "goHome() "></button>
    </div>
    <div id="main-content">
                <table id="playlist-table">
                    <thead>
                        <tr>
                            <th>Music Id</th>
                            <th>Name</th>
                            <th>Singer</th>
                            <th>Year</th>
                            <th>Album</th>
                            <th>Genres</th>
                            <th>Duration</th>
                        </tr>
                    </thead>
                    <tbody>)";
                        str<<R"(
                            <tr>
                                <td>)"<<selectedSong->id<<R"(</td>
                                <td>)"<<selectedSong->get_name()<<R"(</td>
                                <td><a href="javascript:void(0);" onclick="submitUserForm(')"<<selectedSong->creatorId<<R"(') ">
                                )"<<selectedSong->get_creatorName()<<R"(
                                    <form id="userForm)"<<selectedSong->creatorId<<R"(" action="/viewUser" method="post" style="display: none;">
                                        <input type="hidden" name="userId" value=")"<<selectedSong->creatorId<<R"(">
                                    </form>
                                </a></td>
                                <td>)"<<selectedSong->get_yearString()<<R"(</td>
                                <td>)"<<selectedSong->get_AlbumName()<<R"(</td>
                                <td>)"<<selectedSong->get_tagsString()<<R"(</td>
                                <td>)"<<selectedSong->get_durationString()<<R"(</td>
                            </tr> )";
                        str<<R"(
                    </tbody>
                </table>
                <div id="audio" >
                <audio controls autoplay>)";
                str<<R"(<source src="/musicIntro/)"<<playingSong<<R"(">
                 </audio>
                </div>
    </div><div id="likeBar">
        )";
    auto it = std::find(sputify->currentUser->likedSongs.begin(),sputify->currentUser->likedSongs.end(),selectedSong);
                    if(it == sputify->currentUser->likedSongs.end()){
                            str<<R"(<form action="/like" method="post">
                                    <button type="submit" class ="like-button"></button>
                                    <input type="hidden" name="musicId" value =")"<<selectedSong->id<<R"(">
                             </form>)";
                            }
                    else{
                            str<<R"(
                                    <button class ="liked-button"></button>
                                    )";
                            }
    str<<R"(
        </div>
    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitUserForm(userId) {
                    var form = document.getElementById('userForm' + userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";
    res->setBody(str.str());
    server->get("/musicIntro/"+playingSong, new ShowFile(playingSong, "audio/mpeg"));
    return res;

}

PlaylistIntroHandler::PlaylistIntroHandler(Sputify* sp){
sputify = sp;
}
Response* PlaylistIntroHandler::callback(Request * req){
    Response *res = new Response;
    Playlist* selectedPlaylist =sputify->browser->findPlaylistByName(sputify->currentUser->userPlaylists,req->getSessionId());
    res->setHeader("Content-Type", "text/html");
    stringstream str;
str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }
        #header button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
    
        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }


        #playlist-table {
            margin: 20px auto;
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #playlist-table th,
        #playlist-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #playlist-table th {
            background-color: #1DB954;
            color: #000;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>)"<<selectedPlaylist->name<<R"( Playlist Information</h1>
        <button onclick= "goHome() "></button><br>
        </div>

    <div id="main-content">
                <table id="playlist-table">
                    <thead>
                        <tr>
                            <th>Music Id</th>
                            <th>Name</th>
                            <th>Singer</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(MUSIC* s:selectedPlaylist->containingMusics){
                        str<<R"(
                            <tr>
                                <td>)"<<s->id<<R"(</td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitForm(')"<<s->id<<R"(') ">
                                    )"<<s->get_name()<<R"(
                                        <form id="musicForm)"<<s->id<<R"(" action="/viewMusic" method="post" style="display: none;">
                                            <input type="hidden" name="musicId" value=")"<<s->id<<R"(">
                                        </form>
                                    </a>
                                </td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitUserForm(')"<<s->creatorId<<R"(') ">
                                    )"<<s->get_creatorName()<<R"(
                                        <form id="userForm)"<<s->creatorId<<R"(" action="/viewUser" method="post" style="display: none;">
                                            <input type="hidden" name="userId" value=")"<<s->creatorId<<R"(">
                                        </form>
                                    </a>
                                </td>
                                </tr> )";
                                cout<<s->get_creatorName()<<endl;
                    }
                        str<<R"(
                    </tbody>
                </table>
    </div>
    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitForm(musicId) {
            var form = document.getElementById('musicForm' + musicId);
            form.submit();
        }
        function submitUserForm(userId) {
                    var form = document.getElementById('userForm' + userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";

    res->setBody(str.str());
    return res;

}

UserIntroHandler::UserIntroHandler(Sputify* sp){
sputify = sp;
}
Response* UserIntroHandler::callback(Request * req){
    Response *res = new Response;
    Person* selectedUser =sputify->browser->findPersonById(sputify->allUsers,stoi(req->getSessionId()));
    res->setHeader("Content-Type", "text/html");
    stringstream str;
str<<R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sputify</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #1DB954;
        }

        #header {
            background-color: #333;
            color: #1DB954;
            padding: 10px;
            text-align: center;
        }
        #header button {
            background-color: #1DB954;
            color: #fff;
            padding: 35px;
            margin: 0;
            border: none;
            border-radius: 55px;
            cursor: pointer;
            background-image: url('home.png');
            background-size: 30px;
            background-repeat: no-repeat;
            background-position: center;
            text-indent: 30px;
        }
        #header #follow-button{
            background-color: #1DB954;
            color: #fff;
            padding: 15px;
            margin: 0;
            border: none;
            background-image: none;
            border-radius: 15px;
            cursor: pointer;
            text-align: center;
            text-indent: 0px;
        }
        #main-content {
            color: #fff;
            display: flex;
            padding: 20px;
        }


        #playlist-table {
            margin: 20px auto;           
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        #playlist-table th,
        #playlist-table td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }

        #playlist-table th {
            background-color: #1DB954;
            color: #000;
        }
    </style>
</head>

<body>

    <div id="header">
        <h1>User Information</h1>
        <button onclick= "goHome() "></button>
        <div>
                            <P>Id : )"<<selectedUser->id<<R"(</P>
                            <P>Name : )"<<selectedUser->name<<R"(</P>
                            <P>Mode : )"<<selectedUser->mode<<R"(</P>
                    </p>
                        <a href="javascript:void(0);" onclick="submitFollowForm('e)"<<selectedUser->id<<R"(') ">
                                        Followers: )"<<selectedUser->followers.size()<<R"(
                                        <form id="followForme)"<<selectedUser->id<<R"(" action="/viewFollow" method="post" style="display: none;">
                                            <input type="hidden" name="list_userId" value="e)"<<selectedUser->id<<R"(">
                                        </form>
                        </a>
                    </p>
                    </p>
                        <a href="javascript:void(0);" onclick="submitFollowForm('i)"<<selectedUser->id<<R"(') ">
                                        Followings: )"<<selectedUser->followings.size()<<R"(
                                        <form id="followFormi)"<<selectedUser->id<<R"(" action="/viewFollow" method="post" style="display: none;">
                                            <input type="hidden" name="list_userId" value="i)"<<selectedUser->id<<R"(">
                                        </form>
                        </a>
                    </p>)";
                    auto it = std::find(sputify->currentUser->followings.begin(),sputify->currentUser->followings.end(),selectedUser);
                    if(it == sputify->currentUser->followings.end()){
                            str<<R"(<form action="/followUnfollow" method="post">
                                    <button type="submit" class="button" id ="follow-button">Follow</button>
                                    <input type="hidden" name="userId" value =")"<<selectedUser->id<<R"(">
                                    <input type="hidden" name="opperation" value ="follow">
                             </form>)";
                            }
                    else{
                            str<<R"(<form action="/followUnfollow" method="post">
                                    <button type="submit" class="button" id ="follow-button">Unfollow</button>
                                    <input type="hidden" name="userId" value =")"<<selectedUser->id<<R"(">
                                    <input type="hidden" name="opperation" value ="unfollow">
                             </form>)";
                            }
        str<<R"(</div>
    </div>

    <div id="main-content"> )";
                        if(selectedUser->mode == "artist"){
                str<<R"(
                    <h2>Artist Gallery</h2><br>
                    <table id="playlist-table">
                    
                    <thead>
                        <tr>
                            <th>Music Id</th>
                            <th>Name</th>
                            <th>Singer</th>
                            <th>Year</th>
                            <th>Album</th>
                            <th>Genres</th>
                            <th>Duration</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(MUSIC* s:selectedUser->artistMusics){
                        str<<R"(
                            <tr>
                                <td>)"<<s->id<<R"(</td>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitForm(')"<<s->id<<R"(') ">
                                    )"<<s->get_name()<<R"(
                                        <form id="musicForm)"<<s->id<<R"(" action="/viewMusic" method="post" style="display: none;">
                                            <input type="hidden" name="musicId" value=")"<<s->id<<R"(">
                                        </form>
                                    </a>
                                </td>
                                <td>)"<<s->get_creatorName()<<R"(</td>
                                <td>)"<<s->get_yearString()<<R"(</td>
                                <td>)"<<s->get_AlbumName()<<R"(</td>
                                <td>)"<<s->get_tagsString()<<R"(</td>
                                <td>)"<<s->get_durationString()<<R"(</td>
                            </tr> )";
                    }
                        str<<R"(
                    </tbody>
                </table>)";
                        }
                        else{

                str<<R"(
                    <h2>User Playlists</h2><br>
                <table id="playlist-table">
                    <thead>
                        <tr>
                            <th>Playlist Name</th>
                            <th>Duration</th>
                            <th>Songs Count</th>
                        </tr>
                    </thead>
                    <tbody>)";
                    for(Playlist* p:sputify->currentUser->userPlaylists){
                        str<<R"(
                            <tr>
                                <td>
                                    <a href="javascript:void(0);" onclick="submitPlaylistForm(')"<<p->name<<R"(') ">
                                    )"<<p->name<<R"(
                                        <form id="playlistForm)"<<p->name<<R"(" action="/viewPlaylist" method="post" style="display: none;">
                                            <input type="hidden" name="playlistName" value=")"<<p->name<<R"(">
                                        </form>
                                    </a>
                                </td>
                                <td>)"<<p->durationStr<<R"(</td>
                                <td>)"<<p->containingMusics.size()<<R"(</td>
                            </tr> )";
                    }
                        str<<R"(
                    </tbody>
                </table>)";
                        }

                        str<<R"(
    </div>
    <script>
        function goHome() {
            window.location.href = 'http://localhost:5000';
        }
        function submitForm(musicId) {
            var form = document.getElementById('musicForm' + musicId);
            form.submit();
        }
        function submitPlaylistForm(playlistName) {
                    var form = document.getElementById('playlistForm' + playlistName);
                    form.submit();
        }
        function submitFollowForm(list_userId) {
                    var form = document.getElementById('followForm' + list_userId);
                    form.submit();
        }
    </script>

</body>

</html>
)";

    res->setBody(str.str());
    return res;

}

