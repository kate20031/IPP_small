#!/bin/bash
declare -A results
green='\033[0;32m'
red='\033[0;31m'
clear='\033[0m'
cmake
cd cmake-build-debug || exit

for file in $2/*; do
  if [[ $file == *.in ]]; then
    make
    valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./nowaWersja "$file"
    basefileName=$(basename -s .in $file)

    expectedResult="$2/$basefileName.out"
    expectedError="$2/$basefileName.err"
    DIFF1=$(diff "file.err" $expectedError)
    DIFF2=$(diff "file.out" $expectedResult)

    if [ "$DIFF1" == "" -a "$DIFF2" == "" ]; then
      echo
      echo -e TEST: "$basefileName  ${green}OK${clear}"
      results["$basefileName"]=${green}OK${clear}
      echo
    else
      echo
      echo -e TEST: "$basefileName  ${red}ERROR${clear}"
      results["$basefileName"]=${red}ERROR${clear}
      echo Expected result:
      cat $expectedResult
      echo result:
      cat file.out
      echo Expected error:
      cat $expectedError
      echo error:
      cat file.err
      echo
    fi

    >file.out
    >file.err
  fi
done

echo TOTAL RESULTS
for key in "${!results[@]}"; do
  echo -e "$key ${results[$key]}"
done
