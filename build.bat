
IF NOT EXIST dist/NUL mkdir dist
IF NOT EXIST logs/NUL mkdir logs
echo Compiling
g++ mac.cpp InternalSys.cpp InternalErrors.cpp InternalErrorlogger.cpp Cryp.cpp InternalLib.cpp Memory.cpp InternalFsys.cpp InternalEvents.cpp InternalFileVec.cpp InternalPrettyConsoleOut.cpp Chars.cpp CommandFile.cpp Game.cpp Terminal.cpp main.cpp -std=c++17 -o dist/DigitalDiscord.exe -static 2> logs/latest.txt
echo Done!
