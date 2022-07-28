#!/bin/bash
green='\033[0;32m'
red='\033[0;31m'
clear='\033[0m'
cmake
cd cmake-build-debug

for file in $2/* ; do
 if [[ $file == *.in ]] ; then
    make
    valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./nowaWersja "$file"

    expectedResult="$2/$(basename -s .in $file).out"
    expectedError="$2/$(basename -s .in $file).err"
    DIFF1=$(diff "file.err" $expectedError)
    DIFF2=$(diff "file.out" $expectedResult)

    if [ "$DIFF1" == ""  -a  "$DIFF2" == "" ] ; then
        echo
        echo -e TEST: "$(basename -s .in $file)  ${green}OK${clear}"
        echo
        else
          echo
          echo -e TEST: "$(basename -s .in $file)  ${red}ERROR${clear}"
          echo
    fi

    > file.out
    > file.err
fi
done
