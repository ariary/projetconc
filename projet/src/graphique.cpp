#include "include/graphique.h"
#include <iostream>
#include "include/contexte.h"
#include <unistd.h>

using namespace std;


void *afficher (void *t){
	cout << ">> debut thread graphique" <<endl;
	if (t != nullptr){
      	terrain* ptr_terrain =(terrain*) t;// recuperation du contexte applicatif
        //terrain* t=ptr_terrain;
        //if(ptr_contexte->_etape != 1){
		        sf::RenderWindow window(sf::VideoMode(512, 128), "Titre");
		   		window.clear(sf::Color(214,214,214));
			    sf::Color black = sf::Color::Black;
			    sf::Color white = sf::Color::White;
			    sf::Color red = sf::Color::Red;
		    	
		      	while (window.isOpen() || !ptr_terrain->finish()){
		      			//cout << "salutxxx" <<endl;
                    for (int i = 0; i < ptr_terrain->liste_personnes.size(); ++i)
                    {
                        ptr_terrain->liste_personnes.at(i).print_personne(); 
                    }
                    if(ptr_terrain->finish()){
                        
                        break;
                    }

		      			window.clear();
				        for(int i = 0; i < 128; i++){
				            for(int j = 0; j < 512; j++){
				                sf::RectangleShape rectangle;
				                rectangle.setSize(sf::Vector2f(1, 1)); // Taille (1x1)
				                rectangle.setPosition(j, i); //Position sur l'écran");
				                //sa couleur : 
				                switch(ptr_terrain->matrice.at(i).at(j)){
				                    case 2 : rectangle.setFillColor(black);
				                            break;
				                    case 1 : rectangle.setFillColor(red);
				                            break;
				                    //default: rectangle.setFillColor(white);
				                      //      break;
				                }
				                window.draw(rectangle);
				            }
				        }
				        window.display();

                        
		        }
		   	 		cout << "la simulation est terminée" << endl;
				    window.close();
      	//}
   }else{
   		cout<< "problème dans la récupération du contexte applicatif du thread (affichage graphique)"<<endl;
   }
   cout << ">> fin du thread graphique" <<endl;
} 



/*void* afficher(terrain* t){
    /* ici faire la partie graphique */
    /*sf::RenderWindow window(sf::VideoMode(512, 128), "Titre");

    window.clear(sf::Color(214,214,214));
     
    sf::Color black = sf::Color::Black;
    sf::Color white = sf::Color::White;
    sf::Color red = sf::Color::Red;
    //t.print_liste_personnes(); 
    while (window.isOpen())
    {
        for(int i = 0; i < 128; i++){
            for(int j = 0; j < 512; j++){
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(1, 1)); // Taille (1x1)
                rectangle.setPosition(j, i); //Position sur l'écran");
                //sa couleur : 
                switch(t.matrice.at(i).at(j)){
                    case 2 : rectangle.setFillColor(black);
                            break;
                    case 1 : rectangle.setFillColor(red);
                            break;
                    default: rectangle.setFillColor(white);
                            break;
                }
                window.draw(rectangle);
            }
        }
        window.display();
        cout << "la simulation est terminée" << endl;
        window.close();
    }
}*/