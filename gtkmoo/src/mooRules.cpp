/*
    mooRules.cpp
    Created by Rohit Yadav on 19/10/08.
    
    GtkMoo: Bulls n Cows in Gtk+
    Copyright (C) 2008-10  Rohit Yadav

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

#include "mooRules.h"
#include <gtk/gtk.h>

void mooRules(GtkMenuItem *menuitem, gpointer user_data)
{
  GtkWidget *mooRules;
  GtkWidget *rulesLabel;
  GtkWidget *OK;
  gchar* filename;
  
  GtkWidget *vBox;
  
  gchar *RULES = {
  "<span underline=\"single\"><big><b>Rules</b></big></span>\n"
  "\nThe digits of the randomly generated secret"
  "\nnumber are different. The first digit cannot"
  "\nbe zero. If the Guess has matching digits in"
  "\nexact places, they are Bulls. If the Guess "
  "\nhas matching digits in different places they"
  "\nare Cows."
  "\nYour aim is to find the secret number."
  "\nExample:"
  "\nSecret: <span foreground=\"blue\">4</span><span foreground=\"#af000f\">2</span><b>7</b><span foreground=\"red\">1</span>"
  "\nGuess: <span foreground=\"red\">1</span><span foreground=\"#af000f\">2</span><b>3</b><span foreground=\"blue\">4</span>"
  "\n\nResult: <b>1B2C</b>\n"
  };

  mooRules = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  //gtk_widget_set_size_request (mooRules, 300, 270);
  gtk_window_set_title (GTK_WINDOW (mooRules), "GtkMoo: Rules");
  gtk_container_set_border_width (GTK_CONTAINER (mooRules), 10);
  gtk_window_set_position (GTK_WINDOW (mooRules), GTK_WIN_POS_CENTER);
  
  filename = g_build_filename (g_get_current_dir(), "moo.png", NULL);
  gtk_window_set_icon_from_file (GTK_WINDOW(mooRules), (const gchar*)filename, NULL);

  gtk_window_set_resizable (GTK_WINDOW (mooRules), FALSE);

  vBox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (mooRules), vBox);
  gtk_widget_show (vBox);
  
  rulesLabel = gtk_label_new ("");
  gtk_label_set_justify (GTK_LABEL (rulesLabel), GTK_JUSTIFY_CENTER);
  gtk_label_set_text((GtkLabel*)rulesLabel,RULES);
  gtk_label_set_use_markup (GTK_LABEL (rulesLabel), TRUE);
  gtk_widget_show (rulesLabel);
  gtk_box_pack_start (GTK_BOX (vBox), rulesLabel, TRUE, TRUE, 0);
  
  OK = gtk_button_new_with_label("That's All");
  gtk_widget_show (OK);
  gtk_widget_set_size_request (OK, 50, 30);
  gtk_box_pack_start (GTK_BOX (vBox), OK, TRUE, TRUE, 0);
  
  g_signal_connect_swapped (G_OBJECT (OK), "clicked",
			       G_CALLBACK (gtk_widget_destroy), mooRules);

  g_signal_connect (G_OBJECT (mooRules), "destroy",
			       G_CALLBACK (gtk_widget_destroy), NULL);
  gtk_widget_show (mooRules);
}
