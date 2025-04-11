CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = pastry_sim

SRCS = main.cpp \
       State.cpp \
       MakePastryEvent.cpp \
       BakePastryEvent.cpp \
       SellPastryEvent.cpp \
       Simulator.cpp

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)
