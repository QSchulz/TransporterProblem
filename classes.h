#ifndef CLASSES_H
#define CLASSES_H

#include <stdlib.h>
#include <vector>
#include <iostream>

extern float ETA;

//using namespace std;

class Client{
	private:
		float cout_stockage=0.f;
		int numero=0;
		int distance_fournisseur=0;
	public:
		Client(int numero, float cout_stockage, int distance);
		float getCoutStockage();
		int getNumero();	
		int getDistanceFournisseur();
};

class Commande{
	private:
		Client* client=NULL;
		int quantite=0;
		float date_limite=0.f;
		int numero=0;
	public:
		Commande(Client* client, int quantite, float date_limite, int numero);
		Client* getClient();
		int getQuantite();
		void setQuantite(int quantite);
		float getDateLimite();
		int getNumero();
		float getCout(float date_livraison);	
		friend std::ostream& operator<<(std::ostream& out, const Commande& commande);	
};

class Trajet{
	private:
		/* Commandes venant du même client que l'on peut envoyer en un seul trajet */
		std::vector<Commande> commandes;
		float date_depart=0.f;
	public:
		Trajet(Commande commande);
		std::vector<Commande> getCommandes();
		void addCommande(Commande commande);
		float getCout();
		float getDateLimite();
		float getDateDepart();
		void setDateDepart(float date_depart_limite);
};

class Livraison{
	private:
		std::vector<Trajet> trajets;
		float date_depart=0.f;
		float cout=0.f;
	public:
		Livraison();
		std::vector<Trajet> getTrajets();
		float getDateDepart();
		float getCout();
		bool addTrajet(Trajet trajet);
		void updateCout();
		bool changeLast(Trajet trajet, bool firstTime);
		
		friend std::ostream& operator<<(std::ostream& out, const Livraison& livraison);
		
};



#endif
