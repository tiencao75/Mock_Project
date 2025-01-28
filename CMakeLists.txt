# # Yêu cầu phiên bản CMake
# cmake_minimum_required(VERSION 3.10)

# # Đặt tên project
# project(MyApplication)

# # Đặt cờ biên dịch và phiên bản C++
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Cờ biên dịch cho việc thu thập coverage
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fprofile-arcs -ftest-coverage")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# # Các thư mục cần thêm vào đường dẫn tìm kiếm header
# include_directories(
#     /usr/local/include/taglib
#     /usr/local/include
#     ${CMAKE_SOURCE_DIR}/header
#     ${CMAKE_SOURCE_DIR}/header/include
#     ${CMAKE_SOURCE_DIR}/header/model
#     ${CMAKE_SOURCE_DIR}/header/controller
#     ${CMAKE_SOURCE_DIR}/header/view
# )

# # Các thư viện cần liên kết
# link_directories(/usr/local/lib /usr/lib/x86_64-linux-gnu)
# set(LIBRARIES
#     avformat avcodec avutil swresample swscale
#     tag SDL2 SDL2_mixer SDL2_ttf SDL2_image stdc++fs z m pthread
# )

# # Các thư mục chứa tệp nguồn
# set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)
# set(MODEL_DIR ${SRC_DIR}/model)
# set(CONTROLLER_DIR ${SRC_DIR}/controller)
# set(VIEW_DIR ${SRC_DIR}/view)
# set(INCLUDE_DIR ${SRC_DIR}/include)

# # Tìm tất cả các tệp nguồn
# file(GLOB MODEL_SOURCES ${MODEL_DIR}/*.cpp)
# file(GLOB CONTROLLER_SOURCES ${CONTROLLER_DIR}/*.cpp)
# file(GLOB VIEW_SOURCES ${VIEW_DIR}/*.cpp)
# file(GLOB INCLUDE_SOURCES ${INCLUDE_DIR}/*.cpp)
# set(MAIN_SOURCE ${SRC_DIR}/main.cpp)

# # Tổng hợp tất cả các tệp nguồn
# set(SOURCES ${MODEL_SOURCES} ${CONTROLLER_SOURCES} ${VIEW_SOURCES} ${INCLUDE_SOURCES} ${MAIN_SOURCE})

# # Thư mục chứa các tệp đối tượng
# set(OBJ_DIR ${CMAKE_BINARY_DIR}/obj)

# # Tạo thư mục chứa tệp đối tượng nếu chưa tồn tại
# file(MAKE_DIRECTORY ${OBJ_DIR})

# # Tạo tệp đối tượng từ các tệp nguồn
# add_executable(main ${SOURCES})
# target_link_libraries(main ${LIBRARIES})

# # Cấu hình bài kiểm thử (test)
# enable_testing()

# # Tìm Google Test
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# # Tìm các bài kiểm thử trong thư mục test
# file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)
# add_executable(unit_tests ${TEST_SOURCES})

# # Liên kết các thư viện cần thiết cho bài kiểm thử
# target_link_libraries(unit_tests ${GTEST_LIBRARIES} pthread ${LIBRARIES})

# # Thêm quy tắc để chạy test
# add_test(NAME UnitTests COMMAND unit_tests)

# # Quy tắc dọn dẹp
# add_custom_target(clean_all
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}  # Xóa thư mục build
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/coverage_report  # Xóa thư mục báo cáo coverage
#     COMMENT "Dọn dẹp thư mục build và coverage_report"
# )
# # Quy tắc sinh báo cáo coverage
# add_custom_target(coverage
#     COMMAND gcovr -r . --html --html-details -o ${CMAKE_SOURCE_DIR}/coverage_report/index.html
#     COMMENT "Tạo báo cáo coverage"
# )

# # Quy tắc mặc định
# add_custom_target(build_all
#     DEPENDS unit_tests main
# )

# cmake_minimum_required(VERSION 3.10)

# project(MockProject)

# # Đặt cờ biên dịch
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "-Wall -g")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# # Thêm thư mục chứa tệp header
# include_directories(
#     /usr/local/include/taglib
#     /usr/local/include
#     ${CMAKE_SOURCE_DIR}/header
#     ${CMAKE_SOURCE_DIR}/header/include
#     ${CMAKE_SOURCE_DIR}/header/model
#     ${CMAKE_SOURCE_DIR}/header/controller
#     ${CMAKE_SOURCE_DIR}/header/view
# )

