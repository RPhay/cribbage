//	FILE:		CribbageEngine.cpp
//
//	AUTHOR:		Ryan R. Phay
//
//	DESCRIPTION:
//		Refer to the UML diagrams as the CribbageEngine has not been documented yet

#include<time.h>
#include<stdlib.h>
#include"Card.h"
#include<String.h>
#include<ctype.h>
#include<iostream.h>
#include"CardCo~1.h"
#include"Cribba~2.h"

//		Creates a CribbageEngine state machine without a gui
//---------------------------------------------------------------------------------
CribbageEngine::CribbageEngine(){
	outputString = new char[320];
	gui = FALSE;
	gotoState0();
};

//		Creates a CribbageEngine state machine
// If isThisAGui == TRUE then gui is set to TRUE for proper compilation
//---------------------------------------------------------------------------------
CribbageEngine::CribbageEngine(int isThisAGui){
	outputString = new char[320];
	(isThisAGui > 0) ? gui = TRUE : gui = FALSE;
	gotoState0();
};

//		Destructor of the Universe!
//---------------------------------------------------------------------------------
CribbageEngine::~CribbageEngine(){
	delete outputString;
};

// NEEDS EXTRA STUFF FOR GUI:  "New game? (Y/N)"
//---------------------------------------------------------------------------------
int CribbageEngine::restartGame(){
	char a;
	int areYouSure = FALSE;
	strcpy(outputString, "New game? (Y/N) ");
	displayOutput();
	if(gui){
	}
	else{
		cin >> a;
		if(a == 'y' || a == 'Y')
			areYouSure = TRUE;
	}
	if(areYouSure)
		gotoState0();
	return areYouSure;
};

//		Displays output to the gui or stdout, depending on state of gui
//---------------------------------------------------------------------------------
int CribbageEngine::displayOutput(){
	if(gui){
		return messages.displayOutput(outputString);
	}
	else{
		cout << outputString;
	};
	return 1;
};

//		Used by the interface to pass a played card over to the engine.
//	Returns 1 means the card is acceptable
//  Returns 0 means the engine isn't in a state that is accepting cards
//---------------------------------------------------------------------------------
int CribbageEngine::playCard(int cardPosition){
	Card tempCard;
	int out = FALSE, c = currentState;
	if(cardPosition <= playersHand.getNumberOfCards())
		out = TRUE;
	if(out && ((c == 1) || (c == 2) || (c == 3) || (c == 4))){
		tempCard = playersHand.removeCard(cardPosition);
		playCard(tempCard);
	}
	else{
		out = FALSE;
	};
	return out;
};

// A CARD SHOULD NEVER GET HERE IF IT CANNOT BE PLAYED
// playCard(int cardPosition) checks this out first!
// currentState will be 1, 2, 3, or 4  OR we don't even get here!!!
//---------------------------------------------------------------------------------
void CribbageEngine::playCard(Card thisCard){
	while(isBusy);
	isBusy = TRUE;

	switch(currentState){
	case(1):
		gotoState2(thisCard);
		break;
	case(2):
		gotoState3(thisCard);
		break;
	case(3):
		gotoState4(thisCard);
		break;
	case(4):
		gotoState4(thisCard);
		break;
	}
	isBusy = FALSE;
};

// int CribbageEngine::quitGame()--------------------------------------------------
//
//	NEEDS GUI STUFF FOR "Quit? (Y/N)"
//
//---------------------------------------------------------------------------------
int CribbageEngine::quitGame(){
	char a;
	int areYouSure = FALSE;
	strcpy(outputString, "Quit? (Y/N) ");
	displayOutput();
	if(gui){
	}
	else{
		cin >> a;
		if(a == 'y' || a == 'Y')
			areYouSure = TRUE;
	}
	if(areYouSure){
		strcpy(outputString, "\n\nThank you for playing\n");
		strcat(outputString, "Cribbage for the Blind\n\n");
		strcat(outputString, "Quitting Game\n\n\n");
		displayOutput();

		deck.CardCollection::reset();
		resetCribHand();
		resetFieldHand();
		resetComputersHand();
		resetPlayersHand();
		currentState = 8;
	};
	return areYouSure;
};

