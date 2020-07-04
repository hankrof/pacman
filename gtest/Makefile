CC            = gcc
CXX           = g++
CFLAGS        = -pipe -g -Wall -Wextra -D_REENTRANT -fPIC
CXXFLAGS      = -pipe -g -Wall -Wextra -D_REENTRANT -fPIC
CXXLIBS       = $(SUBLIBS) /usr/lib/libQt5Widgets.so /usr/lib/libQt5Gui.so /usr/lib/libQt5Core.so -lGL -lpthread -lgtest
INCPATH       = -I. -I../model/ -isystem /usr/include/qt -isystem /usr/include/qt/QtWidgets -isystem /usr/include/qt/QtGui -isystem /usr/include/qt/QtCore -I. -I/usr/lib/qt/mkspecs/linux-g++
CXXSRCS       = $(notdir $(wildcard *.cpp))
PREBUILT_OBJS = $(notdir $(wildcard *.o))
OBJS          = $(PREBUILT_OBJS) $(CXXSRCS:%.cpp=%.o)
PROGRAM       = main
.PHONY: clean
all:
	$(MAKE) -C ../
	rm -f $(PREBUILT_OBJS)
	cp ../*.o .
	rm -f main.o
	$(MAKE) $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $(PROGRAM) $(OBJS) $(CXXLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) -c -o $@ $<

clean:
	rm -f $(PROGRAM) *.o
