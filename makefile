# Compiler và cờ biên dịch
CC = g++
CFLAGS = -Wall -g -I./header

# Thư mục chứa tệp nguồn, tệp đối tượng và tệp thực thi
SRC_DIR = ./source
OUT_DIR = ./out
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin

# Các thư mục con trong source
MODEL_DIR = $(SRC_DIR)/model
CONTROLLER_DIR = $(SRC_DIR)/controller
VIEW_DIR = $(SRC_DIR)/view

# Tìm tất cả các tệp nguồn .cpp trong các thư mục con
MODEL_SOURCES = $(wildcard $(MODEL_DIR)/*.cpp)
CONTROLLER_SOURCES = $(wildcard $(CONTROLLER_DIR)/*.cpp)
VIEW_SOURCES = $(wildcard $(VIEW_DIR)/*.cpp)

# Tổng hợp các nguồn
SOURCES = $(MODEL_SOURCES) $(CONTROLLER_SOURCES) $(VIEW_SOURCES)

# Tạo danh sách tệp đối tượng từ danh sách tệp nguồn
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Tên tệp thực thi
TARGET = $(BIN_DIR)/main

# Quy tắc mặc định
all: $(BIN_DIR) $(OBJ_DIR) $(TARGET)

# Tạo thư mục out/ nếu chưa tồn tại
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Tạo thư mục obj/ nếu chưa tồn tại
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Tạo thư mục bin/ nếu chưa tồn tại
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Quy tắc tạo tệp thực thi
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# Quy tắc tạo tệp đối tượng từ tệp nguồn .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Quy tắc dọn dẹp
clean:
	rm -rf $(OUT_DIR)
