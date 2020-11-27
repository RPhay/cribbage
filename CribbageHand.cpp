// FILE:		cribbagehand.cpp
//
// AUTHOR:		Ryan R. Phay
// LAST DATE:	March 4, 1998
//
// DESCRIPTION:
//		A CribbageHand is a CardCollection that can return the score calculated from
// the cards it contains.
//
// NOTE:  The scoring functionality has not been implimented, but returns random
// scores back to the caller!  Will be fixed at a later date!

#include<stdlib.h>
#include<string.h>
#include "Cribba~1.h"

// CribbageHand::CribbageHand()------------------------------------------------------
//		Create an empty CribbageHand
// ----------------------------------------------------------------------------------
CribbageHand::CribbageHand(){
	 getScore();
};

// CribbageHand::~CribbageHand()-----------------------------------------------------
//		Desctructor!!! ;-)~
// ----------------------------------------------------------------------------------
CribbageHand::~CribbageHand(){
	clearStrings();
	reset();
};

// SCORING FUNCITONS HAVE NOT BEEN WRITTEN--HENCE WE ARE KLUDGING DOG DOO HERE 4 NOW
// ADDMITTEDDLY THIS IS A MESS AND I CAN"T SPEEL WORTH GODDY VOODOO
// ----------------------------------------------------------------------------------
int CribbageHand::getScore(){
		fifteenScoreString = new char[2];
		pairScoreString = new char[2];
		runScoreString = new char[2];
		totalScoreString = new char[18];
	int s = 0;
	if(1 == 0){//numberOfCards == 0){  get rid until scoring functions correct
		delete fifteenScoreString;
		delete pairScoreString;
		delete runScoreString;
		delete totalScoreString;
		strcpy(fifteenScoreString, "");
		strcpy(pairScoreString, "");
		strcpy(runScoreString, "");
		strcpy(totalScoreString, "Score in hand is 0");
	}
	else{
		delete fifteenScoreString;
		delete pairScoreString;
		delete runScoreString;
		delete totalScoreString;
		fifteenScoreString = new char[20];
		pairScoreString = new char[20];
		runScoreString = new char[20];
		totalScoreString = new char[20];
		s = 1 + rand() % 20;
		char temp[3];
		itoa(s, temp, 10);
		strcpy(fifteenScoreString, "BS fifteens\n");
		strcpy(pairScoreString, "BS pairs\n");
		strcpy(runScoreString, "BS runs");
		strcpy(totalScoreString, fifteenScoreString);
		strcat(totalScoreString, pairScoreString);
		strcat(totalScoreString, runScoreString);
	};
// REMARKED OUT UNTIL THESE ARE WRITTEN PROPERLY	
//	else{
//		clearStrings();
//		s = getScoreFifteens();
//		s += getScorePairs();
//		s += getScoreRuns();
//	};
	return s;
};

// int CribbageHand::getScoreAsPlayingField()----------------------------------------
//		Score a hand as if it were the playing field.  The right most card on the
// field corresponds to the tail of the CardCollection!
// ----------------------------------------------------------------------------------
int CribbageHand::getScoreAsPlayingField(){
	
	return getScore();		// THIS LINE HERE UNTIL SCORING FUNCTIONS ARE WRITTEN!!!

	int s = 0;
	clearStrings();
	if(numberOfCards == 0){
		fifteenScoreString = new char[2];
		strcpy(fifteenScoreString, "");
		pairScoreString = new char[2];
		strcpy(pairScoreString, "");
		runScoreString = new char[2];
		strcpy(runScoreString, "");
		totalScoreString = new char[18];
		strcpy(totalScoreString, "Total score is 0");
	}
	else{
		//  ???  HOW THE HELL DO I DO THIS  ???	
	};
	return s;
};

// int CribbageHand::getScoreFifteens()----------------------------------------------
//		Finds all ways that the sum 15 can be made in the hand
// Returns the number of points the 15's are worth.
// ----------------------------------------------------------------------------------
int CribbageHand::getScoreFifteens(){
	int s = 0;
	if(numberOfCards > 1){
		
	}
	return s;
};

// int CribbageHand::getScorePairs()-------------------------------------------------
//		Finds all the ways that pairs can be made in the hand
// Returns the number of points the pairs are worth.
// ----------------------------------------------------------------------------------
int CribbageHand::getScorePairs()
{
	int s = 0, c[14], temp;
	for(int i = 0; i <= 14; i++)
		c[i] = 0;
	if(numberOfCards > 1){
		for(i = 1; i <= numberOfCards; i++){
			temp = getCard(i).getCardNumber();
			if((temp % 52) == 0){
				++(c[1]);
			}
			else if(temp == 53){
				// Don't do anything
			}
			else{
				++(c[temp]);
			};
		};
		
	}
	return s;
};

// int CribbageHand::getScoreRuns()--------------------------------------------------
//		Finds all the ways that runs can be made in the hand
// Returns the number of points the runs are worth.
// ----------------------------------------------------------------------------------
int CribbageHand::getScoreRuns(){
	int s = 0;
	if(numberOfCards > 1){
		
	}
	return s;
};

// char * CribbageHand::getFifteenScoreString()--------------------------------------
//		Returns the string associated with the 15's scoring
// ----------------------------------------------------------------------------------
char * CribbageHand::getFifteenScoreString(){
	return fifteenScoreString;
};

// char * CribbageHand::getPairScoreString()-----------------------------------------
//		Returns the string associated with the pairs scoring
// ----------------------------------------------------------------------------------
char * CribbageHand::getPairScoreString(){
	return pairScoreString;
};

// char * CribbageHand::getRunScoreString()------------------------------------------
//		Returns the string associated with the runs scoring
// ----------------------------------------------------------------------------------
char * CribbageHand::getRunScoreString(){
	return runScoreString;
};

// int CribbageHand::getTotalScore()-------------------------------------------------
//		Returns the total score of this hand
// ----------------------------------------------------------------------------------
int CribbageHand::getTotalScore(){
	return totalScore;
};

// char * CribbageHand::getTotalScoreString()----------------------------------------
//		Returns the string associated with the total score of this hand
// ----------------------------------------------------------------------------------
char * CribbageHand::getTotalScoreString(){
	return totalScoreString;
};

// void CribbageHand::clearStrings()-------------------------------------------------
//		Frees all the memory associated with the strings in this object
// ----------------------------------------------------------------------------------
void CribbageHand::clearStrings(){
	delete totalScoreString;
	delete fifteenScoreString;
	delete pairScoreString;
	delete runScoreString;
};

// char * CribbageHand::printCollection()--------------------------------------------
//		Overrides CardCollection::printCollection() to display the cards to return
// a string corresponding to the way a CribbageHand would be seen
// ----------------------------------------------------------------------------------
char * CribbageHand::printCollection(){
	if(numberOfCards == 0){
		delete collectionString;
		collectionString = new char[24];
		strcpy(collectionString, "No cards");
	}
	else{
		setCollectionString();
	};
	return collectionString;
};
