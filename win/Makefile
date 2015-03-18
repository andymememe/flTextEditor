all : flTextEditor.exe

CC = $(shell /usr/x86_64-w64-mingw32/bin/fltk-config --cc)
CXX = $(shell /usr/x86_64-w64-mingw32/bin/fltk-config --cxx)

CFLAGS = $(shell /usr/x86_64-w64-mingw32/bin/fltk-config --cflags) -Wall -O3 -I.. 
CXXFLAGS = $(shell /usr/x86_64-w64-mingw32/bin/fltk-config --cxxflags) -Wall -O3 -I..

LINKFLTK = $(shell /usr/x86_64-w64-mingw32/bin/fltk-config --ldstaticflags) --std=c++11

flTextEditor.exe : main.o FindForm.o ReplForm.o MainForm.o
	$(CXX) -o $@ $^ $(LINKFLTK) 

main.o : ../main.cpp
	$(CXX) -c -o $@ $^ -I..

FindForm.o : ../src/FindForm.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^

ReplForm.o : ../src/ReplForm.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^

MainForm.o : ../src/MainForm.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $^

clean :
	rm *.o

clean-all :
	rm *.o
	rm flTextEditor.exe

uninstall :
	rm flTextEditor.exe
