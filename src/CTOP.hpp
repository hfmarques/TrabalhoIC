#ifndef _CTOP_HPP_
#define _CTOP_HPP_

#include "Graph.hpp"
#include "Point.hpp"

#define size 100 // Tamanho do vetor de leitura
#define ign 10000 // Qtd de caracteres a ignorar


namespace ctop {

class CTOP {
private:
   Graph 				locations;
   std::vector< std::vector<int> > 	vehicles;
   int nVehicles;
   int					capacity;
   int         time;

   //! Lista de arestas ordenada pela distância entre os vértices
   std::vector<Graph::Edge>   orderedEdges;
   //! Rotas de cada veículo
   std::vector<Graph>         rotes;

public:
   CTOP();
   virtual ~CTOP();

   enum METHOD {GREED = 0, GRA = 1};

   /** \brief Inicializador. Lê arquivo e carrega instância
   *	 \param file Caminho do arquivo com a instância do problema
   *	 \return true se instância criada com sucesso, false c.c.
   */
   bool operator () (const std::string& filename);

   /** \brief Inicia a busca da solução */
   void start(METHOD m = GREED);

   /** \brief Verificador. Checa a saída do problema, se solução é válida
   *	 \return true se solução válida, false c.c.
   */
   bool check();

   /** \brief Busca o vertice depósito
   *	 \return CTOPVertexData se encontrou, NULL c.c.
   */

   int getDepot();

private:
   // Ordena as arestas do Grafo pela distância entre os vértices
   void ordersEdges();

   class CTOPVertexData : public ProblemVertexData {
   public:
      Point coord;
      int demand, timeServ;
      float profit;
      bool $visited;

      CTOPVertexData();
      virtual ~CTOPVertexData();

      virtual bool empty() const;

      friend std::istream& operator >> (std::istream& in, CTOPVertexData& data) {
         in>> data.coord >> data.demand >> data.timeServ >> data.profit;
         return in;
      }

      friend std::ostream& operator << (std::ostream& out, CTOPVertexData& data) {
         out << "{ " << data.coord << ", " << data.demand << ", " << data.timeServ << ", " << data.profit << " }";
         return out;
      }

   };

   class CTOPEdgeData : public ProblemEdgeData {
   public:
      float distance;

      CTOPEdgeData();
      virtual ~CTOPEdgeData();

      virtual bool empty() const;
   };

   //class Automata

   static bool compare(const Graph::Edge& e1, const Graph::Edge& e2) {
      float profit1 = (static_cast<CTOPVertexData*>(e1.t.data))->profit;
      float profit2 = (static_cast<CTOPVertexData*>(e2.t.data))->profit;

      float dist1 = (static_cast<CTOPEdgeData*>(e1.data))->distance;
      float dist2 = (static_cast<CTOPEdgeData*>(e2.data))->distance;

      if(!profit1 && !profit2)
         return (dist1 < dist2);
      if(!profit1)
         return false;
      if(!profit2)
         return true;
      return ((dist1/profit1) < (dist2/profit2));
   }
};

}// namespace ctop

#endif // _CTOP_HPP_
