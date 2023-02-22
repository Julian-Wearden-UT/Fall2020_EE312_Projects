// FILE: deck.h
// written by Owen Astrachan, Roger Priebe and Michael Yang
// this class respresents a deck of cards
// When a Deck is constructed, it contains 52 cards
// in a "regular" order (aces, twos, threes, ... , kings)
//
// Shuffling a deck makes it consist of 52 cards in a random order
//
// dealCard() returns a card from the deck and decreases the
// number of cards in the deck (returned by size())
// The idea is that after shuffling, calling dealCard() 52 times
// returns each card in the deck after shuffling.
//
// Calling shuffle again replenishes the deck with 52 cards.


#ifndef _DECK_H
#define _DECK_H

#include <array>
#include "card.h"

using namespace std;

class Deck
{
  static constexpr int SIZE = 52;
  
  public:

    Deck();           // pristine, sorted deck

    void shuffle();   // shuffle the deck, all 52 cards present
    Card dealCard();   // get a card, after 52 are dealt, fail 

    int  size() const; // # cards left in the deck

  private:

    array<Card, SIZE> myCards;
    int myIndex;  // current card to deal
};

#endif