# # Các thư viện cần liên kết
# link_directories(/usr/local/lib /usr/lib/x86_64-linux-gnu)
# set(LIBRARIES
#     avformat avcodec avutil swresample swscale
#     tag SDL2 SDL2_mixer SDL2_ttf SDL2_image stdc++fs z m pthread
# )

# # Thư mục chứa các tệp nguồn
# set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)
# set(MODEL_DIR ${SRC_DIR}/model)
# set(CONTROLLER_DIR ${SRC_DIR}/controller)
# set(VIEW_DIR ${SRC_DIR}/view)
# set(INCLUDE_DIR ${SRC_DIR}/include)

# # Tìm tất cả các tệp nguồn .cpp
# file(GLOB MODEL_SOURCES ${MODEL_DIR}/*.cpp)
# file(GLOB CONTROLLER_SOURCES ${CONTROLLER_DIR}/*.cpp)
# file(GLOB VIEW_SOURCES ${VIEW_DIR}/*.cpp)
# file(GLOB INCLUDE_SOURCES ${INCLUDE_DIR}/*.cpp)
# set(MAIN_SOURCE ${SRC_DIR}/main.cpp)

# # Tổng hợp tất cả các tệp nguồn
# set(SOURCES ${MODEL_SOURCES} ${CONTROLLER_SOURCES} ${VIEW_SOURCES} ${INCLUDE_SOURCES} ${MAIN_SOURCE})

# # Tạo executable từ tất cả các tệp nguồn
# add_executable(unit_tests ${SOURCES})

# # Thêm thư mục chứa các bài kiểm tra
# file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)

# # Thêm tệp kiểm tra vào mục tiêu
# add_executable(unit_tests ${SOURCES} ${TEST_SOURCES})

# # Liên kết các thư viện
# target_link_libraries(unit_tests ${GTEST_LIBRARIES} pthread ${LIBRARIES})

# # Quy tắc dọn dẹp
# add_custom_target(clean-all
#     COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_clean.cmake
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
# )

# # Thêm các quy tắc kiểm thử
# enable_testing()
# add_test(NAME UnitTests COMMAND unit_tests)


# cmake_minimum_required(VERSION 3.10)

# project(MockProjectTests)

# set(CMAKE_CXX_STANDARD 17)

# # Tìm Google Test
# find_package(GTest REQUIRED)

# # Bao gồm các thư mục header
# include_directories(header/include header/model header/controller ${GTEST_INCLUDE_DIRS} /usr/local/include)

# # Liên kết thư viện TagLib và FFmpeg
# link_directories(/usr/local/lib)

# # Tạo executable cho test Metadata
# add_executable(test_Metadata 
#     test/test_Metadata.cpp 
#     source/model/Metadata.cpp
# )
# target_link_libraries(test_Metadata 
#     PRIVATE gtest gtest_main pthread tag avformat avcodec avutil
# )

# # Tạo executable cho test MediaFile
# add_executable(test_MediaFile 
#     test/test_MediaFile.cpp 
#     source/model/MediaFile.cpp 
#     source/model/Metadata.cpp
# )
# target_link_libraries(test_MediaFile 
#     PRIVATE gtest gtest_main pthread tag avformat avcodec avutil swresample swscale
# )

# # Tạo executable cho test MediaLibrary
# add_executable(test_MediaLibrary 
#     test/test_MediaLibrary.cpp 
#     source/model/MediaLibrary.cpp 
#     source/model/MediaFile.cpp 
#     source/model/Metadata.cpp 
#     source/controller/ExceptionLib.cpp
# )
# target_link_libraries(test_MediaLibrary 
#     PRIVATE gtest gtest_main pthread tag avformat avcodec avutil swresample swscale
# )

# # Bật tính năng testing và đăng ký các test với ctest
# enable_testing()
# add_test(NAME MetadataTest COMMAND test_Metadata)
# add_test(NAME MediaFileTest COMMAND test_MediaFile)
# add_test(NAME MediaLibraryTest COMMAND test_MediaLibrary)


# # Yêu cầu phiên bản CMake
# cmake_minimum_required(VERSION 3.10)

