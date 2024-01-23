#ifndef DEMAND_H
#define DEMAND_H
#include "Constants.h"

class Demand
{
public:
    enum class HttpMethod
    {
        GET,
        PUT,
        DELETE,
        POST
    };
    enum class PostCommand
    {
        signup,
        login,
        music,
        playlist,
        logout,
        follow,
        unfollow,
        like
    };
    enum class GetCommand
    {
        registered_musics,
        search_music,
        musics,
        users,
        playlist,
        recommendations,
        likes
    };
    enum class PutCommand
    {
        add_playlist
    };
    enum class DeleteCommand
    {
        music,
        playlist
    };
    Demand(bool userState, bool artistState, std::string input);
    void handleStates();
    std::string command;
    std::string username;
    std::string password;
    std::string albumName;
    std::string tagsString;
    std::string title;
    std::string path;
    std::string yearStr;
    std::string musicName;
    std::string singer;
    std::string durationStr;
    std::string playlistName;
    std::string musicIdStr;
    std::string userIdStr;
    std::string inputLine;

    int musicId;
    int userId;
    int year;
    int minutes;
    int hours;
    int seconds;

    std::string mode;
    HttpMethod method;
    PostCommand postCommand;
    PutCommand putCommand;
    GetCommand getCommand;
    DeleteCommand deleteCommand;

private:
    int argEndpoint;
    std::string qSign;
    std::vector<std::string> inputWords;
    std::vector<std::string>genres;
    bool userWindow = false;
    bool artistWindow = false;
    bool loginWindow;


    HttpMethod convertToHttpMethod(const std::string &method);

    PostCommand convertToPostCommand(const std::string &cmnd);
    PutCommand convertToPutCommand(const std::string &cmnd);
    GetCommand convertToGetCommand(const std::string &cmnd);
    DeleteCommand convertToDeleteCommand(const std::string &cmnd);

    void takeRequests(std::string inputLine);
    void commandIsValid();
    bool argumentsFinder(std::string &argument, const std::string argumentStr, int index);
    
    void handlePostCommandsArguments();
    void handleGetCommandsArguments();
    void handlePutCommandsArguments();
    void handleDeleteCommandsArguments();

    void handleLoginWindow();
    void handleUserWindow();
    void handleArtistWindow();

    void parseMusicTags();
    void readDurationString();

};

#endif