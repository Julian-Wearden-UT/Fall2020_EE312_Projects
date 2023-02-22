#include "player.h"

void Player::addCard(Card c) {  //adds a card to the hand
    myHand.push_back(c);
}
void Player::bookCards(Card c1, Card c2){  //adds pair of cards to book and removes them from hand
    myBook.push_back(c1);
    myBook.push_back(c2);
    removeCardFromHand(c1);
    removeCardFromHand(c2);
}

//OPTIONAL
// comment out if you decide to not use it
//this function will check a players hand for a pair.
//If a pair is found, it returns true and populates the two variables with the cards that make the pair.

bool Player::checkHandForBook(Card &c1, Card &c2){
    if (c1.getRank() == c2.getRank()){
        bookCards(c1, c2);
        return true;
    }
    else{
        return false;
    }
}

//OPTIONAL
// comment out if you decide to not use it
//Does the player have a card with the same rank as c in her hand?
bool Player::rankInHand(Card c) const{
    for(auto &&it: myHand){
        if(c.getRank() == it.getRank()){
            return true;
        }
    }
    return false;
}

//uses some strategy to choose one card from the player's
//hand so they can say "Do you have a 4?"
Card Player::chooseCardFromHand() const{
    srand((unsigned) time(0));
    int randomVal = rand() % myHand.size();
    return myHand.at(randomVal);
}

//Choose card at specific position
Card Player::chooseCardFromHand(int x) const{
    return myHand.at(x);
}

//Does the player have the card c in her hand?
bool Player::cardInHand(Card c) const{
    for(auto &&it: myHand){
        if(c == it){
            return true;
        }
    }
    return false;
}

//Remove the card c from the hand and return it to the caller. Returns -1s if none found
Card Player::removeCardFromHand(Card c){
    unsigned int i = 0;
    while (i < myHand.size()) {
        Card cardToRemove = myHand.at(i);
        if(cardToRemove == c) {
            myHand.erase(myHand.begin() + i); // Delete
            return cardToRemove;
        }
        ++i;
    }
    return Card(-1, Card::spades);
}

//Remove card in hand with same rank as card c. Returns -1s if none found
Card Player::removeRankFromHand(Card c){
    unsigned int i = 0;
    while (i < myHand.size()) {
        Card cardToRemove = myHand.at(i);
        if(cardToRemove.getRank() == c.getRank()) {
            myHand.erase(myHand.begin() + i); // Delete
            return cardToRemove;
        }
        ++i;
    }
    return Card(-1, Card::spades);
}

string Player::showHand() const{
    string hand;
    for (auto &&it: myHand){
        hand += it.toString() + " ";
    }
    return hand;
}
string Player::showBooks() const{
    string book;
    for (unsigned int i = 0; i < myBook.size(); i += 2){
        book += myBook[i].rankString(myBook[i].getRank()) + " ";
    }
    return book;
}

int Player::getHandSize() const{
    return myHand.size();
}
int Player::getBookSize() const{
    return myBook.size();
}

//OPTIONAL
// comment out if you decide to not use it
//this function will check a players hand for a pair.
//If a pair is found, it returns true and populates the two variables with the cards tha make the pair.

//bool Player::checkHandForPair(Card &c1, Card &c2){}

//OPTIONAL
// comment out if you decide to not use it
//Does the player have a card with the same rank as c in her hand?
//e.g. will return true if the player has a 7d and the parameter is 7c

//bool Player::sameRankInHand(Card c) const{}
