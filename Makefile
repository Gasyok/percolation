# Компилятор
CXX = g++

# Опции компиляции
CXXFLAGS = -std=c++11 -Wall

# Имя исполняемого файла
TARGET = percolation

all: $(TARGET)

$(TARGET): percolation.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

