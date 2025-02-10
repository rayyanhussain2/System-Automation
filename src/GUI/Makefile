CXX = g++
CXXFLAGS = `pkg-config --cflags gtkmm-3.0` -Wall
LDFLAGS = `pkg-config --libs gtkmm-3.0` -lsqlite3

all: MyApp

MyApp: MyApp.cpp AppDB.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f MyApp