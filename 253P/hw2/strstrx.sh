set -x

PROGRAM=./strstrx

ls -l
cat Makefile $PROGRAM
make $PROGRAM
ls -l

echo "example from assignment"
valgrind $PROGRAM chem alchemy
valgrind $PROGRAM chem heartache

echo "test input"
valgrind $PROGRAM batman batman
valgrind $PROGRAM man batman
valgrind $PROGRAM any batman
valgrind $PROGRAM ab ababa

echo "important edge case 1"
valgrind $PROGRAM batman man

echo "important edge case 2"
valgrind $PROGRAM @$% %$^*
valgrind $PROGRAM %$ @%$^*

echo "important edge case 3"
valgrind $PROGRAM Bat batman
