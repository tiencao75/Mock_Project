# Compiler và cờ biên dịch
CC = g++
CFLAGS = -Wall -g \
	-I/usr/local/include/taglib \
	-I/usr/local/include \
	-I./header \
	-I./header/include \
	-I./header/model \
	-I./header/controller \
	-I./header/view

# Các thư viện cần liên kết
LDFLAGS = -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu \
    -lavformat -lavcodec -lavutil -lswresample -lswscale \
    -ltag -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lstdc++fs -lz -lm -pthread









# Thư mục chứa tệp nguồn, tệp đối tượng và tệp thực thi
SRC_DIR = ./source
OUT_DIR = ./out
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin

# Các thư mục con trong source
MODEL_DIR = $(SRC_DIR)/model
CONTROLLER_DIR = $(SRC_DIR)/controller
VIEW_DIR = $(SRC_DIR)/view
INCLUDE_DIR = $(SRC_DIR)/include
MAIN_SOURCE = $(SRC_DIR)/main.cpp

# Tìm tất cả các tệp nguồn .cpp trong các thư mục con
MODEL_SOURCES = $(wildcard $(MODEL_DIR)/*.cpp)
CONTROLLER_SOURCES = $(wildcard $(CONTROLLER_DIR)/*.cpp)
VIEW_SOURCES = $(wildcard $(VIEW_DIR)/*.cpp)
INCLUDE_SOURCES = $(wildcard $(INCLUDE_DIR)/*.cpp)

# Tổng hợp các nguồn
SOURCES = $(MODEL_SOURCES) $(CONTROLLER_SOURCES) $(VIEW_SOURCES) $(MAIN_SOURCE) $(INCLUDE_SOURCES)

# Tạo danh sách tệp đối tượng từ danh sách tệp nguồn
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Tên tệp thực thi
TARGET = $(BIN_DIR)/main.exe

# Quy tắc mặc định
all: dirs $(TARGET)

# Quy tắc tạo thư mục nếu chưa tồn tại
dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Quy tắc tạo tệp thực thi
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)


# Quy tắc tạo tệp đối tượng từ tệp nguồn .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Quy tắc dọn dẹp
clean:
	rm -rf $(OUT_DIR)













# # Compiler và cờ biên dịch
# CC = g++
# CFLAGS = -Wall -g -I/usr/local/include/taglib -I./header -I./header/include -I./header/model -I./header/controller -I./header/view
# LDFLAGS = -lSDL2 -lSDL2_mixer -ltag -ltag_c -lz
# # Thư mục chứa tệp nguồn, tệp đối tượng và tệp thực thi
# SRC_DIR = ./source
# OUT_DIR = ./out
# OBJ_DIR = $(OUT_DIR)/obj
# BIN_DIR = $(OUT_DIR)/bin

# # Các thư mục con trong source
# MODEL_DIR = $(SRC_DIR)/model
# CONTROLLER_DIR = $(SRC_DIR)/controller
# VIEW_DIR = $(SRC_DIR)/view
# INCLUDE_DIR = $(SRC_DIR)/include
# MAIN_SOURCE = $(SRC_DIR)/main.cpp

# # Tìm tất cả các tệp nguồn .cpp trong các thư mục con
# MODEL_SOURCES = $(wildcard $(MODEL_DIR)/*.cpp)
# CONTROLLER_SOURCES = $(wildcard $(CONTROLLER_DIR)/*.cpp)
# VIEW_SOURCES = $(wildcard $(VIEW_DIR)/*.cpp)
# INCLUDE_SOURCES = $(wildcard $(INCLUDE_DIR)/*.cpp)

# # Tổng hợp các nguồn
# SOURCES = $(MODEL_SOURCES) $(CONTROLLER_SOURCES) $(VIEW_SOURCES) $(MAIN_SOURCE) $(INCLUDE_SOURCES)

# # Tạo danh sách tệp đối tượng từ danh sách tệp nguồn
# OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# # Thư viện
# LOCAL_LIB_DIRS = -L/usr/local/lib         # Đường dẫn thư viện tùy chỉnh (local)
# SYSTEM_LIB_DIRS = -L/usr/lib/x86_64-linux-gnu  # Đường dẫn thư viện hệ thống

# # Gộp lại các thư mục thư viện
# LIB_DIRS = $(LOCAL_LIB_DIRS) $(SYSTEM_LIB_DIRS)

# # Thư viện cần liên kết
# LIBS = -ltag -lz

# # Tên tệp thực thi
# TARGET = $(BIN_DIR)/main.exe

# # Quy tắc mặc định
# all: dirs $(TARGET)

# # Quy tắc tạo thư mục nếu chưa tồn tại
# dirs:
# 	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# # Quy tắc tạo tệp thực thi
# $(TARGET): $(OBJECTS)
# 	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIB_DIRS) $(LIBS) $(LDFLAGS)

# # Quy tắc tạo tệp đối tượng từ tệp nguồn .cpp
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) -c -o $@ $<

# # Quy tắc dọn dẹp
# clean:
# 	rm -rf $(OUT_DIR)

