#include "classes.h"

Client::Client(int _numero, float _cout_stockage, int _distance):numero(_numero), cout_stockage(_cout_stockage), distance_fournisseur(_distance){};

float Client::getCoutStockage(){
	return cout_stockage;
}

int Client::getNumero(){
	return numero;
}	

int Client::getDistanceFournisseur(){
	return distance_fournisseur;
}


Commande::Commande(Client* _client, int _quantite, float _date_limite, int _numero):client(_client), quantite(_quantite), date_limite(_date_limite), numero(_numero){};

Client* Commande::getClient(){
	return client;
}

int Commande::getQuantite(){
	return quantite;
}

float Commande::getDateLimite(){
	return date_limite;
}

void Commande::setQuantite(int quantite){
	this->quantite = quantite;
}

int Commande::getNumero(){
	return numero;
}

float Commande::getCout(float date_depart){
	return quantite*(date_limite-date_depart+client->getDistanceFournisseur())*client->getCoutStockage();
}		


Trajet::Trajet(Commande commande){
	commandes.push_back(commande);
	date_depart = commande.getDateLimite()-commande.getClient()->getDistanceFournisseur();
}

std::vector<Commande> Trajet::getCommandes(){
	return commandes;
}

void Trajet::addCommande(Commande commande){
	commandes.push_back(commande);
}

float Trajet::getCout(){
	float cout=0;
	for (Commande commande : commandes)
		cout+=commande.getCout(date_depart)+commande.getClient()->getDistanceFournisseur()*2*ETA;
	return cout;
}

float Trajet::getDateDepart(){
	return date_depart;
}

void Trajet::setDateDepart(float date_depart_limite){
	date_depart = date_depart_limite;
}

void setDateDepart(float date_depart_limite);

std::vector<Trajet> Livraison::getTrajets(){
	return trajets;
}

Livraison::Livraison(){
	trajets= std::vector<Trajet>();
}

float Livraison::getDateDepart(){
	return date_depart;
}

float Livraison::getCout(){
	return cout;
}

bool Livraison::addTrajet(Trajet trajet){
	float date_depart_limite_cursor, date_depart_limite = trajet.getCommandes().front().getDateLimite()-trajet.getCommandes().front().getClient()->getDistanceFournisseur();
	trajet.setDateDepart(date_depart_limite);
	if (trajets.size()==0){}
	else if (trajets.back().getDateDepart()+trajets.back().getCommandes().front().getClient()->getDistanceFournisseur()<=date_depart_limite){}
	else{
		//Décalage
		//Pour la possibilité financière: faite dans le main.cpp
		int size = trajets.size();
		for (int i(size-1); i>=0; i--)
		{
			date_depart_limite_cursor = trajets[i].getDateDepart();
			if (date_depart_limite_cursor+2*trajets[i].getCommandes().front().getClient()->getDistanceFournisseur()<=date_depart_limite)
				break;
			else
			{
				date_depart_limite -= 2*trajets[i].getCommandes().front().getClient()->getDistanceFournisseur();
				if (date_depart_limite < 0)
					return false;
				trajets[i].setDateDepart(date_depart_limite);
			}
		}
	}
	trajets.push_back(trajet);
	date_depart = trajets[0].getDateDepart();
	updateCout();
	return true;
}

void Livraison::updateCout(){
	cout=0;
	int size=trajets.size();
	for (int i(0); i<size; i++)
		cout+=trajets[i].getCout();
}

bool Livraison::changeLast(Trajet trajet, bool firstTime){
	if (trajets.size()!=0 && !firstTime)
		trajets.pop_back();
	return addTrajet(trajet);
}

std::ostream& operator<<(std::ostream& out, const Livraison& livraison){
	out << livraison.date_depart << std::endl << livraison.cout << std::endl;
	return out;
}