# # Đặt tên project
# project(MyApplication)

# # Đặt cờ biên dịch và phiên bản C++
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Cờ biên dịch cho việc thu thập coverage
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fprofile-arcs -ftest-coverage")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# # Các thư mục cần thêm vào đường dẫn tìm kiếm header
# include_directories(
#     /usr/local/include/taglib
#     /usr/local/include
#     ${CMAKE_SOURCE_DIR}/header
#     ${CMAKE_SOURCE_DIR}/header/include
#     ${CMAKE_SOURCE_DIR}/header/model
#     ${CMAKE_SOURCE_DIR}/header/controller
#     ${CMAKE_SOURCE_DIR}/header/view
# )

# # Các thư viện cần liên kết
# link_directories(/usr/local/lib /usr/lib/x86_64-linux-gnu)
# set(LIBRARIES
#     avformat avcodec avutil swresample swscale
#     tag SDL2 SDL2_mixer SDL2_ttf SDL2_image stdc++fs z m pthread
# )

# # Các thư mục chứa tệp nguồn
# set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)
# set(MODEL_DIR ${SRC_DIR}/model)
# set(CONTROLLER_DIR ${SRC_DIR}/controller)
# set(VIEW_DIR ${SRC_DIR}/view)
# set(INCLUDE_DIR ${SRC_DIR}/include)

# # Tìm tất cả các tệp nguồn
# file(GLOB MODEL_SOURCES ${MODEL_DIR}/*.cpp)
# file(GLOB CONTROLLER_SOURCES ${CONTROLLER_DIR}/*.cpp)
# file(GLOB VIEW_SOURCES ${VIEW_DIR}/*.cpp)
# file(GLOB INCLUDE_SOURCES ${INCLUDE_DIR}/*.cpp)
# set(MAIN_SOURCE ${SRC_DIR}/main.cpp)

# # Tổng hợp tất cả các tệp nguồn
# set(SOURCES ${MODEL_SOURCES} ${CONTROLLER_SOURCES} ${VIEW_SOURCES} ${INCLUDE_SOURCES} ${MAIN_SOURCE})

# # Thư mục chứa các tệp đối tượng
# set(OBJ_DIR ${CMAKE_BINARY_DIR}/obj)

# # Tạo thư mục chứa tệp đối tượng nếu chưa tồn tại
# file(MAKE_DIRECTORY ${OBJ_DIR})

# # Tạo tệp đối tượng từ các tệp nguồn
# add_executable(main ${SOURCES})
# target_link_libraries(main ${LIBRARIES})

# # Cấu hình bài kiểm thử (test)
# enable_testing()

# # Tìm Google Test
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# # Tìm các bài kiểm thử trong thư mục test
# file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)
# add_executable(unit_tests ${TEST_SOURCES})

# # Liên kết các thư viện cần thiết cho bài kiểm thử
# target_link_libraries(unit_tests ${GTEST_LIBRARIES} GTest::Main pthread ${LIBRARIES})

# # Thêm quy tắc để chạy test
# add_test(NAME UnitTests COMMAND unit_tests)

# # Quy tắc dọn dẹp
# add_custom_target(clean_all
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}  # Xóa thư mục build
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/coverage_report  # Xóa thư mục báo cáo coverage
#     COMMENT "Dọn dẹp thư mục build và coverage_report"
# )
# # Tạo thư mục coverage_report nếu chưa tồn tại
# file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/coverage_report)
# # Quy tắc sinh báo cáo coverage
# add_custom_target(coverage
#     COMMAND gcovr -r . source/controller --html --html-details -o coverage_report/index.html
#     COMMENT "Tạo báo cáo coverage"
# )

# # Quy tắc mặc định
# add_custom_target(build_all
#     DEPENDS unit_tests main
# )



# # Yêu cầu phiên bản CMake
# cmake_minimum_required(VERSION 3.10)

# # Đặt tên project
# project(MyApplication)

# # Đặt cờ biên dịch và phiên bản C++
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Cờ biên dịch cho việc thu thập coverage
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fprofile-arcs -ftest-coverage")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# # Các thư mục cần thêm vào đường dẫn tìm kiếm header
# include_directories(
#     /usr/local/include/taglib
#     /usr/local/include
#     ${CMAKE_SOURCE_DIR}/header
#     ${CMAKE_SOURCE_DIR}/header/include
#     ${CMAKE_SOURCE_DIR}/header/model
#     ${CMAKE_SOURCE_DIR}/header/controller
#     ${CMAKE_SOURCE_DIR}/header/view
# )

