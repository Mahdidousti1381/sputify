#include "Demand.h"
Demand::Demand(bool userState, bool artistState, std::string input)
{
    inputLine = input;
    userWindow = userState;
    artistWindow = artistState;
}
void Demand::takeRequests(std::string inputLine)
{
    std::istringstream lineStream(inputLine);
    std::string methodStr;
    std::string word;
    inputWords.clear();
    while (lineStream >> word)
    {
        inputWords.push_back(word);
    }
    if (inputWords.size() < 3)
        throw std::runtime_error(badReq);
    methodStr = inputWords[0];
    method = convertToHttpMethod(methodStr);
    if (method == static_cast<Demand::HttpMethod>(-1))
    {
        throw std::runtime_error(badReq);
    }
    command = inputWords[1];
    commandIsValid();
    qSign = inputWords[2];
    if (qSign != "?")
        throw std::runtime_error(badReq);
}
void Demand::commandIsValid()
{
    bool definedCommand = (command == likesStr)||(command == signupStr) || (command == loginStr) || (command == logoutStr) || (command == musicsStr) || (command == usersStr) || (command == playlistStr) || (command == addPlaylistStr) || (command == searchMusicsStr) || (command == musicStr) || (command == registeredMusicsStr) || (command == followStr) || (command == unfollowStr) || (command == likeStr)||(command == recommendationsStr);
    bool isPostCommand = (command == likeStr || command == playlistStr || command == signupStr || command == loginStr || command == logoutStr || command == musicStr || command == followStr || command == unfollowStr);
    bool isGetCommand = (command == likesStr|| command == recommendationsStr || command == registeredMusicsStr || command == searchMusicsStr || command == usersStr || command == musicsStr || command == playlistStr);
    bool isDeleteCommand = (command == musicStr || command == playlistStr);
    bool isPutCommand = (command == addPlaylistStr);
    if (!definedCommand)
        throw std::runtime_error(badReq);
    switch (method)
    {
    case Demand::HttpMethod::POST:
        if (!isPostCommand)
            throw std::runtime_error(notFound);
        break;

    case Demand::HttpMethod::GET:
        if (!isGetCommand)
            throw std::runtime_error(notFound);
        break;
    case Demand::HttpMethod::DELETE:
        if (!isDeleteCommand)
            throw std::runtime_error(notFound);
        break;
    case Demand::HttpMethod::PUT:
        if (!isPutCommand)
            throw std::runtime_error(notFound);
        break;
    }
}
Demand::HttpMethod Demand::convertToHttpMethod(const std::string &method)
{
    std::string upperMethod = method;
    if (upperMethod == "GET")
    {
        return Demand::HttpMethod::GET;
    }
    else if (upperMethod == "PUT")
    {
        return Demand::HttpMethod::PUT;
    }
    else if (upperMethod == "DELETE")
    {
        return Demand::HttpMethod::DELETE;
    }
    else if (upperMethod == "POST")
    {
        return Demand::HttpMethod::POST;
    }
    else
    {
        return static_cast<Demand::HttpMethod>(-1);
    }
}

