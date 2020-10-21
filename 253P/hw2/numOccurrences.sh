#!/bin/bash
set -x

PROGRAM=./numOccurrences

ls -l
cat Makefile $PROGRAM
make $PROGRAM
ls -l

echo "example from assignment"
valgrind $PROGRAM na bananas
valgrind $PROGRAM na potato

echo "test input"
valgrind $PROGRAM ab ababa
valgrind $PROGRAM aba ababa
valgrind $PROGRAM man batman
valgrind $PROGRAM any batman

echo "important edge case 1"
valgrind $PROGRAM batman man

echo "important edge case 2"
valgrind $PROGRAM @$% %$^*
valgrind $PROGRAM %$ @%$^*

echo "important edge case 3"
valgrind $PROGRAM Bat batman
