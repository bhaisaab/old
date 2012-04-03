/*
  carousel.h
  
  Part of GtkMoo: Bulls n Cows in Gtk+
  Copyright (C) 2008-2010  Rohit Yadav

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

#ifndef __CAROUSEL__H
#define __CAROUSEL__H

#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

int A = 389,C = 1972;
int SEED = 216, SIZE = 9145;

int qrand()
{
	/*Its the LCG Generator*/
	SEED = fabs( ( A * SEED + C) % SIZE );
	SIZE =  ( SIZE * A + C ) % 100000;

	return SEED;
}

void qseed(int seed)
{
	SEED = seed;
}

class digits
{
	public:
			short int digit[10];
			bool mask[10];
			unsigned short int total; 

			digits()
			{
				makeFresh();
			}
			void makeVoid( int index )
			{
				mask[index] = false;
				makeShift( index );
				total--;
				if( total == 0 )
					makeFresh();
				return;
			}
			void makeShift( int index )
			{
				int i;
				for( i = index; i < total; i++ )
					digit[i] = digit[i+1];

				return;
			}
			void makeFresh()
			{
				int i;
				for( i = 0; i < 10; i++)
				{
					digit[i] = i;
					mask[i] = true;	
				}
				total = 10;
				return;
			}
};

struct snowNode
{
	int field;
	snowNode* left;
	snowNode* right;
};

/**********************************************************   
 ******** Carousel Queue: My Data Structure is like *******  
 ******** ============== a rotating carousel with   *******
 ******** packets of <0-9 digits> information on    *******  
 ******** the conveyer belt, the popMachine() pops  *******   
 ******** some packets and also pushes them at rear *******
 ******** end, random number of times thus popping  *******
 ******** generating random numbers.                *******
 ******** UTILITY: Always generates random numbers  *******
 ******** with different Digits.                    *******
 **********************************************************
 ********            © Rohit Yadav, 2008            *******
 ********            ALL RIGHTS RESERVED.           *******
 **********************************************************
 **********************rohityadav.in***********************
 **********************************************************/

class Carousel
{
	private:
			struct snowNode *FRONT;
			struct snowNode *REAR;
			int totalPackets;
			digits dj;
	public:
			int pop();
			void push( int );
			void init();
			int popMachine();
			Carousel()
			{	
				FRONT = NULL;
				REAR  = NULL;
				init();
			}
};

void Carousel::init()
{
	int i, ran;
	int MAX = 10;
	
	qseed((int)clock());
	
	/*-->snow, drop and flake are temporary pointers*/	
	struct snowNode *snow, *drop, *flake;

	if( FRONT != NULL )
	{
		snow = FRONT;
		while( snow->right != REAR )
		{
			snow = snow->right;
			free(snow->left);
		}
		free(snow->right);
	}
	
  flake = ( snowNode* )malloc( sizeof( snowNode) );
	drop = flake;
	
	totalPackets = MAX;
	
	for( i = 0; i < 10; i++ )
	{
		snow = ( snowNode* )malloc( sizeof(snowNode) );
		snow->left   = flake;
		flake->right = snow;
		
		ran = qrand() % (dj.total);
		snow->field = dj.digit[ran];
		dj.makeVoid(ran);
		
		flake = snow;
	}
	
	FRONT = drop->right; 
	REAR  = flake;
	
	FRONT->left = REAR;
	REAR->right = FRONT;
}
/*-------------------------------------------*\ 
 *    Push on Front end, Pop on Rear end     *
 *      So amazing with carousel queues      *  
\*-------------------------------------------*/

int Carousel::pop()
{
	int snowDrop = FRONT->field;
	
	FRONT = FRONT->right;
	free(FRONT->left);
	REAR->right = FRONT;
	FRONT->left = REAR;
	totalPackets--;
	
	return snowDrop;
}

void Carousel::push( int snowBoard )
{
	struct snowNode* flake;
	flake = ( struct snowNode* )malloc( sizeof(snowNode) );
	
	flake->left = REAR;
	flake->right = FRONT;
	
	FRONT->left = flake;
	
	REAR->right = flake;
	REAR = flake;
	
	REAR->field = snowBoard;
	totalPackets++;
	
	return ;
}

int Carousel::popMachine()
{
	int snowPopper, i = 0;
	int ticket;

	if(totalPackets == 2)
		init();

	ticket = qrand() % 81;
	
	for( i = 0; i <= ticket; i++ )
	{
		snowPopper = pop();
		push( snowPopper );
	}
	
	snowPopper = pop();
	
	return snowPopper;
}

#endif // #define __CAROUSEL__H
