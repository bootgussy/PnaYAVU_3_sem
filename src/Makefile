CXX = g++
CXXFLAGS = -Iheader -Wall -std=c++17
LDFLAGS = -lsqlite3
SOURCES = cpp/main.cpp cpp/Account.cpp cpp/Database.cpp cpp/Menu.cpp cpp/MenuOption.cpp cpp/Order.cpp cpp/Buyer.cpp cpp/Manager.cpp cpp/Admin.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)