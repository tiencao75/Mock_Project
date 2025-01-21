// S32K144Interface.cpp (Đầy đủ tính năng với Singleton)
#include "S32K144Interface.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "PlayingMediaController.hpp"

std::mutex S32K144Interface::instanceMutex;
std::mutex S32K144Interface::signalMutex;
S32K144Interface* S32K144Interface::instance = nullptr;

S32K144Interface::S32K144Interface(PlayingMediaController& playerController)
    : player(&playerController), serial(io), timer(io), running(false) {
    try {
        serial.open("/dev/ttyACM0");
        serial.set_option(boost::asio::serial_port_base::baud_rate(115200));
        serial.set_option(boost::asio::serial_port_base::character_size(8));
        serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
        serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
        serial.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
        connected = true;
        std::cout << "Serial port initialized successfully!" << std::endl;
    } catch (boost::system::system_error& e) {
        // std::cerr << "Error initializing serial port: " << e.what() << std::endl;
        // throw;
        connected = false; // Không kết nối được
        std::cerr << "Error initializing serial port: " << e.what() << std::endl;
    }
}

S32K144Interface::~S32K144Interface() {
    stopReadingSignal();
    if (serial.is_open()) {
        serial.close();
    }
}

S32K144Interface& S32K144Interface::getInstance(PlayingMediaController& playerController) {
    std::lock_guard<std::mutex> lock(instanceMutex);
    if (instance == nullptr) {
        instance = new S32K144Interface(playerController);
    }
    return *instance;
}

void S32K144Interface::startReadingSignal() {
    running = true;
    readingThread = std::thread(&S32K144Interface::readSignal, this);
}

void S32K144Interface::stopReadingSignal() {
    running = false;
    // Ngắt I/O ngay lập tức
    std::lock_guard<std::mutex> lock(signalMutex);
    if (serial.is_open()) {
        serial.cancel(); // Ngừng tất cả các thao tác I/O đang chờ
    }
    io.stop(); // Dừng tất cả các sự kiện đang chờ trong io_service

    if (readingThread.joinable()) {
        readingThread.join();
    }
}

void S32K144Interface::sendTime(uint8_t minutes, uint8_t seconds) {
    try {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << static_cast<int>(minutes) << " "
           << std::setw(2) << std::setfill('0') << static_cast<int>(seconds);
        std::string time_str = ss.str();

        boost::asio::write(serial, boost::asio::buffer(time_str));
        //std::cout << "Sent: " << time_str << std::endl;
    } catch (boost::system::system_error& e) {
        std::cerr << "Error sending data: " << e.what() << std::endl;
    }
}

void S32K144Interface::readSignal() {
    if (!connected) {
        std::cerr << "Serial port is not connected. Skipping signal reading.\n";
        return;
    }
    try {
        while (running) {
            char buffer[1];
            boost::system::error_code error;
            std::lock_guard<std::mutex> lock(signalMutex);

            // Thiết lập timeout
            timer.expires_from_now(boost::posix_time::milliseconds(500));
            timer.async_wait([this](const boost::system::error_code& ec) {
                if (!ec && running) {
                    serial.cancel(); // Hủy thao tác I/O nếu timeout
                }
            });

            // Đọc dữ liệu không đồng bộ
            serial.async_read_some(boost::asio::buffer(buffer, 1),
                [&](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                    if (!running) {
                        return; // Ngừng xử lý nếu đã dừng
                    }

                    if (ec) {
                        if (ec == boost::asio::error::operation_aborted) {
                            // Không in thêm "Operation aborted"
                            return;
                        }
                        if (ec != boost::asio::error::eof) {
                            std::cerr << "Error during read: " << ec.message() << "\n";
                            return;
                        }
                    }

                    // Hủy timer nếu đọc thành công
                    timer.cancel();

                    if (bytes_transferred > 0) {
                        uint8_t received_byte = static_cast<uint8_t>(buffer[0]);
                        if ((received_byte & 0xE0) == 0xE0) {
                            int button_id = received_byte & 0x1F;
                            switch (button_id) {
                                case 1:
                                    player->resume();
                                    sendTime(99, 99);
                                    break;
                                case 2:
                                    player->skipToNext();
                                    break;
                                case 3:
                                    player->stop();
                                    sendTime(00, 00);
                                    break;
                                case 4:
                                    player->skipToPrevious();
                                    break;
                                case 5:
                                    player->pause();
                                    sendTime(99, 99);
                                    break;
                                default:
                                    std::cout << "Unknown Button ID: " << button_id << std::endl;
                                    break;
                            }
                        } else if ((received_byte & 0x80) == 0) {
                            uint8_t adc_value = received_byte & 0x7F;
                            player->adjustVolume(adc_value);
                            //std::cout << "Volume adjusted to: " << static_cast<int>(adc_value) << std::endl;
                        } else {
                            //std::cout << "Invalid Signal Received: " << static_cast<int>(received_byte) << std::endl;
                        }
                    }
                });

            // Chờ các sự kiện I/O hoàn thành
            io.run_one();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        // Khi kết thúc vòng lặp, dừng io_service
        io.reset();
    } catch (boost::system::system_error& e) {
        std::cerr << "Error reading signal: " << e.what() << std::endl;
    }
}
