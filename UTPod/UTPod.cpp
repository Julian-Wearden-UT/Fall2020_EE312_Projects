
#include "UTPod.h"


//Default constructor
//set the memory size to MAX_MEMORY
//Initialize head pointer to null
UTPod::UTPod(){
    memSize = MAX_MEMORY;
    totalMemSize = memSize;
    songs = nullptr;
}

//Constructor with size parameter
//The user of the class will pass in a size.
//If the size is greater than MAX_MEMORY or less than or equal to 0,
//set the size to MAX_MEMORY.
//Initialize head pointer to null
UTPod::UTPod(int size){
    // If invalid size entered, set memsize to MAX_MEMORY
    if(size > MAX_MEMORY || size <= 0){
        memSize = MAX_MEMORY;
        totalMemSize = memSize;
        songs = nullptr;
    }
    //Else set memsize to user's memory value
    else{
        memSize = size;
        totalMemSize = memSize;
        songs = nullptr;
    }
}

/* FUNCTION - int addSong
 * attempts to add a new song to the UTPod
     o returns a 0 if successful
     o returns -1 if not enough memory to add the song

 precondition: s is a valid Song

 input parms - Song object

 output parms - Adds song to linked list. Returns 0 if successful, -1 if not enough memory.
*/

int UTPod::addSong(Song const &s){
    // If there isn't enough memory to add the song, return -1
    if((memSize - s.getSongSize()) < 0){
        return NO_MEMORY;
    }
    // Else, add song to linked list and return 0
    else{
        SongNode* songPtr = new SongNode;
        songPtr->s = s;
        songPtr->next = nullptr;
        songPtr->next = this->songs;
        this->songs = songPtr;
        memSize = memSize - s.getSongSize();
        return SUCCESS;
    }
}


/* FUNCTION - int removeSong
 * attempts to remove a song from the UTPod
 * removes the first instance of a song that is in the the UTPod multiple times
     o returns 0 if successful
     o returns -2 if nothing is removed


   input parms - Song object

   output parms - Removed song from linked list. Returns 0 if successful, -2 if nothing removed
*/

int UTPod::removeSong(Song const &s){
    // If list is empty, reutn -2
    if(this->songs == nullptr){  //List is empty
        return NOT_FOUND;
    }
    // Else if we need to remove the head node
    else if (this->songs->s == s){  //Remove head node
        SongNode* headPtr = this->songs;
        memSize = memSize + s.getSongSize();
        this->songs = this->songs->next;
        delete headPtr;
        return SUCCESS;
    }
    // Else, traverse through linked list until we find matching song. If match found return 0, else -2.
    else{
        SongNode* prevPtr = this->songs;
        SongNode* currentPtr = this->songs->next;
        while(currentPtr != nullptr){
            // If found, stop traversing through loop and remove it
            if(currentPtr->s == s){
                break;
            }
            // Move pointer over
            else{
                prevPtr = currentPtr;
                currentPtr = currentPtr->next;
            }
        }
        if (currentPtr == nullptr){
            return NOT_FOUND;
        }
        // Remove item from linked list and add memory back to memsize
        else{
            prevPtr->next = currentPtr->next;
            delete currentPtr;
            memSize = memSize + s.getSongSize();
            return SUCCESS;
        }

    }

}


/* FUNCTION - void shuffle
 *  shuffles the songs into random order
    o will do nothing if there are less than two songs in the current list

   input parms - Linked list

   output parms - Shuffled linked list
*/

void UTPod::shuffle(){
    // If there are < 2 Nodes, do nothing
    if(this->songs == nullptr || this->songs->next == nullptr){}
    else{
        SongNode* laterPtr = this->songs;
        SongNode* earlierPtr = this->songs;
        SongNode* tempPtr = new SongNode;
        int i = 0;
        int lengthOfLL = length();  //Find length of Linked list
        // Do for all items in linked list
        while(i < lengthOfLL){
            laterPtr = this->songs;
            earlierPtr = this->songs;
            //Pick random number. Traverse linked list that many times and select that node
            srand(time(0));
            int randomVal = rand() % lengthOfLL;
            for (int idx = 0; idx < randomVal; idx++) {
                laterPtr = laterPtr->next;
            }
            // Pick second node 1 by 1
            for (int idx = 0; idx < i; idx++){
                earlierPtr = earlierPtr->next;
            }
            //Swap first and second nodes s values
            tempPtr->s = laterPtr->s;
            laterPtr->s = earlierPtr->s;
            earlierPtr->s = tempPtr->s;
            i++;
        }
        //Free temporary pointer
        delete tempPtr;
    }

}

