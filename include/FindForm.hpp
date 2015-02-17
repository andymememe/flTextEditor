#ifndef FINDFORM
#define FINDFORM

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>

class FindForm
{
	public :
		FindForm () ;

		/* Form Function */
		void callbackFunctionSetting (void *v) ;
		void showForm (char *find) ;
		void hideForm () ;

		/* Text Function */
		const char* getFind () ;
				
	private :
		/* FLTK Widget */
		Fl_Window *_findForm ;
		Fl_Input *_findInp ;
		Fl_Return_Button *_findNextBtn ;
		Fl_Button *_cancelBtn ;
} ;

#endif
