#!/bin/bash

if (( $# == 1 ))
then
    make clean && make
fi
bin/main test_io/test_in.txt test_io/test_out.txt
