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
#include <cfloat>

#include "Graph.hpp"

class Maxmeandp {
  protected:
    Graph workingGraph;
    std::vector<int> bestSolution;
    float bestSolutionValue;

    float getMax(void);

  public:
    Maxmeandp(Graph myGraph);
    ~Maxmeandp();

    std::vector<int> getBestSolution();
    int getBestSoluctionValue();

    float md(float);
    float mdFromSet(std::vector<int>);
    bool isInSolution(int);
    virtual float solve() = 0;

    std::ostream& write(std::ostream&);
};
