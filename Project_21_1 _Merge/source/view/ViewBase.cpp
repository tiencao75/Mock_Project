#include "ViewBase.hpp"
void ViewBase::pauseScreen(){
    std::cout << "Press Enter to continue...";
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Xóa b? d?m
    std::cin.get(); 
}

void ViewBase::hide(){
    #ifdef _WIN32

    system("cls");
    #else

    system("clear");
    #endif
}
