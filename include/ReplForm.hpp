#ifndef REPLFORM
#define REPLFORM

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>

/*******************/
/* Extern Function */
/*******************/
extern void replace_next_cb (Fl_Widget *w, void *v) ;
extern void replace_all_cb (Fl_Widget *w, void *v) ;
extern void repl_dialog_exit_cb (Fl_Widget *w, void *v) ;

class ReplForm
{
	public :
		ReplForm () ;

		/* Form Function */
		void callbackFunctionSetting (void *v) ;
		void showForm (char *find, char *repl) ;
		void hideForm () ;

		/* Text Function */
		const char* getFind () ;
		const char* getRepl () ;
		
	private :
		/* FLTK Widget */
		Fl_Window *_replForm ;
		Fl_Input *_findInp ;
		Fl_Input *_replInp ;
		Fl_Button *_replAllBtn ;
		Fl_Return_Button *_replNextBtn ;
		Fl_Button *_cancelBtn ;
} ;

#endif
