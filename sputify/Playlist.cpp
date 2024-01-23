#include "Playlist.h"

Playlist::Playlist(std::string name_)
{
    name = name_;
    totalSeconds = 0;
    durationStr = "00:00:00";
}
void Playlist::eraseMusic(MUSIC *deleteIt)
{
    std::vector<MUSIC *>::iterator it = std::find(containingMusics.begin(), containingMusics.end(), deleteIt);
    if (it != containingMusics.end())
    {
        containingMusics.erase(it);
    }
    this->updateDuration();
}
void Playlist::introduce()
{
    std::cout << name << commaSpaceStr << containingMusics.size() << commaSpaceStr << durationStr<<std::endl;
}
void Playlist::updateDuration()
{
    this->totalSeconds = 0;
    for (MUSIC *s : this->containingMusics)
    {
        this->totalSeconds += s->get_length();
    }
    updateDurationString();
}
std::string correctDurationFormat(int const t)
{
    std::string f;
    if (t == 0)
        f = "00";
    else if (t < 10)
        f = "0" + std::to_string(t);
    else
        f = std::to_string(t);
    return f;
}

void Playlist::updateDurationString()
{
    int hours = std::floor(totalSeconds / 3600);
    int minutes = std::floor((totalSeconds - (hours * 3600)) / 60);
    int seconds = totalSeconds - (hours * 3600) - (minutes * 60);
    std::string h;
    std::string m;
    std::string s;
    h = correctDurationFormat(hours);
    m = correctDurationFormat(minutes);
    s = correctDurationFormat(seconds);
    this->durationStr = h + ":" + m + ":" + s;
}
