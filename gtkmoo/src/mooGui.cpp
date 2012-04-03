/*
    mooGui.cpp
    Created by Rohit Yadav on 13/10/08.
    
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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "mooGui.h"
#include "mooMenuBar.h"
#include "mooToolBar.h"
#include "mooInputBox.h"
#include "mooGuessTable.h"
#include "mooStatusBar.h"
#include "mooGame.h"

GtkWidget *mooVbox;
GtkWidget* create_mooWindow (void)
{
  GtkWidget *mooWindow;
  
  GtkWidget *menubar;
  GtkWidget *toolbar;
  GtkWidget *mooHbox;
  GtkWidget *hseparator;
  GtkWidget *mooSBar; 
  gchar* filename;

 // GtkTooltips *tooltips;

  /*-------------------------------------------*\ 
   *   Create GtkMoo Window: CENTER, TOPLEVEL  * 
  \*-------------------------------------------*/
  
  mooWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (mooWindow, 420, 450);
  gtk_window_set_title (GTK_WINDOW (mooWindow),  "Gtk Moo" );
  gtk_window_set_position (GTK_WINDOW (mooWindow), GTK_WIN_POS_CENTER_ALWAYS);
  
  filename = g_build_filename (g_get_current_dir(), "moo.png", NULL);
  gtk_window_set_icon_from_file (GTK_WINDOW(mooWindow), (const gchar*)filename, NULL);
  
  g_signal_connect ((gpointer) mooWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);


  /*-------------------------------------------*\ 
   *   Create VBOX: 8 items contained          * 
  \*-------------------------------------------*/  
 
  mooVbox = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (mooVbox);
  gtk_container_add (GTK_CONTAINER (mooWindow), mooVbox);

  /*-------------------------------------------*\ 
   *   Create menubar: Game, View, Help        * 
  \*-------------------------------------------*/
  
  menubar = mooMenuBar(mooWindow);
  gtk_widget_show (menubar);
  gtk_box_pack_start (GTK_BOX (mooVbox), menubar, FALSE, TRUE, 0);
  
  /*-------------------------------------------*\ 
   *   Create ToolBar: NewGame, Scores, Quit   * 
  \*-------------------------------------------*/
  
  toolbar = mooToolBar();
  gtk_widget_show (toolbar);
  gtk_box_pack_start (GTK_BOX (mooVbox), toolbar, FALSE, TRUE, 0);
  gtk_widget_set_size_request (toolbar, -1, 90);
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH);
  
  /*-------------------------------------------*\ 
   *   Create Input HBox: Input, TextBox, OK   * 
  \*-------------------------------------------*/
  
  mooHbox = mooInputBox(mooVbox);
  gtk_widget_show (mooHbox);
  gtk_box_pack_start (GTK_BOX (mooVbox), mooHbox, TRUE, TRUE, 0);
  gtk_widget_set_size_request (mooHbox, -1, 30);
  
  /*-------------------------------------------*\ 
   *   Horizontal Separator                    * 
  \*-------------------------------------------*/
  
  hseparator = gtk_hseparator_new ();
  gtk_widget_show (hseparator);
  gtk_box_pack_start (GTK_BOX (mooVbox), hseparator, FALSE, TRUE, 0);
  gtk_widget_set_size_request (hseparator, -1, 5);
  
  /*-------------------------------------------*\ 
   *   Draw Guess Table for Gtk Moo            * 
  \*-------------------------------------------*/
  mooGuessTable(mooVbox);
  
  /*-------------------------------------------*\ 
   *   Horizontal Separator                    * 
  \*-------------------------------------------*/
  
  hseparator = gtk_hseparator_new ();
  gtk_widget_show (hseparator);
  gtk_box_pack_start (GTK_BOX (mooVbox), hseparator, FALSE, TRUE, 0);
  gtk_widget_set_size_request (hseparator, -1, 5);

  /*-------------------------------------------*\ 
   *   Create GtkMoo StatusBar: Event, Time    * 
  \*-------------------------------------------*/
  
  mooSBar = mooStatusBar();
  gtk_widget_show (mooSBar);
  gtk_box_pack_start (GTK_BOX (mooVbox), mooSBar, FALSE, TRUE, 0);
  gtk_widget_set_size_request (mooSBar, -1, 20);

  return mooWindow;
}
