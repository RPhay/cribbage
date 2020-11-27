// FILE:		cardcollection.h
//
// AUTHOR:		Ryan R. Phay
// LAST DATE:	March 4, 1998
//
// DESCRIPTION:
//		A CardCollection is a collection of Cards.  These cards are linked
// together as a doubly linked list.  A CardCollection can be used as a stand
// alone, but it is suggested that it be used to parent other classes, such as
// a Deck or Poker Hand, etc.

#ifndef CARD_COLLECTION_H
#define CARD_COLLECTION_H

#include"Card.h"
#include<stdio.h>
#include<iostream.h>

// The following structure is used for
// storing each Card's relative position
// as a Node in the Collection
struct CardCollectionNode{
	Card thisCard;							// Value of the card in this Node
	CardCollectionNode *next, *prev;		// Pointers to next and previous Nodes
};

class CardCollection{

	friend ostream &operator<<(ostream &os, CardCollection &outputCollection);

public:
	CardCollection(CardCollection &rightCollection);
	void addCard(int cardNo, int position);
	CardCollection& operator=(CardCollection &otherCollection);
	CardCollection();
	virtual ~CardCollection();

	int isEmpty();							// Returns 1 if the Collection is empty
	int getNumberOfCards();					// Returns numberOfCards in the Collection

	void addCard(int cardNumber);			// Creates and adds Card at the current position
	void addCard(Card newCard);				// Adds a Card at the current position
	void addCard(Card newCard, int position);	// Adds a Card at the indicated position
	Card getCard(int position);				// Returns the Card at the indicated position
	Card getCard();							// Returns the Card at the current position
	Card removeCard(int position);			// Removes & returns the Card at the indicated position
	Card removeCard();						// Removes & returns the Card at the current position

	void setCardState(int position, visibility cardState); // Set state of card at position
	
	void gotoPrev();						// Moves current to the previous card
	void gotoNext();						// Moves current to the next card
	void gotoTail();						// Moves current to the tail of the Collection
	void gotoHead();						// Moves current to the head of the Collection
	int gotoPosition(int position);			// Moves current to the indicated position

	virtual void sort();					// Sorts the list by cardNumber values 1 - 52
	virtual void reset();					// Clears the Collection
	virtual char * printCollection();		// Returns a string representing the Cards in the Collection

protected:
	char * collectionString;				// String representing the Cards in the Collection
	Card joker;								// Card returned only on errors
	int numberOfCards;						// Number of Cards in the Collection
	void setCollectionString();				// Maintains collectionString's correctness

private:
	CardCollectionNode * head, * tail, * current;	// Pointers to the head, tail and current nodes

};

#endif
