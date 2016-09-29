/*
 * Personne.h
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 */

#ifndef PERSONNE_H_
#define PERSONNE_H_

class personne {
	private:
		int position_x;
		int position_y;
		int position_x_fin;
		int position_y_fin;

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
		int get_pos_x_fin();
		int get_pos_y_fin();



};

#endif /* PERSONNE_H_ */
