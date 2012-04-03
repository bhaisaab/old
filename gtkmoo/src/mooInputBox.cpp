/*
    mooInputBox.cpp
    Created by Rohit Yadav on 13/10/08.
    
    GtkMoo: Bulls n Cows in Gtk+
    Copyright (C) 2008  Rohit Yadav

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
*/

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "mooGame.h"
#include "mooInputBox.h"
#include "mooGuessTable.h"
#include "mooToolBar.h"

extern int totalChances;
extern GtkWidget *table_guess_result;
extern GtkWidget* timeLabel;
extern GtkWidget* statusLabel;
extern char* randMoo;
GtkWidget *guessLabel[2][11];
GtkWidget *textBox;
GtkWidget *ok_button;

void setTextBoxVisible()
{
  gtk_widget_set_sensitive((GtkWidget*)textBox, TRUE);
  gtk_widget_set_sensitive((GtkWidget*)ok_button, TRUE);
}

void setMaxLength( int num )
{
  gtk_entry_set_max_length (GTK_ENTRY (textBox), num);
}

void resetTable(bool *started)
{
  gint row, col;
  
  if(*started == false)
  {
  	*started = true;
	return;
  }
  
  for( row = 0; row < 2; row++)
    for( col = 0; col < 10; col++ )
	  gtk_label_set_text( (GtkLabel*)guessLabel[row][col], " " );

	return;
}

void mooInput ( GtkButton *button, gpointer textBox )
{
  GtkWidget *table;
  gint row;
  
  table = table_guess_result;
  const gchar *Input;
  char input[5];
  gchar* result;

  if( totalChances >= 10 )
    return;
  
  Input = gtk_entry_get_text (GTK_ENTRY (textBox));
  
  if( !strcmp(Input, "") )
    return; 
  
  strcpy(input,Input);
  result = checkMoo( input, textBox );
  
  if( !strcmp(result,"error") )
    return;

  totalChances++;
	
  row = totalChances;
  if( totalChances < 11 )
  {
    guessLabel[0][row-1] = gtk_label_new(input);
    gtk_widget_show (guessLabel[0][row-1]);
    gtk_table_attach (GTK_TABLE (table), guessLabel[0][row-1],
					   1, 2, row, row+1,
                       (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                       (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	guessLabel[1][row-1] = gtk_label_new(result);
    gtk_widget_show (guessLabel[1][row-1]);
    gtk_table_attach (GTK_TABLE (table), guessLabel[1][row-1],
					   2, 3, row, row+1,
                       (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                       (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
  }

  
  if( strcmp(input, randMoo) == 0 )
  {
    gtk_label_set_label( (GtkLabel*)statusLabel, "You Win!");
    totalChances = 12;
  }
  gtk_entry_set_text (GTK_ENTRY (textBox), "");

  return;
}

void text_on_Click ( GtkButton *text, gpointer widget )
{
  gtk_entry_set_text (GTK_ENTRY (text), "");
  return;
}

GtkWidget* mooInputBox(GtkWidget *mooVbox)
{
  GtkWidget *hbox_input;
  GtkWidget *hbox_input_label;
  GtkTooltips *tooltips;
  tooltips = gtk_tooltips_new ();
  
  hbox_input = gtk_hbox_new (FALSE, 0);

  hbox_input_label = gtk_label_new ("Input your Guess");
  gtk_widget_show (hbox_input_label);
  gtk_box_pack_start (GTK_BOX (hbox_input), hbox_input_label, TRUE, TRUE, 0);
  gtk_label_set_justify (GTK_LABEL (hbox_input_label), GTK_JUSTIFY_CENTER);

  textBox = gtk_entry_new ();
  gtk_widget_show (textBox);
  gtk_box_pack_start (GTK_BOX (hbox_input), textBox, TRUE, TRUE, 0);
  gtk_widget_set_size_request (textBox, 200, -1);
  gtk_tooltips_set_tip (tooltips, textBox, ("Enter 3 to 5 digit number"), NULL);
  gtk_entry_set_max_length (GTK_ENTRY (textBox), 4);//Default level of 4-Digits
  gtk_widget_set_sensitive((GtkWidget*)textBox, FALSE);

  ok_button = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (ok_button);
  gtk_box_pack_start (GTK_BOX (hbox_input), ok_button, TRUE, FALSE, 0);
  gtk_widget_set_size_request (ok_button, 60, -1);
  gtk_widget_set_sensitive((GtkWidget*)ok_button, FALSE);

  g_signal_connect (G_OBJECT (ok_button), "clicked",
  G_CALLBACK (mooInput), (gpointer)textBox);
  
  g_signal_connect_swapped (G_OBJECT (textBox), "activate",
  G_CALLBACK (mooInput), (gpointer)ok_button);
  
  return hbox_input;
}
