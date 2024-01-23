CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic

BUILD_DIR = build
TEMPLATE_DIR = .template
OUT_EXE = sputify.out

ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
endif

all: $(BUILD_DIR) $(OUT_EXE)

$(OUT_EXE): $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/strutils.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Demand.o $(BUILD_DIR)/MUSIC.o $(BUILD_DIR)/Person.o $(BUILD_DIR)/Artist.o $(BUILD_DIR)/Playlist.o $(BUILD_DIR)/User.o $(BUILD_DIR)/SearchEngine.o $(BUILD_DIR)/Sputify.o $(BUILD_DIR)/MainHandler.o 
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Artist.o: sputify/Artist.cpp sputify/Artist.h  sputify/Person.cpp sputify/Person.h sputify/Playlist.cpp sputify/Playlist.h sputify/MUSIC.cpp sputify/MUSIC.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/User.o: sputify/User.cpp sputify/User.h  sputify/Person.cpp sputify/Person.h sputify/Playlist.cpp sputify/Playlist.h sputify/MUSIC.cpp sputify/MUSIC.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Person.o: sputify/Person.cpp sputify/Person.h sputify/Playlist.cpp sputify/Playlist.h sputify/MUSIC.cpp sputify/MUSIC.h sputify/Constants.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Demand.o: sputify/Demand.cpp sputify/Demand.h sputify/Constants.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/MUSIC.o: sputify/MUSIC.cpp sputify/MUSIC.h sputify/Constants.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Playlist.o: sputify/Playlist.cpp sputify/Playlist.h sputify/MUSIC.cpp sputify/MUSIC.h sputify/Constants.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/SearchEngine.o: sputify/SearchEngine.cpp sputify/SearchEngine.h sputify/Person.cpp sputify/Person.h sputify/Playlist.cpp sputify/Playlist.h sputify/MUSIC.cpp sputify/MUSIC.h sputify/Constants.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Sputify.o: sputify/Sputify.cpp sputify/Sputify.h sputify/Demand.cpp sputify/Demand.h sputify/Artist.cpp sputify/Artist.h sputify/User.cpp sputify/User.h sputify/SearchEngine.cpp sputify/SearchEngine.h sputify/Playlist.cpp sputify/Playlist.h sputify/MUSIC.cpp sputify/MUSIC.h sputify/Constants.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp utils/strutils.hpp utils/strutils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/strutils.o: utils/strutils.cpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/strutils.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/handlers.o: examples/handlers.cpp server/server.hpp sputify/Sputify.cpp sputify/Sputify.h utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/MainHandler.o: examples/MainHandler.cpp examples/MainHandler.h server/server.cpp server/server.hpp examples/handlers.cpp examples/handlers.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: examples/main.cpp sputify/Sputify.cpp sputify/Sputify.h server/server.hpp examples/MainHandler.h examples/MainHandler.cpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
