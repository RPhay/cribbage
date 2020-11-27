// FILE:			card.h
//
// AUTHOR:		Ryan R. Phay
// LAST DATE:	March 4, 1998
//
// DESCRIPTION:
//		A card is an object that knows what it is (cardNumber) and whether it is showing
// or not showing (cardState).  Card values are stored in the order of Clubs, Diamonds,
// Hearts, and Spades, numbering from 1 through 52.  Card states are 0 = NOT_SHOWING and
// 1 = SHOWING.  A card also has a cardname, which is a string 20 bytes long (for example,
// a Card with cardNumber == 1 would have the cardName "Ace of Clubs").

#ifndef CARD_H
#define CARD_H

#include<iostream.h>

enum visibility {NOT_SHOWING, SHOWING};

class Card{

		friend ostream &operator<<(ostream &os, const Card &outputCard);
	
	public:
		Card();										// Gives Card a random value
  	    Card(const Card &otherCard);
		Card(int cardNum);						// Sets Cards cardNumber with state as showing
		Card(int cardNum, int showing);     // Creates new card as cardNumber with state info
		~Card(){	delete cardNameString;
					delete cardNumberString;
					delete cardSuitString;};

		const Card &operator=(const Card &otherCard);		// Copy function
		int operator==(const Card &otherCard) const;		// Equality function
		int operator!=(const Card &otherCard) const;		// Non-equality function
		int operator<=(const Card &otherCard) const;		// Less than or equal to fn
		int operator<(const Card &otherCard) const;			// Strictly less than fn

		inline void setCardNumber(int cardNum)
			{	if ((cardNum > 0) && (cardNum <= 53)) cardNumber = cardNum;
				createCardName();};
		inline void setCardState(int newState)
      	{if ((newState == 0) || (newState == 1)) cardState = newState;}; 

		int getCardBasicNumber();								// Returns an int from 1 thru 13
		inline int getCardNumber(){return cardNumber;}; // Returns an int from 1 thru 52
		inline int getCardState(){return cardState;};   // Returns SHOWING, NOT_SHOWING (1,0)
		int getCardSuit();										// Returns an int from 1 thru 4
		char *getCardNameString();								// Returns string of card's name
		char *getCardNumberString();							// Returns string of card's number
		char *getCardSuitString();								// Returns string of card's suit
     
	protected:
		int cardNumber, cardState;
		char *cardNameString, *cardNumberString, *cardSuitString;

	private:
		void createCardName();					// Sets the char * data members
};
#endif