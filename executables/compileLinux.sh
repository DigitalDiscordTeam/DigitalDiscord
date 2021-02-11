
if [[ -e DigitalDiscord.exe ]]; then
    echo deleting old version...
    unlink DigitalDiscord.exe 
fi
if [[ -e ErrorLog.txt ]]; then
    echo deleting old ErrorLog.txt...
    unlink ErrorLog.txt
fi

cd ../src
echo Brewing a coffee...

g++ mac.cpp InternalSys.cpp InternalErrors.cpp InternalErrorLogger.cpp Cryp.cpp InternalLib.cpp Memory.cpp InternalFsys.cpp InternalEvents.cpp InternalFileVec.cpp InternalPrettyConsoleOut.cpp Chars.cpp CommandFile.cpp Game.cpp Terminal.cpp main.cpp -std=c++17 -o DigitalDiscord -static 2> "ErrorLog.txt"

mv DigitalDiscord ../executables/
mv ErrorLog.txt ../executables/
echo Done!

sleep 1
