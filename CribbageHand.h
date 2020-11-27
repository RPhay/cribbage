// FILE:		cribbagehand.h
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

#ifndef CRIGGABE_HAND_H
#define CRIBBAGE_HAND_H

#include "CardCo~1.h"

class CribbageHand : public CardCollection  
{
public:
	CribbageHand();
	virtual ~CribbageHand();

	int getScore();						// Calculate the score and return it
	int getTotalScore();				// Return hands total score as normal hand
	int getScoreAsPlayingField();		// Return score when seen as playing field
	
	char * getTotalScoreString();		// Return string representing total scoring
	char * getRunScoreString();			// Return string representing runs scoring
	char * getPairScoreString();		// Return string representing pairs scoring
	char * getFifteenScoreString();		// Return string representing 15's scoring
	virtual char * printCollection();	// Return string representing the hand

protected:
	char * runScoreString;				// See above
	char * pairScoreString;
	char * fifteenScoreString;
	char * totalScoreString;
	int totalScore;

private:
	void clearStrings();				// Frees memory used by strings
	int getScoreRuns();					// Gets score of this hands runs
	int getScorePairs();				// Gets score of this hands pairs
	int getScoreFifteens();				// Gets score of this hands 15's
};

#endif