# # Các thư viện cần liên kết
# link_directories(/usr/local/lib /usr/lib/x86_64-linux-gnu)
# set(LIBRARIES
#     avformat avcodec avutil swresample swscale
#     tag SDL2 SDL2_mixer SDL2_ttf SDL2_image stdc++fs z m pthread
# )

# # Các thư mục chứa tệp nguồn
# set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)
# set(MODEL_DIR ${SRC_DIR}/model)
# set(CONTROLLER_DIR ${SRC_DIR}/controller)
# set(VIEW_DIR ${SRC_DIR}/view)
# set(INCLUDE_DIR ${SRC_DIR}/include)

# # Tìm tất cả các tệp nguồn
# file(GLOB MODEL_SOURCES ${MODEL_DIR}/*.cpp)
# file(GLOB CONTROLLER_SOURCES ${CONTROLLER_DIR}/*.cpp)
# file(GLOB VIEW_SOURCES ${VIEW_DIR}/*.cpp)
# file(GLOB INCLUDE_SOURCES ${INCLUDE_DIR}/*.cpp)
# set(MAIN_SOURCE ${SRC_DIR}/main.cpp)

# # Tổng hợp tất cả các tệp nguồn
# set(SOURCES ${MODEL_SOURCES} ${CONTROLLER_SOURCES} ${VIEW_SOURCES} ${INCLUDE_SOURCES} ${MAIN_SOURCE})

# # Thư mục chứa các tệp đối tượng
# set(OBJ_DIR ${CMAKE_BINARY_DIR}/obj)

# # Tạo thư mục chứa tệp đối tượng nếu chưa tồn tại
# file(MAKE_DIRECTORY ${OBJ_DIR})

# # Tạo tệp đối tượng từ các tệp nguồn
# add_executable(main ${SOURCES})
# target_link_libraries(main ${LIBRARIES})

# # Cấu hình bài kiểm thử (test)
# enable_testing()

# # Tìm Google Test
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# # Tìm các bài kiểm thử trong thư mục test
# file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)

# # Đảm bảo các tệp trong source/controller được biên dịch với cờ coverage
# add_library(controller_lib ${CONTROLLER_SOURCES})
# target_compile_options(controller_lib PRIVATE -fprofile-arcs -ftest-coverage)
# target_link_libraries(controller_lib gcov)

# # Tạo executable cho test
# add_executable(unit_tests ${TEST_SOURCES})
# target_link_libraries(unit_tests ${GTEST_LIBRARIES} GTest::Main pthread ${LIBRARIES} controller_lib)

# # Thêm quy tắc để chạy test
# add_test(NAME UnitTests COMMAND unit_tests)

# # Quy tắc dọn dẹp
# add_custom_target(clean_all
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}  # Xóa thư mục build
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/coverage_report  # Xóa thư mục báo cáo coverage
#     COMMENT "Dọn dẹp thư mục build và coverage_report"
# )

# # Tạo thư mục coverage_report nếu chưa tồn tại
# file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/coverage_report)

# # Quy tắc sinh báo cáo coverage
# add_custom_target(coverage
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/coverage_report
#     COMMAND gcovr -r ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/source/controller --html --html-details -o ${CMAKE_SOURCE_DIR}/coverage_report/index.html
#     COMMENT "Tạo báo cáo coverage cho source/controller"
# )

# # Quy tắc mặc định
# add_custom_target(build_all
#     DEPENDS unit_tests main
# )







# # Yêu cầu phiên bản CMake
# cmake_minimum_required(VERSION 3.10)

# # Đặt tên project
# project(MyApplication)

# # Đặt cờ biên dịch và phiên bản C++
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Cờ biên dịch cho việc thu thập coverage
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fprofile-arcs -ftest-coverage")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# # Các thư mục cần thêm vào đường dẫn tìm kiếm header
# include_directories(
#     /usr/local/include/taglib
#     /usr/local/include
#     ${CMAKE_SOURCE_DIR}/header
#     ${CMAKE_SOURCE_DIR}/header/include
#     ${CMAKE_SOURCE_DIR}/header/model
#     ${CMAKE_SOURCE_DIR}/header/controller
#     ${CMAKE_SOURCE_DIR}/header/view
# )

