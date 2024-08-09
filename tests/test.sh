#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BOLD="\033[1m"
RESET='\033[0m'

DIR=../philo/
OUT=./outputs/out.txt
TEST=1

function wait_for_timeout()
{
	sleep 2
	if kill -0 $1 &> /dev/null
	then
		kill $1
	fi
}

function print_aligned() {
    local line_number=$1
    local command=$2
    local status=$3
    local color=0

    if [ "$status" == "OK" ]; then
        color=$GREEN
    elif [ "$status" == "KO" ]; then
        color=$RED
    else
        return
    fi
    printf "${color}%-3s %-28s %5s\n${RESET}" "$line_number" "$command" "$status"
}

make -C ${DIR} &> /dev/null
if [ $? -ne 0 ]; then
    echo "Make error"
    make -C ${DIR} clean &> /dev/null
    exit 1
else    
    mv ${DIR}philo ./
fi
make -C ${DIR} clean &> /dev/null

while IFS= read -r line; do
  ((TEST+=1))
  echo "$line" | xargs ./philo > ${OUT} & bg_process=$!
  wait_for_timeout "${bg_process}" & wait "${bg_process}"
  if grep -q "has died" "${OUT}"; then
    print_aligned "${TEST}" "${line}" "KO"
  else
    print_aligned "${TEST}" "${line}" "OK"
  fi
  > ${OUT}
done < "./should_alive.in"

rm ./philo && > ${OUT}