#ifndef UTPod_H
#define UTPod_H
#include "Song.h"


//UTPod class declaration
class UTPod
{
   private:
      static const int MAX_MEMORY = 512;
      static const int SUCCESS = 0;
      static const int NO_MEMORY = -1;
      static const int NOT_FOUND = -2;
      
      struct SongNode
      {
         Song s;
         SongNode *next;
      };
      
      SongNode *songs;  //the head pointer
      
      int memSize;
      int totalMemSize;

      // Helper function for shuffle. Returns number of elements in linked list
      int length();


   public:

    //Default constructor
    //set the memory size to MAX_MEMORY
    //Initialize head pointer to null
      UTPod();

    //Constructor with size parameter
    //The user of the class will pass in a size.
    //If the size is greater than MAX_MEMORY or less than or equal to 0,
    //set the size to MAX_MEMORY.
    //Initialize head pointer to null
      UTPod(int size);

    /* FUNCTION - int addSong
    * attempts to add a new song to the UTPod
       o returns a 0 if successful
       o returns -1 if not enough memory to add the song

    precondition: s is a valid Song

    input parms - Song object

    output parms - Adds song to linked list. Returns 0 if successful, -1 if not enough memory.
    */
      int addSong(Song const &s);

    /* FUNCTION - int removeSong
    * attempts to remove a song from the UTPod
    * removes the first instance of a song that is in the the UTPod multiple times
       o returns 0 if successful
       o returns -2 if nothing is removed


     input parms - Song object

     output parms - Removed song from linked list. Returns 0 if successful, -2 if nothing removed
    */
      int removeSong(Song const &s);

    /* FUNCTION - void shuffle
     *  shuffles the songs into random order
        o will do nothing if there are less than two songs in the current list

       input parms - Linked list

       output parms - Shuffled linked list
    */

      void shuffle();

    /* FUNCTION - void showSongList
     * prints the current list of songs in order from first to last to standard output
     * format - Title, Artist, size in MB (one song per line)

       input parms - Linked list

       output parms - Prints each element of linked list. Prints "List is empty" if no songs.
    */

      void showSongList();


    /* FUNCTION - void sortSongList
     *  sorts the songs in ascending order
        o will do nothing if there are less than two songs in the current list

       input parms - Linked list

       output parms - Sorted linked list by Artist, then Name, then Size
    */

      void sortSongList();


    /* FUNCTION - void clearMemory
     * clears all the songs from memory

       input parms - Linked list

       output parms - Deleted every item from linked list
    */
      void clearMemory();


      /* FUNCTION - int getTotalMemory
       *  returns the total amount of memory in the UTPod

         input parms - None

         output parms - total memory set when UTPod was constructed
      */

      int getTotalMemory() const {
         return totalMemSize;
      }



    /* FUNCTION - int getRemainingMemory
     *  returns the amount of memory available for adding new songs

       input parms - None

       output parms - Memory available
    */

      int getRemainingMemory() const;


      ~UTPod();

};



#endif
