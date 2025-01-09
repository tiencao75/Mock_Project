#ifndef VIEWPLAY_H
#define VIEWPLAY_H

#include "ViewBase.h"
#include <string>

class ViewPlay : public ViewBase
{
public:
    void showPlayerControls();
    void showSongInfo(const std::string &file);
    void show() override;
    void hide() override;
    void handleInput(const std::string &input) override;
};

#endif