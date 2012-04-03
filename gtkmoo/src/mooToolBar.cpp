/*
    mooToolBar.cpp
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
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1301  USA
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "mooLevel.h"
#include "mooGame.h"
#include "mooToolBar.h"

gint DIG;
char* randMoo;
int totalChances;

void
init_Settings (GtkMenuItem *menuitem, gpointer)
{
  //Set insensitive mooSettings:
  gtk_widget_set_sensitive((GtkWidget*)menuitem, FALSE);
  mooLevelSettings(menuitem, &DIG);
}

void init_new (GtkMenuItem *, gpointer)
{
  totalChances = 0;
  if( DIG == 0 )
    DIG = 4;

  randMoo = startGame( DIG );
}

GtkWidget* mooToolBar (void)
{
  GtkWidget *toolbar;
  GtkIconSize tmp_toolbar_icon_size;
  GtkWidget *tmp_image;
  GtkWidget *toolbar_button_start;
  
  GtkWidget *mooSettings;
  
  GtkWidget *separatortoolitem2;
  GtkWidget *toolbar_button_quit;

  GtkAccelGroup *accel_group;
  gchar* filename;

  accel_group = gtk_accel_group_new ();
  
  toolbar = gtk_toolbar_new ();
  tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar));
 
  filename = g_build_filename (g_get_current_dir(), "moo.png", NULL);		

  tmp_image = gtk_image_new_from_file (filename);
  
  gtk_widget_show (tmp_image);
  toolbar_button_start = (GtkWidget*) gtk_tool_button_new (tmp_image, "New Game");
  gtk_widget_show (toolbar_button_start);
  gtk_container_add (GTK_CONTAINER (toolbar), toolbar_button_start);
  gtk_widget_add_accelerator (toolbar_button_start, "clicked", accel_group,
                              GDK_N, (GdkModifierType) GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  tmp_image = gtk_image_new_from_stock (GTK_STOCK_PREFERENCES, GTK_ICON_SIZE_MENU);
  gtk_widget_show (tmp_image);
 
  mooSettings = (GtkWidget*) gtk_tool_button_new (tmp_image, "Game Level");
  gtk_widget_show (mooSettings);
  gtk_container_add (GTK_CONTAINER (toolbar), mooSettings);
  gtk_widget_add_accelerator (mooSettings, "clicked", accel_group,
                              GDK_l, (GdkModifierType) GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);
							  

  separatortoolitem2 = (GtkWidget*) gtk_separator_tool_item_new ();
  gtk_widget_show (separatortoolitem2);
  gtk_container_add (GTK_CONTAINER (toolbar), separatortoolitem2);

  tmp_image =  gtk_image_new_from_icon_name ("gtk-quit", GTK_ICON_SIZE_MENU);
  gtk_widget_show (tmp_image);
  toolbar_button_quit = (GtkWidget*) gtk_tool_button_new (tmp_image, ("Quit"));
  gtk_widget_show (toolbar_button_quit);
  gtk_container_add (GTK_CONTAINER (toolbar), toolbar_button_quit);
  gtk_widget_add_accelerator (toolbar_button_quit, "clicked", accel_group,
                              GDK_N, (GdkModifierType) GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);
  
  g_signal_connect ((gpointer) toolbar_button_start, "clicked",
                    G_CALLBACK (init_new),
                    NULL);
  g_signal_connect ((gpointer) mooSettings, "clicked",
                    G_CALLBACK (init_Settings),
                    NULL);
					
  g_signal_connect ((gpointer) toolbar_button_quit, "clicked",
                    G_CALLBACK (gtk_main_quit),
                    NULL);
  return toolbar;
}
