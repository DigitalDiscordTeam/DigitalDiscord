# DigitalDiscord

DigitalDiscord is a text-based puzzle game in the Terminal. You have to solve some problems by editing the config files!

## Story

A company named Digital Inc. is searching for new people who are interrested in IT to hire them. To find the right one they made a test where the user has to solve some problems.
Together with the AI named Ikarus the user has to find an exit and a way to apply his success to the company!
But what's that? Ikarus seems like to freak out because of an internal system error?!
Quick, you have to finish the test befor Ikarus is going to destroy your PC!

- ***This program is still "work in progress". That means that you cant actually play the game yet.***
## Available operating systems

DigitalDiscord supports Linux and Windows 10

## Compiling yourself

If you want to compile the code yourself, you just have to execute compileLinux.sh or compileWindows.sh in the folder "executeables".

## Plugins

If you want to make plugins, you have to create a .h file in the folder "plugins". In it you write your code (no main function needed) and include it in the file "ExternalPlugins.h" in the function "start","update" or "reset"

## Known issues

### "std has no member "this_thread""
That might be because you use MinGW64. You can use Msys2 with minGW64 instead (download here: https://www.msys2.org/)

## Creators

**SirWolf**   : Coding and Story writing

**XECortex**  : Coding and Story writing

## License
This program is licensed under the MIT license.
