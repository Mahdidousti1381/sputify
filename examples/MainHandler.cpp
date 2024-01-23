#include "MainHandler.h"
MainHandler::MainHandler(Sputify* sputify , Server& server){
    sp = sputify;
    this->mapServerPaths(server);
}
void MainHandler::mapServerPaths(Server& server) {    
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler(sp));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler(sp));
    server.post("/logout", new LogoutHandler(sp));
    server.get("/userLibrary",new UserWindowHandler(sp));
    server.get("/artistLibrary",new ArtistWindowHandler(sp));
    
    server.get("/allMusics",new WholeMusicsViewHandler(sp));
    server.get("/allUsers",new WholeUsersViewHandler(sp));


    //server.get("/artistLibrary",new ShowPage("static/ArtistMainWindow.html"));
    server.get("/postMusic", new ShowPage("static/PostMusic.html"));
    server.post("/postMusic", new MusicPostHandler(sp));

    server.post("/deleteMusic", new DeleteMusicHandler(sp));

    server.post("/search_music", new MusicSearchHandler(sp));
    server.get("/foundMusics", new FoundMusicsHandler(sp));
    server.post("/viewMusic", new ViewMusicSetter(sp));


    server.post("/viewPlaylist", new ViewPlaylistSetter(sp));
    server.get("/playlistIntro", new PlaylistIntroHandler(sp));

    server.post("/viewUser", new ViewUserSetter(sp));
    server.get("/userIntro", new UserIntroHandler(sp));

    server.post("/deletePlaylist", new DeletePlaylistHandler(sp));
    server.post("/postPlaylist", new PlaylistPostHandler(sp));
    server.post("/addToPlaylist", new AddToPlaylistHandler(sp));
    server.get("/library",new LibraryHandler(sp));

    server.post("/viewFollow", new ViewFollowSetter(sp));
    server.get("/followList", new FollowViewHandler(sp));

    server.post("/followUnfollow", new FollowUnfollow(sp));
    server.post("/like", new LikeHandler(sp));

    server.get("/favorites", new ShowFavoritesHandler(sp));
    server.get("/recommendations", new RecomendationsHandler(sp));
    server.get("/musicIntro", new MusicIntroHandler(sp ,&server));
    server.get("/musicIntro/"+server.playingSong, new ShowFile(server.playingSong, "audio/mpeg"));
}