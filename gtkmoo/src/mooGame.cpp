/*
    mooGame.cpp
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include <time.h>

#ifndef win32
#include <sys/time.h>
#endif

#include "carousel.h"
#include "mooGame.h"
#include "mooInputBox.h"

extern GtkWidget* timeLabel;
extern GtkWidget* statusLabel;

gchar result[5]={'0','B','0','C', '\0'};
char gtkMoo[5];
extern char* randMoo;
extern gint DIG;
extern int totalChances;

int timerHandle = -1;
int timeTicks = 0;
int startSystemTime = 0;
int historyPos = 1;
float timeElapsed;
static bool started = false;

GtkWidget *textBox2;

char* startGame( int Digit )
{
  Carousel Moo;
  int i, _rand;  
  
  Moo.init();
  memset(gtkMoo,'\0', 5 * sizeof(char) );
  resetTable(&started);
  setMaxLength( Digit );
  setTextBoxVisible();
  
  srand(time(NULL));
  _rand = 1 + rand() % ( Digit - 1 );	
  
  if( !((Digit > 2) && (Digit < 6)) )
    Digit = 4;  

  for( i = 0; i < Digit; i++ )
    gtkMoo[i] = 48 + Moo.popMachine();
  
  /*ASCII 0 = 48*/
  if( gtkMoo[0] == 48 )
  {
    gtkMoo[0] = gtkMoo[_rand];
    gtkMoo[_rand] = 48;
  }
  
  timerHandle = -1;
  timeTicks = 0;
  startSystemTime = 0;
  
  gtk_label_set_label( (GtkLabel*)statusLabel, "Ready! Start Guessing");
  startSystemTime = getCurrentTime () - timeTicks;
  timerHandle = g_timeout_add (100, timeout_callback, NULL);
    
  return gtkMoo;
}

void cheatMoo()
{
  char cheater[20];
  strcpy(cheater,"What a Shame: ");
  strcat(cheater, gtkMoo);
  g_source_remove (timerHandle);
  timerHandle = -1;
  timeTicks = 0;
  startSystemTime = 0;
  totalChances = 11;
  gtk_label_set_label( (GtkLabel*)statusLabel, (gchar*)cheater);
}

bool checkRepetition( char* mooGuess , int maxDig)
{
  int i, j;
  bool repFLAG = false;

  for( i = 0; i < maxDig; i++ )
    for( j = 0; j < maxDig; j++ )
    {
      if( i == j )
        continue;
	
      if( mooGuess[i] == mooGuess[j] )
        repFLAG = true;
    }

  return repFLAG;
}

gchar* checkMoo( char* mooGuess, gpointer textBox )
{
  gchar Bulls = 0, Cows = 0;
  unsigned int FLAG;
  unsigned int i, j;
  unsigned int mooDig = DIG;
  char* gtkMoo;
  static bool lessDig = true;
  
  gtkMoo = randMoo;
  textBox2 = (GtkWidget*)textBox;
  
  if( strlen(mooGuess) < mooDig )
  {
    lessDig = false;
    sprintf(result,"Enter a %d Digit No.", mooDig);
    gtk_label_set_label( (GtkLabel*)statusLabel, (gchar*)result);
    strcpy(result,"error");
    return result;
  }
  
  if( checkRepetition(mooGuess, mooDig) )
  {
    lessDig = false;
    gtk_label_set_label( (GtkLabel*)statusLabel, "Digits Repeated!");
    strcpy(result, "error");
    return result;
  }
  
  if(lessDig == false)
  {
    lessDig = true;
    gtk_label_set_label( (GtkLabel*)statusLabel, "Keep Guessing!");
  }

  for( i = 0; i < mooDig; i++ )
  {
    FLAG = i;
    if( mooGuess[i] == gtkMoo[i] )
      Bulls++;

    for( j = 0; j < mooDig; j++ )
    {
      if( j == FLAG )
        continue;
      if( mooGuess[j] == gtkMoo[i] )
        Cows++;  
    }
  }
  
  if( Bulls == (int) mooDig )
  {
    g_source_remove (timerHandle);
    timerHandle = -1;
    timeTicks = 0;
    startSystemTime = 0;
    gtk_label_set_label( (GtkLabel*)statusLabel, "You W!n:-)");
  }
  
  if( totalChances >= 9 )
  {
    strcpy(result, "Loser, It was: ");
    strcat(result, randMoo);
    gtk_label_set_label( (GtkLabel*)statusLabel, (gchar*)result);
    g_source_remove (timerHandle);
    timerHandle = -1;
    timeTicks = 0;
    startSystemTime = 0;
  }
	
  snprintf(result, 5, "%dB%dC", Bulls, Cows);

  return result;
}

int getCurrentTime()
{
  struct timeval tv;
  int ti, s, us;
  gettimeofday (&tv, NULL);
  s = tv.tv_sec % 100000;
  us = tv.tv_usec / 100000;
  ti = s * 10 + us;
  return ti;
}

gint timeout_callback(gpointer)
{
  static char buffer[20];
  char timerBuffer[10];
  //int h, m;
  int s, ss;

  timeTicks = (getCurrentTime () - startSystemTime);

  ss = timeTicks % 10;
  s = timeTicks / 10;
 // m = s / 60;
 // s = s % 60;
 // h = m / 60;
 // m = m % 60;
  if( totalChances > 9 )
    return FALSE;
  sprintf (timerBuffer, "%d.%d", s, ss);
  snprintf (buffer, 50, "Time Elapsed %ss", timerBuffer);
  gtk_label_set_text (GTK_LABEL (timeLabel), buffer);
  timeElapsed = atof(timerBuffer);
  return TRUE;
}
