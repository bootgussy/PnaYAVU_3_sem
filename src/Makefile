CXX = g++
CXXFLAGS = -Iheader -Wall -std=c++17
LDFLAGS = -lsqlite3
SOURCES = cpp/main.cpp cpp/Account.cpp cpp/Database.cpp cpp/LoyaltySystem.cpp cpp/Menu.cpp cpp/MenuOption.cpp cpp/Order.cpp cpp/Buyer.cpp cpp/Manager.cpp cpp/Admin.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = my_program

main.o: main.cpp Database.h Menu.h MenuOption.h Order.h Account.h LoyaltySystem.h Buyer.h Manager.h Admin.h
Account.o: Account.cpp Account.h
Database.o: Database.cpp Database.h
LoyaltySystem.o: LoyaltySystem.cpp LoyaltySystem.h
Menu.o: Menu.cpp Menu.h MenuOption.h
MenuOption.o: MenuOption.cpp MenuOption.h
Order.o: Order.cpp Order.h
Buyer.o: Buyer.cpp Buyer.h
Manager.o: Manager.cpp Manager.h
Admin.o: Admin.cpp Admin.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)