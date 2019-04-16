# MySQL Decimal(string) to double test
# - hjkim, 2019.04.16

#!/bin/sh



GCC_BIN=/usr/bin/g++
INCS="
	-I/usr/include/mysql \
	-I/usr/include/mysql++ \
"
OPTS="-Wall -O2 -std=c++11"
LIBS="
	-lmysqlpp \
	-lmysqlclient \
"


echo $GCC_BIN -o mysql_test mysql_test.cpp $OPTS $INCS $LIBS
$GCC_BIN -o mysql_test mysql_test.cpp $OPTS $INCS $LIBS


