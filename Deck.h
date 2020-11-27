// FILE:		deck.h
//
// AUTHOR:		Ryan R. Phay
// LAST DATE:	March 4, 1998
//
// DESCRIPTION:
//		A Deck is a Collection of Cards.  When in the standard, "I just bought
// this deck," state, there are 52 cards which are ordered numerically.  The
// decks two main functions are shuffle() and reset(), the latter which returns
// it to the initial state.
//
// NOTE: (4 now)
//		It is not intended that Cards be put back in a deck.  They can be, but
// the deck doesn't look at Cards being added and ask itself it's already got
// that card, so conceivably hundred of Aces could be added.  Therefore, great
// care must be used for anyone wishing to add a card.

#ifndef DECK_H
#define DECK_H

#include "CardCo~1.h"

class Deck : public CardCollection  
{
public:
	Deck();
	virtual ~Deck();

	void shuffle();			// Shuffle the existing Cards
	void reset();			// Put the deck in the "Brand New" state
};

#endif
