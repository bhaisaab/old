/*
    mooGuessTable.cpp
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
#include <stdio.h>
#include "mooGuessTable.h"

extern int totalChances;
GtkWidget *table_guess_result;

void initTable(GtkWidget* mooVbox)
{
  GtkWidget *Guess, *Result, *numLabel;

  int column, row;

  gchar* num[] = {"", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};   

  table_guess_result = gtk_table_new (11, 3, FALSE);

  column = 0;
  for(row = 0; row < 11; row++)
    {
      numLabel = gtk_label_new(num[row]);
      gtk_widget_show (numLabel);
      gtk_table_attach (GTK_TABLE (table_guess_result), numLabel, (gint)column, (gint)column+1, (gint)row, (gint)row+1,
                       (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                       (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
    }

  for( column = 1; column < 3; column++ )
  {
    for(row = 0; row < 11; row++)
    {
      Guess = gtk_label_new(" ");
      gtk_widget_show (Guess);
      gtk_table_attach (GTK_TABLE (table_guess_result), Guess, (gint)column, (gint)column+1, (gint)row, (gint)row+1,
                       (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                       (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

    }
  }

  Result = gtk_label_new (("Result"));
  gtk_widget_show (Result);
  gtk_table_attach (GTK_TABLE (table_guess_result), Result, 2, 3, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  Guess = gtk_label_new (("Guess"));
  gtk_widget_show (Guess);
  gtk_table_attach (GTK_TABLE (table_guess_result), Guess, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
					
  gtk_widget_show (table_guess_result);
  gtk_box_pack_start (GTK_BOX (mooVbox), table_guess_result, TRUE, TRUE, 0);
  gtk_widget_set_size_request (table_guess_result, -1, 250);
  return;
}

void mooGuessTable(GtkWidget* mooVbox)
{
  initTable(mooVbox);
  return;
}
