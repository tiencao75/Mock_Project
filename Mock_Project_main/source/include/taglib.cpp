#include "taglib.hpp"
#include <iostream>
#include <iomanip>
#include <filesystem> // Thư viện filesystem

namespace fs = std::filesystem; // Alias cho namespace filesystem

// In thông tin metadata
void printMetadata(TagLib::Tag *tag, TagLib::AudioProperties *audioProperties)
{
    std::cout << "\n=== Metadata Information ===" << std::endl;
    std::cout << "Title       : " << tag->title().toCString() << std::endl;
    std::cout << "Artist      : " << tag->artist().toCString() << std::endl;
    std::cout << "Album       : " << tag->album().toCString() << std::endl;
    std::cout << "Year        : " << tag->year() << std::endl;
    std::cout << "Track       : " << tag->track() << std::endl;             // Hiển thị Track
    std::cout << "Genre       : " << tag->genre().toCString() << std::endl; // Hiển thị Genre
    std::cout << "Duration    : " << audioProperties->length() << " seconds" << std::endl;

    std::cout << "\n=== Audio Properties ===" << std::endl;
    std::cout << "Bitrate     : " << audioProperties->bitrate() << " kbps" << std::endl;
    std::cout << "Sample Rate : " << audioProperties->sampleRate() << " Hz" << std::endl;
    std::cout << "Channels    : " << audioProperties->channels() << std::endl;
}

// Khôi phục metadata về giá trị ban đầu
void restoreMetadata(TagLib::Tag *tag, const OriginalMetadata &originalMetadata)
{
    tag->setTitle(TagLib::String(originalMetadata.title));
    tag->setArtist(TagLib::String(originalMetadata.artist));
    tag->setAlbum(TagLib::String(originalMetadata.album));
    tag->setYear(originalMetadata.year);
    tag->setTrack(originalMetadata.track);
    tag->setGenre(TagLib::String(originalMetadata.genre));
}

// Hiển thị tất cả các tệp trong thư mục
void showAllFiles(const std::string &directory)
{
    std::cout << "\nFiles in directory " << directory << ":\n"
              << std::endl;
    int index = 1;
    for (const auto &entry : fs::directory_iterator(directory))
    {
        if (fs::is_regular_file(entry))
        {
            std::cout << index++ << ". " << entry.path().filename().string() << std::endl;
        }
    }
}

