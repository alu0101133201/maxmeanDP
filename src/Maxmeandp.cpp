/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase abstracta maxmeandp. Esta 
 * sera la clase padre de diferentes clases que implementarán
 * un algoritmo de resolución para el problema
 */

#include "Maxmeandp.hpp"

Maxmeandp::Maxmeandp(Graph myGraph) {
  workingGraph = myGraph;
}

Maxmeandp::~Maxmeandp() {};

std::vector<int> Maxmeandp::getBestSolution() {
  return(bestSolution);
}

int Maxmeandp::getBestSoluctionValue() {
  return(bestSolutionValue);
}

float Maxmeandp::md(float numerator) {
  return(numerator / bestSolution.size());
}

bool Maxmeandp::isInSolution(int node) {
  for (size_t iter = 0; iter < bestSolution.size(); iter++) {
    if (bestSolution[iter] == node) 
      return true;
  }
  return false;
}

std::ostream& Maxmeandp::write(std::ostream& os) {
  os << "Maxmeandp aplicado sobre la siguiente matriz: \n";
  workingGraph.write(std::cout);
  os << "\nEl mejor valor obtenido es: " << bestSolutionValue << "\n";
  os << "El cjto de nodos solución es: ";
  for (size_t iter = 0; iter < bestSolution.size(); iter++) {
    os << bestSolution[iter] << " ";
  }
  os << "\n";
  return os;
}