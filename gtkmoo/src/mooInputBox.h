/*
 *  mooInputBox.h
 *  GtkMoo
 *
 *  Copyright 2008-10 Rohit Yadav.
 *
 */

#ifndef _MOO_INPUTBOX_
#define _MOO_INPUTBOX_

void setTextBoxVisible();
void setMaxLength( int num );
void resetTable(bool*);
void mooInput ( GtkButton *button, gpointer textBox );
GtkWidget* mooInputBox(GtkWidget *mooVbox);
void text_on_Click ( GtkButton *text, gpointer widget );

#endif
