cd ..\\src
echo going to compile...

g++ mac.cpp InternalSys.cpp InternalErrors.cpp InternalErrorlogger.cpp Cryp.cpp InternalLib.cpp Memory.cpp InternalFsys.cpp InternalEvents.cpp InternalFileVec.cpp InternalPrettyConsoleOut.cpp Chars.cpp CommandFile.cpp Game.cpp Terminal.cpp main.cpp -std=c++17 -o DigitalDiscord.exe -static > ErrorLog.txt

mv DigitalDiscord.exe ..\\executables\\
echo finished...
sleep 10