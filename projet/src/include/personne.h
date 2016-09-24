#ifndef PERSONNE_H
#define PERSONNE_H
typedef struct Personne{
	int position_x;
	int position_y;
}Personne;


void move();

void app();//appellera move sur chaque personne
#endif


