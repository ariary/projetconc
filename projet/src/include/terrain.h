/*
 * Terrain.h
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <vector>
#include <iostream>
#include <list>
#include "personne.h"

class terrain {
	private:
		
		int nb_personnes;
		
		bool coordonnees_correctes(int pos_x, int pos_y);

	public:
		std::vector<personne> liste_personnes;
		std::vector< std::vector<int> > matrice;
		void init_muret();
		terrain(int nombre_personnes);
		int get_nombre_personnes();
		void print_matrice();
		void print_liste_personnes();
		void initialiser_matrice();
		bool finish();
		void avancer_personne(int indicePersonne); //ce serait plus simple si on donnait en parametre une personne
		void avancer(personne p);
		void enlever_personne(int indice);
		void deplacement_personne_SO(int indice);
		void deplacement_personne_S(int indice);
		void deplacement_personne_NO(int indicePersonne);
		void deplacement_personne_N(int indicePersonne);
		void deplacement_personne_O(int indicePersonne);
		bool arrive(int indice);

		std::vector<personne> get_vector_personneNE();
		std::vector<personne> get_vector_personneSE();
		std::vector<personne> get_vector_personneNO();
		std::vector<personne> get_vector_personneSO();
};


#endif /* TERRAIN_H_ */
