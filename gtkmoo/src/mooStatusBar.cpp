/*
    mooStatusBar.cpp
    Created by Rohit Yadav on 18/10/08.
    
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
 
#include <gtk/gtk.h>
#include "mooStatusBar.h"

GtkWidget *timeLabel;
GtkWidget *statusLabel;

GtkWidget* mooStatusBar(void)
{
  GtkWidget *hbox_statusbar;
  
  hbox_statusbar = gtk_hbox_new (TRUE, 0);

  statusLabel = gtk_label_new (("Start a New Game!"));
  gtk_widget_show (statusLabel);
  gtk_box_pack_start (GTK_BOX (hbox_statusbar), statusLabel, TRUE, TRUE, 0);


  timeLabel = gtk_label_new (("Time Elapsed: 0.0s"));
  gtk_widget_set_size_request (timeLabel, 80, -1);
  gtk_widget_show (timeLabel);
  gtk_box_pack_start (GTK_BOX (hbox_statusbar), timeLabel, TRUE, TRUE, 0);
  
  return hbox_statusbar;
}
