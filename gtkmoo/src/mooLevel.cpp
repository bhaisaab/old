/*
    mooLevel.cpp
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

#include <gtk/gtk.h>
//#define DEBUG
#include "mooLevel.h"

GtkMenuItem *menu;
static gint *DIG_SELECTED;

void radio1Clicked (GtkToggleButton *level, GtkWidget *other_toggle)
{

  if( gtk_toggle_button_get_active (level) )
    *DIG_SELECTED = 3;
  #ifdef DEBUG
  gtk_button_set_label (button, "3");
  #endif 
}
void radio2Clicked (GtkToggleButton *level, GtkWidget *other_toggle)
{

  if( gtk_toggle_button_get_active (level) )
    *DIG_SELECTED = 4;
  #ifdef DEBUG
  gtk_button_set_label (button, "4");
  #endif
}
void radio3Clicked (GtkToggleButton *level, GtkWidget *other_toggle)
{

  if( gtk_toggle_button_get_active (level) )
    *DIG_SELECTED = 5;
  #ifdef DEBUG
  gtk_button_set_label (button, "5");
  #endif
}

gint* close_settings(GtkWidget* widget, gpointer data)
{
  gtk_widget_destroy((GtkWidget*) widget);
  gtk_widget_set_sensitive((GtkWidget*)menu, TRUE);
  return DIG_SELECTED;
}

gint* mooLevelSettings(GtkMenuItem *menuitem, gint* LEVEL)
{
  GtkWidget *mooPreferences;
  GtkWidget *vBox;
  GtkWidget *vBoxRadio;  
  GtkWidget *button;
  GtkWidget *l1, *l2, *l3;
  
  menu = menuitem;
  *LEVEL = 4;
  DIG_SELECTED = LEVEL;
  
  mooPreferences = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (mooPreferences, 200, 190);
  gtk_window_set_title (GTK_WINDOW (mooPreferences), "Select Game Level");
  gtk_container_set_border_width (GTK_CONTAINER (mooPreferences), 10);
  gtk_window_set_position (GTK_WINDOW (mooPreferences), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable (GTK_WINDOW (mooPreferences), FALSE);
  gtk_window_set_icon_name (GTK_WINDOW (mooPreferences), GTK_STOCK_PREFERENCES);
  
  g_signal_connect (G_OBJECT (mooPreferences), "delete_event",
			       G_CALLBACK (close_settings), NULL);

  vBox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (mooPreferences), vBox);
  gtk_widget_show (vBox);

  vBoxRadio = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (vBoxRadio), 10);
  gtk_box_pack_start (GTK_BOX (vBox), vBoxRadio, TRUE, TRUE, 0);
  gtk_widget_show (vBoxRadio);
  
  /*Level 1*/
  l1 = gtk_radio_button_new_with_label ( NULL, "Easy: 3 Digits" );

  /*Level 2*/  
  l2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (l1), "Medium: 4 Digits");
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (l2), TRUE);

  /*Level 3*/
  l3 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (l1), "Hard: 5 Digits");
  
  gtk_box_pack_start (GTK_BOX (vBoxRadio), l1, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vBoxRadio), l2, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vBoxRadio), l3, TRUE, TRUE, 0);
  
  gtk_widget_show (l1);
  gtk_widget_show (l2);
  gtk_widget_show (l3);
  
  g_signal_connect (G_OBJECT (l1), "toggled",
			       G_CALLBACK (radio1Clicked), NULL);
				   
  g_signal_connect (G_OBJECT (l2), "toggled",
			       G_CALLBACK (radio2Clicked), NULL);
				   
  g_signal_connect (G_OBJECT (l3), "toggled",
			       G_CALLBACK (radio3Clicked), NULL);
				     
  vBoxRadio = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (vBoxRadio), 10);
  gtk_box_pack_start (GTK_BOX (vBox), vBoxRadio, FALSE, TRUE, 0);
  gtk_widget_show (vBoxRadio);

  button = gtk_button_new_with_label ("Moo");
  gtk_box_pack_start (GTK_BOX (vBoxRadio), button, TRUE, TRUE, 0);
  gtk_button_set_relief (GTK_BUTTON (button), GTK_RELIEF_HALF);
  gtk_widget_show (button);
  
  g_signal_connect_swapped (G_OBJECT (button), "clicked",
							G_CALLBACK (close_settings), (gpointer)mooPreferences);
  
  gtk_widget_show (mooPreferences);
  return DIG_SELECTED;
}
