# DigitalDiscord

DigitalDiscord is a text-based puzzle game in the Terminal. You have to solve some probleams by edit the config files!

## Story
---
A company named Digital Inc. is searching for new people who are interrestet in IT to hire them. To find the right one they made a test where the user has to solve some probleams.
Together with the AI named Ikarus the user has to find an exit and a way to apply his success to the company!
But what's that? Ikarus seems like to freak out because of an internal System error?!
Quick, you have to finish the test befor Ikarus is going to destroy your PC!

## Available operatingsystems
---
DigitalDiscord supports Linux and Windows 10

## File - Structure
---
### 1 src
Here are all source files

### 2 executeables
Here are all files to run the game or compile it

### 3 plugins
Here are all plugins for the game

## Compiling yourself
---
If you want to compile the code yourself, you just have to execute compileLinux.sh or compileWindows.sh in the folder "executeables".

## Plugins
---
If you want to make plugins, you have to make a .h file in the folder "plugins". In it you write your code (no main function needed) and include it in the file "ExternalPlugins.h" in the function "start","update" or "reset"

## Known issues
---
### "std has no member "this_thread""
That might be because you use MinGW64. You can use Msys2 with minGW64 instead (download here: https://www.msys2.org/)

### "Unknown command "g++""
That means that you dont have the C++ compiler "g++"  (download here: https://www.msys2.org/)

## Creators
---
**SirWolf**   : Coding and Story writing

**XECortex**  : Coding and Story writing

## License
This programm uses the MIT license. More informations in "LICENSE.txt"
