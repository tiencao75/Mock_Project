#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <gtest/gtest.h>
#include "ControllerManager.hpp"
#include "ModelManager.hpp"
#include "ViewManager.hpp"
#include <gmock/gmock.h>

class ControllerManagerTest : public ::testing::Test {
protected:
    ControllerManager controllerManager;
    std::string testFilename = "test_file.txt";

    void SetUp() override {
        // Tạo file test
        std::ofstream file(testFilename);
        if (file.is_open()) {
            file << "key1=value1\n";
            file << "key2=value2\n";
            file << "# This is a comment\n";
            file << "key3=value3\n";
            file.close();
        }
    }

    void TearDown() override {
        // Xóa file test sau khi hoàn thành
        std::remove(testFilename.c_str());
    }
};

TEST_F(ControllerManagerTest, ReadDataFromFile_ValidFile) {
    std::map<std::string, std::string> expectedData = {
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"}
    };

    std::map<std::string, std::string> result = controllerManager.readDataFromFile(testFilename);

    EXPECT_EQ(result, expectedData);
}

TEST_F(ControllerManagerTest, ReadDataFromFile_EmptyFile) {
    std::string emptyFile = "empty_test_file.txt";
    std::ofstream file(emptyFile);
    file.close();

    std::map<std::string, std::string> result = controllerManager.readDataFromFile(emptyFile);

    EXPECT_TRUE(result.empty());

    std::remove(emptyFile.c_str());
}

TEST_F(ControllerManagerTest, WriteDataToFile_ValidData) {
    std::map<std::string, std::string> dataToWrite = {
        {"keyA", "valueA"},
        {"keyB", "valueB"},
        {"keyC", "valueC"}
    };

    controllerManager.writeDataToFile(testFilename, dataToWrite);

    // Đọc lại file để kiểm tra
    std::ifstream file(testFilename);
    ASSERT_TRUE(file.is_open());

    std::map<std::string, std::string> readData;
    std::string line;
    while (std::getline(file, line)) {
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            readData[key] = value;
        }
    }
    file.close();

    EXPECT_EQ(readData, dataToWrite);
}

TEST_F(ControllerManagerTest, WriteDataToFile_EmptyData) {
    std::map<std::string, std::string> emptyData;

    controllerManager.writeDataToFile(testFilename, emptyData);

    // Đọc lại file để kiểm tra
    std::ifstream file(testFilename);
    ASSERT_TRUE(file.is_open());

    std::string line;
    bool isEmpty = !std::getline(file, line);
    file.close();

    EXPECT_TRUE(isEmpty);
}

// readPlaylistsFromFile

TEST_F(ControllerManagerTest, ReadPlaylistsFromFile_ValidFile) {
    std::string playlistFile = "test_playlists.txt";
    std::ofstream file(playlistFile);
    if (file.is_open()) {
        file << "Playlist: Rock\n";
        file << "1,/path/to/song1.mp3,mp3\n";
        file << "2,/path/to/song2.mp3,mp3\n";
        file << "---\n";
        file << "Playlist: Jazz\n";
        file << "3,/path/to/song3.mp3,mp3\n";
        file << "---\n";
        file.close();
    }

    controllerManager.readPlaylistsFromFile(playlistFile);

    const auto& playlists = controllerManager.getModelManager().getPlaylistLibrary().getAllPlaylists();

    ASSERT_EQ(playlists.size(), 2);

    auto rockPlaylist = playlists.at(1);
    ASSERT_EQ(rockPlaylist->getName(), "Rock");
    ASSERT_EQ(rockPlaylist->getSongs().size(), 2);
    EXPECT_EQ(rockPlaylist->getSongs().at(1).getPath(), "/path/to/song1.mp3");
    EXPECT_EQ(rockPlaylist->getSongs().at(2).getPath(), "/path/to/song2.mp3");

    auto jazzPlaylist = playlists.at(2);
    ASSERT_EQ(jazzPlaylist->getName(), "Jazz");
    ASSERT_EQ(jazzPlaylist->getSongs().size(), 1);
    EXPECT_EQ(jazzPlaylist->getSongs().at(3).getPath(), "/path/to/song3.mp3");

    std::remove(playlistFile.c_str());
}

TEST_F(ControllerManagerTest, ReadPlaylistsFromFile_InvalidFile) {
    std::string invalidFile = "non_existent_file.txt";

    testing::internal::CaptureStderr();
    controllerManager.readPlaylistsFromFile(invalidFile);
    std::string errorOutput = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(errorOutput.find("Error: Unable to open file") != std::string::npos);
}

//handleInput
// TEST_F(ControllerManagerTest, HandleInputData_InvalidPlaylistFormat) {
//     std::ofstream file("playlistsData.txt");
//     if (file.is_open()) {
//         file << "Invalid data format\n";
//         file.close();
//     }

