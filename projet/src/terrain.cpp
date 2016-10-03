#include "include/terrain.h"
#include <stdlib.h>
#include <list>

using namespace std;

terrain::terrain(int nombre_personnes) {
	this->matrice = std::vector<std::vector<int> > (128, std::vector<int>(512));
	this->nb_personnes = nombre_personnes;
	this->liste_personnes;
	this->initialiser_matrice();
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
	std::vector<personne>::iterator it;
	srand (time(NULL));
	for(int i = 0; i < this->nb_personnes; i++){
		rand_X = rand() % 128;
		rand_Y = rand() % 512;

		while(!this->coordonnees_correctes(rand_X, rand_Y)){
			rand_X = rand() % 128;
			rand_Y = rand() % 512;
		}
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

	for (vector<personne>::iterator it=this->liste_personnes.begin(); it!=this->liste_personnes.end(); ++it)
	    it-> print_personne();

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

bool terrain::finish(){
	return this->nb_personnes == 0;
}

void terrain::avancer_personne(personne& p){
	//personne p = this->liste_personnes.at(indicePersonne);
	if(p.aFini()){
		this->enlever_personne(p);
	}else{ 
		if(p.au_dessus_azimuth1()){
				this->deplacement_personne_SO(p);
		}else{
			/*if(p.au_dessous_azimuth2())
				this->deplacement_personne_NO(indicePersonne);
			else
				this->deplacement_personne_O(indicePersonne);
				*/
		}
	}

}

void terrain::enlever_personne(personne& p){
	for(int i = 0; i < this->liste_personnes.size(); i++){
		if(this->liste_personnes.at(i).get_pos_x() == p.get_pos_x() && this->liste_personnes.at(i).get_pos_y() == p.get_pos_y()){
			this->liste_personnes.erase(this->liste_personnes.begin() + i);
			break;
		}
	} 
	//mettre les zéros dans la matrice pour faire disparaitre la personne arrivée
	this->nb_personnes--;
}

void terrain::deplacement_personne_SO(personne& p){
	//personne p = this->liste_personnes.at(indice);
	bool possible_deplacement = true;
	if(this->matrice.at(p.get_pos_x()+1).at(p.get_pos_y()-1) == 1 || this->matrice.at(p.get_pos_x()+1).at(p.get_pos_y()-1) == 2)
		possible_deplacement = false;
	if(this->matrice.at(p.get_pos_x()+2).at(p.get_pos_y()-1) == 1 || this->matrice.at(p.get_pos_x()+2).at(p.get_pos_y()-1) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()+3).at(p.get_pos_y()-1) == 1 || this->matrice.at(p.get_pos_x()+3).at(p.get_pos_y()-1) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()-1) == 1 || this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()-1) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()) == 1 || this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()+1) == 1 || this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()+1) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()+2) == 1 || this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()+2) == 2)
		possible_deplacement = false;
	
	if(possible_deplacement){
		this->matrice.at(p.get_pos_x()+1).at(p.get_pos_y()-1) = 1;
		this->matrice.at(p.get_pos_x()+2).at(p.get_pos_y()-1) = 1;
		this->matrice.at(p.get_pos_x()+3).at(p.get_pos_y()-1) = 1;
		this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()-1) = 1;
		this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()) = 1;
		this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()+1) = 1;
		this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()+2) = 1;


		this->matrice.at(p.get_pos_x()).at(p.get_pos_y()) = 0;
		this->matrice.at(p.get_pos_x()).at(p.get_pos_y()+1) = 0;
		this->matrice.at(p.get_pos_x()).at(p.get_pos_y()+2) = 0;
		this->matrice.at(p.get_pos_x()).at(p.get_pos_y()+3) = 0;
		this->matrice.at(p.get_pos_x()+1).at(p.get_pos_y()+3) = 0;
		this->matrice.at(p.get_pos_x()+2).at(p.get_pos_y()+3) = 0;
		this->matrice.at(p.get_pos_x()+3).at(p.get_pos_y()+3) = 0;

		
		this->liste_personnes.erase(liste_personnes.begin()+indice);
		personne newP = personne(p.get_pos_x()+1,p.get_pos_y()-1);
		//newP.print_personne();
		this->liste_personnes.insert(liste_personnes.begin()+indice,newP);	
		if(this->arrive(indice)){
			this->enlever_personne(indice);
		}
	}/*else{
		this->deplacement_personne_S(indice);
	}*/
}

void terrain::deplacement_personne_S(int indice){
	//verifier si on peut aller vers le Sud
	/*personne p = this->liste_personnes.at(indice);
	bool possible_deplacement = true;
	for(int i = 0; i < 3;i++){
		if(this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()+i) == 1 || this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y()+i) == 2)
			possible_deplacement = false;
	}
	
	if(possible_deplacement){
		for(int i = 0; i < 3; i++){
			this->matrice.at(p.get_pos_x()+4).at(p.get_pos_y() + i) = 1;
			this->matrice.at(p.get_pos_x()).at(p.get_pos_y() + i) = 0 ;
		}
		this->liste_personnes.erase(liste_personnes.begin()+indice);
		personne newP = personne(p.get_pos_x()+1,p.get_pos_y());
		this->liste_personnes.insert(liste_personnes.begin()+indice,newP);
	}*/
}


