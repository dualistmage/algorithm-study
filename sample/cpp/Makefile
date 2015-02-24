CXX = g++

######################################################
# if $(COMPILE_FLAGS) is given by upper makefile 
# else if no $(COMPILE_FLAGS) is given 
ifneq ($(COMPILE_FLAGS),)
CXXFLAGS += $(COMPILE_FLAGS) 
else
#CXXFLAGS = -Wall -O3
CXXFLAGS = -Wall -g -DTEST=10000
endif


TARGET = test

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

INCLUDE_PATH = 

LIB_FLAGS = $(LIB_PATH) $(LIB)

LIB_PATH = 

LIB = 

%.o : %.cpp
	$(CXX) $(INCLUDE_PATH) $(CXXFLAGS) -c -o $@ $^ 

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) -o $@ $^ $(LIB_FLAGS)
	echo $(CURDIR)

clean:
	rm -rf *.o $(TARGET) 