//     testing::internal::CaptureStderr();
//     controllerManager.handleInputData();
//     std::string errorOutput = testing::internal::GetCapturedStderr();

//     EXPECT_TRUE(errorOutput.find("Warning: Invalid song format in line") != std::string::npos);

//     std::remove("playlistsData.txt");
// }

// TEST_F(ControllerManagerTest, HandleInputData_ScanfOptionExecuted) {
//     // Mock scanfOptionController behavior
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_MediaFileExecuted) {
//     // Mock mediaFileController behavior
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_MetadataExecuted) {
//     // Mock metadataController behavior
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_PlaylistManagerExecuted) {
//     // Mock playlistController behavior
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_PlayingMediaExecuted) {
//     // Mock playingMediaController behavior
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_ExitOption) {
//     // Simulate Exit case
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_InvalidOption) {
//     // Simulate invalid option case
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_ExceptionInScanfOption) {
//     // Simulate exception in scanfOptionController.handleInput
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_ExceptionInMediaFile) {
//     // Simulate exception in mediaFileController.handleInput
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_ExceptionInMetadata) {
//     // Simulate exception in metadataController.handleInput
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_ExceptionInPlaylist) {
//     // Simulate exception in playlistController.handleInput
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

// TEST_F(ControllerManagerTest, HandleInputData_ExceptionInPlayingMedia) {
//     // Simulate exception in playingMediaController.handleInput
//     EXPECT_NO_THROW(controllerManager.handleInputData());
// }

using ::testing::Return;

class MockViewManager : public ViewManager {
public:
    MOCK_METHOD(ViewBase*, getCurrentView, (), ());
    MOCK_METHOD(ViewBase*, getView, (const std::string&), ());
};

class MockScanfOptionController : public ScanfOptionController {
public:
    MockScanfOptionController(ModelManager& modelManager, ViewManager& viewManager)
        : ScanfOptionController(modelManager, viewManager) {}
    MOCK_METHOD(void, handleInput, (), ());
};

class MockMainMenuController : public MainMenuController {
public:
    MockMainMenuController(ModelManager& modelManager, ViewManager& viewManager)
        : MainMenuController(modelManager, viewManager) {}
    MOCK_METHOD(void, showMainMenu, (), ());
};

// Test fixture
class ControllerManagerTest2 : public ::testing::Test {
protected:
    ModelManager mockModelManager; // Giả lập ModelManager
    MockViewManager mockViewManager; // Mock ViewManager
    MockScanfOptionController mockScanfOptionController;
    MockMainMenuController mockMainMenuController;

    ControllerManager controllerManager; // Đối tượng cần kiểm tra

    // Khởi tạo mock controllers trong constructor
    ControllerManagerTest2()
        : mockScanfOptionController(mockModelManager, mockViewManager),
          mockMainMenuController(mockModelManager, mockViewManager),
          controllerManager() {}

    void SetUp() override {
        // Cấu hình trước khi chạy test
    }

    void TearDown() override {
        // Dọn dẹp sau khi chạy test
    }
};

// // Test case: Lựa chọn ScanfOption
// TEST_F(ControllerManagerTest2, HandleInputData_ScanfOption) {
//     EXPECT_CALL(mockMainMenuController, showMainMenu()).Times(1);
//     EXPECT_CALL(mockScanfOptionController, handleInput()).Times(1);

//     // Giả lập lựa chọn của người dùng là ScanfOption
//     testing::internal::CaptureStdout();
//     controllerManager.handleInputData();
//     std::string output = testing::internal::GetCapturedStdout();

//     EXPECT_TRUE(output.find("ScanfOption executed") != std::string::npos);
// }

// // Test case: Thoát chương trình (Exit)
// TEST_F(ControllerManagerTest2, HandleInputData_Exit) {
//     EXPECT_CALL(mockMainMenuController, showMainMenu()).Times(1);
//     EXPECT_CALL(mockViewManager, getView("ViewMainMenu")).WillOnce(Return(new ViewMainMenu()));

//     // Giả lập lựa chọn của người dùng là Exit
//     testing::internal::CaptureStdout();
//     controllerManager.handleInputData();
//     std::string output = testing::internal::GetCapturedStdout();

//     EXPECT_TRUE(output.find("Exiting application...") != std::string::npos);
// }

// // Test case: Lựa chọn không hợp lệ
// TEST_F(ControllerManagerTest2, HandleInputData_InvalidOption) {
//     EXPECT_CALL(mockMainMenuController, showMainMenu()).Times(1);
//     EXPECT_CALL(mockViewManager, getView("ViewMainMenu")).WillOnce(Return(new ViewMainMenu()));

//     // Giả lập lựa chọn không hợp lệ
//     testing::internal::CaptureStdout();
//     controllerManager.handleInputData();
//     std::string output = testing::internal::GetCapturedStdout();

//     EXPECT_TRUE(output.find("Invalid option. Please try again.") != std::string::npos);
// }