//		Create a help string and display it
//---------------------------------------------------------------------------------
void CribbageEngine::getHelp(){
	strcpy(outputString, "Key Commands are\n");
	strcat(outputString, "My total points:  Control T\n");
	strcat(outputString, "Computers total points:  Control R\n");
	strcat(outputString, "Cards in my hand:  Control M\n");
	strcat(outputString, "Points in my hand:  Control N\n");
	strcat(outputString, "Cards in computers hand:  Control J\n");
	strcat(outputString, "Points in computers hand:  Control H\n");
	strcat(outputString, "Cards in crib:  Control C\n");
	strcat(outputString, "Points in Crib:  Control V\n");
	strcat(outputString, "Cards on field:  Control F\n");
	strcat(outputString, "See cut card:  Control D\n");
	strcat(outputString, "State of game:  Control S\n");
	strcat(outputString, "Repeat last message:  Control L\n");
	strcat(outputString, "Restart game:  Control P\n");
	strcat(outputString, "Quit playing:  Control Q\n");
	displayOutput();	
};

//		Resets the hands that are associated by the player
//---------------------------------------------------------------------------------
void CribbageEngine::resetPlayersHand(){
	playersHand.reset();
	tempPlayersHand.reset();
};

//		Resets the hands the are associated by the computer
//---------------------------------------------------------------------------------
void CribbageEngine::resetComputersHand(){
	computersHand.reset();
	tempComputersHand.reset();
};

//		Resets the hands that are associated with the field
//---------------------------------------------------------------------------------
void CribbageEngine::resetFieldHand(){
	fieldHand.reset();
	tempFieldHand.reset();
};

//		Resets the hands that are associated with the crib
//---------------------------------------------------------------------------------
void CribbageEngine::resetCribHand(){
	cribHand.reset();
	tempCribHand.reset();
};

// void CribbageEngine::resetDeck()------------------------------------------------
//		Put the deck in its original state
//---------------------------------------------------------------------------------
void CribbageEngine::resetDeck(){
	deck.reset();
};

// void CribbageEngine::showPlayersTotalPoints()-----------------------------------
//	Output the player's total points
//---------------------------------------------------------------------------------
void CribbageEngine::showPlayersTotalPoints(){
	char temp[3];
	itoa(playersPoints, temp, 10);
	strcpy(outputString, "You have ");
	strcat(outputString, temp);
	if(playersPoints == 1){
		strcat(outputString, " point\n");
	}
	else{
		strcat(outputString, " points\n");
	};
	displayOutput();
};

// void CribbageEngine::showComputersTotalPoints()---------------------------------
//	Output the computer's total points
//---------------------------------------------------------------------------------
void CribbageEngine::showComputersTotalPoints(){
	char temp[3];
	itoa(computersPoints, temp, 10);
	strcpy(outputString, "The computer has ");
	strcat(outputString, temp);
	if(computersPoints == 1){
		strcat(outputString, " point\n");
	}
	else{
		strcat(outputString, " points\n");
	};
	displayOutput();
};

// void CribbageEngine::showPlayersHand()------------------------------------------
//		Display cards held by the player
//---------------------------------------------------------------------------------
void CribbageEngine::showPlayersHand(){
	strcpy(outputString, "You are holding\n");
	strcat(outputString, playersHand.printCollection());
	strcat(outputString, "\n");
	displayOutput();
}


//		Displays the scoring in the players hand
//---------------------------------------------------------------------------------
void CribbageEngine::showPlayersHandPoints(){
	char temp[3];
	int score = playersHand.getScore();
	itoa(score, temp, 10);
	strcpy(outputString, "Your hand is worth ");
	strcat(outputString, temp);
	if(score == 1){
		strcat(outputString, " point\n");
	}
	else{
		strcat(outputString, " points\n");
	};
	strcat(outputString, playersHand.getTotalScoreString());
	strcat(outputString, "\n");
	displayOutput();
}

