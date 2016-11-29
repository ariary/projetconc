#include "include/graphique.h"
#include <iostream>
#include "include/contexte.h"
#include <unistd.h>

using namespace std;


void *afficher (void *p_data){
	cout << "debut thread graphique" <<endl;
	if (p_data != nullptr){
      	Contexte* ptr_contexte =(Contexte*) p_data;// recuperation du contexte applicatif
        terrain* t=ptr_contexte->t;
        //if(ptr_contexte->_etape != 1){
		        sf::RenderWindow window(sf::VideoMode(512, 128), "Titre");
		   		window.clear(sf::Color(214,214,214));
			    sf::Color black = sf::Color::Black;
			    sf::Color white = sf::Color::White;
			    sf::Color red = sf::Color::Red;
		    	
		      	while (window.isOpen() || !t->finish()){
		      			//cout << "salutxxx" <<endl;
                    if(t->finish()){
                        cout << "finish" << endl;
                        break;
                    }

		      			window.clear();
				        for(int i = 0; i < 128; i++){
				            for(int j = 0; j < 512; j++){
				                sf::RectangleShape rectangle;
				                rectangle.setSize(sf::Vector2f(1, 1)); // Taille (1x1)
				                rectangle.setPosition(j, i); //Position sur l'écran");
				                //sa couleur : 
				                switch(t->matrice.at(i).at(j)){
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
   cout << "fin du thread graphique" <<endl;
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