/* FUNCTION - int length
 *  Calculates number of elements in linked list to aid with shuffle

   input parms - Linked list

   output parms - Number of elements in linked list
*/
int UTPod::length(){
    int length = 0;
    // If list is empty
    if(this->songs == nullptr){
        return 0;
    }
    //Else traverse through linked list and count every node
    else{
        SongNode* tempPtr = this->songs;
        while(tempPtr != nullptr){
            length++;
            tempPtr = tempPtr->next;
        }
        // Return nodes counted
        return length;
    }
}


/* FUNCTION - void showSongList
 * prints the current list of songs in order from first to last to standard output
 * format - Title, Artist, size in MB (one song per line)

   input parms - Linked list

   output parms - Prints each element of linked list. Prints "List is empty" if no songs.
*/

void UTPod::showSongList(){
    cout << endl;
    // If list is empty
    if(this->songs == nullptr){
        cout << "List is empty" << endl;
    }
    // Traverse through list and print every song object in list
    else{
        SongNode* tempPtr = this->songs;
        while(tempPtr != nullptr){
            cout << tempPtr->s.getSongTitle() << ", " << tempPtr->s.getSongArtist() << ", " << tempPtr->s.getSongSize() << "MB" << endl;
            tempPtr = tempPtr->next;
        }
    }
    cout << endl;
}


/* FUNCTION - void sortSongList
 *  sorts the songs in ascending order
    o will do nothing if there are less than two songs in the current list

   input parms - Linked list

   output parms - Sorted linked list by Artist, then Name, then Size
*/

void UTPod::sortSongList(){
    // Does nothing if less than two songs in current list
    if(this->songs == nullptr || this->songs->next == nullptr){return;}
    // Sort list
    else{
        int isSorted = 0;   //0 when not sorted, 1 if sorted
        while(isSorted == 0) {
            SongNode *homePtr = this->songs;            //Pointer to first node
            SongNode *comparePtr = this->songs->next;   //Pointer to second node
            Song homeSong = homePtr->s;
            // Do until we reach end of linked list
            while (comparePtr != nullptr) {
                // If second node is less than first node, swap their s values
                if (comparePtr->s < homePtr->s) {
                    SongNode *tempPtr = new SongNode;
                    tempPtr->s = homePtr->s;
                    homePtr->s = comparePtr->s;
                    comparePtr->s = tempPtr->s;
                    delete tempPtr;
                    homePtr = comparePtr;
                    comparePtr = comparePtr->next;
                    isSorted = 0;
                }
                // Else continue on through list
                else {
                    homePtr = homePtr->next;
                    comparePtr = comparePtr->next;
                }
            }

            SongNode *tempPtr = this->songs;
            SongNode *tempCompPtr = this->songs->next;
            // Last pass through to see if list is actually sorted
            while (tempCompPtr != nullptr) {
                // If it finds two nodes that aren't sorted, exit and re-do previous loop
                if (tempPtr->s > tempCompPtr->s) {
                    tempPtr = tempPtr->next;
                    tempCompPtr = tempCompPtr->next;
                    isSorted = 0;
                    break;
                }
                // Else, set isSorted to 1 and end function
                else {
                    tempPtr = tempPtr->next;
                    tempCompPtr = tempCompPtr->next;
                    isSorted = 1;
                }
            }
        }
    }
}


/* FUNCTION - void clearMemory
 * clears all the songs from memory

   input parms - Linked list

   output parms - Deleted every item from linked list
*/
void UTPod::clearMemory(){
    SongNode* tempPtr = this->songs;
    // Traverse through list
    while(tempPtr != nullptr){
        // Re-add memory to memsize
        memSize = memSize + tempPtr->s.getSongSize();
        // Delete node and free
        this->songs = tempPtr->next;
        tempPtr->next = nullptr;
        delete tempPtr;
        tempPtr = this->songs;
    }
}



/* FUNCTION - int getRemainingMemory
 *  returns the amount of memory available for adding new songs

   input parms - None

   output parms - Memory available
*/

int UTPod::getRemainingMemory() const {
    // Return memory available
    return memSize;
}

// Frees head pointer space
UTPod::~UTPod(){
    // Removes all nodes
    clearMemory();
    // Deletes head pointer
    delete songs;
}

