typedef struct Terrain{
	int[][] taleau;
	int nb_personnes;
}Terrain;


void init(int nb_personnes, int nb_threads);//init les personnes sur le terrain avec le nombre de thread indiqué