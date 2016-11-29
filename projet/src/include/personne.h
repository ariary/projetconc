/*
 * Personne.h
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 *
 * Version: rendu du 10 octobre 2016
 *
 * Declaration de la classe représentant les personnes présentes sur le terrain
 */

#ifndef PERSONNE_H_
#define PERSONNE_H_
#include <iostream>


class personne {
	private:
		int position_x;
		int position_y;


	public:
		personne(int x, int y);
		void print_personne();
		bool aFini();

		int get_pos_x();
		int get_pos_y();

		void changer_position(int newX,int newY);
		void set_position(int x, int y);

		bool droite_du_centre();
		bool au_dessus_azimuth1();
		bool au_dessous_azimuth2();

		bool near_NO();
		bool near_SO();
		bool near_SE();
		bool near_NE();

		bool isOut();
		

};

#endif /* PERSONNE_H_ */
