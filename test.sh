#!/bin/bash
declare -A results
green='\033[0;32m'
red='\033[0;31m'
clear='\033[0m'
make

programme=$1
tests=$2
allTests=0
correctTests=0

for inputFile in $tests/*; do
    if [[ $inputFile == *.in ]]; then
      if (($# < 2)); then
          echo "Too few arguments to function"
          echo "First argument : name of program"
          echo "Second argument : path to directory with tests"
          exit 1
      fi

      touch file.out
      touch file.err
      basefileName=$(basename -s .in $inputFile)
      expectedResult="$tests/$basefileName.out"
      expectedError="$tests/$basefileName.err"

#      valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all
       ./"$programme" < "$inputFile" 1> "file.out"

      if [[ $? == 123 ]]; then
          echo "Out of memory";
      fi

      ./"$programme" < "$inputFile" 2> "file.err"
      echo -e TEST: "$basefileName"
      if [ $? == 1 ] && [ -s $expectedResult ]; then
          echo "Error EXIT code";

      elif [ $? == 0 ] &&  ! [ -s $expectedResult ] ; then
          echo "Error EXIT code";
      fi

      allTests=$((allTests+1))

      diff "file.out" $expectedResult
      if [ $? -eq 0 ]; then
        diff "file.err" $expectedError
        if [ $? -eq 0 ]; then
          correctTests=$((correctTests+1))
          results["$basefileName"]=${green}OK${clear}
          else
            results["$basefileName"]=${red}ERROR${clear}
        fi
      else
        results["$basefileName"]=${red}ERROR${clear}
      fi

      rm file.out
      rm file.err
    fi
done

echo TOTAL RESULTS
for key in "${!results[@]}"; do
  echo -e "$key ${results[$key]}"
done

for key in "${!results[@]}"; do
  if [ "${results[$key]}" == ${red}ERROR ]; then
  echo -e "$key ${results[$key]}"
  fi
done

echo $correctTests / $allTests
make clean