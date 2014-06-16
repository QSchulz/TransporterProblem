#include "parse.h"

void parse(char* path, int* nbProduits, int* nbClients, int* capa, float* coutTransport, std::vector<Commande>* commandes, std::vector<Client>* clients)
{
	std::string line;

	char* copystring;
	char* copy = NULL;
	int JOBLINE=-1;
	int compteur = 1, i, numclient;
	std::ifstream f(path);
	int *storeclients,k=0;

	if(f.is_open())
	{
		while(getline(f,line))
		{
			if(copy)
				delete[] copy;
			copy = new char[strlen(line.c_str())+1];
			strcpy(copy, line.c_str());

			/*	on teste les différentes valeurs de compteur 	*/
			if(compteur == 1)
			{
				/*	Nombre de produits */
				copystring = strtok(copy, ":");
				copystring = strtok(NULL, ":");
				(*nbProduits) = atoi(copystring);
				std::cout << "Nombre de produits : " << (*nbProduits) << std::endl;
			}
			else if(compteur == 2)
			{
				/*	Nombre de clients	*/
				copystring = strtok(copy, ":");
				copystring = strtok(NULL, ":");
				(*nbClients) = atoi(copystring);
				std::cout << "Nombre de clients : " << (*nbClients) << std::endl;

				//clients = new Client[(*nbClients)];
			}
			else if(compteur == 3)
			{
				/*	Capacité du tansporteur	*/
					copystring = strtok(copy, ":");
					copystring = strtok(NULL, ":");
					(*capa) = atoi(copystring);
					std::cout << "Capacité du transporteur : " << (*capa) << std::endl;
			}
			else if(compteur == 4)
			{
				/*	Cout eta du transporteur	*/
				copystring = strtok(copy, ":");
				copystring = strtok(NULL, ":");
				(*coutTransport) = atof(copystring);
				std::cout << "Cout eta du transport : " << (*coutTransport) << std::endl;
			}
			else if(compteur == 5)
			{
				/*	On s'occupe de tous les clients : cout de stockage & temps de déplacement	*/
				for(i = 0; i < (*nbClients); ++i)
				{	
					/*	numéro du client	*/
					copystring = strtok(copy, ":");
					copystring = strtok(NULL, ":");
					numclient = atoi(copystring) - 1;					
					
					/*	cout de stockage	*/
					getline(f,line);
					delete[] copy;
					copy = new char[strlen(line.c_str())+1];
					strcpy(copy, line.c_str());
					copystring = strtok(copy, ":");
					copystring = strtok(NULL, ":");
					float cout = atof(copystring);
//					clients[numclient].cout_stockage = atof(copystring);

					/*	temps de livraison entre fournisseur et client	*/
					getline(f,line);
					delete[] copy;
					copy = new char[strlen(line.c_str())+1];
					strcpy(copy, line.c_str());
					copystring = strtok(copy, ":");
					copystring = strtok(NULL, ":");
					clients->push_back(Client(numclient, cout, atoi(copystring)));
					std::cout << "temps de transport du fournisseur au client " << numclient << " : " << atoi(copystring) << std::endl;
					std::cout << "coût de stockage chez le client " << numclient << " : " << clients->back().getCoutStockage() << std::endl;
		
					if(i < (*nbClients)-1)
					{
						getline(f,line);
						delete[] copy;
						copy = new char[strlen(line.c_str())+1];
						strcpy(copy, line.c_str());
					}
				}
			}
			else if(compteur == (5+3*(*nbClients)))
			{
				k=0;
				storeclients = (int*) malloc(sizeof(int)*(*nbProduits+1));
				/*	parse du numéro du client qui a demandé le job	*/
				std::cout << "jobs : " ;
				for(i = 0 ; i < (*nbProduits); ++i)
					std::cout << "\t" << (i+1);
				std::cout << "\nclts :  ";
				copystring = strtok(copy, ":;");
				while(copystring && k<*nbProduits)
				{
					copystring = strtok(NULL, ":;");
					/*	le num du client qui demande le job est dans copystring => tester si NULL	*/
					if(copystring)
					{
						storeclients[k++] = atoi(copystring);
						std::cout << atoi(copystring) << "\t";
					}
				}
				std::cout << std::endl;
			}
			else if(compteur == 5+3*(*nbClients)+1)
			{
				k=0;
				i=0;
				std::cout << "date : ";
				copystring = strtok(copy, ":;");
				while(copystring && k<*nbProduits)
				{
					copystring = strtok(NULL, ";");
					if(copystring)
					{
						commandes->push_back(Commande(&clients->at(storeclients[k++]-1), 1, atof(copystring), i++));
						std::cout << "\t" << atof(copystring);
					}
				}
				std::cout << '\n';
			}

			/*	incrémentation du compteur de ligne	*/
			if(compteur == 5)
				compteur += 3*(*nbClients);
			else
				++compteur;
		}
		f.close();
		delete[]  copy;
	}
	else
	{
		std::cout << "Error while opening file"	<< std::endl;
	}
}
