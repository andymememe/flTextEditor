#include <include/ReplForm.hpp>

extern void replace_all_cb (Fl_Widget *w, void *v) ;
extern void replace_next_cb (Fl_Widget *w, void *v) ;
extern void repl_dialog_exit_cb (Fl_Widget *w, void *v) ;

ReplForm::ReplForm ()
{
	this->_replForm = new Fl_Window (500, 170, "Replace...") ;

	this->_findInp = new Fl_Input (100, 20, 350, 30, "   Find : ") ;
	this->_replInp = new Fl_Input (100, 70, 350, 30, "Replace : ") ;
	this->_replAllBtn = new Fl_Button (50, 130, 120, 30, "Replace All") ;
	this->_replNextBtn = new Fl_Return_Button (190, 130, 120, 30, "Replace Next") ;
	this->_cancelBtn = new Fl_Button (330, 130, 120, 30, "Cancel") ;

	this->_replForm->end () ;
}

void ReplForm::callbackFunctionSetting (void *v)
{
	this->_replAllBtn->when (FL_WHEN_RELEASE) ;
	this->_replAllBtn->callback ((Fl_Callback *)replace_all_cb, v) ;
	this->_replNextBtn->when (FL_WHEN_RELEASE) ;
	this->_replNextBtn->callback ((Fl_Callback *)replace_next_cb, v) ;
	this->_cancelBtn->when (FL_WHEN_RELEASE) ;
	this->_cancelBtn->callback ((Fl_Callback *)repl_dialog_exit_cb, this) ;
}

void ReplForm::showForm (char *find, char *repl)
{
	this->_findInp->value (find) ;
	this->_replInp->value (repl) ;
	this->_replForm->show () ;
}

void ReplForm::hideForm ()
{
	this->_replForm->hide () ;
}

const char* ReplForm::getFind ()
{
	return this->_findInp->value () ;
}

const char* ReplForm::getRepl ()
{
	return this->_replInp->value () ;
}
