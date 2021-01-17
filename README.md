## Project 02 - Final
**Project Name:** Horror Visual Novel\
**Team Members:** Jacky Chen, Vincent Jiang, Cullen Ye\
**Class Period:** Period 10

### Project Description:
The project will be a choose-your-own adventure visual novel game. The gameplay will be in first-person, text-based, with images showing up throughout the story. Your choices matter and will result in different endings. We will be allocating memory (kept in our data structure's unique string address) to keep track of your current story location. We will be using stdin for player choice input. We'll be using linked-list-like data structure to create a branching storyline.\
There will be a save file for the player, which remembers the path the player saved, and will return the player to their saved story location (implementing signals to exit and save). The game will keep track of when the game was last saved. We will be working with files and analyzing previous save files' metadata (stat) to accomplish this.\
The player can pull up the menu, save the game, and other features at any point during the game. This will be accomplished through overriding signals. At the end of the game, memory will be cleared so that users can start over, or they can resume the novel using the saved data from save files.

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
- Customize the protagonist's name.
- Custom-drawn pictures.

### Current Issues To Fix:

### Limitations:
- Can't type too much from stdin into the buffers. They are each size 256.

### Project Responsibilities:
**Story Writing:** Jacky, Vincent, Cullen

**Basic Structure:** Jacky, Vincent, Cullen

**Implementing Signals and Miscellaneous Functions:** Jacky

**Implementing Picture Library:** Vincent

**Implementing Save File System:** Cullen

---

### Files:
## main.c
## functions.h
## makefile
## savefile.txt
## story.txt
## numChoice.txt
## picture_addresses.txt
## README.md
## DEVLOG
---

### Required Libraries:
## stdio.h
## stdlib.h 
## sys/stat.h
## signal.h
## string.h
## fcntl.h
## unistd.h
## ImageMagick

### Apt-Get + Prerequisites
// to be updated\
NOTE: WSL and WSL2 users may have to run the program through ssh (i.e. thorugh PuTTY); All users require the installation of an X-server (i.e. Xming, vcXsrv)\
Run the following code:\
$ sudo apt-get install imagemagick\
(maybe) $ sudo apt-get install lxde\ 
$ export DISPLAY=:0.0\
// Try and test out 

### Instructions 
// to be updated