//		Displays the scoring in the computers hand
//---------------------------------------------------------------------------------
void CribbageEngine::showComputersHandPoints(){
	char temp[3];
	int score = computersHand.getScore();
	itoa(score, temp, 10);
	strcpy(outputString, "The computers hand is worth ");
	strcat(outputString, temp);
	if(score == 1){
		strcat(outputString, " point\n");
	}
	else{
		strcat(outputString, " points\n");
	};
	strcat(outputString, computersHand.getTotalScoreString());
	strcat(outputString, "\n");
	displayOutput();
}

//		Displays the computer's hand
//---------------------------------------------------------------------------------
void CribbageEngine::showComputersHand(){
	strcpy(outputString, "The computer is holding\n");
	strcat(outputString, computersHand.printCollection());
	strcat(outputString, "\n");
	displayOutput();
}

//		Displays the crib
//---------------------------------------------------------------------------------
void CribbageEngine::showCribHand(){
	strcpy(outputString, "The crib is holding\n");
	strcat(outputString, cribHand.printCollection());
	strcat(outputString, "\n");
	displayOutput();
}

//		Displays the points in the crib
//---------------------------------------------------------------------------------
void CribbageEngine::showCribPoints(){
	char temp[3];
	int score = cribHand.getScore();
	itoa(score, temp, 10);
	strcpy(outputString, "The crib is worth ");
	strcat(outputString, temp);
	if(score == 1){
		strcat(outputString, " point\n");
	}
	else{
		strcat(outputString, " points\n");
	};
	strcat(outputString, cribHand.getTotalScoreString());
	strcat(outputString, "\n");
	displayOutput();
};

//  LOOKS GOOD, BUT MAY BE BUGGY LATER WHEN THINGS START MESHING TOGETHER
//  MAIN QUESTION:  ARE CARDS BEING READ BACK IN THE CORRECT ORDER OF PLAY???
//---------------------------------------------------------------------------------
void CribbageEngine::showFieldHand(){
	Card tempCard;
	tempFieldHand.reset();
	int num = fieldHand.getNumberOfCards();
	fieldHand.gotoHead();
	for(int i = 1; i <= num; i++){
		tempCard = fieldHand.getCard();
		if(tempCard.getCardState() == SHOWING)
			tempFieldHand.addCard(tempCard);
	};
	strcpy(outputString, "Cards on the field are\n");
	strcat(outputString, tempFieldHand.printCollection());
	strcat(outputString, "\n");
	displayOutput();
};

//		Display the value of the cutCard
//---------------------------------------------------------------------------------
void CribbageEngine::showCutCard(){
	strcpy(outputString, "The cut card is the\n");
	strcat(outputString, cutCard.getCardNameString());
	strcat(outputString, "\n");
	displayOutput();
}

// !!! STATE 0 !!! STATE 0 !!! STATE 0 !!!
//---------------------------------------------------------------------------------
void CribbageEngine::gotoState0(){
	while(isBusy);
	isBusy = TRUE;			// Silly excuse for a semaphor, huh?

	dealer = -1;			// No dealer chosen for this game
	currentState = computersPoints = playersPoints = 0;

	deck.shuffle();

	cutCard.setCardState(NOT_SHOWING);

	dealer = rand() % 2;				// Set the dealer 1 = player, 0 = computer

	if(gui){
		table.showCribOwnership(0);
		table.showCutCard(cutCard);
	};
	
	strcpy(outputString, "Cribbage for the Blind\n");
	strcat(outputString, "Version 1.000.000.001\n");
	strcat(outputString, "By:  Ryan R Phay\n");
	strcat(outputString, "Copyright 1998\n\n");
	strcat(outputString, "Starting New Game\n\n");
	displayOutput();

	isBusy = FALSE;
	gotoState1();
};

