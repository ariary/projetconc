#!/bin/bash
parametre=($1 $2 $3)
if [ $# -gt 3 ]
then
	echo -e "Execution annulée: vous avez rentrez trop de paramètres \n"
else
	cd bin
	echo ${parametre[*]}
	#ligne d'execution exemple: ./main ${parametre[*]}
	#on doit rendre un executable qui permet dexecuter avec les options -m -p4 -t1
fi
