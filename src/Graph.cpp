#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Graph.hpp"

using namespace std;
using namespace ctop;

Graph::Graph() : label("G"){

}

Graph::Graph(unsigned int order) : label("G"){
	(*this)(order);
	it = vertexes.begin();
}

Graph::~Graph(){
	if(!vertexes.empty())
		vertexes.clear();
	if(!edges.empty()){
		for(unsigned int i = 0; i < edges.size(); i++)
			if(!edges[i].empty()){
				for(unsigned int j = 0; j < edges[i].size(); j++)
					if(edges[i][j]) delete edges[i][j];
				edges[i].clear();
			}
		edges.clear();
	}
}


/*	Todo e qualquer modo de inserção de vértices passa por este operador, isto implica em:
*		- vertexes sempre terá vértice(s) default, mesmo que num curto espaço de tempo
*		- se vertexes não está vazio, edges também não estará (chamada para allocateEdges)
*		- o iterator it sempre aponta para a primeira posição que possui um vértice default ou para vertexes.end()
*/
Graph& Graph::operator() (unsigned int order){
	if(order > vertexes.size()){
		int offset = (vertexes.empty()) ? 0 : it - vertexes.begin();
		vertexes.resize(order, Vertex());
		it = vertexes.begin() + offset;
		allocateEdges();
	}
	return (*this);
}

/*	Aloca posições na matriz de arestas pelo número de vértices contidos no grafo, isto implica:
*		- o número de arestas sempre será o quadrado do número de vértices (nulas ou não)
*		- vértices default podem ter arestas
*/
void Graph::allocateEdges(){
	unsigned int order = vertexes.size();
	edges.resize(order);
	for(unsigned int i = 0; i < order; i++)
		edges[i].resize(order, 0x0);
}

void Graph::completeGraph(){
	if(!vertexes.empty()){
		for(unsigned int i = 0; i < edges.size(); i++){
			for(unsigned int j = 0; j < edges[i].size(); j++){
				if(i == j) continue;
				PEdge e = new Edge(vertexes[i], vertexes[j]);
				edges[i][j] = e;
			}
		}
	}
}

unsigned int Graph::getNumberVertexes() const{
	return vertexes.size();
}

unsigned int Graph::getNumberEdges() const{
	int c = 0;
	for(unsigned int i = 0; i < edges.size(); i++){
		for(unsigned int j = 0; j < edges[i].size(); j++){
			if(edges[i][j] != 0x0) c++;
		}
	}
	return c;
}

unsigned int Graph::getVertexDegree(unsigned int id, DEGREE type) const{
	bool flag = false;
	if(type == ALL) flag = true;

	int deg = 0;
	if(type == OUT || flag){
		for(unsigned int j = 0; j < edges[id].size(); j++)
			if(edges[id][j] != 0x0) deg++;
	}
	if(type == IN || flag){
		for(unsigned int i = 0; i < edges.size(); i++)
			if(edges[i][id] != 0x0) deg++;
	}
	return deg;
}

ProblemVertexData& Graph::getVertexData(unsigned int id) const{
	if(0 <= id && id < vertexes.size())
		return *(vertexes[id].data);
	cout << "default" << endl;
	return *(new DefaultVertexData());
}

ProblemEdgeData& Graph::getEdgeData(unsigned int ids, unsigned int idt) const{
	if(0 <= ids && ids < edges.size() && 0 <= idt && idt < edges[ids].size())
		return *((edges[ids][idt])->data);
	return *(new DefaultEdgeData());
}

void Graph::setGraphLabel(std::string label){ this->label = label; }
void Graph::setVertexLabelToId(unsigned int id){ setVertexLabel(id, id); }

void Graph::setVertexLabel(unsigned int id, int label){
	if(0 <= id && id < vertexes.size()){
		ostringstream convert;
		convert << label;
		vertexes[id].label = convert.str();
	}
}

void Graph::setVertexLabel(unsigned int id, std::string label){
	if(0 <= id && id < vertexes.size())
		vertexes[id].label = label;
}

void Graph::insertVertex(ProblemVertexData& data){
	if(vertexes.empty()) (*this)(1);
	else if(it == vertexes.end()) (*this)(vertexes.size()+1);

	(*it) = Vertex(&data); it++;
}

void Graph::insertVertexes(std::vector<ProblemVertexData*>& data){
	if(vertexes.empty()) (*this)(data.size());
	else if(vertexes.end() - it < (int)data.size()) (*this)(data.size());

	for(unsigned int i = 0; i < data.size(); i++){
		if(it == vertexes.end()) break;
		Vertex v = Vertex (data[i]);
		(*it) = v; it++;
	}
}

void Graph::insertEdge(unsigned int ids, unsigned int idt, ProblemEdgeData& data, EDGEDIR dir){
	if(!vertexes.empty()){
		if(0 <= ids && ids < edges.size() && 0 <= idt && idt < edges[ids].size()){
			PEdge e = new Edge(vertexes[ids], vertexes[idt], &data);
			edges[ids][idt] = e;
			if(dir == BI_DIR){
				PEdge e = new Edge(vertexes[idt], vertexes[ids], &data);
				edges[idt][ids] = e;
			}
		}
	}
}

void Graph::deleteEdge(unsigned int ids, unsigned int idt, EDGEDIR dir){
	if(0 <= ids && ids < edges.size() && 0 <= idt && idt < edges[ids].size()){
		delete edges[ids][idt];
		edges[ids][idt] = 0x0;
		if(dir == BI_DIR){
         delete edges[idt][ids];
         edges[idt][ids] = 0x0;
		}
	}
}
