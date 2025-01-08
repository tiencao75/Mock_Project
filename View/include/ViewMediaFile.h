#ifndef VIEWMEDIAFILE_H
#define VIEWMEDIAFILE_H

#include "ViewBase.h"
#include <vector>
#include <string>

class ViewMediaFile : public ViewBase
{
private:
    int currentPage;
    int calculateTotalPages(int totalFiles);

public:
    ViewMediaFile();
    void showMediaFilesPage(const std::vector<std::string> &files, int page);
    void nextPage();
    void previousPage();
    void show() override;
    void hide() override;
    void handleInput(const std::string &input) override;
};

#endif