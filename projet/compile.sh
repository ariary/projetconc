#!/bin/bash

echo -e "\nSi vous voulez compiler le simulateur sans partie graphique entrez 'sans' \nSinon entrez 'avec'"
read -n 5 pgrah
if [ $pgraph="avec" ]
then
	make avec
else
	make sans
fi

#j'aurais juste pu faire make $praph mais le nom de make avec par exemple peut changer