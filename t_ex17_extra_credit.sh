#!/bin/bash
set -e

PROGNAME=./ex17_extra_credit
DBFILE=my.db

# create
CMD="$PROGNAME $DBFILE c"
echo $CMD
$CMD

# set
CMD="$PROGNAME $DBFILE s 1 zed zed@zedshaw.com street1 12345 city1 CA US"
echo $CMD
$CMD

CMD="$PROGNAME $DBFILE s 2 frank frank@zedshaw.com street2 12345 city2 CA US"
echo $CMD
$CMD

CMD="$PROGNAME $DBFILE s 3 joe joe@zedshaw.com street3 12345 city3 CA US"
echo $CMD
$CMD

# list
CMD="$PROGNAME $DBFILE l"
echo $CMD
$CMD

# find
CMD="$PROGNAME $DBFILE f zed"
echo $CMD
$CMD
CMD="$PROGNAME $DBFILE f CA"
echo $CMD
$CMD
CMD="$PROGNAME $DBFILE f US"
echo $CMD
$CMD
