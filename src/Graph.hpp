#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <vector>

namespace ctop
{

/** \brief Classe abstrata para compor informações extras ao Vertex de Graph
*	 \class ProblemVertexData Graph.hpp "Graph.hpp"
*
*	Implemente uma especificação caso precise de mais informações armazenadas em um vértice do grafo
*/
class ProblemVertexData
{
	public:
		ProblemVertexData(){}
		virtual ~ProblemVertexData(){}

		virtual bool empty() const = 0;
};

/** \brief Classe abstrata para compor informações extras à Edge de Graph
*	 \class ProblemEdgeData Graph.hpp "Graph.hpp"
*
*	Implemente uma especificação caso precise de mais informações armazenadas numa aresta do grafo
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
*		A classe contém um conjunto de vértices (V = vector<Vertex>) e um conjunto de
*	arestas representado numa matriz de adjacência (E = vector< vector<Edge> >).
*		Vertex e Edge são structs internas da classe. É possível adicionar informações
*	extras às duas estruturas através de especificações das classes Problem(Vertex|Edge)Data
*/
class Graph
{
	private:
		struct Vertex
		{
			//! \param label Nome/Identificador do vértice (opcional)
			std::string	label;
			//! \param data informações adicionais
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
			//! \param data informações adicionais
			ProblemEdgeData*	data;

			Edge(Vertex s, Vertex t, ProblemEdgeData* data = 0x0) : s(s), t(t), data(data){}
			virtual ~Edge(){ if(data) delete data; }

			inline Edge& operator = (const Edge& e) { s = e.s; t = e.t; data = e.data; return (*this); }
		};

		typedef struct Edge * PEdge;

		//! \param it Marca o vértice default que será substituído na próxima inserção
		std::vector<Vertex>::iterator it;
		//! \param vertexes Conjunto de Vértices (V)
		std::vector<Vertex> vertexes;
		//! \param edges Conjunto de Arestas (E) [Matriz de Adjacência]
		std::vector< std::vector<PEdge> > edges;

	public:
		//! \param label Nome do Grafo (opcional)
		std::string label;

		Graph();
		Graph(unsigned int order);
		virtual ~Graph();

		/** \brief Define tipos para o cálculo do grau de um vértice
		* 		\param IN 	grau de entrada (apenas arestas que entram no vértice)
		*		\param OUT	grau de saída (apenas arestas que saem do vértice)
		*		\param ALL	grau total (toda e qualquer aresta incidente ao vértice)
		*/
		enum DEGREE{IN, OUT, ALL};
		/** \brief Define a direção da aresta a ser inserida
		*     \param BI_DIR  aresta bidirecional
      *     \param S_TO_T  aresta unidirecional (de vértice s para vértice t)
		*/
		enum EDGEDIR{BI_DIR, S_TO_T};

		// Gets
		unsigned int			getNumberVertexes() const;
		unsigned int			getNumberEdges() const;
		unsigned int			getVertexDegree(unsigned int id, DEGREE type = OUT) const;
		//! \fn getVertexData e \fn getEdgeData retornam Default(Vertex|Edge)Data se índices forem inválidos
		ProblemVertexData& 	getVertexData(unsigned int id) const;
		ProblemEdgeData& 		getEdgeData(unsigned int ids, unsigned int idt) const;

		// Sets
		void setGraphLabel(std::string label);
		void setVertexLabelToId(unsigned int id);
		void setVertexLabel(unsigned int id, int label);
		void setVertexLabel(unsigned int id, std::string label);

		// Inserções
		//! Insere um novo vértice ao Grafo
		void 	insertVertex(ProblemVertexData&);
		//! Insere um conjunto de novos vértices ao Grafo
		void 	insertVertexes(std::vector<ProblemVertexData*>&);
		//! Insere uma aresta entre dois vértices (default bidirecional)
		void 	insertEdge(unsigned int ids, unsigned int idt, ProblemEdgeData&, EDGEDIR dir = BI_DIR);

		// Deleções
		//! Remove a aresta existente entre os vértices s e t (default bidirecional)
		void	deleteEdge(unsigned int ids, unsigned int idt, EDGEDIR dir = BI_DIR);

		//! Cria arestas entre todos os vértices do Grafo (com data vazio)
      void completeGraph();

      //! \return true Se Grafo vazio, false c.c.
      inline bool empty() const { return (vertexes.empty()); }

		//! Define a ordem do Grafo. Cria vértices (com data vazio)[Não pode-se diminuir a ordem do Grafo]
		Graph&	operator ()(unsigned int order);

		//! Imprime o conjunto de vértices do Grafo
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

/** \brief Informação complementar de vértice vazia
* \class DefaultVertexData Graph.hpp "Graph.hpp"
*/
class DefaultVertexData : public ProblemVertexData{
	public:
		DefaultVertexData() : ProblemVertexData(){}
		~DefaultVertexData(){}

		virtual bool empty() const { return true; }
};

/** \brief Informação complementar de aresta vazia
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
