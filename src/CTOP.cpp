#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cstring>
#include "CTOP.hpp"

using namespace std;
using namespace ctop;

CTOP::CTOP() {
   this->locations = Graph();
   this->capacity = 0;
}

CTOP::~CTOP() {

}

bool CTOP::operator()(const string& filename) {
   // abrir arquivo
   // ler header criando Grafo e inicializando os atributos desta classe
   // leitura do CUSTUMERDATA

   cout << "> Abrindo arquivo " << filename.c_str() << endl << endl;
   // Abre o arquivo de entrada
   ifstream file(filename.c_str());
   // Se o arquivo n�o puder ser aberto ou n�o existir, sai do programa
   if(file.fail()) {
      cout << "\n\nArquivo n�o encontrado" << endl;
      return false;
      //exit(1);
   }

   cout << "> Carregando dados..." << endl;

   char read[size];
   stringstream convert;
   string word;

   file.ignore(ign,'\n'); //pula as duas primeiras linhas
   file.ignore(ign,'\n');

   file.ignore(size,' '); // l� a quantidade de ve�culos
   file.get(read,size,'\n');
   convert << read;
   convert >> word;
   nVehicles = atoi(word.c_str());
   cout<<atoi(word.c_str())<<endl;
   file.get();
   convert.clear();

   for(int i=0; i<nVehicles; i++) {
      std::vector<int> v = std::vector<int>();
      vehicles.push_back(v);
   }

   file.ignore(size,' '); // l� a capacidade m�xima
   file.get(read,size,'\n');
   convert << read;
   convert >> word;
   capacity = atoi(word.c_str());
   cout<<capacity<<endl;
   file.get();
   convert.clear();

   file.ignore(size,' '); // l� o tempo m�ximo
   file.get(read,size,'\n');
   convert << read;
   convert >> word;
   time = atoi(word.c_str());
   cout<<time<<endl;
   file.get();
   convert.clear();

   file.ignore(ign,'\n');
   file.ignore(size,' ');

   CTOPVertexData data;
   Point p;
   file >> p;
   data.coord = p;
   data.demand = 0;
   data.timeServ = 0;
   data.profit = 0;
   data.setAsDepot();
   locations.insertVertex(data);

   file.ignore(ign,'\n');

   file.ignore(size,' '); // l� o tempo m�ximo
   file.get(read,size,'\n');
   convert << read;
   convert >> word;
   cout<<atoi(word.c_str())<<endl;
   file.get();
   convert.clear();

//  customers = atoi(word.c_str());

   file.ignore(ign,'\n');
   file.ignore(ign,'\n');
   while(!file.eof()) {
      CTOPVertexData data;
      file >> data;
      cout<<data<<endl;
      locations.insertVertex(data);
   }

   cout<<locations<<endl;

   return true;
}

void CTOP::start(METHOD m) {
   int depot = getDepot();

   for(unsigned int i = 0; i<nVehicles; i++){
      vehicles.at(i).push_back(depot);
   }

   ordersEdges();

   for(unsigned i = 0; i<nVehicles; i++){

   }
}

bool CTOP::check(vector<vehicles>) {
   /*
   se o somat�rio do lucro de todos os caminh�es foi maior ou igual a melhor solu��o mais com um somat�rio de tempo menor que a melhor solu��o, solu��o � melhor.
   */
}

void CTOP::ordersEdges() {
   sort(orderedEdges.begin(), orderedEdges.end(), compare);
}

int CTOP::getDepot(){
   for(int i=0;i < locations.getNumberVertexes();i++){
      if(locations.getVertexData(i).isDepot()){
         return i;
      }
   }

   return NULL;
}

/// Classes Internas
// CTOPVertexData
CTOP::CTOPVertexData::CTOPVertexData() {

}

CTOP::CTOPVertexData::~CTOPVertexData() {

}

bool CTOP::CTOPVertexData::empty() const {
   return false;
}

// CTOPEdgeData
CTOP::CTOPEdgeData::CTOPEdgeData() {

}

CTOP::CTOPEdgeData::~CTOPEdgeData() {

}

bool CTOP::CTOPEdgeData::empty() const {
   return false;
}
