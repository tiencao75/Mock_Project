// S32K144Interface.hpp (Cập nhật đầy đủ với con trỏ player)
#ifndef S32K144INTERFACE_HPP
#define S32K144INTERFACE_HPP

#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <cstdint>

class PlayingMediaController; // Forward declaration

class S32K144Interface {
public:
    static S32K144Interface& getInstance(PlayingMediaController& playerController);

    void startReadingSignal();
    void stopReadingSignal();
    void sendTime(uint8_t minutes, uint8_t seconds);
    //boost::asio::deadline_timer timer; // Timer quản lý timeout
private:
    S32K144Interface(PlayingMediaController& playerController);
    ~S32K144Interface();

    S32K144Interface(const S32K144Interface&) = delete;
    S32K144Interface& operator=(const S32K144Interface&) = delete;

    void readSignal();

    PlayingMediaController* player; // Con trỏ đến PlayingMediaController
    boost::asio::io_service io;
    boost::asio::serial_port serial;
    std::thread readingThread;
    bool running;
    boost::asio::deadline_timer timer; // Thêm timer để quản lý timeout

    static std::mutex instanceMutex;
    static std::mutex signalMutex;
    static S32K144Interface* instance;
    bool connected; // Trạng thái kết nối
};

#endif // S32K144INTERFACE_HPP