void Demand::handleStates()
{
    loginWindow = !userWindow & !artistWindow;
    try
    {
        takeRequests(inputLine);
        while (loginWindow)
        {
            handleLoginWindow();
            return;
        }
        while (userWindow)
        {
            handleUserWindow();
            return;
        }
        while (artistWindow)
        {
            handleArtistWindow();
            return;
        }
    }
    catch (std::runtime_error &ex)
    {
        inputLine.clear();
        inputWords.clear();
        throw;
    }
}
void Demand::handleLoginWindow()
{
    bool permittedInLoginState = ((method == HttpMethod::POST) && (command == loginStr || command == signupStr));

    if (permittedInLoginState)
    {
        handlePostCommandsArguments();
        postCommand = convertToPostCommand(command);
        return;
    }
    else if (!permittedInLoginState)
    {
        throw std::runtime_error(permissionDen);
    }
}
void Demand::handleArtistWindow()
{
    bool permittedInArtistState =(((method == HttpMethod::POST) && (command == logoutStr || command == musicStr || command == followStr || command == unfollowStr)) || ((method == HttpMethod::GET) && (command == registeredMusicsStr || command == musicsStr || command == usersStr)) || ((method == HttpMethod::DELETE) && (command == musicStr)));
    if (permittedInArtistState)
    {
        if (method == HttpMethod::POST)
        {
            handlePostCommandsArguments();
            postCommand = convertToPostCommand(command);
            return;
        }
        else if (method == HttpMethod::GET)
        {
            handleGetCommandsArguments();
            getCommand = convertToGetCommand(command);
            return;
        }
        else if (method == HttpMethod::DELETE)
        {
            handleDeleteCommandsArguments();
            deleteCommand = convertToDeleteCommand(command);
            return;
        }
    }
    else if (!permittedInArtistState)
    {
        throw std::runtime_error(permissionDen);
    }
}
void Demand::handleUserWindow()
{
    bool permittedInUserState =
        ((method == HttpMethod::DELETE && command == playlistStr)||((method == HttpMethod::POST) && (command == followStr || command == unfollowStr || command == logoutStr || command == playlistStr || command == likeStr)) || ((method == HttpMethod::GET) && (command == likesStr || command == recommendationsStr || command == musicsStr || command == usersStr || command == playlistStr || command == searchMusicsStr)) || ((method == HttpMethod::PUT) && (command == addPlaylistStr)));
    if (permittedInUserState)
    {
        switch (method)
        {
        case HttpMethod::POST:
            handlePostCommandsArguments();
            postCommand = convertToPostCommand(command);
            return;
        case HttpMethod::PUT:
            handlePutCommandsArguments();
            putCommand = convertToPutCommand(command);
            return;
        case HttpMethod::GET:
            handleGetCommandsArguments();
            getCommand = convertToGetCommand(command);
            return;
        case HttpMethod::DELETE:
            handleDeleteCommandsArguments();
            deleteCommand = convertToDeleteCommand(command);
            return;
        }
    }
    else
        throw std::runtime_error(permissionDen);
}
bool Demand::argumentsFinder(std::string &argument, const std::string argumentStr, int index)
{
    if (inputWords[index] == argumentStr)
    {
        if (index == inputWords.size() - 1)
        {
            throw std::runtime_error(badReq);
        }
        if (inputWords[index + 1][0] == '<')
        {
            argument.clear();
            for (size_t j = index + 1; j < inputWords.size(); j++)
            {
                if (j - (index + 1) > 0)
                    argument += " ";
                argument += inputWords[j];
                if (inputWords[j][inputWords[j].size() - 1] == '>')
                {
                    argEndpoint = j;
                    break;
                }
                else if (j == inputWords.size() - 1 && inputWords[j][inputWords[j].size() - 1] != '>')
                {
                    argEndpoint = j;
                    throw std::runtime_error(badReq);
                }
            }
            argument = argument.substr(1, argument.size() - 2);
            return true;
        }
        else
        {
            argEndpoint = index;
            throw std::runtime_error(badReq);
        }
    }
    else
    {
        return false;
    }
}

