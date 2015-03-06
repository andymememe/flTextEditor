#ifndef MAIN_FORM
#define MAIN_FORM

#include <include/FindForm.hpp>
#include <include/ReplForm.hpp>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_File_Chooser.H>

/*******************/
/* Extern Function */
/*******************/
extern void text_modify_cb (int pos, int nInserted, int nDeleted, int nRestyled, const char* deletedText, void* cbArg) ;
extern void new_cb (Fl_Widget *w, void *v) ;
extern void open_cb (Fl_Widget *w, void *v) ;
extern void save_cb (Fl_Widget *w, void *v) ;
extern void save_as_cb (Fl_Widget *w, void *v) ;
extern void exit_cb (Fl_Widget *w, void *v) ;
extern void select_all_cb (Fl_Widget *w, void *v) ;
extern void copy_cb (Fl_Widget *w, void *v) ;
extern void cut_cb (Fl_Widget *w, void *v) ;
extern void paste_cb (Fl_Widget *w, void *v) ;
extern void find_cb (Fl_Widget *w, void *v) ;
extern void find_next_cb (Fl_Widget *w, void *v) ;
extern void replace_cb (Fl_Widget *w, void *v) ;
extern void replace_next_cb (Fl_Widget *w, void *v) ;

class MainForm
{
	public :
		MainForm (int w, int h) ;

		/* Form Function */
		void formCallbackSetting () ;
		void showForm (int argc, char **argv) ;
		int runForm () ;
		void changeTitle () ;

		/* Editor Function */
		void doEdit (int id) ;
		void editorCallbackSetting () ;
		void showInsertPosition () ;
		void showFind () ;
		void findNext () ;
		void showRepl () ;
		void replNext () ;
		void replAll () ;

		/* File Function */
		bool checkSave () ;
		void newFile () ;
		void openFile () ;
		void saveFile (bool asNew = true) ;

		/* Variable Function */
		bool getChange () ;
		void setChange (bool set) ;
		bool getLoading () ;
		void setLoading (bool set) ;

		/* Constant */
		static const int SELECTALL = 0 ;
		static const int COPY = 1 ;
		static const int CUT = 2 ;
		static const int PASTE = 3 ;

	private :
		/* FLTK Widget */
		Fl_Window *_mainWindow ;
		Fl_Menu_Bar *_menu ;
		Fl_Text_Editor *_textEditor ;
		Fl_Text_Buffer *_textBuffer ;

		/* Dialog Form */
		FindForm *_findDialog ;
		ReplForm *_replDialog ;
		
		/* Variable */
		int _width ;
		int _height ;
		bool _change ;
		bool _loading ;
		char *_fileName ;
		char *_findString ;
		char *_replString ;

		/* Private Function */
		void _addMenu () ;
} ;

#endif
