#ifndef TAGLIB_HPP
#define TAGLIB_HPP

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <string>

// Cấu trúc lưu metadata gốc
struct OriginalMetadata
{
    std::string title;
    std::string artist;
    std::string album;
    unsigned int year;
    unsigned int track;
    std::string genre;
};

// In thông tin metadata
void printMetadata(TagLib::Tag *tag, TagLib::AudioProperties *audioProperties);

// Khôi phục metadata về giá trị ban đầu
void restoreMetadata(TagLib::Tag *tag, const OriginalMetadata &originalMetadata);

// Hiển thị tất cả các tệp trong thư mục
void showAllFiles(const std::string &directory);

#endif // TAGLIB_HPP
