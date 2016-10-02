/*
 * Personne.h
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
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
		void avancer_nord();
		void avancer_nord_est();
		void avancer_nord_ouest();
		void avancer_sud();
		void avancer_sud_est();
		void avancer_sud_ouest();
		void avancer_est();
		void avancer_ouest();
		void print_personne();
		bool aFini();

		int get_pos_x();
		int get_pos_y();

		bool au_dessus_azimuth1();
		bool au_dessous_azimuth2();
		void changer_position(int newX,int newY);



};

#endif /* PERSONNE_H_ */
