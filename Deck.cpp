// FILE:		deck.cpp
//
// AUTHOR:		Ryan R. Phay
// LAST DATE:	March 4, 1998
//
// DESCRIPTION:
//		A CardCollection is a collection of Cards.  These cards are linked
// together as a doubly linked list.  A CardCollection can be used as a stand
// alone, but it is suggested that it be used to parent other classes, such as
// a Deck or Poker Hand, etc.

#include "CardCo~1.h"
#include<stdlib.h>
#include<sys/timeb.h>
#include<time.h>
#include "Deck.h"

// Deck::Deck()----------------------------------------------------------------------
//		Creates a Brand New Deck with 52 cards which are in ascending order
// ----------------------------------------------------------------------------------
Deck::Deck(){
	srand(time(NULL));
	reset();
};

// Deck::~Deck()---------------------------------------------------------------------
//		Deallocates memory used by the Deck
// ----------------------------------------------------------------------------------
Deck::~Deck(){
	CardCollection::reset();
};

// Deck::reset()---------------------------------------------------------------------
//		Get rid of all the Cards in the Deck, then put the Deck in its initial Brand
// New state with 52 cards in ascending order
// ----------------------------------------------------------------------------------
void Deck::reset(){
	CardCollection::reset();
	for(int i = 1; i <= 52; i++){
		addCard(i);
	};
};


// void Deck::shuffle()--------------------------------------------------------------
//		Shuffle the Cards currently in the Deck (if there is more than 1 Card)
// ----------------------------------------------------------------------------------
void Deck::shuffle()
{
	int newSpot, oldSpot, noCards = numberOfCards;
	if(noCards > 1){
		Card temp;
		for(int i = 1; i <= (noCards * 4); i++){
			oldSpot = 1 + rand() % noCards;
			newSpot = 1 + rand() % (noCards - 1);
			if(oldSpot != newSpot){
				temp = removeCard(oldSpot);
				addCard(temp, newSpot);
			};
		};
	};
};
