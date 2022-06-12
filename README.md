## Project 02 - Final
**Project Name:** Horror Visual Novel\
**Team Members:** Vincent Jiang, Cullen Ye, Jacky Chen\
**Class Period:** Period 10

### Project Description:
The project will be a choose-your-own adventure visual novel game. The gameplay will be in first-person, text-based, with images showing up throughout the story, which are child **_processes_** that the parent process (main program) waits on. Your choices matter and will result in different endings. We will be **_allocating memory_** (kept in our data structure's unique string address) to keep track of your current story location and will be using a linked-list-like data structure to create a branching storyline. We will be using stdin for player choice input.\
There will be a save file for the player, which remembers the path the player saved, and will return the player to their saved story location. The game will keep track of when the game was last saved. We will be **_working with files_** and analyzing previous save files' **_data_** (stat) to accomplish this. We will also work with files to read in the story line upon user input and interaction (this includes the display of image files as well).\
The player can pull up the menu, save the game, exit, and perform other features at any point during the game. This will be accomplished through overriding **_signals_**. At the end of the game, memory will be cleared so that users can start over, or they can resume the novel using the saved data from save files.

### Timeline:
- General code structure/design: 1/12 (Tuesday)
- Working Prototype (no saving/extra functions; just going through the story in main.c): 1/15 (Friday)
- Picture implementation: 1/17 (Sunday)
- Rest of the project + additional add-ons by the deadline

### Techniques we're implementing:
1) Allocating memory
2) Working with files
3) Finding information about files
4) Signals
5) Processes

### Current Bugs:
- loading savefile disrupts game features in help()
- "back" is clunky with merged addresses
    - spamming it may result in an infinite loop

### Project Responsibilities:
**Story Writing:** Jacky, Vincent, Cullen

**Basic Structure:** Jacky, Vincent, Cullen

**README.md:** Jacky, Vincent, Cullen

**Bug Catching:** Jacky, Vincent, Cullen

**Implementing Signals and Miscellaneous Functions:** Jacky, Vincent

**Implementing Picture Library:** Vincent

**Implementing Save File System:** Cullen

---

### Files:
#### main.c
#### functions.h
#### makefile
#### savefile.txt
#### prompts.txt
#### pictureAddress.txt
#### story.txt
#### numChoice.txt
#### pics
#### README.md
#### DEVLOG
---

### Required Libraries:
#### stdio.h
#### stdlib.h 
#### sys/stat.h
#### signal.h
#### string.h
#### fcntl.h
#### unistd.h
#### sys/wait.h
#### ImageMagick
#### time.h

### Apt-Get + Prerequisites
NOTE: WSL and WSL2 users may have to run the program through ssh (i.e. thorugh PuTTY); All users require an X server to run the project (i.e. Xming for Windows, vcXsrv, XQuartz for macOS)\
Run the following code to install ImageMagick:\
$ sudo apt-get install imagemagick\
NOTE: sudo apt-get may not work on the macOS operating system. Try the following alternative after installing Homebrew (https://brew.sh/): \
$ brew install imagemagick
$ brew install --cask xquartz
$ brew install tlk/imagemagick-x11/imagemagick

### Instructions 
1.  install ImageMagick
2.  install an X server (options in prerequisites above)
3.  make sure to open up the X server
4.  $ git clone https://github.com/CullenLYe/project02_final.git <dir_name>
5.  $ cd <dir_name>
6.  $ make
7.  $ make run
8.  Throughout the program, input a number from 1-3, depending on the choices available to select that choice.
9.  You may type "help" any time to see optional input choices and features.
10. Have fun!  
 
