// FILE:		card.cpp
//
// AUTHOR:		Ryan R. Phay
// LAST DATE:	March 4, 1998
//
// See card.h for overall description.

#include<iostream.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"Card.h"

// ostream &operator<<(ostream &os, const Card &outputCard)--------------------------
//		Display the cardNameString of the given Card to the output stream.
// ----------------------------------------------------------------------------------
ostream &operator<<(ostream &os, const Card &outputCard){
	os <<  outputCard.cardNameString;
	return os;
};


// Card:: Card()---------------------------------------------------------------------
//		Default card constructor.  Creates a card with a random value.  The card is
// showing.
// ----------------------------------------------------------------------------------
Card::Card(){
	cardNameString = new char[25];
	cardNumberString = new char[7];
    cardSuitString = new char[9];
	cardNumber = 1 + rand() % 52;				// Set this.cardNumber randomly
	cardState = SHOWING;						// set cardSate to showing
	createCardName();							// setup cardName
};

// Card::Card(Card otherCard)--------------------------------------------------------
//		Copy constructor.
// ----------------------------------------------------------------------------------
Card::Card(const Card &otherCard){
	cardNameString = new char[25];
	cardSuitString = new char[9];
	cardNumberString = new char[7];
	*this = otherCard;
};

// Card::Card(int cardNum)-----------------------------------------------------------
//		Creates a card with the value cardNum.  The state is set to showing.
// NOTE:  If !(1 <= cardNum <= 52) then cardNumber is randomized
// ----------------------------------------------------------------------------------
Card::Card(int cardNum){
	cardNameString = new char[25];
	cardNumberString = new char[7];
    cardSuitString = new char[9];
	if((1 <= cardNum) && (cardNum <= 53)){
		cardNumber = cardNum;
	}
	else{
		cardNumber = 1 + rand() % 52;				// Set this.cardNumber randomly
	};
	cardState = SHOWING;								// set cardSate to showing
	createCardName();									// setup cardName
};

// Card::Card(int cardNum, int showing)----------------------------------------------
//		Creates a card with the value cardNum.  The state is set to showing.
// NOTE:  If !(1 <= cardNum <= 52) then cardNumber is randomized.
//			 If !(showing == SHOWING || showing == NOT_SHOWING) then cardState = SHOWING
// ----------------------------------------------------------------------------------
Card::Card(int cardNum, int showing){
	cardNameString = new char[25];
	cardNumberString = new char[7];
    cardSuitString = new char[9];

	if((1 <= cardNum) && (cardNum <= 53)){
		cardNumber = cardNum;
	}
	else{
		cardNumber = 1 + rand() % 52;				// Set this.cardNumber randomly
	};
   if((showing == SHOWING) || (showing == NOT_SHOWING)){
		cardState = showing;							// set cardSate to showing
	}
	else{
		cardState = SHOWING;
   };
	createCardName();									// setup cardName
};

// void Card::operator=(const Card otherCard)----------------------------------------
//		Copy the values of otherCard into this.
// ----------------------------------------------------------------------------------
const Card &Card::operator=(const Card &otherCard){
	this->cardNumber = otherCard.cardNumber;
	this->cardState = otherCard.cardState;
	strcpy(this->cardNameString, otherCard.cardNameString);
	strcpy(this->cardSuitString, otherCard.cardSuitString);
	strcpy(this->cardNumberString, otherCard.cardNumberString);
	return *this;
};


// void Card::operator==(const Card otherCard) const---------------------------------
//		Checks to see if the cardNumber of this and otherCard are equal.
// ----------------------------------------------------------------------------------
int Card::operator==(const Card &otherCard) const{
	return (cardNumber == otherCard.cardNumber) ? 1 : 0;
};

int Card::operator!=(const Card &otherCard) const{
	return !(*this == otherCard);
};

int Card::operator<=(const Card &otherCard) const{
	return (cardNumber <= otherCard.cardNumber) ? 1 : 0;
};

int Card::operator<(const Card &otherCard) const{
	return (cardNumber < otherCard.cardNumber) ? 1 : 0;
};


// int Card::getCardSuit()-----------------------------------------------------------
//		Returns a value from 0 to 4
// 0 = N/A
// 1 = Clubs	   2 = Diamonds
// 3 = Hearts      4 = Spades
// ----------------------------------------------------------------------------------
int Card::getCardSuit(){
	int temp = 1;
	if(cardNumber > 13)	++temp;
	if(cardNumber > 26)	++temp;
	if(cardNumber > 39) ++temp; 
	if(cardNumber == 53) temp = 0;
   return temp;
};

// int Card::getCardBasicNumber()----------------------------------------------------
//		Returns the basic number that a card would be interpretted as by a human.
// For instance, an Ace of Spades and an Ace of Hearts are both considered a 1.
// A King is considered 13.  And so on.  0 = Joker
// ----------------------------------------------------------------------------------
int Card::getCardBasicNumber(){
	int temp = cardNumber % 13;
	if(cardNumber == 0) ++temp;
	if(cardNumber == 53) temp = 0;
   return temp;
};

// void Card::createCardName()-------------------------------------------------------
//		Creates a string expression representing the card which is stored in cardName.
// ----------------------------------------------------------------------------------
void Card::createCardName(){
	if(cardNumber != 53){
		switch(getCardBasicNumber()){
			case 1:   strcpy(cardNumberString, "Ace"); break;
			case 2:   strcpy(cardNumberString, "Two"); break;
			case 3:   strcpy(cardNumberString, "Three"); break;
			case 4:   strcpy(cardNumberString, "Four"); break;
			case 5:   strcpy(cardNumberString, "Five"); break;
			case 6:   strcpy(cardNumberString, "Six"); break;
			case 7:   strcpy(cardNumberString, "Seven"); break;
			case 8:   strcpy(cardNumberString, "Eight"); break;
			case 9:   strcpy(cardNumberString, "Nine"); break;
			case 10:  strcpy(cardNumberString, "Ten"); break;
			case 11:  strcpy(cardNumberString, "Jack"); break;
			case 12:  strcpy(cardNumberString, "Queen"); break;
			case 0:   strcpy(cardNumberString, "King"); break;
			default:  strcpy(cardNumberString, "Bug!"); break;
		};
		switch(getCardSuit()){
			case 1: 	strcpy(cardSuitString, "Clubs"); break;
			case 2:  strcpy(cardSuitString, "Diamonds"); break;
			case 3:	strcpy(cardSuitString, "Hearts"); break;
			case 4:  strcpy(cardSuitString, "Spades"); break;
		};
		strcpy(cardNameString, cardNumberString);
		strcat(cardNameString, " of ");
		strcat(cardNameString, cardSuitString);
	}
	else{
		strcpy(cardNumberString, "Joker");
		strcpy(cardSuitString, "Jokers");
		strcpy(cardNameString, "Joker of Jokers");
	};
};

// char * Card::getCardNameString()--------------------------------------------------
// 	Returns a string corresponding to this card's Name (Ex:  "King of Spades")
// ----------------------------------------------------------------------------------
char * Card::getCardNameString(){
	return cardNameString;

}

// char * Card::getCardSuitString()--------------------------------------------------
// 	Returns a string corresponding to the suit
// ----------------------------------------------------------------------------------
char * Card::getCardSuitString(){
	return cardSuitString;
}

// char * Card::getCardNumberString()------------------------------------------------
// 	Returns a string corresponding to this card's number
// ----------------------------------------------------------------------------------
char * Card::getCardNumberString(){
	return cardNumberString;
}
