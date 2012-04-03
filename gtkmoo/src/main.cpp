/*
    main.cpp
    Created by Rohit Yadav on 10/10/08.
    
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
#include "mooGui.h"

GtkWidget *window;
gboolean TOGGLE = FALSE;

void tray_icon_on_click(GtkStatusIcon *, gpointer)
{
  if(!TOGGLE)
    gtk_widget_hide (window);
  else
    gtk_widget_show (window);

  TOGGLE = !TOGGLE;
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER_ALWAYS);
  return;
}

static GtkStatusIcon *create_tray_icon() 
{
  GtkStatusIcon *tray_icon;
  gchar* filename;
  tray_icon = gtk_status_icon_new();
      
  g_signal_connect(G_OBJECT(tray_icon), "popup-menu", 
                         G_CALLBACK(tray_icon_on_click), NULL);
  g_signal_connect(G_OBJECT(tray_icon), "activate",
                         G_CALLBACK(tray_icon_on_click), NULL);
		
  filename = g_build_filename (g_get_current_dir(), "moo.png", NULL);
  printf("PATH for sysIcon: %s\n",filename);		
  gtk_status_icon_set_from_file(tray_icon, filename);
        
  gtk_status_icon_set_tooltip(tray_icon, "Click to Hide/Show GtkMoo\n \302\251 Rohit Yadav, 2008-10");
  gtk_status_icon_set_visible(tray_icon, TRUE);
  return tray_icon;
}

int main (int argc, char **argv)
{
  GtkStatusIcon *tray_icon;
  
  gtk_init (&argc, &argv);

  tray_icon = create_tray_icon();
  window = create_mooWindow ();
  gtk_widget_show (window);
  
  gtk_main ();

  return 0;
}
