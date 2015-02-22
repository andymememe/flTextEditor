#ifndef CALLBACK
#define CALLBACK

#include <FL/Fl_Widget.H>

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

extern void replace_all_cb (Fl_Widget *w, void *v) ;

extern void find_dialog_exit_cb (Fl_Widget *w, void *v) ;

extern void repl_dialog_exit_cb (Fl_Widget *w, void *v) ;

#endif
