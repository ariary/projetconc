#include "include/terrain.h"
#include <stdlib.h>
#include <list>

using namespace std;

terrain::terrain(int nombre_personnes) {
	this->matrice = std::vector<std::vector<int> > (128, std::vector<int>(512));
	this->nb_personnes = nombre_personnes;
	this->nb_threads = 1; //pour l'instant à 1
	this->initialiser_matrice();
//	this->liste_personnes = std::list(nombre_personnes, 0);
}

void terrain::print_matrice(){
	for(int i = 0; i < this->matrice.size(); i++){
		for (int j = 0; j < this->matrice.at(i).size(); j++ ){
			cout << this->matrice.at(i).at(j);
		}
		cout << endl;
	}
}

void terrain::initialiser_matrice(){

	//on met tous les pixels à 0
	for(int i = 0; i < 128; i++){
		for(int j = 0; j < 512; j++){
			this->matrice.at(i).at(j) = 0;
		}
	}
	this->init_muret();
	//on va prendre deux nombres au hasard (coordonnées x et y) pour insérer les personnes sur le terrain
	int rand_X;
	int rand_Y;
	std::list<personne>::iterator it;
	srand (time(NULL));
	for(int i = 0; i < this->nb_personnes; i++){
		rand_X = rand() % 128;
		rand_Y = rand() % 512;

		while(!this->coordonnees_correctes(rand_X, rand_Y)){
			rand_X = rand() % 128;
			rand_Y = rand() % 512;
		}
		cout << "rand_X : " << rand_X << " rand_Y : " << rand_Y << endl;
		//on peut mettre la personne sur la matrice
		for(int j = 0 ; j < 4; j++){
			for(int k = 0; k < 4; k++){
				this->matrice.at(rand_X + j).at(rand_Y + k) = 1;
			}
		}
		personne p(rand_X,rand_Y);
		this->liste_personnes.push_back(p);
	}
}

bool terrain::coordonnees_correctes(int pos_x,int pos_y){

	//on gère d'abord les effets de bord
	if(pos_y + 3 >= 512)
		return false;
	if(pos_x + 3 >= 128)
		return false;

	//on gère la collision avec les autres personnes et les murs sur le terrain
	for(int x = 0; x < 4; x++){
		for(int y = 0; y < 4; y++){
			if(this->matrice.at(pos_x+x).at(pos_y+y) == 1 || this->matrice.at(pos_x+x).at(pos_y+y) == 2 )
					return false;
		}
	}
	return true;
}


void terrain::print_liste_personnes(){

	for (list<personne>::iterator it=this->liste_personnes.begin(); it!=this->liste_personnes.end(); ++it)
	    cout << "(" << it->get_pos_x() << ", " << it->get_pos_y() << ")" << endl;

}

void terrain::init_muret(){

	//création du premier muret
	for(int i = 0; i < 128; i++){
		for(int j = 0; j < 16; j++){
			if(i == 60)
				i +=8;
			else
				this->matrice.at(i).at(j) = 2;
		}
	}
	for(int i = 0; i < 128; i++){
		for(int j = 112; j < 128; j++){
			if(i == 56)
				i += 16;
			else
				this->matrice.at(i).at(j) = 2;
		}
	}

}
int terrain::get_nombre_personnes(){
	return this->nb_personnes;
}

