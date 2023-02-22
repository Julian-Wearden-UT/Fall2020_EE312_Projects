// FILE: go_fish.cpp
// Main driver for go fish game
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "card.h"
#include "player.h"
#include "deck.h"
#include <fstream>  // Provides output to file
#include <string>

using namespace std;


// PROTOTYPES for functions:
void dealHand(Deck &d, Player &p, int numCards);
bool checkInitialBooks(Player &p);
void checkBooksMain(Player &p);
void showHandsBook(Player &p);
void showHandsBook(Player &p);
bool askPlayer(Player &p1, Player &p2, Deck &d);
bool checkEmptyHand(Player &p1, Player &p2, Deck &d);
bool isEmptyGame(Player &p1, Player &p2, Deck &d);
void winner(Player &p1, Player &p2);

static ofstream ofs("gofish_results.txt");  // File to output data to

int main( )
{
    int numCards = 5;
    // Create deck
    Deck d;
    // Shuffle deck
    d.shuffle();

    // Create 2 players
    Player p1("Player 1");
    Player p2("Player 2");

    // Deal 5 cards to each player
    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);
    //Show initial state of each player
    ofs << "Initial Cards Dealt:" << std::endl;
    showHandsBook(p1);
    showHandsBook(p2);
    ofs << std::endl;

    //Book any cards that can be booked from initial cards dealt
    ofs << "Book Initial Cards:" << std::endl;
    checkBooksMain(p1);
    checkBooksMain(p2);
    ofs << std::endl;

    // Do while there are still cards in the game
    while(!isEmptyGame(p1, p2, d)){
        // Show status of each player
        showHandsBook(p1);
        showHandsBook(p2);
        ofs << std::endl;

        // If hand is empty, get new card and skip turn
        if(checkEmptyHand(p1, p2, d)){}
        // Else ask player 2 for card until player 2 calls go fish
        else {
            bool foundCard = askPlayer(p1, p2, d);
            ofs << std::endl;
            // Do if it's still this player's turn since they got a card
            while (foundCard) {
                showHandsBook(p1);
                showHandsBook(p2);
                ofs << std::endl;
                if(checkEmptyHand(p1, p2, d)){break;}
                else{
                    foundCard = askPlayer(p1, p2, d);
                    ofs << std::endl;
                }
            }
        }

        // Only do if playable cards available
        if(!isEmptyGame(p1, p2, d)) {
            showHandsBook(p1);
            showHandsBook(p2);
            ofs << std::endl;
            // If hand is empty, get new card and skip turn
            if (checkEmptyHand(p2, p1, d)) {}
            // Else ask player 1 for card until player 1 calls go fish
            else {
                bool foundCard = askPlayer(p2, p1, d);
                ofs << std::endl;
                // Do if it's still this player's turn since they got a card
                while (foundCard) {
                    showHandsBook(p1);
                    showHandsBook(p2);
                    ofs << std::endl;
                    if(checkEmptyHand(p2, p1, d)){break;}
                    else{
                        foundCard = askPlayer(p2, p1, d);
                        ofs << std::endl;
                    }
                }
            }
        }
    }

    // Show final results of game
    ofs << "Results:" << std::endl;
    winner(p1, p2);
    // Close file
    ofs.close();
    // Print to terminal that program has ended
    cout << "Done writing result to gofish_results.txt" << std::endl;
    return EXIT_SUCCESS;
}

// Checks if no cards are left to play. True if game over, false if cards available.
bool isEmptyGame(Player &p1, Player &p2, Deck &d){
    if (d.size() <= 1 && p1.getHandSize() <= 0 && p2.getHandSize() <= 0){
        return true;
    }
    else{return false;}
}

// Checks if a player's hand is empty. Deals card to player and returns true if hand is empty. False if hand not empty.
bool checkEmptyHand(Player &p1, Player &p2, Deck &d){
    if (p1.getHandSize() <= 0 && !isEmptyGame(p1, p2, d)){
        Card cardName = d.dealCard();
        p1.addCard(cardName);
        ofs << p1.getName() << " has no cards, so " << p1.getName() << " draws a " << cardName;
        return true;
    }
    return false;
}

