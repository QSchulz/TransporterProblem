#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include "classes.h"
#include "parse.h"

Livraison* livraison_optimale=NULL;
int CAPA=0;
float ETA=0.f;

void merge(std::vector<Commande>* restant, Commande lastElement, Livraison* livraison)
{
	//TODO
}

void check_validity(std::vector<Commande>* commandes)
{
	std::vector<Commande>::iterator it = commandes->begin();
	for (int i(0); i<commandes->size(); i++)
	{
		it++;
		if ((*commandes)[i].getQuantite()>CAPA)
		{
			it = commandes->insert(it, Commande((*commandes)[i].getClient(), (*commandes)[i].getQuantite()-CAPA, (*commandes)[i].getDateLimite(), (*commandes)[i].getNumero()));
			(*commandes)[i].setQuantite(CAPA);
		}
	}
}

void permut(std::vector<Commande> restant, Livraison livraison)
{
	if (restant.size()==0)
	{
		if (livraison_optimale == NULL)
		{
			livraison_optimale = new Livraison();
			*livraison_optimale = livraison;
		}
		else if (livraison_optimale->getCout()>livraison.getCout())
			*livraison_optimale = livraison;
		return;
	}
	int i(0);
	std::vector<Commande>::iterator it = restant.begin();
	std::vector<Commande>::iterator end = restant.end();
	bool firstTime=true;
	while(it != end)
	{
		Commande commande = *it;
		if (livraison.changeLast(Trajet(commande), firstTime))
		{
			firstTime = false;
			if (livraison_optimale!=NULL && livraison.getCout()>=livraison_optimale->getCout())
				break;
			std::vector<Commande> merge_commandes(restant);
			std::vector<Commande>::iterator iter = merge_commandes.begin();
			for (int k(0); k<i; k++)
				iter++;
			merge_commandes.erase(iter);
			//checker le merge de commandes pour le même client
			merge(&merge_commandes, commande, &livraison);
			permut(merge_commandes, livraison);
		}
		i++;
		it++;
	}
	
}

 
int main(int argc, char** argv){
	int nbProduits=0, nbClients=0;
	std::vector<Commande> commandes = std::vector<Commande>();
	std::vector<Client> clients = std::vector<Client>();
	
	if (argc!=2)
	{
		printf("Commande invalide.\nAppelez le programme comme suit: \"./prog file\" (avec file le fichier contenant les données du problème).\n");
		exit(0);
	}
	/* On remplit les valeurs du problème grâce au parse */
	parse(argv[1], &nbProduits, &nbClients, &CAPA, &ETA, &commandes, &clients);
	
	//vérifier que les commandes ne dépassent pas la capacité du camion, sinon, il faut les dissocier
	check_validity(&commandes);
	//vérifier que 2+ commandes pour le même client ne sont pas à moins de 200 unités de temps l'une des autres, sinon, scinder les 2+ commandes ==> à vérifier dans addTrajet()
		
		//==> est-ce qu'il y a toujours un intérêt?
	
	permut(commandes, Livraison());
	
	std::cout << *livraison_optimale;
	return EXIT_SUCCESS;
}

