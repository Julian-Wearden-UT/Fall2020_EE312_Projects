//
// Created by juliw on 10/27/2020.
//

#ifndef UTPOD1_SONG_H
#define UTPOD1_SONG_H

#include <string>
using namespace std;
#include <iostream>
#include <utility>

class Song
{
    private:
        string songTitle;
        string songArtist;
        int songSize;
    public:
        //Constructor. Assumes user enters valid arguments
        Song(string songArtist = "No Artist", string songTitle = "No Title", int songSize = -1){
            this->songTitle = songTitle;
            this->songArtist = songArtist;
            this->songSize = songSize;
        }

        //Accessors
        string getSongTitle() const{return (this->songTitle);}
        string getSongArtist() const{return (this->songArtist);}
        int getSongSize() const{return (this->songSize);}

        //Mutators not needed because we assume title, artist, size will not change

        //Overload operators
        bool operator==(const Song& rhs);
        bool operator<(const Song& rhs);
        bool operator>(const Song& rhs);
};

#endif //UTPOD1_SONG_H

