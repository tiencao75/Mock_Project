
////scanUSB/////

#include "MediaLibrary.hpp"
#include <iostream>

void testUSBScan()
{
    // Tạo đối tượng MediaLibrary
    MediaLibrary mediaLibrary;

    // Thực hiện quét thiết bị USB
    std::cout << "Starting USB scan...\n";
    mediaLibrary.scanUSBDevice();

    // Lấy danh sách file MP3/MP4 sau khi quét
    auto mediaFiles = mediaLibrary.getAllMediaFiles();

    // Hiển thị kết quả
    if (mediaFiles.empty())
    {
        std::cout << "No MP3/MP4 files found on the selected USB device.\n";
    }
    else
    {
        std::cout << "Found MP3/MP4 files:\n";
        for (const auto &file : mediaFiles)
        {
            std::cout << "- " << file->getName()
                      << " (Type: " << file->getType() << ")\n";
        }
    }
}

int main()
{
    // Gọi hàm test để kiểm tra tính năng
    testUSBScan();
    return 0;
}

/// playingmedia/////

// #include "PlayingMedia.hpp"
// #include "MediaFile.hpp"
// #include <iostream>
// #include <filesystem>
// #include <vector>
// namespace fs = std::filesystem;

// int main()
// {
//     try
//     {
//         // Initialize PlayingMedia object
//         PlayingMedia player;

//         // Directory containing media files
//         std::string videoDir = "./video";
//         std::vector<MediaFile> mediaFiles;

//         // Iterate through all files in the directory
//         for (const auto &entry : fs::directory_iterator(videoDir))
//         {
//             if (entry.is_regular_file())
//             {
//                 std::string filePath = entry.path().string();
//                 std::string fileType = filePath.substr(filePath.find_last_of('.') + 1);

//                 if (fileType == "mp4")
//                 {
//                     mediaFiles.emplace_back(entry.path().filename().string(), filePath, "video");
//                 }
//                 else if (fileType == "mp3")
//                 {
//                     mediaFiles.emplace_back(entry.path().filename().string(), filePath, "audio");
//                 }
//             }
//         }

//         // Play each media file
//         for (auto &mediaFile : mediaFiles)
//         {
//             std::cout << "Testing playback for: " << mediaFile.getPath() << std::endl;
//             player.setCurrentMediaFile(&mediaFile);
//             player.play();
//             std::cout << "Press Enter to stop playback and continue to the next file..." << std::endl;
//             std::cin.get();
//             player.stop();
//         }
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     return 0;
// }
