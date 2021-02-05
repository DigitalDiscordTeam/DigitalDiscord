cd ../src
echo Brewing a coffee...

g++ mac.cpp InternalSys.cpp InternalErrors.cpp InternalErrorLogger.cpp Cryp.cpp InternalLib.cpp Memory.cpp InternalFsys.cpp InternalEvents.cpp InternalFileVec.cpp InternalPrettyConsoleOut.cpp Chars.cpp CommandFile.cpp Game.cpp Terminal.cpp main.cpp -std=c++17 -o DigitalDiscord -static > ErrorLog.txt

mv DigitalDiscord ../executables/
echo Done!

sleep 1

cd ../executables/
echo "Executing..."
./DigitalDiscord