void Demand::handlePostCommandsArguments()
{
    if (command == signupStr)
    {
        username.clear();
        password.clear();
        mode.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(username, usernameStr, i) && !argumentsFinder(mode, Mode, i) &&
                !argumentsFinder(password, passwordStr, i))
                throw std::runtime_error(badReq);

            i = argEndpoint + 1;
        }
        if (username.empty() || password.empty() || mode.empty())
        {
            throw std::runtime_error(badReq);
        }
    }
    else if (command == loginStr)
    {
        username.clear();
        password.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(username, usernameStr, i) && !argumentsFinder(password, passwordStr, i))
                throw std::runtime_error(badReq);
            i = argEndpoint + 1;
        }
        if (username.empty() || password.empty())
        {
            throw std::runtime_error(badReq);
        }
    }
    else if (command == logoutStr)
    {
        if(inputWords.size() > 3)
            throw std::runtime_error(badReq);
        username.clear();
        password.clear();
        mode.clear();
    }
    else if (command == musicStr)
    {
        title.clear();
        path.clear();
        yearStr.clear();
        albumName.clear();
        tagsString.clear();
        durationStr.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(title, Title, i) && !argumentsFinder(path, Path, i) &&
                !argumentsFinder(yearStr, Year, i) && !argumentsFinder(albumName, Album, i) &&
                !argumentsFinder(tagsString, Tags, i) && !argumentsFinder(durationStr, Duration, i))
                throw std::runtime_error(badReq);

            i = argEndpoint + 1;
        }
        if (title.empty() || path.empty() || yearStr.empty() || albumName.empty() || tagsString.empty() || durationStr.empty())
        {
            throw std::runtime_error(badReq);
        }
        try
        {
            year = std::stoi(yearStr);
        }
        catch (std::invalid_argument &inv)
        {
            throw std::runtime_error(badReq);
        }
        parseMusicTags();
        readDurationString();
    }
    else if (command == playlistStr)
    {
        playlistName.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(playlistName, Name, i))
                throw std::runtime_error(badReq);
            i = argEndpoint + 1;
        }
    }
    else if (command == followStr)
    {
        userIdStr.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(userIdStr, idStr, i))
                throw std::runtime_error(badReq);
            i = argEndpoint + 1;
        }
        if (userIdStr.empty())
        {
            throw std::runtime_error(badReq);
        }
        try
        {
            userId = std::stoi(userIdStr);
        }
        catch (std::invalid_argument &inv)
        {
            throw std::runtime_error(badReq);
        }
    }
    else if (command == unfollowStr)
    {
        userIdStr.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(userIdStr, idStr, i))
                throw std::runtime_error(badReq);
            i = argEndpoint + 1;
        }
        if (userIdStr.empty())
        {
            throw std::runtime_error(badReq);
        }
        try
        {
            userId = std::stoi(userIdStr);
        }
        catch (std::invalid_argument &inv)
        {
            throw std::runtime_error(badReq);
        }
    }
    else if (command == likeStr)
    {
        musicIdStr.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(musicIdStr, idStr, i))
                throw std::runtime_error(badReq);
            i = argEndpoint + 1;
        }
        if (musicIdStr.empty())
        {
            throw std::runtime_error(badReq);
        }
        try
        {
            musicId = std::stoi(musicIdStr);
        }
        catch (std::invalid_argument &inv)
        {
            throw std::runtime_error(badReq);
        }
    }
    inputWords.clear();
    return;
}
void Demand::handleDeleteCommandsArguments()
{

    if (command == musicStr)
    {
        musicIdStr.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(musicIdStr, idStr, i))
                throw std::runtime_error(badReq);
            i = argEndpoint + 1;
        }
        if (musicIdStr.empty())
            throw std::runtime_error(badReq);
        try
        {
            musicId = std::stoi(musicIdStr);
        }
        catch (std::invalid_argument &inv)
        {
            throw std::runtime_error(badReq);
        }
    }
    else if (command == playlistStr)
    {
        playlistName.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(playlistName, nameStr, i))
                throw std::runtime_error(badReq);
            i = argEndpoint + 1;
        }
        if (playlistName.empty())
            throw std::runtime_error(badReq);
    }
    inputWords.clear();
    return;
}
void Demand::handlePutCommandsArguments()
{

    if (command == addPlaylistStr)
    {
        playlistName.clear();
        musicIdStr.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(playlistName, nameStr, i) && !argumentsFinder(musicIdStr, idStr, i))
                throw std::runtime_error(badReq);
            i = argEndpoint + 1;
        }
        if (playlistName.empty() || musicIdStr.empty())
            throw std::runtime_error(badReq);
        try
        {
            musicId = std::stoi(musicIdStr);
        }
        catch (std::invalid_argument &inv)
        {
            throw std::runtime_error(badReq);
        }
        inputWords.clear();
        return;
    }
}
void Demand::handleGetCommandsArguments()
{
    if (command == registeredMusicsStr)
    {
        if(inputWords.size() > 3)
            throw std::runtime_error(badReq);
    }
    else if (command == searchMusicsStr)
    {
        musicName.clear();
        singer.clear();
        tagsString.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(musicName, nameStr, i) && !argumentsFinder(singer, artistStr, i) &&
                !argumentsFinder(tagsString, tagStr, i))
                throw std::runtime_error(badReq);

            i = argEndpoint + 1;
        }
    }
    else if (command == musicsStr)
    {
        musicIdStr.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(musicIdStr, idStr, i))
                throw std::runtime_error(badReq);

            i = argEndpoint + 1;
        }
        try
        {
            if (!musicIdStr.empty())
            {
                musicId = std::stoi(musicIdStr);
            }
        }
        catch (std::invalid_argument &inv)
        {
            throw std::runtime_error(badReq);
        }
    }
    else if (command == usersStr)
    {
        userIdStr.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(userIdStr, idStr, i))
                throw std::runtime_error(badReq);
            i = argEndpoint + 1;
        }
        try
        {
            if (!userIdStr.empty())
            {
                userId = std::stoi(userIdStr);
            }
        }
        catch (std::invalid_argument &inv)
        {
            throw std::runtime_error(badReq);
        }
    }
    else if (command == playlistStr)
    {
        playlistName.clear();
        userIdStr.clear();
        for (size_t i = 3; i < inputWords.size(); i = i)
        {
            if (!argumentsFinder(userIdStr, idStr, i) && !argumentsFinder(playlistName, nameStr, i))
                throw std::runtime_error(badReq);

            i = argEndpoint + 1;
        }
        if (userIdStr.empty())
            throw std::runtime_error(badReq);
        try
        {
            userId = std::stoi(userIdStr);
        }
        catch (std::invalid_argument &inv)
        {
            throw std::runtime_error(badReq);
        }
    }
    else if (command == recommendationsStr)
    {
        if(inputWords.size() > 3)
            throw std::runtime_error(badReq);
    }
    else if (command == likesStr)
    {
        if(inputWords.size() > 3)
            throw std::runtime_error(badReq);    
    }
    inputWords.clear();
    return;
}

