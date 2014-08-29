
LIBS = -L$(LIBRARY_PATH) -lgcexsocket -lxthread -lappframe
INCLUDES = -I$(CPLUS_INCLUDE_PATH)

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
TARGET = server
CXXFLAGS = -g -Wall -fPIC 

all: $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LIBS) $(CXXFLAGS)

$(OBJ): %.o : %.cpp
	$(CXX) -o $@ -c $< $(INCLUDES) $(CXXFLAGS)

.PHONY : clean
clean:
	$(RM) $(OBJ) $(TARGET)
