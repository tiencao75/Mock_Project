#ifndef MEDIA_LIBRARY_HPP
#define MEDIA_LIBRARY_HPP

#include <map>
#include <memory>
#include <string>
#include "MediaFile.hpp"

class MediaLibrary
{
private:
    std::map<unsigned int, std::shared_ptr<MediaFile>> mediaFiles;

    std::string truncateString(const std::string& str, size_t width);
 
    

public:
    MediaLibrary(); // Constructor
    const std::map<unsigned int, std::shared_ptr<MediaFile>> &getAllMediaFiles() const;
    void addMediaFile(int index, const std::shared_ptr<MediaFile> &file);
    void removeMediaFile(unsigned int index);
    std::shared_ptr<MediaFile> getMediaFileByIndex(unsigned int index) const;
    void scanDirectory(const std::string &directory);

    void scanUSBDevice();

    // Pagination display
    void displayPaginatedFiles(const std::map<unsigned int, std::shared_ptr<MediaFile>>& files, size_t pageSize = 25);

    void clearScreen() ;

    // // Helper function to truncate long strings
    // std::string truncateString(const std::string& str, size_t width);
};

#endif // MEDIA_LIBRARY_HPP