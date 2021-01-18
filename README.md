## Project 02 - Final
**Project Name:** Horror Visual Novel\
**Team Members:** Jacky Chen, Vincent Jiang, Cullen Ye\
**Class Period:** Period 10

### Project Description:
The project will be a choose-your-own adventure visual novel game. The gameplay will be in first-person, text-based, with images showing up throughout the story. Your choices matter and will result in different endings. We will be **_allocating memory_** (kept in our data structure's unique string address) to keep track of your current story location and will be using a linked-list-like data structure to create a branching storyline. We will be using stdin for player choice input.\
There will be a save file for the player, which remembers the path the player saved, and will return the player to their saved story location. The game will keep track of when the game was last saved. We will be **_working with files_** and analyzing previous save files' **_metadata_** (stat) to accomplish this. We will also work with files to read in the story line upon user input and interaction (this includes the display of image files as well).\
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

### Possible Additions (if we have enough time):
- Add quick-time choices. (Use the wait() function)
- Include a pause option. (Signals)
- Custom-drawn pictures.
- Items
- Mini-games
- Awards

### Current Issues To Fix:
- update instruction here 
- update help function with additional add-ons and features
- update apt-get instructions
- confirm whether program runs in Linux
- story writing
- picture implementation

### Project Responsibilities:
**Story Writing:** Jacky, Vincent, Cullen

**Basic Structure:** Jacky, Vincent, Cullen

**Implementing Signals and Miscellaneous Functions:** Jacky

**Implementing Picture Library:** Vincent

**Implementing Save File System:** Cullen

---

### Files:
#### main.c
#### functions.h
#### makefile
#### savefile.txt
#### story.txt
#### numChoice.txt
#### picture_addresses.txt
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
#### ImageMagick

### Apt-Get + Prerequisites
// to be updated\
NOTE: WSL and WSL2 users may have to run the program through ssh (i.e. thorugh PuTTY); All users require an X server to run the project (i.e. Xming, vcXsrv)\
Run the following code:\
$ sudo apt-get install imagemagick\
// Try and test out 

### Instructions 
// to be updated\
// To be included (or fixed) later: throughout the program, please close image files after each decision input before continuing. Failure to do so would stop the program from running. 