# # Các thư viện cần liên kết
# link_directories(/usr/local/lib /usr/lib/x86_64-linux-gnu)
# set(LIBRARIES
#     avformat avcodec avutil swresample swscale
#     tag SDL2 SDL2_mixer SDL2_ttf SDL2_image stdc++fs z m pthread
# )

# # Các thư mục chứa tệp nguồn
# set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)
# set(MODEL_DIR ${SRC_DIR}/model)
# set(CONTROLLER_DIR ${SRC_DIR}/controller)
# set(VIEW_DIR ${SRC_DIR}/view)
# set(INCLUDE_DIR ${SRC_DIR}/include)

# # Tìm tất cả các tệp nguồn
# file(GLOB MODEL_SOURCES ${MODEL_DIR}/*.cpp)
# file(GLOB CONTROLLER_SOURCES ${CONTROLLER_DIR}/*.cpp)
# file(GLOB VIEW_SOURCES ${VIEW_DIR}/*.cpp)
# file(GLOB INCLUDE_SOURCES ${INCLUDE_DIR}/*.cpp)
# set(MAIN_SOURCE ${SRC_DIR}/main.cpp)

# # Tổng hợp tất cả các tệp nguồn
# set(SOURCES ${MODEL_SOURCES} ${CONTROLLER_SOURCES} ${VIEW_SOURCES} ${INCLUDE_SOURCES} ${MAIN_SOURCE})

# # Thư mục chứa các tệp đối tượng
# set(OBJ_DIR ${CMAKE_BINARY_DIR}/obj)

# # Tạo thư mục chứa tệp đối tượng nếu chưa tồn tại
# file(MAKE_DIRECTORY ${OBJ_DIR})

# # Tạo tệp đối tượng từ các tệp nguồn
# add_executable(main ${SOURCES})
# target_link_libraries(main ${LIBRARIES})

# # Cấu hình bài kiểm thử (test)
# enable_testing()

# # Tìm Google Test
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# # Tìm các bài kiểm thử trong thư mục test
# file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)

# # Đảm bảo các tệp trong source/controller được biên dịch với cờ coverage
# add_library(controller_lib ${CONTROLLER_SOURCES} ${MODEL_SOURCES} ${VIEW_SOURCES} ${INCLUDE_SOURCES})
# target_compile_options(controller_lib PRIVATE -fprofile-arcs -ftest-coverage)
# target_link_libraries(controller_lib gcov)

# # Tạo executable cho test
# add_executable(unit_tests ${TEST_SOURCES})
# target_link_libraries(unit_tests ${GTEST_LIBRARIES} GTest::Main pthread ${LIBRARIES} controller_lib)

# # Thêm quy tắc để chạy test
# add_test(NAME UnitTests COMMAND unit_tests)

# # Quy tắc dọn dẹp
# add_custom_target(clean_all
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}  # Xóa thư mục build
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/coverage_report  # Xóa thư mục báo cáo coverage
#     COMMENT "Dọn dẹp thư mục build và coverage_report"
# )

# # Tạo thư mục coverage_report nếu chưa tồn tại
# file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/coverage_report)

# # Quy tắc sinh báo cáo coverage
# add_custom_target(coverage
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/coverage_report
#     COMMAND gcovr -r ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/source/controller --html --html-details -o ${CMAKE_SOURCE_DIR}/coverage_report/index.html
#     COMMENT "Tạo báo cáo coverage cho source/controller"
# )

# # Quy tắc mặc định
# add_custom_target(build_all
#     DEPENDS unit_tests main
# )





# Yêu cầu phiên bản CMake
cmake_minimum_required(VERSION 3.10)

# Đặt tên project
project(MyApplication)

# Đặt cờ biên dịch và phiên bản C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Cờ biên dịch cho việc thu thập coverage
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Thêm đường dẫn tìm kiếm cho GTest & GMock
set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake")

# Các thư mục cần thêm vào đường dẫn tìm kiếm header
include_directories(
    /usr/local/include/taglib
    /usr/local/include
    ${CMAKE_SOURCE_DIR}/header
    ${CMAKE_SOURCE_DIR}/header/include
    ${CMAKE_SOURCE_DIR}/header/model
    ${CMAKE_SOURCE_DIR}/header/controller
    ${CMAKE_SOURCE_DIR}/header/view
)

