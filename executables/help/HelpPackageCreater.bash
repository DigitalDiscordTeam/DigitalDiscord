#!/bin/bash

for i in $(ls)
do
    extention=""
    bool=0
    current=0
    for j in $(seq 1 ${#i})
    do
        if [[ ${i:$j-1:1} == "." ]]; then
            bool=1

        fi

        if [[ $bool == 1 ]]; then
            extention=$extention${i:$j-1:1}
        fi
    done
    if [[ $extention == ".DDhelp" ]]; then
        read -p "Do you want to delete $i? (type r to skip this) [y/n]:" INP
        extention=""
        bool=0
        if [[ $INP == "r" ]]; then
            break
        elif [[ $INP == "y" ]]; then
            rm $i
        fi
    fi
    
done

echo Please give us a description of the bug: 
read DES

t="$(date +'%N')"
dirname=$t-DD_HELPDIR.DDhelp
mkdir $dirname
mkdir $dirname/plugins
cp ../ErrorLog.txt $dirname/ErrorLog.txt

for i in ../../plugins/*.h
do 
    cp $i $dirname/plugins
done
echo $DES > $dirname/DES.txt

sleep 2
echo done\!
sleep 10