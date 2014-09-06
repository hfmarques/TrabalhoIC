#include <iostream>
#include <fstream>

#include "CTOP.hpp"

using namespace std;
using namespace ctop;

int main(int argc, char* args[]) {
   Graph g1, g2;
   g1(23);
   for(int i = 0; i < 23; i++)
      g1.setVertexLabel(i, i+2);
   g2(7);
   for(int i = 0; i < 7; i++)
      g2.setVertexLabelToId(i);
   g1.completeGraph();
   g2.completeGraph();
   g1.label = "G1";
   g2.label = "G2";

   cout << g1 << endl;
   cout << g2 << endl << endl;

//	ifstream file("../data/teste.tst"); // parte do arquivo
//	float is[50];
//
//	int n = 0;
//	while(!file.eof())
//		file >> is[n++];
//
//	for(int j = 0; j < n; j++) cout << is[j] << " ";
//	cout << endl;


   string filename;
   int numIteracoes;

   cout << "- Digite o nome e formato do arquivo\t>> ";
   cin >> filename;
   cout << "- Digite o numero maximo de iteracoes\t>> ";
   cin >> numIteracoes;

#ifdef _WIN32
   //      system("cls");
#else
   system("clear");
#endif

   filename = "../data/" + filename + ".cri";

   CTOP *cp = new CTOP();
   (*cp)(filename);


   return 0;
}
