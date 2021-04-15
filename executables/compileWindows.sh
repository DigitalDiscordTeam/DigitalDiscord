
if [[ -e DigitalDiscord.exe ]]; then
    echo deleting old version...
    unlink DigitalDiscord.exe 
fi
if [[ -e ErrorLog.txt ]]; then
    echo deleting old ErrorLog.txt...
    unlink ErrorLog.txt
fi

cd ..\\src
echo going to compile...

g++ mac.cpp InternalSys.cpp InternalErrors.cpp InternalErrorlogger.cpp Cryp.cpp InternalLib.cpp Memory.cpp InternalFsys.cpp InternalEvents.cpp InternalPrettyConsoleOut.cpp Chars.cpp Game.cpp Terminal.cpp main.cpp -std=c++17 -o DigitalDiscord.exe -static 2> "ErrorLog.txt"

mv DigitalDiscord.exe ..\\executables\\
mv ErrorLog.txt ..\\executables\\
echo finished...
sleep 10