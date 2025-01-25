#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <gtest/gtest.h>

// Assuming Playlist is a simple class that has a name and path (simplified for the test)
class Playlist {
public:
    std::string name;
    std::string path;
    Playlist(std::string name, std::string path) : name(name), path(path) {}
};

// ControllerManager class with the method we're testing
class ControllerManager {
public:
    void writeDataToFile(const std::string& filename, const std::map<std::string, std::string>& data) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& entry : data) {
                outFile << entry.first << "," << entry.second << "\n";
            }
            outFile.close();
        }
    }

    std::map<std::string, std::string> readDataFromFile(const std::string& filename) {
        std::map<std::string, std::string> data;
        std::ifstream inFile(filename);
        std::string line;
        while (std::getline(inFile, line)) {
            // Assuming simple CSV format, parse the line
            size_t delimiterPos = line.find(',');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                data[key] = value;
            }
        }
        return data;
    }
};

// Unit test to write and read data from a file
TEST(ControllerManagerTest, WriteAndReadDataTest) {
    ControllerManager controllerManager;
    std::string testFile = "test_data.txt";
    
    // Prepare some test data
    std::map<std::string, std::string> testData = {
        {"key1", "value1"},
        {"key2", "value2"}
    };
    
    // Write data to the file
    controllerManager.writeDataToFile(testFile, testData);

    // Read data from the file
    std::map<std::string, std::string> data = controllerManager.readDataFromFile(testFile);
    
    // Test that the data matches
    ASSERT_EQ(data["key1"], "value1");
    ASSERT_EQ(data["key2"], "value2");

    // Cleanup test file
    std::remove(testFile.c_str());
}