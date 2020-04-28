/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa la clase grafo
 */

#include "Graph.hpp"

Graph::Graph() {}

Graph::Graph(std::string fileName) {
  build(fileName);
}

Graph::~Graph() {}

void Graph::build(std::string fileName) {
  std::ifstream graphFile(fileName);
  int iIndex = 0;
  int jIndex = 0;
  
  if(!graphFile) {
    throw "Problem opening graph file\n";
  }
  graphFile >> numberOfNodes;
  adjacencyMatrix.resize(numberOfNodes * numberOfNodes, 0);

  while (!graphFile.eof() && (iIndex < numberOfNodes) && (jIndex < numberOfNodes)) {
    float readData = 0;
    if (iIndex != jIndex) {
      graphFile >> readData;
      setData(iIndex, jIndex, readData);
      setData(jIndex, iIndex, readData);
    }
    else 
      setData(iIndex, jIndex, 0);
    jIndex++;
    if (jIndex >= numberOfNodes) {
      iIndex++;
      jIndex = iIndex;
    }
  }
}

int Graph::getNumberOfNodes(void) {
  return(numberOfNodes);
}

float Graph::at(int i, int j) {
  return (adjacencyMatrix[(i * numberOfNodes) + j]);
}

void Graph::setData(int i, int j, float data) {
  if ((size_t)((i * numberOfNodes) + j) >= adjacencyMatrix.size()) {
    throw "Setting data in a position out of adjacency matrix\n";
  }
  adjacencyMatrix[(i * numberOfNodes) + j] = data;
}

std::ostream& Graph::write(std::ostream& os) {
  for (int i = 0; i < numberOfNodes; i++) {
    os << "\n";
    for (int j = 0; j < numberOfNodes; j++) {
      os << at(i, j) << " ";
    }
  }
  os << "\n";
  return os;
}