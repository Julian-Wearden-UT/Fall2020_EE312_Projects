//
// Created by juliw on 10/27/2020.
//

#include "Song.h"

// Overloaded == operator for Song object
bool Song::operator==(const Song& rhs){
    //If every value in Song equal to each other return true
    if (this->songTitle == rhs.songTitle && this->songArtist == rhs.songArtist && this->songSize == rhs.songSize){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded == operator for Song object
bool Song::operator<(const Song& rhs){
    // Compare by artist first, then title, then size
    if (this->songArtist < rhs.songArtist){
        return true;
    }
    else if (this->songArtist == rhs.songArtist && this->songTitle < rhs.songTitle){
        return true;
    }
    else if (this->songArtist == rhs.songArtist && this->songTitle == rhs.songTitle && this->songSize < rhs.songSize){
        return true;
    }
    else{
        return false;
    }
}

// Overloaded == operator for Song object
bool Song::operator>(const Song& rhs){
    // Compare by artist first, then title, then size
    if (this->songArtist > rhs.songArtist){
        return true;
    }
    else if (this->songArtist == rhs.songArtist && this->songTitle > rhs.songTitle){
        return true;
    }
    else if (this->songArtist == rhs.songArtist && this->songTitle == rhs.songTitle && this->songSize > rhs.songSize){
        return true;
    }
    else{
        return false;
    }
}
