/*************/
/* Main Form */
/*************/

#include <include/MainForm.hpp>

#include <iostream>
#include <cstring>

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

/*******************************/
/* Parameter 'w' is the width  */
/* Parameter 'h' is the height */
/*******************************/
MainForm::MainForm (int w, int h)
{
	this->_width = w ;
	this->_height = h ;
	this->_change = false ;
	this->_loading = false ;
	this->_fileName = NULL ;
	this->_findString = (char *)malloc (sizeof (char) * 256) ;
	strcpy (this->_findString, "") ;
	this->_replString = (char *)malloc (sizeof (char) * 256) ;
	strcpy (this->_replString, "") ;

	this->_mainWindow = new Fl_Window (w, h, "Text Editor") ;

	/* Menu Bar */
	this->_addMenu () ;

	/* Text Editor */
	this->_textEditor = new Fl_Text_Editor (0, 30, w, h - 30) ;
	this->_textBuffer = new Fl_Text_Buffer () ;
	this->_textEditor->buffer (this->_textBuffer) ;

	this->_mainWindow->end () ;

	/* Dialog */
	this->_findDialog = new FindForm () ;
	this->_replDialog = new ReplForm () ;
}

/**********************************/
/* Form Callback Function Setting */
/**********************************/
void MainForm::formCallbackSetting ()
{
	this->_mainWindow->callback ((Fl_Callback *)exit_cb, this) ;
	this->_findDialog->callbackFunctionSetting (this) ;
	this->_replDialog->callbackFunctionSetting (this) ;
}

void MainForm::showForm (int argc, char **argv)
{
	this->_mainWindow->show (argc, argv) ;
}

int MainForm::runForm ()
{
	return Fl::run () ;
}

void MainForm::changeTitle ()
{
	char *title = (char *)malloc (sizeof (char) * 20) ;

	if (this->_change)
	{
		strcpy (title, "Text Editor (*)") ;
	}
	else
	{
		strcpy (title, "Text Editor") ;
	}

	this->_mainWindow->label (title) ;
}

/*********************************/
/* Parameter 'id'                */
/* --SELECTALL : Select All      */
/* --COPY : Copy Selected Word   */
/* --CUT : Cut Selected Word     */
/* --PASTE : Paste Selected Word */
/*********************************/
void MainForm::doEdit (int id)
{
	switch (id)
	{
		case MainForm::SELECTALL :
			Fl_Text_Editor::kf_select_all (0, this->_textEditor) ;
			break ;
		case MainForm::COPY :
			Fl_Text_Editor::kf_copy (0, this->_textEditor) ;
			break ;
		case MainForm::CUT :
			Fl_Text_Editor::kf_cut (0, this->_textEditor) ;
			break ;
		case MainForm::PASTE :
			Fl_Text_Editor::kf_paste (0, this->_textEditor) ;
			break ;
	}
}

/************************************/
/* Editor Callback Function Setting */
/************************************/
void MainForm::editorCallbackSetting ()
{
	this->_textBuffer->add_modify_callback (text_modify_cb, this) ;
	this->_textBuffer->call_modify_callbacks () ;
}

void MainForm::showInsertPosition ()
{
	this->_textEditor->show_insert_position () ;
}

/********************/
/* Show Find Dialog */
/********************/
void MainForm::showFind ()
{
	this->_findDialog->showForm (this->_findString) ;
}

/*************/
/* Find Word */
/*************/
void MainForm::findNext ()
{
	if(this->_findDialog->getFind ()[0] == '\0')
	{
		return ;
	}
	strcpy (this->_findString, this->_findDialog->getFind ()) ;

	int pos = this->_textEditor->insert_position () ;
	if (this->_textBuffer->search_forward (pos, this->_findString, &pos))
	{
		this->_textBuffer->select (pos, pos + strlen (this->_findString)) ;
		this->_textEditor->insert_position (pos + strlen (this->_findString)) ;
		this->_textEditor->show_insert_position () ;
		this->_findDialog->hideForm () ;
	}
	else
	{
		fl_alert ("Not found : \"%s\"", this->_findString) ;
	}
}

/***********************/
/* Show Replace Dialog */
/***********************/
void MainForm::showRepl ()
{
	this->_replDialog->showForm (this->_findString, this->_replString) ;
}

/****************/
/* Replace Word */
/****************/
void MainForm::replNext ()
{
	if ((this->_replDialog->getFind ()[0] == '\0') || (this->_replDialog->getRepl ()[0] == '\0'))
	{
		return ;
	}
	strcpy (this->_findString, this->_replDialog->getFind ()) ;
	strcpy (this->_replString, this->_replDialog->getRepl ()) ;

	int pos = this->_textEditor->insert_position () ;
	if (this->_textBuffer->search_forward (pos, this->_findString, &pos))
	{
		this->_textBuffer->select (pos, pos + strlen (this->_findString)) ;
		this->_textBuffer->remove_selection () ;
		this->_textBuffer->insert (pos, this->_replString) ;
		this->_textBuffer->select (pos, pos + strlen (this->_replString)) ;
		this->_textEditor->insert_position (pos + strlen (this->_replString)) ;
		this->_textEditor->show_insert_position () ;
		this->_replDialog->hideForm () ;
	}
	else
	{
		fl_alert ("Not found : \"%s\"", this->_findString) ;
	}
}

