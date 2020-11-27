// FILE:		Cribbage.cpp
//
// AUTHOR:		Ryan R. Phay
//
// DESCRIPTION:
//		This is the driver for the CribbageEngine when compiled for a text-only environment

#include<stdio.h>
#include<stdlib.h>
#include<iostream.h>
#include<process.h>
#include"Cribba~2.h"

void main(void){
	Deck deck;
	deck.shuffle();
	CribbageEngine myGame;
	char a;
	int i;
	while(TRUE){
		cin >> a;
		i = myGame.keyboardInput(a);
		if((i == 1) && (a == 'q'))
			exit(1);
		if(i != 1)
			cout << "Not a valid option or play!\a\n";
	};
};
