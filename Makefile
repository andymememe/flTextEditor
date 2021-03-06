all : flTextEditor.exe

CC = $(shell fltk-config --cc)
CXX = $(shell fltk-config --cxx)

CFLAGS = $(shell fltk-config --cflags) -Wall -O3 -I. 
CXXFLAGS = $(shell fltk-config --cxxflags) -Wall -O3 -I.

LINKFLTK = $(shell fltk-config --ldflags) --std=c++14

flTextEditor.exe : main.o FindForm.o ReplForm.o MainForm.o
	$(CXX) -o $@ $^ $(LINKFLTK) 

main.o : main.cpp
	$(CXX) -c -o $@ $^ -I.

FindForm.o : ./src/FindForm.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^

ReplForm.o : ./src/ReplForm.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^

MainForm.o : ./src/MainForm.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^

clean :
	rm *.o

clean-all :
	rm *.o
	rm flTextEditor.exe

uninstall :
	rm flTextEditor.exe