# Các thư viện cần liên kết
link_directories(/usr/local/lib /usr/lib/x86_64-linux-gnu)
set(LIBRARIES
    avformat avcodec avutil swresample swscale
    tag SDL2 SDL2_mixer SDL2_ttf SDL2_image stdc++fs z m pthread
)

# Các thư mục chứa tệp nguồn
set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)
set(MODEL_DIR ${SRC_DIR}/model)
set(CONTROLLER_DIR ${SRC_DIR}/controller)
set(VIEW_DIR ${SRC_DIR}/view)
set(INCLUDE_DIR ${SRC_DIR}/include)

# Tìm tất cả các tệp nguồn
file(GLOB MODEL_SOURCES ${MODEL_DIR}/*.cpp)
file(GLOB CONTROLLER_SOURCES ${CONTROLLER_DIR}/*.cpp)
file(GLOB VIEW_SOURCES ${VIEW_DIR}/*.cpp)
file(GLOB INCLUDE_SOURCES ${INCLUDE_DIR}/*.cpp)
set(MAIN_SOURCE ${SRC_DIR}/main.cpp)

# Tổng hợp tất cả các tệp nguồn
set(SOURCES ${MODEL_SOURCES} ${CONTROLLER_SOURCES} ${VIEW_SOURCES} ${INCLUDE_SOURCES} ${MAIN_SOURCE})

# Thư mục chứa các tệp đối tượng
set(OBJ_DIR ${CMAKE_BINARY_DIR}/obj)

# Tạo thư mục chứa tệp đối tượng nếu chưa tồn tại
file(MAKE_DIRECTORY ${OBJ_DIR})

# Tạo tệp đối tượng từ các tệp nguồn
add_executable(main ${SOURCES})
target_link_libraries(main ${LIBRARIES})

# Cấu hình bài kiểm thử (test)
enable_testing()

# 🔍 Tìm Google Test và Google Mock
find_package(GTest REQUIRED)
find_library(GMOCK_LIB gmock HINTS /usr/local/lib)
find_library(GMOCK_MAIN_LIB gmock_main HINTS /usr/local/lib)

if(GMOCK_LIB AND GMOCK_MAIN_LIB)
    message(STATUS "Found GMock: ${GMOCK_LIB}, ${GMOCK_MAIN_LIB}")
    set(GMOCK_LIBRARIES ${GMOCK_LIB} ${GMOCK_MAIN_LIB})
else()
    message(FATAL_ERROR "GMock library not found!")
endif()

# Bao gồm thư mục của GTest & GMock
include_directories(${GTEST_INCLUDE_DIRS} /usr/local/include/gmock)

# Tìm các bài kiểm thử trong thư mục test
file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)

# Đảm bảo các tệp trong source/controller được biên dịch với cờ coverage
add_library(controller_lib ${CONTROLLER_SOURCES} ${MODEL_SOURCES} ${VIEW_SOURCES} ${INCLUDE_SOURCES})
target_compile_options(controller_lib PRIVATE -fprofile-arcs -ftest-coverage)
target_link_libraries(controller_lib gcov)

# Tạo executable cho test
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests 
    ${GTEST_BOTH_LIBRARIES} 
    ${GMOCK_LIBRARIES} 
    GTest::GTest 
    GTest::Main 
    pthread 
    ${LIBRARIES} 
    controller_lib
)

# Thêm quy tắc để chạy test
add_test(NAME UnitTests COMMAND unit_tests)

# Quy tắc dọn dẹp
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}  # Xóa thư mục build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/coverage_report  # Xóa thư mục báo cáo coverage
    COMMENT "Dọn dẹp thư mục build và coverage_report"
)

# Tạo thư mục coverage_report nếu chưa tồn tại
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/coverage_report)

# Quy tắc sinh báo cáo coverage
add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/coverage_report
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/source/controller --html --html-details -o ${CMAKE_SOURCE_DIR}/coverage_report/index.html
    COMMENT "Tạo báo cáo coverage cho source/controller"
)

# Quy tắc mặc định
add_custom_target(build_all
    DEPENDS unit_tests main
)

