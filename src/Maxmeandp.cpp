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