#ifndef VIEWMEDIAFILE_HPP
#define VIEWMEDIAFILE_HPP

#include "ViewBase.hpp"
#include <string>
#include <vector>
#include "MediaFile.hpp"

class ViewMediaFile : public ViewBase {
private:
    int currentPage;

public:
    ViewMediaFile();

    void show() override;
    void hide() override;
    void update(const std::string& data) override;
    std::string getName() const override;

    void showMediaFilesPage(const std::vector<MediaFile>& files, int page);
    void nextPage();
    void previousPage();
};

#endif // VIEWMEDIAFILE_HPP
