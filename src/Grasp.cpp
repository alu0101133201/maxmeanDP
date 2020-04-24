/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa la clase que implementará
 * el algoritmo GRASP
 */

#include "Grasp.hpp"

Grasp::Grasp(Graph workingGraph, int numberOfCardinality):
    Maxmeandp(workingGraph),
    cardinality(numberOfCardinality) {
  srand (time(NULL));
  LRC.resize(numberOfCardinality, -1);
}

Grasp::~Grasp() {}

void Grasp::buildLRC() {
  std::vector<int> auxSolution = bestSolution;

  for (int iter = 0; iter < workingGraph.getNumberOfNodes(); iter++) {
    auxSolution.push_back(iter);
    int currentValue = mdFromSet(auxSolution);
    
  }
}

float Grasp::construct() {
  buildLRC();
  return 1.0;
}

float Grasp::solve() {
 construct();
  return 1.0;
}