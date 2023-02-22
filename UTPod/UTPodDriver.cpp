/* UTPod_driver.cpp create project
Demo Driver for the UTPod.

Roger Priebe
EE 312 10/16/18

This is a basic driver for the UTPod.

You will want to do more complete testing.

*/
#include <cstdlib>
#include <iostream>
#include "Song.h"
#include "UTPod.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Test with UTPod() constructor (No memory value inputted)
    UTPod t;

    //Test addSongs. Should print 0
    cout << "Add s1: " << endl;
    Song s1("Beatles", "Hey Jude1", 4);
    int result = t.addSong(s1);
    cout << "result = " << result << endl;

    //Show list with only one item
    t.showSongList();

    //Test remove on list with only one item
    cout << "Remove s1: " << endl;
    result = t.removeSong(s1);
    cout << "delete result = " << result << endl;

    //Empty list prints "List is empty"
    cout << "Should be Empty List: ";
    t.showSongList();


    //Shuffle and sort empty list
    cout << "Test shuffle and sort on empty list: ";
    t.shuffle();
    t.sortSongList();
    t.showSongList();

    // Re-add song1
    cout << "Add s1: " << endl;
    result = t.addSong(s1);
    cout << "result = " << result << endl;

    //Show list with only one item
    t.showSongList();

    cout << "Add s2: " << endl;
    Song s2("Beatles", "Hey Jude2", 5);
    result = t.addSong(s2);
    cout << "result = " << result << endl;

    //Show list with two items
    t.showSongList();

    cout << "Add s3: " << endl;
    Song s3("Beatles", "Hey Jude3", 6);
    result = t.addSong(s3);
    cout << "result = " << result << endl;

    //Show list with three item
    t.showSongList();

    cout << "Add s4: " << endl;
    Song s4("Beatles", "Hey Jude4", 7);
    result = t.addSong(s4);
    cout << "result = " << result << endl;

    //Show list with four items
    t.showSongList();

    cout << "Add s5: " << endl;
    Song s5("Beatles", "Hey Jude5", 200);
    result = t.addSong(s5);
    cout << "add result = " << result << endl;

    //Show list with five items
    t.showSongList();


    // Should return -1 because item doesn't fit in memory
    cout << "Add song with too much memory (Shouldn't be added): " << endl;
    Song s6("Beatles", "Hey Jude6", 300);
    result = t.addSong(s6);
    cout << "add result = " << result << endl;

    //Show list. Shouldn't have s6 added
    t.showSongList();

    //Add duplicate song and remove it to make sure remove only removes first instance of it
    cout << "Add duplicate s1: " << endl;
    result = t.addSong(s1);
    cout << "result = " << result << endl;
    //Print list with added duplicate song
    t.showSongList();
    cout << "Remove first s1: " << endl;
    t.removeSong(s1);
    // Should only have one s1
    t.showSongList();

    cout << endl << "Shuffle list:";
    t.shuffle();
    t.showSongList();

    //Test sort. Should print song list sorted
    cout << endl << "Sort list:";
    t.sortSongList();
    t.showSongList();

    cout << "Add song to fill memory (s7):" << endl;
    Song s7("Beatles", "Hey Jude6", 290);
    result = t.addSong(s7);
    cout << "add result = " << result << endl;

    //Show list with six items
    t.showSongList();

    //Test get memory for full list
    cout << "Test get memory for 0 memory:" << endl;
    cout << "memory = " << t.getRemainingMemory() << endl;
    cout << "Test get total memory on full list:" << endl;
    cout << "total memory = " << t.getTotalMemory() << endl << endl;


    //Remove s7
    cout << "Remove s7:"<< endl;
    t.removeSong(s7);
    t.showSongList();



    //Test Remove
    cout << "Remove s2: " << endl;
    result = t.removeSong(s2);
    cout << "delete result = " << result << endl;

    t.showSongList();

    cout << "Remove s3: " << endl;
    result = t.removeSong(s3);
    cout << "delete result = " << result << endl;

    t.showSongList();

    cout << "Remove s1: " << endl;
    result = t.removeSong(s1);
    cout << "delete result = " << result << endl;

    t.showSongList();

    cout << "Remove s5: " << endl;
    result = t.removeSong(s5);
    cout << "delete result = " << result << endl;

    t.showSongList();

    cout << "Remove s4: " << endl;
    result = t.removeSong(s4);
    cout << "delete result = " << result << endl;

    t.showSongList();
    cout << "Test get memory for empty list:" << endl;
    cout << "memory = " << t.getRemainingMemory() << endl << endl;

    cout << "Test clear memory for empty list:"<< endl;
    t.clearMemory();
    cout << "memory = " << t.getRemainingMemory() << endl << endl;

    cout << "Add s5: " << endl;
    result = t.addSong(s5);
    cout << "add result = " << result << endl;

    t.showSongList();
    cout << "Test get memory:" << endl;
    cout << "memory = " << t.getRemainingMemory() << endl;
    cout << "Test get total memory:" << endl;
    cout << "total memory = " << t.getTotalMemory() << endl;

    //Test clear memory
    cout << "Test clear memory:"<< endl;
    t.clearMemory();
    cout << "memory = " << t.getRemainingMemory() << endl;
    cout << "Test get total memory with empty list:" << endl;
    cout << "total memory = " << t.getTotalMemory() << endl;



    // Test UTPod Constructor with memory passed in
    cout << endl << "Test UTPod constructor with memory > MAX_MEMORY. Total memory should be 512 MB." << endl;
    UTPod x(513);
    cout << "Total Memory = " << x.getTotalMemory();
    cout << endl << "Test UTPod constructor with memory < 0. Total memory should be 512 MB." << endl;
    UTPod y(-15);
    cout << "Total Memory = " << y.getTotalMemory();
    cout << endl << "Test UTPod constructor with MAX_MEMORY >= memory > 0." << endl;
    UTPod z(250);
    cout << "Total Memory = " << z.getTotalMemory() << endl;

    cout <<  endl << "Test shuffle and sort for songs similar to each other:";

    //Test shuffle and sort for values similar to each other
    Song z1("Beatles", "A", 4);
    z.addSong(z1);
    Song z2("Beatles", "A", 3);
    z.addSong(z2);
    Song z3("Beatles", "B", 4);
    z.addSong(z3);
    Song z4("Beatles", "A", 5);
    z.addSong(z4);
    Song z5("Beatles", "B", 4);
    z.addSong(z5);

    Song z6("Animal", "A", 12);
    z.addSong(z6);
    Song z7("Animal", "B", 12);
    z.addSong(z7);
    Song z8("Animal", "C", 12);
    z.addSong(z8);
    Song z9("Zoo", "7 Lions", 20);
    z.addSong(z9);
    Song z10("Beatles", "3 Million", 15);
    z.addSong(z10);
    Song z11("Zoo", "7 Lions", 22);
    z.addSong(z11);

    cout << endl << "Shuffled song list:";
    z.shuffle();
    z.showSongList();

    cout << "Sorted song list";
    z.sortSongList();
    z.showSongList();

}
