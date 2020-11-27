// FILE:		cardcollection.cpp
//
// AUTHOR:		Ryan R. Phay
// LAST DATE:	March 4, 1998
//
// DESCRIPTION:
//		See cardcollection.h for overall description.

#include "Card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include "CardCo~1.h"

// ostream &operator<<(ostream &os, CardCollection &outputCollection)----------------
//		Sends a CardCollection to an ostream
// ----------------------------------------------------------------------------------
ostream &operator<<(ostream &os, CardCollection &outputCollection){
	outputCollection.setCollectionString();
	os << outputCollection.collectionString;
	return os;
};


// CardCollection::CardCollection()--------------------------------------------------
//		Creates an empty CardCollection
// ----------------------------------------------------------------------------------
CardCollection::CardCollection(){
	joker.setCardNumber(53);
	numberOfCards = 0;
	head = tail = current = NULL;
	collectionString = new char[1];
}

// CardCollection::CardCollection(CardCollection rightCollection)--------------------
//		Copy constructor
// ----------------------------------------------------------------------------------
CardCollection::CardCollection(CardCollection &rightCollection){
	joker.setCardNumber(53);
	collectionString = new char[1];
	this->operator=(rightCollection);
}

// CardCollection::~CardCollection()-------------------------------------------------
//		Delete all the nodes in this collection
// ----------------------------------------------------------------------------------
CardCollection::~CardCollection(){
	reset();
	delete collectionString;
}

// int CardCollection::isEmpty()-----------------------------------------------------
//		Returns 1 if this Collection is empty, 0 otherwise
// ----------------------------------------------------------------------------------
int CardCollection::isEmpty(){
	return (numberOfCards == 0) ? 1 : 0;
}

// int CardCollection::getNumberOfCards()--------------------------------------------
//		Returns the numberOfCards in this Collection
// ----------------------------------------------------------------------------------
int CardCollection::getNumberOfCards(){
	return numberOfCards;
}

// void CardCollection::addCard(Card card)-------------------------------------------
//		Insert a Card into this Collection after the current position
// ----------------------------------------------------------------------------------
void CardCollection::addCard(Card card){
	CardCollectionNode *newNode;
	newNode = new CardCollectionNode;
	newNode->thisCard = card;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	if(numberOfCards == 0){
		head = tail = current = newNode;
	}
	else if(current == tail){
		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = NULL;
		current = tail = newNode;
	}
	else{
		newNode->next = current->next;
		newNode->prev = current;
		current->next->prev = newNode;
		current->next = newNode;
		current = newNode;
	};
	++numberOfCards;
}

// void CardCollection::addCard(int cardNumber)--------------------------------------
//		Create a Card using cardNumber and add it to the Collection at
// the current position
// ----------------------------------------------------------------------------------
void CardCollection::addCard(int cardNumber){
	Card newCard(cardNumber);
	addCard(newCard);
}

// void CardCollection::gotoHead()---------------------------------------------------
//		Move the current pointer to the head of this Collection
// ----------------------------------------------------------------------------------
void CardCollection::gotoHead(){
	current = head;
}

// void CardCollection::gotoTail()---------------------------------------------------
//		Move the current pointer to the tail of this Collection
// ----------------------------------------------------------------------------------
void CardCollection::gotoTail(){
	current = tail;
}

// void CardCollection::gotoNext()---------------------------------------------------
//		Move the current pointer to the next Node in this Collection
// ----------------------------------------------------------------------------------
void CardCollection::gotoNext(){
	if(current != tail)
		current = current->next;
}

// void CardCollection::gotoPrev()---------------------------------------------------
//		Move the current pointer to the previous Node in this Collection
// ----------------------------------------------------------------------------------
void CardCollection::gotoPrev(){
	if(current != head)
		current = current->prev;
}

// char * CardCollection::printCollection()------------------------------------------
//		Print the collection to stdout
// ----------------------------------------------------------------------------------
char * CardCollection::printCollection(){
	setCollectionString();
	return collectionString;
}

// void CardCollection::setCollectionString()----------------------------------------
//		Sets collectionString by going through the Cards currently in the Collection
// and updating the string to match
// ----------------------------------------------------------------------------------
void CardCollection::setCollectionString(){

	if(numberOfCards == 0){
		delete collectionString;
		collectionString = new char[24];
		strcpy(collectionString, "No cards in collection");
	}
	else{
		delete collectionString;
		collectionString = new char[numberOfCards * 24];
		CardCollectionNode *temp;
		temp = head;
		strcpy(collectionString, temp->thisCard.getCardNameString());
		temp = temp->next;
		while(temp != NULL){
			strcat(collectionString, "\n");
			strcat(collectionString, temp->thisCard.getCardNameString());
			temp = temp->next;
		};
	};
}

// int CardCollection::gotoPosition(int position)------------------------------------
//		Move the current pointer to point at the Node at position
// ----------------------------------------------------------------------------------
int CardCollection::gotoPosition(int position){
	if((position > numberOfCards) || (position <= 0)){
		return 0;
	}
	else{
		current = head;
		--position;
		while(position > 0){
			current = current->next;
			--position;
		};
	};
	return 1;
}