// STATE 1 STATE 1 STATE 1
//---------------------------------------------------------------------------------
void CribbageEngine::gotoState1(){
	while(isBusy);
	isBusy = TRUE;
	
	currentState = 1;

	resetCribHand();
	resetFieldHand();
	resetPlayersHand();
	resetComputersHand();
	
	Card tempCard, tempCard2;
	for(int i = 1; i <= 6; i++){		// Dealing cards
		tempCard = deck.removeCard(1);
		tempCard2 = deck.removeCard(1);
		if(dealer){
			computersHand.addCard(tempCard);
			playersHand.addCard(tempCard2);
		}
		else{
			playersHand.addCard(tempCard);
			computersHand.addCard(tempCard2);
		};
	};
	tempPlayersHand = playersHand;
	tempComputersHand = computersHand;
	
	cutCard = deck.removeCard(1);
	cutCard.setCardState(NOT_SHOWING);

	for(i = 1; i <= 6; i++){
		computersHand.setCardState(i, NOT_SHOWING);
	};

// AI UNIT REMOVED -- TAKING OUT RANDOM CARDS INSTEAD!  -- WILL BE UPDATED LATER!

	i = 1 + rand() % 6;
	tempCard = computersHand.removeCard(i);
	cribHand.addCard(tempCard);
	i = 1 + rand() % 5;
	tempCard = computersHand.removeCard(i);
	cribHand.addCard(tempCard);

	if(gui){
		table.updatePlayersHand(playersHand);
		table.updateComputersHand(computersHand);
		table.updatePlayingField(cribHand);
		table.showCutCard(cutCard);
		table.showCribOwnership(0);

	};
	if(dealer){
		strcpy(outputString, "You are dealing\n\n");
	}
	else{
		strcpy(outputString, "Computer is dealing\n\n");
	};
	strcat(outputString, "You were dealt\n");
	strcat(outputString, playersHand.printCollection());
	strcat(outputString, "\n\n");
	strcat(outputString, "The computer adds two cards to crib\n\n");
	displayOutput();

	showCurrentState();
	isBusy = FALSE;
};

// STATE 2 STATE 2 STATE 2
//---------------------------------------------------------------------------------
void CribbageEngine::gotoState2(Card cribCard){
	//while(isBusy);		// WHY THE HELL WON"T THIS WORK IN THIS SPOT???
	isBusy = TRUE;
	currentState = 2;

	cribCard.setCardState(NOT_SHOWING);

	cribHand.addCard(cribCard);

	if(gui){
		table.updatePlayingField(cribHand);
		table.updatePlayersHand(playersHand);
	};

	strcpy(outputString, "Adding ");
	strcat(outputString, cribCard.getCardNameString());
	strcat(outputString, " to the crib\n\n");
	displayOutput();

	showCurrentState();

	isBusy = FALSE;
};

//---------------------------------------------------------------------------------
// STATE 3 STATE 3 STATE 3
//---------------------------------------------------------------------------------
void CribbageEngine::gotoState3(Card cribCard){
	//while(isBusy);	OR THIS SPOT???
	isBusy = TRUE;
	currentState = 3;

	cribCard.setCardState(NOT_SHOWING);

	cribHand.addCard(cribCard);

	cutCard.setCardState(SHOWING);
	
	if(gui){
		table.updatePlayingField(cribHand);
		table.updatePlayersHand(playersHand);
		table.updateComputersHand(computersHand);
		table.showCutCard(cutCard);
		if(dealer){
			table.showCribOwnership(1);
		}
		else{
			table.showCribOwnership(2);
		};
	};
	
	// ARE YOU SURE YOU WANT TO DISCARD???  IF NOT, PUT CARDS BACK AND GO BACK
	// ADD THIS LATER!

	strcpy(outputString, "Adding ");
	strcat(outputString, cribCard.getCardNameString());
	strcat(outputString, " to the crib\n\n");
	displayOutput();

	showCurrentState();

	isBusy = FALSE;
};

//---------------------------------------------------------------------------------
// RESPONSIBLE FOR GOING TO STATE 5 WHEN PLAYING IS DONE
// STATE 4 STATE 4 STATE 4
//---------------------------------------------------------------------------------
void CribbageEngine::gotoState4(Card playedCard){
	isBusy = TRUE;
	currentState = 4;
	isBusy = FALSE;
}

