#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <vector>

namespace ctop
{

/** \brief Classe abstrata para compor informa��es extras ao Vertex de Graph
*	 \class ProblemVertexData Graph.hpp "Graph.hpp"
*
*	Implemente uma especifica��o caso precise de mais informa��es armazenadas em um v�rtice do grafo
*/
class ProblemVertexData
{
	public:
		ProblemVertexData(){}
		virtual ~ProblemVertexData(){}

		virtual bool empty() const = 0;
};

/** \brief Classe abstrata para compor informa��es extras � Edge de Graph
*	 \class ProblemEdgeData Graph.hpp "Graph.hpp"
*
*	Implemente uma especifica��o caso precise de mais informa��es armazenadas numa aresta do grafo
*/
class ProblemEdgeData
{
	public:
		ProblemEdgeData(){}
		virtual ~ProblemEdgeData(){}

		virtual bool empty() const = 0;
};


/** \brief Implementa a estrutura de um Grafo (G(V,E))
*	 \class Graph Graph.hpp "Graph.hpp"
*
*		A classe cont�m um conjunto de v�rtices (V = vector<Vertex>) e um conjunto de
*	arestas representado numa matriz de adjac�ncia (E = vector< vector<Edge> >).
*		Vertex e Edge s�o structs internas da classe. � poss�vel adicionar informa��es
*	extras �s duas estruturas atrav�s de especifica��es das classes Problem(Vertex|Edge)Data
*/
class Graph
{
	private:
		struct Vertex
		{
			//! \param label Nome/Identificador do v�rtice (opcional)
			std::string	label;
			//! \param data informa��es adicionais
			ProblemVertexData*	data;

			Vertex(ProblemVertexData* data = 0x0) : label(""), data(data){}
			Vertex(const Vertex& v) : label(v.label), data(v.data){}
			virtual ~Vertex(){ if(data) delete data; }

			inline Vertex& operator = (const Vertex& v) { label = v.label; data = v.data; return (*this); }
		};

		struct Edge
		{
			//! \param s source vertex \param t target vertex
			Vertex 				s, t;
			//! \param data informa��es adicionais
			ProblemEdgeData*	data;

			Edge(Vertex s, Vertex t, ProblemEdgeData* data = 0x0) : s(s), t(t), data(data){}
			virtual ~Edge(){ if(data) delete data; }

			inline Edge& operator = (const Edge& e) { s = e.s; t = e.t; data = e.data; return (*this); }
		};

		typedef struct Edge * PEdge;

		//! \param it Marca o v�rtice default que ser� substitu�do na pr�xima inser��o
		std::vector<Vertex>::iterator it;
		//! \param vertexes Conjunto de V�rtices (V)
		std::vector<Vertex> vertexes;
		//! \param edges Conjunto de Arestas (E) [Matriz de Adjac�ncia]
		std::vector< std::vector<PEdge> > edges;

	public:
		//! \param label Nome do Grafo (opcional)
		std::string label;

		Graph();
		Graph(unsigned int order);
		virtual ~Graph();

		/** \brief Define tipos para o c�lculo do grau de um v�rtice
		* 		\param IN 	grau de entrada (apenas arestas que entram no v�rtice)
		*		\param OUT	grau de sa�da (apenas arestas que saem do v�rtice)
		*		\param ALL	grau total (toda e qualquer aresta incidente ao v�rtice)
		*/
		enum DEGREE{IN, OUT, ALL};
		/** \brief Define a dire��o da aresta a ser inserida
		*     \param BI_DIR  aresta bidirecional
      *     \param S_TO_T  aresta unidirecional (de v�rtice s para v�rtice t)
		*/
		enum EDGEDIR{BI_DIR, S_TO_T};

		// Gets
		unsigned int			getNumberVertexes() const;
		unsigned int			getNumberEdges() const;
		unsigned int			getVertexDegree(unsigned int id, DEGREE type = OUT) const;
		//! \fn getVertexData e \fn getEdgeData retornam Default(Vertex|Edge)Data se �ndices forem inv�lidos
		ProblemVertexData& 	getVertexData(unsigned int id) const;
		ProblemEdgeData& 		getEdgeData(unsigned int ids, unsigned int idt) const;

		// Sets
		void setGraphLabel(std::string label);
		void setVertexLabelToId(unsigned int id);
		void setVertexLabel(unsigned int id, int label);
		void setVertexLabel(unsigned int id, std::string label);

		// Inser��es
		//! Insere um novo v�rtice ao Grafo
		void 	insertVertex(ProblemVertexData&);
		//! Insere um conjunto de novos v�rtices ao Grafo
		void 	insertVertexes(std::vector<ProblemVertexData*>&);
		//! Insere uma aresta entre dois v�rtices (default bidirecional)
		void 	insertEdge(unsigned int ids, unsigned int idt, ProblemEdgeData&, EDGEDIR dir = BI_DIR);

		// Dele��es
		//! Remove a aresta existente entre os v�rtices s e t (default bidirecional)
		void	deleteEdge(unsigned int ids, unsigned int idt, EDGEDIR dir = BI_DIR);

		//! Cria arestas entre todos os v�rtices do Grafo (com data vazio)
      void completeGraph();

      //! \return true Se Grafo vazio, false c.c.
      inline bool empty() const { return (vertexes.empty()); }

		//! Define a ordem do Grafo. Cria v�rtices (com data vazio)[N�o pode-se diminuir a ordem do Grafo]
		Graph&	operator ()(unsigned int order);

		//! Imprime o conjunto de v�rtices do Grafo
		friend std::ostream& operator << (std::ostream& out, const Graph& g){
			out << "V(" << g.label << ") = { ";
			for(unsigned int id = 0; id < g.vertexes.size(); id++){
				out << g.vertexes[id].label << ", ";
				if( (id+1) % 10 == 0 ) out << std::endl << "\t";
			}
			out << " \b\b\b }";
			return out;
		}

		friend class CTOP;

	private:
		void	allocateEdges(); // uso interno
};

/** \brief Informa��o complementar de v�rtice vazia
* \class DefaultVertexData Graph.hpp "Graph.hpp"
*/
class DefaultVertexData : public ProblemVertexData{
	public:
		DefaultVertexData() : ProblemVertexData(){}
		~DefaultVertexData(){}

		virtual bool empty() const { return true; }
};

/** \brief Informa��o complementar de aresta vazia
* \class DefaultEdgeData Graph.hpp "Graph.hpp"
*/
class DefaultEdgeData : public ProblemEdgeData{
	public:
		DefaultEdgeData() : ProblemEdgeData(){}
		~DefaultEdgeData(){}

		virtual bool empty() const { return true; }
};

} // namespace ctop

#endif // _GRAPH_HPP_
