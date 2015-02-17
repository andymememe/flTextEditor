#ifndef CALLBACK
#define CALLBACK

#include <include/MainForm.hpp>
#include <include/FindForm.hpp>
#include <include/ReplForm.hpp>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Text_Editor.H>

void text_modify_cb (int pos, int nInserted, int nDeleted, int nRestyled, const char* deletedText, void* cbArg)
{
	MainForm *w = (MainForm *)cbArg ;

	if ((nInserted || nDeleted) && !(w->getLoading ()))
	{
		w->setChange (true) ;
		w->changeTitle () ;
	}
	if (w->getLoading ())
	{
		w->showInsertPosition () ;
	}
}

void new_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm*)v ;
	m->newFile () ;
	m->changeTitle () ;
}

void open_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->openFile () ;
	m->changeTitle () ;
}

void save_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->saveFile (false) ;
	m->changeTitle () ;
}

void save_as_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->saveFile () ;
	m->changeTitle () ;
}

void exit_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;

	if (m->getChange())
	{
		if (!(m->checkSave ()))
		{
			return ;
		}
	}

	exit (0) ;
}

void select_all_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->doEdit (MainForm::SELECTALL) ;
}

void copy_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->doEdit (MainForm::COPY) ;
}

void cut_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->doEdit (MainForm::CUT) ;
	m->setChange (true) ;
	m->changeTitle () ;
}

void paste_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->doEdit (MainForm::PASTE) ;
	m->setChange (true) ;
	m->changeTitle () ;
}

void find_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->showFind () ;
}

void find_next_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->findNext () ;
}

void replace_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->showRepl () ;
}

void replace_next_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->replNext () ;
}

void replace_all_cb (Fl_Widget *w, void *v)
{
	MainForm *m = (MainForm *)v ;
	m->replAll () ;
}

void find_dialog_exit_cb (Fl_Widget *w, void *v)
{
	FindForm *f = (FindForm *)v ;
	f->hideForm () ;
}

void repl_dialog_exit_cb (Fl_Widget *w, void *v)
{
	ReplForm *r = (ReplForm *)v ;
	r->hideForm () ;
}

#endif