//---------------------------------------------------------------------------------
// STATE 5 STATE 5 STATE 5
//---------------------------------------------------------------------------------
void CribbageEngine::gotoState5(){
	isBusy = TRUE;
	currentState = 5;
	isBusy = FALSE;
}

//---------------------------------------------------------------------------------
// STATE 6 STATE 6 STATE 6
//---------------------------------------------------------------------------------
void CribbageEngine::gotoState6(){
	isBusy = TRUE;
	currentState = 6;
	isBusy = FALSE;
}

//---------------------------------------------------------------------------------
// STATE 7 STATE 7 STATE 7
//---------------------------------------------------------------------------------
void CribbageEngine::gotoState7(){
	isBusy = TRUE;
	currentState = 7;
	isBusy = FALSE;
}

//---------------------------------------------------------------------------------
//		Displays the current state of the game for the player (ie.  What do I do 
// next? is answered.)
//---------------------------------------------------------------------------------
void CribbageEngine::showCurrentState(){
	switch(currentState){
	case 0:
		strcpy(outputString, "The cards are now being delt\n");
		break;
	case 1:
		strcpy(outputString, "Discard first card into the crib\n");
		break;
	case 2:
		strcpy(outputString, "Discard second card into the crib\n");
		break;
	case 3:
		strcpy(outputString, "Play a card\n");
		break;
	case 4:
		strcpy(outputString, "Play a card\n");
		break;
	case 5:
		strcpy(outputString, "Counting first players points\n");
		break;
	case 6:
		strcpy(outputString, "Counting dealers points\n");
		break;
	case 7:
		strcpy(outputString, "Counting the crib\n");
		break;
	case 8:
		strcpy(outputString, "No game currently in progress\n");
		break;
	};
	displayOutput();
};

// void CribbageEngine::showLastMessage()------------------------------------------
//		Display the last message seen in the message window (or stdout for non-gui)
//---------------------------------------------------------------------------------
void CribbageEngine::showLastMessage(){
	displayOutput();
};

//---------------------------------------------------------------------------------
//		Gets input and decides what to do (play card, display message, etc.)
//	Valid Key Commands are as follows:
//		Shoe help file:					?
//		My total points:				T
//		Computers total points:			R
//		Cards in my hand:				M
//		Points in my hand:				N
//		Cards in computers hand:		J
//		Points in computers hand:		H
//		Cards in crib:					C
//		Points in Crib:					V
//		Cards on field:					F
//		See cut card:					D
//		State of game:					S
//		Repeat last message:			L
//		Restart game:					P
//		Quit playing:					Q
//		Select a card:					1 - 6
//---------------------------------------------------------------------------------
int CribbageEngine::keyboardInput(char in){
	int out = TRUE, n = atoi(&in);
	switch(tolower(in)){
	case '?':
		getHelp();
		break;
	case '1':
		out = playCard(n);
		break;
	case '2':
		out = playCard(n);
		break;
	case '3':
		out = playCard(n);
		break;
	case '4':
		out = playCard(n);
		break;
	case '5':
		out = playCard(n);
		break;
	case '6':
		out = playCard(n);
		break;
	case 'c':
		showCribHand();
		break;
	case 'd':
		showCutCard();
		break;
	case 'f':
		showFieldHand();
		break;
	case 'h':
		showComputersHandPoints();
		break;
	case 'j':
		showComputersHand();
		break;
	case 'l':
		showLastMessage();
		break;
	case 'm':
		showPlayersHand();
		break;
	case 'n':
		showPlayersHandPoints();
		break;
	case 'p':
		out = restartGame();
		break;
	case 's':
		showCurrentState();
		break;
	case 'q':
		out = quitGame();
		break;
	case 'r':
		showComputersTotalPoints();
		break;
	case 't':
		showPlayersTotalPoints();
		break;
	case 'v':
		showCribPoints();
		break;
	default:
		out = FALSE;
		break;
	};
	return out;
};