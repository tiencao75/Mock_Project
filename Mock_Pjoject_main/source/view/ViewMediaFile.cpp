#include "ViewMediaFile.hpp"
#include <iostream>
#include <algorithm>

ViewMediaFile::ViewMediaFile() : currentPage(0) {}

int ViewMediaFile::calculateTotalPages(int totalFiles)
{
    const int filesPerPage = 10;
    return (totalFiles + filesPerPage - 1) / filesPerPage;
}

void ViewMediaFile::showMediaFilesPage(const std::vector<std::string> &files, int page)
{
    int start = page * 10;
    int end = std::min(start + 10, (int)files.size());
    std::cout << "Showing files on page " << page + 1 << ":" << std::endl;
    for (int i = start; i < end; ++i)
    {
        std::cout << "- " << files[i] << std::endl;
    }
}
void ViewMediaFile::nextPage()
{
    currentPage++;
    std::cout << "Moving to next page: " << currentPage + 1 << std::endl;
}

void ViewMediaFile::previousPage()
{
    if (currentPage > 0)
    {
        currentPage--;
        std::cout << "Switched to previous page.\n";
    }
    else
    {
        std::cout << "Already on the first page.\n";
    }
}
void ViewMediaFile::show()
{
    std::cout << "Displaying Media Files View.\n";
}
void ViewMediaFile::hide()
{
    std::cout << "Hiding Media Files View.\n";
}
void ViewMediaFile::handleInput(const std::string &input)
{
    if (input == "next")
    {
        nextPage();
    }
    else if (input == "previous")
    {
        previousPage();
    }
    else
    {
        std::cout << "Invalid input.\n";
    }
}