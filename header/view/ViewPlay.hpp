#ifndef VIEWPLAY_HPP
#define VIEWPLAY_HPP

#include "ViewBase.hpp"
#include <string>
#include "MediaFile.hpp"

class ViewPlay : public ViewBase {
public:
    void show() override;
    void hide() override;
    void update(const std::string& data) override;
    std::string getName() const override;

    void showPlayerControls();
    void showSongInfo(const MediaFile& file);
};

#endif // VIEWPLAY_HPP
