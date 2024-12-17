# Derleyici ve bayraklar
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm

# Dizinler
SRC_DIR = C:/Ceng209_Homework_Fall_2024/src
BUILD_DIR = C:/Ceng209_Homework_Fall_2024/build
TARGET_DIR = C:/Ceng209_Homework_Fall_2024
TARGET = $(TARGET_DIR)/program.exe

# Kaynak ve obje dosyaları
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Ana hedef
all: $(TARGET)

# Program oluştur
$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# .o dosyalarını oluştur
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $< into $@..."
	$(CC) $(CFLAGS) -c $< -o $@

# build klasörünü oluştur
$(BUILD_DIR):
	@echo "Creating build directory..."
	mkdir $(BUILD_DIR)

# Temizlik (Windows uyumlu)
clean:
	@echo "Cleaning up..."
	del /s /q $(BUILD_DIR)\*.o $(TARGET) 2>nul || echo "No files to clean."

# Programı çalıştır
run: $(TARGET)
	@echo "Running program..."
	$(TARGET)
