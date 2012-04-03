/*
    mooMenuBar.cpp
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
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include "mooAbout.h"
#include "mooMenuBar.h"
#include "mooGame.h"
#include "mooRules.h"
#include "mooToolBar.h"

void
start_newgame (GtkMenuItem *, gpointer)
{
 printf("NewGame");
 init_new(NULL,NULL);
}

void init_about (GtkMenuItem *, gpointer)
{
  GtkWidget* about;
  
  about = aboutGtkMoo();

  gtk_dialog_run (GTK_DIALOG (about));
  gtk_widget_destroy (about);
  return;
}

void showHint (GtkMenuItem *, gpointer)
{
  cheatMoo();
}

GtkWidget* mooMenuBar (GtkWidget* window)
{
  GtkWidget *menubar, *game, *view, *help;
  GtkWidget *gamemenu, *viewmenu, *helpmenu;
  GtkWidget *newgame, *quit, *hint, *rules, *about;
  GtkWidget *newgame_image, *quit_image, 
            *hint_image, *rules_image;
  GtkWidget *separator;
  
  GtkAccelGroup *accel_group;

  accel_group = gtk_accel_group_new ();
  gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);
  gtk_menu_set_accel_group (GTK_MENU (menubar), accel_group);


  /*-------------------------------------------*\ 
   *   Create menubar: Game, View, Help        * 
  \*-------------------------------------------*/  
  
  menubar = gtk_menu_bar_new ();

  game = gtk_menu_item_new_with_mnemonic ("_Game");
  gtk_widget_show (game);
  gtk_container_add (GTK_CONTAINER (menubar), game);
  
  /*-->Game Menu Starts Here<--*/	
  gamemenu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (game), gamemenu);  
  gtk_widget_set_size_request (menubar, -1, 25);
  
  newgame = gtk_image_menu_item_new_with_mnemonic ("_New Game");
  gtk_widget_show (newgame);
  gtk_container_add (GTK_CONTAINER (gamemenu), newgame);
  gtk_widget_add_accelerator (newgame, "activate", accel_group,
                              GDK_N, (GdkModifierType) GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  newgame_image = gtk_image_new_from_stock ("gtk-new", GTK_ICON_SIZE_MENU);

  gtk_widget_show (newgame_image);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (newgame), newgame_image);
  
  g_signal_connect ((gpointer) newgame, "activate",
                    G_CALLBACK (start_newgame), NULL);

  separator = gtk_separator_menu_item_new ();
  gtk_widget_show (separator);
  gtk_container_add (GTK_CONTAINER (gamemenu), separator);
  gtk_widget_set_sensitive (separator, FALSE);

  quit = gtk_image_menu_item_new_with_mnemonic ("_Quit");
  gtk_widget_show (quit);
  gtk_container_add (GTK_CONTAINER (gamemenu), quit);
  gtk_widget_add_accelerator (quit, "activate", accel_group,
                              GDK_Q, (GdkModifierType) GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  quit_image = gtk_image_new_from_stock ("gtk-quit", GTK_ICON_SIZE_MENU);
  //create_pixmap (mainwindow, "Eket Mask.xpm");
  gtk_widget_show (quit_image);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (quit), quit_image);
  
  g_signal_connect ((gpointer) quit, "activate",
                    G_CALLBACK (gtk_main_quit),
                    NULL);
  /*-->Game Menu Ends Here<--*/

  /*-->View Menu Starts Here Here<--*/					
  view = gtk_menu_item_new_with_mnemonic ("_View");
  gtk_widget_show (view);
  gtk_container_add (GTK_CONTAINER (menubar), view);

  viewmenu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (view), viewmenu);

  hint = gtk_image_menu_item_new_with_mnemonic ("Show _Hint");
  gtk_widget_show (hint);
  gtk_container_add (GTK_CONTAINER (viewmenu), hint);
  gtk_widget_add_accelerator (hint, "activate", accel_group,
                              GDK_h, (GdkModifierType) GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  hint_image = gtk_image_new_from_stock ("gtk-dialog-info", GTK_ICON_SIZE_MENU);
  gtk_widget_show (hint_image);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (hint), hint_image);
  
  g_signal_connect ((gpointer) hint, "activate",
                    G_CALLBACK (showHint),
                    NULL);

  /*-->View Menu Ends Here<--*/
  
  /*-->Help Menu Starts Here<--*/
  help = gtk_menu_item_new_with_mnemonic ("_Help");
  gtk_widget_show (help);
  gtk_container_add (GTK_CONTAINER (menubar), help);

  helpmenu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (help), helpmenu);

  rules = gtk_image_menu_item_new_with_mnemonic ("_Rules");
  gtk_widget_show (rules);
  gtk_container_add (GTK_CONTAINER (helpmenu), rules);
  gtk_widget_add_accelerator (rules, "activate", accel_group,
                              GDK_F1, (GdkModifierType) 0,
                              GTK_ACCEL_VISIBLE);

  rules_image = gtk_image_new_from_stock ("gtk-help", GTK_ICON_SIZE_MENU);
  gtk_widget_show (rules_image);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (rules), rules_image);
  
  g_signal_connect ((gpointer) rules, "activate",
                    G_CALLBACK (mooRules), NULL);
  
  separator = gtk_separator_menu_item_new ();
  gtk_widget_show (separator);
  gtk_container_add (GTK_CONTAINER (helpmenu), separator);
  gtk_widget_set_sensitive (separator, FALSE);
 
  about = gtk_image_menu_item_new_from_stock ("gtk-about", accel_group);
  gtk_widget_show (about);
  gtk_container_add (GTK_CONTAINER (helpmenu), about);
  
  g_signal_connect ((gpointer) about, "activate",
                    G_CALLBACK (init_about),
                    NULL);
  
  /*-->Help Menu Ends Here<--*/
  return menubar;
}
