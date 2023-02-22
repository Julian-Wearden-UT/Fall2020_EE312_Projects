#include "deck.h"

// pristine, sorted deck
Deck::Deck(){
    myIndex = 0;
    Card::Suit suit[4] = {Card::spades, Card::hearts, Card::diamonds, Card::clubs};
    for(int j = 1; j <= 13; j++) {
        for(auto & i : suit) {
            myCards[myIndex] = Card(j, i);
            myIndex ++;
        }
    }
}

// shuffle the deck, all 52 cards present
void Deck::shuffle(){
    if (myCards.empty()){
        Deck();
    }
    myIndex = 0;
    srand((unsigned) time(0));
    while (myIndex < SIZE){
        int randomVal = rand() % SIZE;
        Card temp = myCards[randomVal];
        myCards[randomVal] = myCards[myIndex];
        myCards[myIndex] = temp;
        myIndex++;
    }
}
// get a card, after 52 are dealt, fail
Card Deck::dealCard(){
    myIndex -= 1;
    if (myIndex < 0){
        return (Card(-1, Card::spades));
    }
    else{
        Card cardToRet = myCards[myIndex];
        return cardToRet;
    }
}

// # cards left in the deck
int  Deck::size() const{
    return myIndex + 1;
}
