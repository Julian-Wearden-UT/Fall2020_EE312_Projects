Programming Project 3 Equation Checker Array ReadMe
Program by: Julian F. Wearden
UTEID: jfw864
Email: juliwramos@gmail.com
5 Digit Section ID: 16020

If you do not have unzip installed, first run:
	sudo apt-get install unzip

After the unzip installation completes, cd to the directory the "prog03linked_jfw864.zip" file is in and run:
	unzip prog03array_jfw864.zip	//Run this command to unzip in current director
	OR
	unzip prog03array_jfw864.zip -d DESTINATION_FOLDER //Run this command to unzip in a specific directory

Now, cd to the location you unzipped your file to and run:
	make

This will build the C program. To run the program, type:
	./check FILE.dat

Where FILE.dat is the .dat file that contains the test expressions, one expression per line.

Note: Equation must be at most 80 characters

The program will then print to the screen each equation, and whether that equation is valid, or is missing a paranthesis, square bracker, or angle bracket.
