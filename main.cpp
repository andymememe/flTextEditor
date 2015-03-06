#include <iostream>
#include <include/MainForm.hpp>
#include "src/callback.cpp"

int main (int argc, char **argv)
{
	MainForm *mainWin = new MainForm (600, 500) ;
	mainWin->formCallbackSetting () ;
	mainWin->editorCallbackSetting () ;
	mainWin->showForm (argc, argv) ;

	return mainWin->runForm () ;
}
