#include <iostream>
#include <string>
#include <filesystem> // Để kiểm tra file tồn tại
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>

namespace fs = std::filesystem;

// Hàm kiểm tra file tồn tại
bool fileExists(const std::string &filePath)
{
    return fs::exists(filePath);
}

// Hàm hiển thị metadata
void displayMetadata(const std::string &filePath)
{
    if (!fileExists(filePath))
    {
        std::cerr << "Error: File does not exist: " << filePath << std::endl;
        return;
    }

    TagLib::FileRef file(filePath.c_str());
    if (!file.isNull() && file.tag())
    {
        TagLib::Tag *tag = file.tag();
        std::cout << "=== Metadata Information ===" << std::endl;
        std::cout << "File        : " << filePath << std::endl;
        std::cout << "Title       : " << tag->title() << std::endl;
        std::cout << "Artist      : " << tag->artist() << std::endl;
        std::cout << "Album       : " << tag->album() << std::endl;
        std::cout << "Year        : " << tag->year() << std::endl;
        std::cout << "Track       : " << tag->track() << std::endl;
        std::cout << "Genre       : " << tag->genre() << std::endl;
    }
    else
    {
        std::cerr << "Error: Unable to read metadata from file: " << filePath << std::endl;
    }
}

// Hàm chỉnh sửa metadata
void editMetadata(const std::string &filePath)
{
    if (!fileExists(filePath))
    {
        std::cerr << "Error: File does not exist: " << filePath << std::endl;
        return;
    }

    TagLib::FileRef file(filePath.c_str());
    if (!file.isNull() && file.tag())
    {
        TagLib::Tag *tag = file.tag();
        std::string newTitle, newArtist, newAlbum, newGenre;
        int newYear, newTrack;

        std::cout << "Enter new Title: ";
        std::getline(std::cin, newTitle);
        std::cout << "Enter new Artist: ";
        std::getline(std::cin, newArtist);
        std::cout << "Enter new Album: ";
        std::getline(std::cin, newAlbum);
        std::cout << "Enter new Year: ";
        std::cin >> newYear;
        std::cout << "Enter new Track: ";
        std::cin >> newTrack;
        std::cin.ignore(); // Clear input buffer
        std::cout << "Enter new Genre: ";
        std::getline(std::cin, newGenre);

        tag->setTitle(newTitle);
        tag->setArtist(newArtist);
        tag->setAlbum(newAlbum);
        tag->setYear(newYear);
        tag->setTrack(newTrack);
        tag->setGenre(newGenre);

        if (file.save())
        {
            std::cout << "Metadata updated successfully!" << std::endl;
        }
        else
        {
            std::cerr << "Error: Failed to save metadata." << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Unable to read metadata from file: " << filePath << std::endl;
    }
}

// Hàm xóa metadata
void clearMetadata(const std::string &filePath)
{
    if (!fileExists(filePath))
    {
        std::cerr << "Error: File does not exist: " << filePath << std::endl;
        return;
    }

    TagLib::FileRef file(filePath.c_str());
    if (!file.isNull() && file.tag())
    {
        TagLib::Tag *tag = file.tag();

        tag->setTitle("");
        tag->setArtist("");
        tag->setAlbum("");
        tag->setYear(0);
        tag->setTrack(0);
        tag->setGenre("");

        if (file.save())
        {
            std::cout << "Metadata cleared successfully!" << std::endl;
        }
        else
        {
            std::cerr << "Error: Failed to clear metadata." << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Unable to read metadata from file: " << filePath << std::endl;
    }
}

// Hàm hiển thị thông tin audio
void displayAudioProperties(const std::string &filePath)
{
    if (!fileExists(filePath))
    {
        std::cerr << "Error: File does not exist: " << filePath << std::endl;
        return;
    }

    TagLib::FileRef file(filePath.c_str());
    if (!file.isNull() && file.audioProperties())
    {
        TagLib::AudioProperties *audio = file.audioProperties();

        std::cout << "=== Audio Properties ===" << std::endl;
        std::cout << "File         : " << filePath << std::endl;
        std::cout << "Bitrate      : " << audio->bitrate() << " kbps" << std::endl;
        std::cout << "Sample Rate  : " << audio->sampleRate() << " Hz" << std::endl;
        std::cout << "Channels     : " << audio->channels() << std::endl;
        std::cout << "Length       : " << audio->length() << " seconds" << std::endl;
    }
    else
    {
        std::cerr << "Error: Unable to read audio properties from file: " << filePath << std::endl;
    }
}

// Menu hiển thị lựa chọn
void showMenu()
{
    std::cout << "=== TagLib Metadata Editor ===" << std::endl;
    std::cout << "1. Display Metadata" << std::endl;
    std::cout << "2. Edit Metadata" << std::endl;
    std::cout << "3. Clear Metadata" << std::endl;
    std::cout << "4. Display Audio Properties" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

// Hàm chính
int main()
{
    int choice;
    std::string filePath;

    do
    {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer

        switch (choice)
        {
        case 1:
            std::cout << "Enter file path: ";
            std::getline(std::cin, filePath);
            displayMetadata(filePath);
            break;
        case 2:
            std::cout << "Enter file path: ";
            std::getline(std::cin, filePath);
            editMetadata(filePath);
            break;
        case 3:
            std::cout << "Enter file path: ";
            std::getline(std::cin, filePath);
            clearMetadata(filePath);
            break;
        case 4:
            std::cout << "Enter file path: ";
            std::getline(std::cin, filePath);
            displayAudioProperties(filePath);
            break;
        case 0:
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;

    } while (choice != 0);

    return 0;
}