/***************/
/* Replace All */
/***************/
void MainForm::replAll ()
{
	int times = 0 ;

	if ((this->_replDialog->getFind ()[0] == '\0') || (this->_replDialog->getRepl ()[0] == '\0'))
	{
		return ;
	}
	strcpy (this->_findString, this->_replDialog->getFind ()) ;
	strcpy (this->_replString, this->_replDialog->getRepl ()) ;

	this->_textEditor->insert_position (0) ;
	for (int found = 1 ; found ;)
	{
		int pos = this->_textEditor->insert_position () ;
		found = this->_textBuffer->search_forward (pos, this->_findString, &pos) ;
		if (found)
		{
			this->_textBuffer->select (pos, pos + strlen (this->_findString)) ;
			this->_textBuffer->remove_selection () ;
			this->_textBuffer->insert (pos, this->_replString) ;
			this->_textEditor->insert_position (pos + strlen (this->_replString)) ;
			this->_textEditor->show_insert_position () ;
			times++ ;
		}
	}

	if (!(times))
	{
		fl_alert ("Not found : \"%s\"", this->_findString) ;
	}
	else
	{
		this->_replDialog->hideForm () ;
	}
}

/**********************************************************************************/
/* Check what user want to do, when he want to close a modified file without save */
/**********************************************************************************/
bool MainForm::checkSave ()
{
	int ans = fl_choice ("This file hasn't saved yet.\nWhat do you want do?", "Cancel", "Save", "Discard") ;

	switch (ans)
	{
		case 0 :
			return false ;
		case 1 :
			this->saveFile (false) ;
		case 2 :
			break ;
	}
	
	return true ;		
}

void MainForm::newFile ()
{
	if (this->_change)
	{
		if (!(this->checkSave ()))
		{
			return ;
		}
	}

	this->_textBuffer->select (0, this->_textBuffer->length ()) ;
	this->_textBuffer->remove_selection () ;
	this->_change = false ;
	this->_textBuffer->call_modify_callbacks () ;
	this->_fileName = NULL ;
}

void MainForm::openFile ()
{
	if (this->_change)
	{
		if (!(this->checkSave ()))
		{
			return ;
		}
	}

	this->_fileName = fl_file_chooser ("Open File", "Text File (*.txt)", "*.txt") ;

	this->_loading = true ;

	if (this->_fileName == NULL)
	{
		this->_loading = false ;
		return ;
	}
	else if (this->_textBuffer->loadfile (this->_fileName))
	{
		fl_alert ("File Error : %s", this->_fileName) ;
	}

	this->_loading = false ;
	this->_textBuffer->call_modify_callbacks () ;
}

/*************************************************/
/* Parameter 'asNew' : Force to save as new file */
/*************************************************/
void MainForm::saveFile (bool asNew)
{
	if (asNew || (this->_fileName == NULL))
	{
		this->_fileName = fl_file_chooser ("Save File", "Text File (*.txt)", "Unnamed.txt") ;
		if (this->_fileName == NULL)
		{
			return ;
		}
	}
	
	if (this->_textBuffer->savefile (this->_fileName))
	{
		fl_alert ("File Error : %s", this->_fileName) ;
	}
	this->_change = false ;
	this->_textBuffer->call_modify_callbacks () ;
}

bool MainForm::getChange ()
{
	return this->_change ;
}

void MainForm::setChange (bool set)
{
	this->_change = set ;
}

bool MainForm::getLoading ()
{
	return this->_loading ;
}

void MainForm::setLoading (bool set)
{
	this->_loading = set ;
}

void MainForm::_addMenu ()
{
	this->_menu = new Fl_Menu_Bar (0, 0, this->_width, 30) ;

	/* Menu Items */
	Fl_Menu_Item items[] =
	{
		{"File", 0, 0, 0, FL_SUBMENU},
			{"&New", FL_COMMAND + 'n', (Fl_Callback *)new_cb, this},
			{"&Open", FL_COMMAND + 'o', (Fl_Callback *)open_cb, this, FL_MENU_DIVIDER},
			{"&Save", FL_COMMAND + 's', (Fl_Callback *)save_cb, this},
			{"Save &As", FL_COMMAND + 'w', (Fl_Callback *)save_as_cb, this, FL_MENU_DIVIDER},
			{"&Exit", FL_COMMAND + 'e', (Fl_Callback *)exit_cb, this},
		{0},
		{"Edit", 0, 0, 0, FL_SUBMENU},
			{"Select All", FL_COMMAND + 'a', (Fl_Callback *)select_all_cb, this, FL_MENU_DIVIDER},
			{"&Copy", FL_COMMAND + 'c', (Fl_Callback *)copy_cb, this},
			{"Cut", FL_COMMAND + 'x', (Fl_Callback *)cut_cb, this},
			{"&Paste", FL_COMMAND + 'p', (Fl_Callback *)paste_cb, this},
		{0},
		{"Search", 0, 0, 0, FL_SUBMENU},
			{"&Find", FL_COMMAND + 'f', (Fl_Callback *)find_cb, this},
			{"Find Next", FL_F + 3, (Fl_Callback *)find_next_cb, this, FL_MENU_DIVIDER},
			{"&Replace", FL_COMMAND + 'r', (Fl_Callback *)replace_cb, this},
			{"Replace Next", FL_CTRL + FL_F + 3, (Fl_Callback *)replace_next_cb, this},
		{0},
	{0}} ;
	/* End */

	this->_menu->copy (items) ;
}
