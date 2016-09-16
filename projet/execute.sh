#!/bin/bash
parametre=($1 $2 $3)
if [ $# -gt 3 ]
then
	echo -e "Execution annulée: vous avez rentrez trop de paramètres \n"
else
	cd bin
	echo ${parametre[*]}
	#ligne d'execution exemple: ./main ${parametre[*]}
fi