void terrain::deplacement_personne_NO( int indicePersonne){
	/*personne p = this->liste_personnes.at(indicePersonne);
	bool possible_deplacement = true;
	if(this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()-1) == 1 || this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()-1) == 2)
		possible_deplacement = false;
	if(this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()) == 1 || this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()+1) == 1 || this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()+1) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()+2) == 1 || this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()+2) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()).at(p.get_pos_y()-1) == 1 || this->matrice.at(p.get_pos_x()).at(p.get_pos_y()-1) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()+1).at(p.get_pos_y()-1) == 1 || this->matrice.at(p.get_pos_x()+1).at(p.get_pos_y()-1) == 2)
		possible_deplacement = false;
	
	if(this->matrice.at(p.get_pos_x()+2).at(p.get_pos_y()-1) == 1 || this->matrice.at(p.get_pos_x()+2).at(p.get_pos_y()-1) == 2)
		possible_deplacement = false;
	
	if(possible_deplacement){
		this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()-1) = 1;
		this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()) = 1;
		this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()+1) = 1;
		this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()+2) = 1;
		this->matrice.at(p.get_pos_x()).at(p.get_pos_y()-1) = 1;
		this->matrice.at(p.get_pos_x()+1).at(p.get_pos_y()-1) = 1;
		this->matrice.at(p.get_pos_x()+2).at(p.get_pos_y()+1) = 1;


		this->matrice.at(p.get_pos_x()).at(p.get_pos_y()+3) = 0;
		this->matrice.at(p.get_pos_x()+1).at(p.get_pos_y()+3) = 0;
		this->matrice.at(p.get_pos_x()+2).at(p.get_pos_y()+3) = 0;
		this->matrice.at(p.get_pos_x()+3).at(p.get_pos_y()+3) = 0;
		this->matrice.at(p.get_pos_x()+3).at(p.get_pos_y()) = 0;
		this->matrice.at(p.get_pos_x()+3).at(p.get_pos_y()+1) = 0;
		this->matrice.at(p.get_pos_x()+3).at(p.get_pos_y()+2) = 0;

		
		this->liste_personnes.erase(liste_personnes.begin()+indicePersonne);
		personne newP = personne(p.get_pos_x()-1,p.get_pos_y()-1);
		//newP.print_personne();
		this->liste_personnes.insert(liste_personnes.begin()+indicePersonne,newP);	
		if(this->arrive(indicePersonne)){
			this->enlever_personne(indicePersonne);
		}
	}else{
		this->deplacement_personne_N(indicePersonne);
	}
	*/
}

void terrain::deplacement_personne_N(int indice){
	//verifier si on peut aller vers le Nord
	/*personne p = this->liste_personnes.at(indice);
	bool possible_deplacement = true;
	for(int i = 0; i < 3;i++){
		if(this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()+i) == 1 || this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y()+i) == 2)
			possible_deplacement = false;
	}
	
	if(possible_deplacement){
		for(int i = 0; i < 3; i++){
			this->matrice.at(p.get_pos_x()-1).at(p.get_pos_y() + i) = 1;
			this->matrice.at(p.get_pos_x()+3).at(p.get_pos_y() + i) = 0 ;
		}
		this->liste_personnes.erase(liste_personnes.begin()+indice);
		personne newP = personne(p.get_pos_x()-1,p.get_pos_y());
		this->liste_personnes.insert(liste_personnes.begin()+indice,newP);
	}*/
}
void terrain::deplacement_personne_O( int indicePersonne){
	//verifier si on peut aller vers l'ouest
	/*personne p = this->liste_personnes.at(indicePersonne);
	bool possible_deplacement = true;
	for(int i = 0; i < 3;i++){
		if(this->matrice.at(p.get_pos_x()+i).at(p.get_pos_y()-1) == 1 || this->matrice.at(p.get_pos_x()+i).at(p.get_pos_y()-1) == 2)
			possible_deplacement = false;
	}
	
	if(possible_deplacement){
		for(int i = 0; i < 3; i++){
			this->matrice.at(p.get_pos_x()+i).at(p.get_pos_y() - 1) = 1;
			this->matrice.at(p.get_pos_x()+i).at(p.get_pos_y() + 3) = 0 ;
		}
		this->liste_personnes.erase(liste_personnes.begin()+indicePersonne);
		personne newP = personne(p.get_pos_x(),p.get_pos_y()-1);
		this->liste_personnes.insert(liste_personnes.begin()+indicePersonne,newP);
		if(this->arrive(indicePersonne)){
			this->enlever_personne(indicePersonne);
		}
	}*/
}

bool terrain::arrive(int indice){
	personne p = this->liste_personnes.at(indice);
	return p.get_pos_y() == 0;
}

std::vector<personne> terrain::get_vector_personneNE(){
	return this->liste_personnes;
}

std::vector<personne> terrain::get_vector_personneSE(){
	return this->liste_personnes;
}

std::vector<personne> terrain::get_vector_personneNO(){
	return this->liste_personnes;
}

std::vector<personne> terrain::get_vector_personneSO(){
	return this->liste_personnes;
}

void terrain::avancer(personne p){
	return;
}