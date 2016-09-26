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
		std::vector< std::vector<int> > matrice;
		int nb_personnes;
		int nb_threads;
		std::list<personne> liste_personnes;
		bool coordonnees_correctes(int pos_x, int pos_y);

	public:
		void init_muret();
		terrain(int nombre_personnes);
		int get_nombre_personnes();
		void print_matrice();
		void print_liste_personnes();
		void initialiser_matrice();

};


#endif /* TERRAIN_H_ */
