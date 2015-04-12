#!/bin/bash

n=$1

for (( i=0; i<n; i++ ))
{
    if (( $i==0 ))
    then
        ./run.sh 1
    else
        ./run.sh
    fi

    s=`diff test_io/test_in.txt test_io/test.dec`
    if [[ "$s" != "" ]]
    then
        printf "test number $i: Failed\n"
        printf "s is :'$s'\n"
        exit 1
    else
        printf "test number $i: OK\n"
    fi

}
