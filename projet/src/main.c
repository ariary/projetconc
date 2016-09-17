#include <stdio.h>
#include <stdbool.h>
#include <time.h>

//main de test juste pour verifier si on peut créer un tableau 128 x 512 en C , ON NE PEUT PAS !!

int main(){

	bool tab[128][512];

	int compteurFail = 0;
	int compteurSucces = 0;
	printf("DEBUT\n");
	for(int i = 0; i < 128; i++){
		for(int j = 0; j < 512; j++){
			if(tab[i][j] != 0){
				printf("position %d, %d\n", i,j);
				compteurFail++;
			}else
				compteurSucces++;
		}
	}
	printf("compteur = fail %d, succes %d\n", compteurFail, compteurSucces);
	printf("FIN\n");
	return 0;
}








