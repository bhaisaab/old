# GtkMoo MakeFile
# (c) 2008-10 Rohit Yadav

CC = g++
CFLAGS = -g 

GtkMoo: main.cpp
	$(CC) main.cpp -o GtkMoo mooGui.cpp mooGame.cpp mooAbout.cpp mooGuessTable.cpp mooInputBox.cpp mooLevel.cpp mooMenuBar.cpp mooStatusBar.cpp mooToolBar.cpp mooRules.cpp `pkg-config --cflags --libs gtk+-2.0`

clean: 
	rm -f *.o GtkMoo
