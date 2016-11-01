/*
 * Terrain.h
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 *
 * Version: rendu du 10 octobre 2016
 *
 * Declaration de la classe modélisant le terrain (ressource partagée)
 *
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
		std::vector<personne> liste_personnesNO;
		std::vector<personne> liste_personnesNE;
		std::vector<personne> liste_personnesSO;
		std::vector<personne> liste_personnesSE;
		std::vector< std::vector<int> > matrice;
		void init_muret();
		terrain(int nombre_personnes);
		int get_nombre_personnes();
		void print_matrice();
		void print_liste_personnes();
		void initialiser_matrice();
		bool finish();
		void avancer(personne& p);
		void enlever_personne(personne& p);
		void deplacement_personne_SO(personne& p);
		void deplacement_personne_S(personne& p);
		void deplacement_personne_NO(personne& p);
		void deplacement_personne_N(personne& p);
		void deplacement_personne_O(personne& p);
		bool arrive(personne& p);

		void refresh_vector_personnesNE();
		void refresh_vector_personnesSE();
		void refresh_vector_personnesNO();
		void refresh_vector_personnesSO();
};


#endif /* TERRAIN_H_ */