// Card CardCollection::getCard()----------------------------------------------------
//		Returns the value of the Card at the current position
// ----------------------------------------------------------------------------------
Card CardCollection::getCard(){
	return current->thisCard;
}

// Card CardCollection::getCard(int position)----------------------------------------
//		Returns the value of the Card at position
// NOTE:  Joker is returned when position is out of bounds
// ----------------------------------------------------------------------------------
Card CardCollection::getCard(int position){
	if(gotoPosition(position)){
		return getCard();
	}
	else{
		return joker;
	};
};

// Card CardCollection::removeCard()-------------------------------------------------
//		Returns and removes the Card at the current position
// ----------------------------------------------------------------------------------
Card CardCollection::removeCard(){
	Card temp;

	if(numberOfCards == 0){
		temp = joker;
	}
	else if((current != head) && (current != tail)){
		CardCollectionNode *tempPointer;
		tempPointer = current;
		temp = current->thisCard;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		current = current->next;
		delete tempPointer;
		--numberOfCards;
	}
	else if((current == head) && (current == tail)){
		temp = current->thisCard;
		delete current;
		head = tail = current = NULL;
		numberOfCards = 0;
	}
	else if(current == head){
		temp = current->thisCard;
		current = current->next;
		head = current;
		delete current->prev;
		current->prev = NULL;
		--numberOfCards;
	}
	else if(current == tail){
		temp = current->thisCard;
		current = current->prev;
		tail = current;
		delete current->next;
		current->next = NULL;
		--numberOfCards;
	};
	return temp;
}

// Card CardCollection::removeCard(int position)-------------------------------------
//		Returns and removes the value of the Card at position
// NOTE:  Joker is returned when position is out of bounds
// ----------------------------------------------------------------------------------
Card CardCollection::removeCard(int position){
	if(gotoPosition(position)){
		return removeCard();
	}
	else{
		return joker;
	};
}

// void CardCollection::reset()------------------------------------------------------
//		Resets the Collection to its initial empty state
// ----------------------------------------------------------------------------------
void CardCollection::reset(){
	if(numberOfCards != 0){
		CardCollectionNode *temp;
		temp = current = head;
		while(temp != NULL){
			temp = temp->next;
			delete current;
			current = temp;
		};
		numberOfCards = 0;
		delete collectionString;
		collectionString = new char[24];
		strcpy(collectionString, "No cards in collection");
	};
}

// void CardCollection::addCard(Card newCard, int position)--------------------------
//		Add a Card at the indicated position
// ----------------------------------------------------------------------------------
void CardCollection::addCard(Card newCard, int position){
	Card temp;
	int noCards = numberOfCards;
	gotoPosition(position);
	if(noCards <= 0){
		addCard(newCard);
	}
	else if(((position == 1) && (noCards >= 1))){
		addCard(newCard);
		gotoHead();
		temp = removeCard();
		addCard(temp);
	}
	else if((current == tail) && (noCards < position)){
		addCard(newCard);
	}
	else if((position <= 1) && (noCards > position)){
		gotoHead();
		addCard(newCard);
		gotoHead();
		temp = removeCard();
		addCard(temp);
	}
	else{
		addCard(newCard);
		gotoPrev();
		temp = removeCard();
		addCard(temp);
	};
};

// void CardCollection::sort()-------------------------------------------------------
//		Sort this Collection.  The Collection is sorted using the Card number values
// of 1 thru 53, where it is sorted in ascending order.  Inheriting classes should
// consider whether they want to create their own sort function.
// ----------------------------------------------------------------------------------
void CardCollection::sort()
{
	if(numberOfCards > 1){
		int i, j, moveFrom, noCards = numberOfCards;
		Card temp1, temp2;
		for(i = 1; i < noCards; i++){
			temp1 = getCard(i);
			temp2 = getCard(moveFrom = (i + 1));
			for(j = (i + 1); j <= noCards; j++){
				if(getCard(j) < temp2){
					temp2 = getCard(j);
					moveFrom = j;
				};
			};
			if(temp2 < temp1){
				addCard(removeCard(moveFrom), i);
			};
		};
	};
}

// CardCollection& CardCollection::operator =(CardCollection & otherCollection)------
//		Equality operator for CardCollections
// ----------------------------------------------------------------------------------
CardCollection& CardCollection::operator =(CardCollection & otherCollection)
{
	CardCollection::reset();
	if(otherCollection.numberOfCards > 0){
		otherCollection.gotoHead();
		for(int i = 1; i <= otherCollection.numberOfCards; i++){
			addCard(otherCollection.getCard());
			otherCollection.gotoNext();
		};
	};
	return *this;
}

// void CardCollection::addCard(int cardNo, int position)----------------------------
//		Create a card using cardNo and insert it at position
// ----------------------------------------------------------------------------------
void CardCollection::addCard(int cardNo, int position)
{
	Card temp(cardNo);
	addCard(temp, position);
}

// void CardCollection::setCardStates(int position, visibility cardState)------------
//		Set the state of a card (SHOWING vs. NOT_SHOWING) at position
// ----------------------------------------------------------------------------------
void CardCollection::setCardState(int position, visibility cardState)
{
	if(position > 0 && position <= numberOfCards){
		gotoPosition(position);
		current->thisCard.setCardState(cardState);
	};
};
