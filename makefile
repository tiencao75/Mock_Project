# # Compiler và cờ biên dịch
# CC = g++
# CFLAGS = -Wall -g -I./header -I./header/model -I./header/controller -I./header/view

# # Thư mục chứa tệp nguồn, tệp đối tượng và tệp thực thi
# SRC_DIR = ./source
# OUT_DIR = ./out
# OBJ_DIR = $(OUT_DIR)/obj
# BIN_DIR = $(OUT_DIR)/bin

# # Các thư mục con trong source
# MODEL_DIR = $(SRC_DIR)/model
# CONTROLLER_DIR = $(SRC_DIR)/controller
# VIEW_DIR = $(SRC_DIR)/view
# MAIN_SOURCE = $(SRC_DIR)/main.cpp

# # Tìm tất cả các tệp nguồn .cpp trong các thư mục con
# MODEL_SOURCES = $(wildcard $(MODEL_DIR)/*.cpp)
# CONTROLLER_SOURCES = $(wildcard $(CONTROLLER_DIR)/*.cpp)
# VIEW_SOURCES = $(wildcard $(VIEW_DIR)/*.cpp)

# # Tổng hợp các nguồn
# SOURCES = $(MODEL_SOURCES) $(CONTROLLER_SOURCES) $(VIEW_SOURCES) $(MAIN_SOURCE)

# # Tạo danh sách tệp đối tượng từ danh sách tệp nguồn
# OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# # Tên tệp thực thi
# TARGET = $(BIN_DIR)/main.exe

# # Quy tắc mặc định
# all: dirs $(TARGET)

# # Quy tắc tạo thư mục nếu chưa tồn tại
# dirs:
# 	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# # Quy tắc tạo tệp thực thi
# $(TARGET): $(OBJECTS)
# 	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# # Quy tắc tạo tệp đối tượng từ tệp nguồn .cpp
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) -c -o $@ $<

# # Quy tắc dọn dẹp
# clean:
# 	rm -rf $(OUT_DIR)

# Compiler và cờ biên dịch
CC = g++
CFLAGS = -Wall -g -I/usr/local/include/taglib -I./header -I./header/include -I./header/model -I./header/controller -I./header/view

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
SOURCES = $(MODEL_SOURCES) $(CONTROLLER_SOURCES) $(VIEW_SOURCES) $(INCLUDE_SOURCES) $(MAIN_SOURCE)

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
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib -ltag

# Quy tắc tạo tệp đối tượng từ tệp nguồn .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Quy tắc dọn dẹp
clean:
	rm -rf $(OUT_DIR)

