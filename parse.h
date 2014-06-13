#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string.h>
#include "classes.h"

//using namespace std;

void parse(char* path, int* nbProduits, int* nbClients, int* capa, float* coutTransport, std::vector<Commande>* commandes, std::vector<Client>* clients);

#endif
