#include "ExceptionLib.hpp"

void validateAlphaSring(const std::string& alString) {
    std::regex alStringTemplate(R"([a-zA-Z\s]+)");
    if (!std::regex_match(alString,alStringTemplate)) {
        throw InvalidAlphaSringException();
    }
}

void validateYear(const std::string& year) {
    std::regex YearTemplate("\\d{4}$");
    if (!std::regex_match(year, YearTemplate)) {
        throw InvalidYearException();
    }
    size_t _year = std::stoi(year);
    if (_year > 2025) {
        throw InvalidYearException();
    }
}

void validateScanUSB(const size_t& value, const size_t maxValue) {
    if (value < 1 || value > maxValue) {
        throw InvalidMenuChoiceException(); // Ném ngoại lệ nếu giá trị không hợp lệ
    }
}


void validatePosInteger(const size_t& value) {
    if (value < 0) {
        throw InvalidInputIntegerException();
    }
}

void validateScanfMenu(const size_t& value) {
    if (value < 1 || value > 4) {
        throw InvalidMenuChoiceException();
    }
}

void validateMainMenu(const size_t& value) {
    if (value < 0 || value > 5) {
        throw InvalidMenuChoiceException();
    } 
}
void validateMediaFilesMenu(const size_t& value) {
    if (value < 0 || value > 2) {
        throw InvalidMenuChoiceException();
    }    
}
void validateMetadataMenu(const size_t& value) {
    if (value < 0 || value > 1) {
        throw InvalidMenuChoiceException();
    }   
}
// void validateEditVideoMenu(const size_t& value) {
//     if (value < 0 || value > 1) {
//         throw InvalidMenuChoiceException();
//     }  
// }
void validateEditAudioMenu(const size_t& value) {
    if (value < 0 || value > 7) {
        throw InvalidMenuChoiceException();
    }  
}
void validatePlaylistsMenu(const size_t& value) {
    if (value < 0 || value > 6) {
        throw InvalidMenuChoiceException();
    } 
}
void validateDetailedPlaylistMenu(const size_t& value) {
    if (value < 0 || value > 4) {
        throw InvalidMenuChoiceException();
    }  
}
void validatePlayingMediaMenu(const size_t& value) {
    if (value < 0 || value > 9) {
        throw InvalidMenuChoiceException();
    }  
}

void validateVolume(const size_t& value) {
    if (value < 0 || value > 128) {
        throw InvalidVolumeException();
    }   
}

// void validateID(const std::string& ID) {
//     std::regex idTemplate(R"(\d+)");
//     if (!std::regex_match(ID, idTemplate)) {
//         throw InvalidIDException();
//     }
// }

void validateID(const size_t& ID) {
    if (ID <= 0) { // Adjust validation logic if needed
        throw InvalidIDException();
    }
}


void validateTrack(const std::string& value) {
    std::regex TrackTemplate(R"(\d+)");
    if (!std::regex_match(value, TrackTemplate)) {
        throw InvalidTrackException();
    }
}
namespace fs = std::filesystem;

bool validatePath(const std::string& path) {
    fs::path p(path);
    // if (!fs::exists(p) || !fs::is_directory(p)) {
    //     throw InvalidPathException();
    // }
    return fs::exists(p) && fs::is_directory(p);
}

bool isUSBDevicePresent(const std::string& device) {
    std::ifstream file("/dev/" + device);
    return file.good();
}

void Exception_Handler(const std::string& str,std::string& variable, void(*func)(const std::string&)) {
    while(1) {
        try {
            std::cout << str;
            std::getline(std::cin,variable);     
            func(variable);
            break;
        }
        catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }
    }
}

void Exception_Handler(const std::string& str,size_t& variable, void(*func)(const size_t&)) {
    while(1) {
        try {
            std::cout << str;
            std::cin >> variable;
            if (std::cin.fail()) {
                throw InvalidInputIntegerException();
            }
            func(variable);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;  
        }
        catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
void Exception_Handler(const std::string& str, std::string& variable, bool(*func)(const std::string&), bool& backToMenu) {
    while (true) {
        try {
            std::cout << str;
            std::getline(std::cin, variable);

            // Kiểm tra giá trị nhập vào
            if (func(variable)) {
                backToMenu = false;
                break; // Nếu kiểm tra thành công, thoát vòng lặp
            } else {
                std::cerr << "[ERROR] Validation failed. The path does not exist or is not a valid directory.\n";
                std::cout << "What would you like to do?\n";
                std::cout << " [1] Try again\n";
                std::cout << " [2] Back to menu\n";
                std::cout << "Enter your choice: ";

                int choice;
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bỏ qua phần nhập thừa

                if (choice == 2) {
                    backToMenu = true; // Đặt cờ quay về menu
                    return; // Thoát khỏi Exception_Handler
                } else if (choice != 1) {
                    std::cerr << "[ERROR] Invalid choice. Assuming 'Back to menu'.\n";
                    backToMenu = true; // Mặc định quay về menu nếu nhập sai
                    return;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Exception caught: " << e.what() << "\n";
        }
    }
}