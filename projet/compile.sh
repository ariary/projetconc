#!/bin/bash

#Equipe 19: Adrien Prestini & Antoine Rabenandrasana
path=`dirname $0`
cd $path
mkdir $path/bin
test "graphique" = "$1"
res=$?
juste=0
if [ "$res" -eq "$juste" ];
then
	echo "Compilation avec interface graphique"
	make GRAPHIQUE=yes
else
	echo "Compilation sans interface graphique"
	make GRAPHIQUE=no
fi