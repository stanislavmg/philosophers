#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BOLD="\033[1m"
RESET='\033[0m'

DIR=../philo/
LOG=./outputs/tmp/
rows=4
cols=2

die=(
    [0,0]=1 [0,1]=800 [0,2]=200 [0,3]=200
    [1,0]=4 [1,1]=310 [1,2]=200 [1,3]=100
)

life=(
    [0,0]=1 [0,1]=800 [0,2]=200 [0,3]=200
    [1,0]=4 [1,1]=310 [1,2]=200 [1,3]=100
)

function start()
{
    make -C ${DIR}
    if [ $? -ne 0 ]; then
        echo "Make errors"
        make -C ${DIR} clean
        exit 1
    else
        mv ${DIR}philo ./
    fi
    make -C ${DIR} clean
    touch ${LOG}out.txt
}

function print_aligned() {
    local line_number=$1
    local command=$2
    local status=$3
    local color

    if [ "$status" -eq "OK" ]; then
        color = $GREEN
    elif [ "$status" -eq "KO"]; then
        color = $RED
    else
        return
    fi
    printf "${color}%-3s %-28s %5s\n${RESET}" "$line_number" "$command" "$status"
}

function finish()
{
    rm -f ${LOG}* ./philo
    > ${LOG}out.txt
}

start
for ((i=0; i<2; i++)); do
    ./philo "${die[$i,0]}" "${die[$i,1]}" "${die[$i,2]}" "${die[$i,3]}" |
    head -n 30 | grep "died" >> ${LOG}out.txt
done
finish