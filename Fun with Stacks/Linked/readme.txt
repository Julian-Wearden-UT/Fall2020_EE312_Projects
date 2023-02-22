Programming Project 3 Flood Fill Linked List ReadMe
Program by: Julian F. Wearden
UTEID: jfw864
Email: juliwramos@gmail.com
5 Digit Section ID: 16020

If you do not have unzip installed, first run:
	sudo apt-get install unzip

After the unzip installation completes, cd to the directory the "prog03linked_jfw864.zip" file is in and run:
	unzip prog03linked_jfw864.zip

Now, cd to the prog03linked_jfw864 folder and run:
	make

This will build the C program. To run the program, type:
	./flood_fill TEXT_FILE.txt

Where TEXT_FILE.txt is the text file that contains a grid of character "pixels" and is, at most, 25 rows x 25 columns. Once the program executes, it will prompt you to input three things:
	1)The row number of the pixel you want to flood.
	2)The column number of the pixel you want to flood.
	3)The new color you would like to flood fill with.

Note: When you enter the row and column, you can only enter an integer. If the integer is beyond the bounds of the 2D grid in the text file, you will be prompted to re-input a row or column number. The color you enter must be a single alphanumeric character, or a single of type char.

You will continuously be prompted to flood fill. To exit and end the program enter -1 as the Row or Column input.
