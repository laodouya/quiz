LIBS = -lmagic
TARGET = filetype
SRCS = $(wildcard ./*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

$(TARGET) : $(OBJS)
	g++ -o $@ $^  $(LIBS)
$(OBJS) : $(SRCS)
	g++ -c $^ -o $@

.PHONY : clean
clean :
	-rm $(TARGET) $(OBJS)

