#include "card.h"

// default, ace of spades
Card::Card(){
    myRank = 1;
    mySuit = spades;
}

Card::Card(int rank, Suit s){
    myRank = rank;
    mySuit = s;
}

// return string version e.g. Ac 4h Js
string Card::toString() const{
    return (rankString(this->myRank) + suitString(this->mySuit));
}

// true if suit same as c
bool Card::sameSuitAs(const Card& c) const{
    if (this->mySuit == c.mySuit){
        return true;
    }
    else return false;
}

// return rank, 1..13
int  Card::getRank() const{
    return this->myRank;
}

// return "s", "h",...
string Card::suitString(Suit s) const{
    string cardValue;
    switch (s) {
        case spades:
            cardValue = "s";
            break;
        case hearts:
            cardValue = "h";
            break;
        case diamonds:
            cardValue = "d";
            break;
        case clubs:
            cardValue = "c";
            break;
        default:
            cardValue = "-1";   //Invalid card suit
    }
    return cardValue;
}

// return "A", "2", ..."Q"
string Card::rankString(int r) const{
    string cardValue;
    switch (r) {
        case 1:
            cardValue = "A";
            break;
        case 2:
            cardValue = "2";
            break;
        case 3:
            cardValue = "3";
            break;
        case 4:
            cardValue = "4";
            break;
        case 5:
            cardValue = "5";
            break;
        case 6:
            cardValue = "6";
            break;
        case 7:
            cardValue = "7";
            break;
        case 8:
            cardValue = "8";
            break;
        case 9:
            cardValue = "9";
            break;
        case 10:
            cardValue = "10";
            break;
        case 11:
            cardValue = "J";
            break;
        case 12:
            cardValue = "Q";
            break;
        case 13:
            cardValue = "K";
            break;
        default:
            cardValue = "0"; // Catch all if myRank is out of bounds value
    }
    return cardValue;
}

// Necessary overloaded operators for card class
bool Card::operator == (const Card& rhs) const{
    if (this->mySuit == rhs.mySuit && this->myRank == rhs.myRank){
        return true;
    }
    else return false;
}

bool Card::operator != (const Card& rhs) const{
    if (this->mySuit != rhs.mySuit || this->myRank != rhs.myRank){
        return true;
    }
    else return false;
}

ostream& operator << (ostream& out, const Card& c){
    out << c.toString() << endl;
    return out;
}