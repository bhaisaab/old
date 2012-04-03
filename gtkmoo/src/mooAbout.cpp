/*
    mooAbout.cpp
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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <glib.h>

#include "mooAbout.h"

GtkWidget* aboutGtkMoo (void)
{
  GtkWidget *aboutdialog;

  gchar* filename;
  const gchar* VERSION = "2.0";
  const gchar *authors[] = {
    "Rohit Yadav\n",
    NULL
  };
  
  const gchar *license = {
     "GtkMoo: Bulls n Cows in GTK+ interface.\nCopyright (C) 2008-10  Rohit Yadav.\n"
	 "\nThis program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version."
	 "\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY, without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details."
	 "\n\nYou should have received a copy of the GNU General Public License along with this program.  If not, see http://www.gnu.org/licenses."
	 "\nContact me AT: rohit_yadav@users.sourceforge.net for bugs/suggestions."
  };
  
  filename = g_build_filename (g_get_current_dir(), "moo.png", NULL);
  
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);

  aboutdialog = gtk_about_dialog_new ();
  gtk_window_set_position (GTK_WINDOW (aboutdialog), GTK_WIN_POS_CENTER_ALWAYS);
  
  gtk_container_set_border_width (GTK_CONTAINER (aboutdialog), 5);
  gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (aboutdialog), VERSION);
  gtk_about_dialog_set_name (GTK_ABOUT_DIALOG (aboutdialog), ("GtkMoo"));
  gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (aboutdialog), ("Copyright \302\251 2008-10 Rohit Yadav"));
  gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG (aboutdialog), ("Bulls n Cows in GTK+ interface."));
  gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (aboutdialog), (license));
  gtk_about_dialog_set_wrap_license (GTK_ABOUT_DIALOG (aboutdialog), TRUE);
  gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (aboutdialog), "http://gtk-moo.sourceforge.net");
  gtk_about_dialog_set_website_label (GTK_ABOUT_DIALOG (aboutdialog), ("http://gtk-moo.sourceforge.net"));
  gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (aboutdialog), authors);

  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(aboutdialog), pixbuf);
  gtk_window_set_icon(GTK_WINDOW(aboutdialog),pixbuf);

  return aboutdialog;
}