Demand::PostCommand Demand::convertToPostCommand(const std::string &cmnd)
{
    if (cmnd == signupStr)
    {
        return Demand::PostCommand::signup;
    }
    else if (cmnd == loginStr)
    {
        return Demand::PostCommand::login;
    }
    else if (cmnd == likeStr)
    {
        return Demand::PostCommand::like;
    }
    else if (cmnd == logoutStr)
    {
        return Demand::PostCommand::logout;
    }
    else if (cmnd == musicStr)
    {
        return Demand::PostCommand::music;
    }
    else if (cmnd == playlistStr)
    {
        return Demand::PostCommand::playlist;
    }
    else if (cmnd == unfollowStr)
    {
        return Demand::PostCommand::unfollow;
    }
    else if (cmnd == followStr)
    {
        return Demand::PostCommand::follow;
    }
    else
    {
        return static_cast<Demand::PostCommand>(-1);
    }
}
Demand::PutCommand Demand::convertToPutCommand(const std::string &cmnd)
{
    if (cmnd == addPlaylistStr)
    {
        return Demand::PutCommand::add_playlist;
    }
    else
    {
        return static_cast<Demand::PutCommand>(-1);
    }
}
Demand::GetCommand Demand::convertToGetCommand(const std::string &cmnd)
{
    if (cmnd == playlistStr)
    {
        return Demand::GetCommand::playlist;
    }
    else if (cmnd == usersStr)
    {
        return Demand::GetCommand::users;
    }
    else if (cmnd == musicsStr)
    {
        return Demand::GetCommand::musics;
    }
    else if (cmnd == searchMusicsStr)
    {
        return Demand::GetCommand::search_music;
    }
    else if (cmnd == registeredMusicsStr)
    {
        return Demand::GetCommand::registered_musics;
    }
    else if (cmnd == recommendationsStr)
    {
        return Demand::GetCommand::recommendations;
    }
    else if (cmnd == likesStr)
    {
        return Demand::GetCommand::likes;
    }
    else
    {
        return static_cast<Demand::GetCommand>(-1);
    }
}
Demand::DeleteCommand Demand::convertToDeleteCommand(const std::string &cmnd)
{
    if (cmnd == musicStr)
    {
        return Demand::DeleteCommand::music;
    }
    else if (cmnd == playlistStr)
    {
        return Demand::DeleteCommand::playlist;
    }
    else
    {
        return static_cast<Demand::DeleteCommand>(-1);
    }
}

void Demand::readDurationString()
{
    std::string songDuration = this->durationStr;
    std::string minString;
    std::string hourString;
    std::string secString;
    size_t startPos = 0;
    size_t endPos = songDuration.find(':');
    hourString = songDuration.substr(startPos, endPos - startPos);
    songDuration = songDuration.substr(endPos + 1, songDuration.size() - (endPos + 1));
    try
    {
        this->hours = stoi(hourString);
        if (this->hours > 99)
            throw std::runtime_error(badReq);
    }
    catch (std::invalid_argument &inv)
    {
        throw std::runtime_error(badReq);
    }

    endPos = songDuration.find(':');
    minString = songDuration.substr(startPos, endPos - startPos);
    songDuration = songDuration.substr(endPos + 1, songDuration.size() - (endPos + 1));
    try
    {
        this->minutes = stoi(minString);
        if (this->minutes >= 60)
            throw std::runtime_error(badReq);
    }
    catch (std::invalid_argument &inv)
    {
        throw std::runtime_error(badReq);
    }

    endPos = songDuration.size();
    secString = songDuration.substr(startPos, endPos - startPos);
    try
    {
        this->seconds = stoi(secString);
        if (this->seconds >= 60)
            throw std::runtime_error(badReq);
    }
    catch (std::invalid_argument &inv)
    {
        throw std::runtime_error(badReq);
    }
}
void Demand::parseMusicTags()
{
    std::string songTags = this->tagsString;
    size_t startPos = 0;
    size_t endPos = songTags.find(';');

    while (endPos != std::string::npos)
    {
        genres.push_back(songTags.substr(startPos, endPos - startPos));
        startPos = endPos + 1;
        endPos = songTags.find(';', startPos);
    }

    // Add the last word if there are no more ";" characters
    if (endPos == std::string::npos)
    {
        genres.push_back(songTags.substr(startPos, songTags.length() - startPos));
    }
}
