/*
 *  mooGame.h
 *  GtkMoo
 *
 *  Copyright 2008-10 Rohit Yadav.
 *
 */

#ifndef _MOO_GAME_
#define _MOO_GAME_

#include <gtk/gtk.h>

char* startGame( int Digit );
char* checkMoo( char* mooGuess, gpointer textBox );
int getCurrentTime ();
gint timeout_callback (gpointer data);
void cheatMoo();
bool checkRepetition( char* mooGuess , int maxDig);

#endif
