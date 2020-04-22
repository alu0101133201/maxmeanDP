/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase abstracta maxmeandp. Esta 
 * sera la clase padre de diferentes clases que implementarán
 * un algoritmo de resolución para el problema
 */

#pragma once

#include <vector>
#include "Graph.hpp"

class Maxmeandp {
  private:
    Graph workingGraph;
    std::vector<int> bestSolution;
    int bestSolutionValue;

  public:
    Maxmeandp(Graph myGraph);
    ~Maxmeandp();

    std::vector<int> getBestSolution();
    int getBestSoluctionValue();
    virtual int solve() = 0;
};
