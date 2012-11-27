#!/bin/bash

rm -rf Makefile Makefile.in aclocal.m4 autom4te.cache config.guess config.h config.h.in config.log config.status config.sub configure depcomp install-sh libtool ltmain.sh missing mkinstalldirs stamp-h1 autoscan.log configure.scan

echo autoheader
autoheader

echo aclocal
aclocal

echo libtoolize --force
libtoolize --force

echo automake --add-missing
automake --add-missing

echo automake
automake

echo autoconf
autoconf

echo ./configure
./configure

echo make clean
make clean

echo make
make

#echo make install
#make install
