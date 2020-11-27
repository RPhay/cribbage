// FILE:		CribbageEngine.h
//
// AUTHOR:		Ryan R. Phay
//
// DESCRIPTION:
//		See the UML diagrams for description as this has not been documented worth beans!


#ifndef CRIBBAGE_ENGINE_H
#define CRIBBAGE_ENGINE_H

#include"Cribba~1.h"
#include "Deck.h"
#include "Card.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// REM OUT BELOW IF GUI BASED SYSTEM !!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class MessageWindow{
public:
	int displayOutput(const char *bob){ return 1;};
};
class PlayingArea{
public:
	int updatePlayersHand(CribbageHand bob){return 1;};
	int updateComputersHand(CribbageHand bob){return 1;};
	int updatePlayingField(CribbageHand bob){return 1;};
	int showCribOwnership(int i){return 1;};
	int showCutCard(Card cutCard){return 1;};
};
class Board{
public:
	int incPlayersPoints(int i){return 1;};
	int incComputersPoints(int i){return 1;};
};
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// REM OUT ABOVE IF GUI BASED SYSTEM !!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


enum state {FALSE, TRUE};

class CribbageEngine  
{
public:
	CribbageEngine();					// Creates a Cribbage game (no gui)
	CribbageEngine(int isThisAGui);		// Creates a Cribbage game with/without a gui
	~CribbageEngine();

	int playCard(int cardPosition);		// Used by driver to play a card
	int keyboardInput(char in);			// Used by driver for keyboard input

private:
	int quitGame();						// End the current game
	int restartGame();					// Restarts the game
	void getHelp();						// Displays a help file to message window

	void playCard(Card thisCard);		// Used by engine to play card

	void resetDeck();					// Resets the deck to original 52 card state
	void resetCribHand();				// Empties crib & tempCrib hands
	void resetFieldHand();				// Empties field & tempField hands
	void resetComputersHand();			// Empties computer & tempComputer hands
	void resetPlayersHand();			// Empties player & tempPlayer hands

	int displayOutput();				// Display output to the message window

	Deck deck;							// Deck used to deal cards
	Card cutCard;						// Storage for the cut card
	state isBusy, gui;					// Semi-semaphore for states used in gui's
										// gui = 1 = "Yes, this is being compiled for a gui"
	// Following are the CribbageHands needed by the engine during game play
	CribbageHand cribHand, computersHand, fieldHand, playersHand;
	CribbageHand tempCribHand, tempComputersHand, tempPlayersHand, tempFieldHand;

	// Points are for the players, currentState keeps the state of the state machine,
	// cutCardState may or may not be used (???), and dealer tells use who is dealing
	// (-1 = no dealer yet, 0 = computer is dealing, 1 = player is dealing)
	int computersPoints, playersPoints, currentState, cutCardState, dealer;
	char * outputString;				// Stores any output going to the message window

	MessageWindow messages;				// Stuff
	Board board;						//		For
	PlayingArea table;					//			Gui compilations

protected:
	void gotoState0();					// These functions are the state machine's
	void gotoState1();					// responsibilities for states 0 - 7.
	void gotoState2(Card cribCard);		// State 8 = "No game in progress" which
	void gotoState3(Card cribCard);		// Needs no functionality
	void gotoState4(Card playedCard);
	void gotoState5();
	void gotoState6();
	void gotoState7();

// The following functions return strings associated to what they say.
// In other words, figure it out ;)
	void showCutCard();			
	void showFieldHand();
	void showCribPoints();
	void showCribHand();
	void showLastMessage();				
	void showComputersHand();
	void showComputersHandPoints();
	void showPlayersHand();
	void showPlayersHandPoints();
	void showComputersTotalPoints();
	void showPlayersTotalPoints();
	void showCurrentState();
};

#endif
