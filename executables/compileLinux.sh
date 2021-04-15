#!/bin/bash

if [[ -e ErrorLog.txt ]]; then
    echo deleting old ErrorLog.txt...
    unlink ErrorLog.txt
fi
if [[ -e DigitalDiscord.x86_64 ]]; then
    echo deleting old DigitalDiscord.x86_64...
    unlink DigitalDiscord.x86_64
fi

echo checking for plugins...

plugins=""
foundC=0
counter=0
cd ../plugins/
for file in *; do
    
    filename=$(basename -- "$file")
    extension="${filename##*.}"
    filename="${filename%.*}"

    if [[ $extension == "cpp" ]]; then
        if [[ $foundC == 0 ]]; then
            plugins="../plugins/"$filename".cpp"
            foundC=1
        else
            plugins=$plugins" ../plugins/"$filename".cpp"
        fi
        counter=$(expr $counter + 1 ) 

    fi
done
if [[ $1 == "--debug" ]]; then
    debug=" -g"
fi
if [[ $counter != 0 ]]; then
    echo loaded $counter plugin/s...
fi


cd ../src
echo Brewing a coffee...
g++ $plugins $debug -g mac.cpp InternalSys.cpp InternalErrors.cpp InternalErrorLogger.cpp Cryp.cpp InternalLib.cpp Memory.cpp InternalFsys.cpp InternalEvents.cpp InternalPrettyConsoleOut.cpp Chars.cpp Game.cpp Terminal.cpp main.cpp -std=c++17 -o DigitalDiscord.x86_64 -static 2> "ErrorLog.txt"

cd ../src

mv DigitalDiscord.x86_64 ../executables/
mv ErrorLog.txt ../executables/
echo Done!

sleep 1