// Checks for multiple books in hand
void checkBooksMain(Player &p){
    bool moreLeft = checkInitialBooks(p);
    while(moreLeft){
        moreLeft = checkInitialBooks(p);
    }
}

// Search for pair in player's hand
bool checkInitialBooks(Player &p){
    for(int i = 0; i < p.getHandSize(); i++) {
        for (int j = 0; j < p.getHandSize(); j++) {
            if (j == i) {}  //Don't compare card to itself
            else {
                // If card 1 and card 2 form a book, add book and return true.
                Card card1 = p.chooseCardFromHand(i);
                Card card2 = p.chooseCardFromHand(j);
                bool bookFound = p.checkHandForBook(card1, card2);
                if (bookFound){
                    // Print to file when book is found
                    ofs << p.getName() << " books the " << card1.rankString(card1.getRank())<< std::endl;
                    return true;
                };
            }
        }
    }
    return false;
}

// Deal initial cards to each player
void dealHand(Deck &d, Player &p, int numCards){
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}

// Print hand and book of player
void showHandsBook(Player &p){
    if (p.getHandSize() == 0){ofs << p.getName() <<"'s hand : " << "<No Cards>" << std::endl;}  //If no cards in hand
    else{ofs << p.getName() <<"'s hand : " << p.showHand() << std::endl;}

    if (p.getBookSize() == 0){ofs << p.getName() <<"'s books : " << "<No Books>" << std::endl;} //If no books
    else{ofs << p.getName() <<"'s books : " << p.showBooks() << std::endl;}
}

// Player p1 asks player p2 for card. Returns true if card found. False if go fish.
bool askPlayer(Player &p1, Player &p2, Deck &d){
    if(isEmptyGame(p1, p2, d)){return false;} //Return false if game over
    Card chosenCard = p1.chooseCardFromHand();
    ofs << p1.getName() <<" asks - Do you have a " << chosenCard.rankString(chosenCard.getRank()) << "?" << std::endl;
    // Card found
    if (p2.rankInHand(chosenCard)){
        ofs << p2.getName() <<" says - Yes. I have a " << chosenCard.rankString(chosenCard.getRank()) << "." << std::endl;
        // Pass over all cards with that suit
        while(p2.rankInHand(chosenCard)) {
            Card remCard = p2.removeRankFromHand(chosenCard);
            p1.addCard(remCard);
        }
        // Book any cards
        checkBooksMain(p1);
        return true;
    }
    // Go Fish
    else{
        ofs << p2.getName() <<" says - Go Fish " << std::endl;
        //Draw new card
        if(d.size() > 0){   //Make sure deck isn't empty
            Card newCard = d.dealCard();
            ofs << p1.getName() << " draws " << newCard;
            p1.addCard(newCard);
            checkBooksMain(p1);
        }
        else{
            // Should never run, but for testing purposes
            ofs << "No Cards left in Deck" << std::endl;
        }
        return false;
    }
}

// Shows count of books and books for each player. Declares winner or tie.
void winner(Player &p1, Player &p2){
    // Print how many books each player had. Prints string of books.
    ofs << p1.getName() << " had " << (p1.getBookSize()/2) << " books: " << p1.showBooks() << std::endl;
    ofs << p2.getName() << " had " << (p2.getBookSize()/2) << " books: " << p2.showBooks() << std::endl;
    //Prints total number of books. Should always print 26 (Mainly for testing)
    ofs << "Total Books: " << (p1.getBookSize()/2) + (p2.getBookSize()/2) << std::endl;
    // If player 1 has more books, print player 1 wins.
    if (p1.getBookSize()/2 > p2.getBookSize()/2 ){
        ofs << p1.getName() << " wins! " << std::endl;
    }
    // If player 2 has more books, print player 2 win
    else if (p2.getBookSize()/2 > p1.getBookSize()/2 ){
        ofs << p2.getName() << " wins! " << std::endl;
    }
    // If player 1 and player 2 have same number of books, call it a tie;
    else if(p2.getBookSize()/2  == p1.getBookSize()/2){
        ofs << p1.getName() << " and " << p2.getName() << " tied! " << std::endl;
    }
}