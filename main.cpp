#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>
#include <iostream>
#include <string>


struct OriginalMetadata {
    std::string title;
    std::string artist;
    std::string album;
    unsigned int year;
    unsigned int track;
    std::string genre;
};

void printMetadata(TagLib::Tag* tag, TagLib::AudioProperties* audioProperties) {
    std::cout << "General Information:" << std::endl;
    std::cout << "Title    : " << tag->title() << std::endl;
    std::cout << "Artist   : " << tag->artist() << std::endl;
    std::cout << "Album    : " << tag->album() << std::endl;
    std::cout << "Year     : " << tag->year() << std::endl;
    std::cout << "Duration : " << audioProperties->length() << " seconds" << std::endl;

    std::cout << "\nAudio Information:" << std::endl;
    std::cout << "Channels : " << audioProperties->channels() << std::endl;
    std::cout << "Sample Rate : " << audioProperties->sampleRate() << " Hz" << std::endl;
    std::cout << "Bitrate : " << audioProperties->bitrate() << " kbps" << std::endl;
}

void restoreMetadata(TagLib::Tag* tag, const OriginalMetadata& originalMetadata) {
    tag->setTitle(TagLib::String(originalMetadata.title));
    tag->setArtist(TagLib::String(originalMetadata.artist));
    tag->setAlbum(TagLib::String(originalMetadata.album));
    tag->setYear(originalMetadata.year);
    tag->setTrack(originalMetadata.track);
    tag->setGenre(TagLib::String(originalMetadata.genre));
}

int main() {
    const char* filepath = "media/LiLy.mp3";
    TagLib::FileRef f(filepath);

    if (!f.isNull() && f.tag() && f.audioProperties()) {
        TagLib::Tag* tag = f.tag();
        TagLib::AudioProperties* audioProperties = f.audioProperties();

        
        OriginalMetadata originalMetadata = {
            tag->title().toCString(),
            tag->artist().toCString(),
            tag->album().toCString(),
            tag->year(),
            tag->track(),
            tag->genre().toCString()
        };

        
        printMetadata(tag, audioProperties);

        
        int choice;
        do {
            std::cout << "\nChoose an option to edit metadata (0 to exit, 7 to restore original values):" << std::endl;
            std::cout << "1. Edit Title" << std::endl;
            std::cout << "2. Edit Artist" << std::endl;
            std::cout << "3. Edit Album" << std::endl;
            std::cout << "4. Edit Genre" << std::endl;
            std::cout << "5. Edit Year" << std::endl;
            std::cout << "6. Edit Track" << std::endl;
            std::cout << "7. Restore Original Values" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore();  

            std::string newValue;
            unsigned int newYear;
            switch (choice) {
                case 1:
                    std::cout << "Enter new title: ";
                    std::getline(std::cin, newValue);
                    tag->setTitle(TagLib::String(newValue));
                    break;
                case 2:
                    std::cout << "Enter new artist: ";
                    std::getline(std::cin, newValue);
                    tag->setArtist(TagLib::String(newValue));
                    break;
                case 3:
                    std::cout << "Enter new album: ";
                    std::getline(std::cin, newValue);
                    tag->setAlbum(TagLib::String(newValue));
                    break;
                case 4:
                    std::cout << "Enter new genre: ";
                    std::getline(std::cin, newValue);
                    tag->setGenre(TagLib::String(newValue));
                    break;
                case 5:
                    std::cout << "Enter new year: ";
                    std::cin >> newYear;
                    tag->setYear(newYear);
                    std::cin.ignore();  
                    break;
                case 6:
                    std::cout << "Enter new track number: ";
                    std::cin >> newYear;
                    tag->setTrack(newYear);
                    std::cin.ignore();  
                    break;
                case 7:
                    
                    std::cout << "Restoring original values..." << std::endl;
                    restoreMetadata(tag, originalMetadata);
                    break;
                case 0:
                    std::cout << "Exiting editing..." << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice, please try again." << std::endl;
            }

            
            if (choice != 0) {
                printMetadata(tag, audioProperties);
            }
        } while (choice != 0);

        
        if (f.save()) {
            std::cout << "\nMetadata updated successfully!" << std::endl;
        } else {
            std::cerr << "Error: Could not save changes to the file." << std::endl;
        }
    } else {
        std::cerr << "Error: Could not open file or retrieve metadata." << std::endl;
    }

    return 0;
}
