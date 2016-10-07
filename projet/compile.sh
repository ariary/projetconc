#!/bin/bash

#Equipe 19: Adrien Prestini & Antoine Rabenandrasana

mkdir bin
echo -e "\nSi vous voulez compiler le simulateur sans partie graphique entrez 'sans' \nSinon entrez 'avec'"
read -n 5 pgrah
if [ $pgraph="avec" ]
then
	make avec
else
	make sans
fi