/******************/
/* Find Word Form */
/******************/

#include <include/FindForm.hpp>

FindForm::FindForm()
{
	this->_findForm = new Fl_Window(500, 120, "Find...");

	this->_findInp = new Fl_Input(100, 20, 350, 30, "Find : ");
	this->_findNextBtn = new Fl_Return_Button(120, 80, 120, 30, "Find Next");
	this->_cancelBtn = new Fl_Button(260, 80, 120, 30, "Cancel");

	this->_findForm->end();
}

/**********************************/
/* Form Callback Function Setting */
/* Parameter 'v' is a MainForm    */
/**********************************/
void FindForm::callbackFunctionSetting(void *v)
{
	this->_findNextBtn->when(FL_WHEN_RELEASE);
	this->_findNextBtn->callback((Fl_Callback *)find_next_cb, v);
	this->_cancelBtn->when(FL_WHEN_RELEASE);
	this->_cancelBtn->callback((Fl_Callback *)find_dialog_exit_cb, this);
}

/*********************************************/
/* Parameter 'find' is the last finding word */
/*********************************************/
void FindForm::showForm(char *find)
{
	this->_findInp->value(find);
	this->_findForm->show();
}

void FindForm::hideForm()
{
	this->_findForm->hide();
}

const char *FindForm::getFind()
{
	return this->_findInp->value();
}
