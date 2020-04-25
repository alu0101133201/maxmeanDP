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

#define ITERACIONES 0
#define SINMEJORA 1
#define OPEN 0
#define CLOSE 1
#define GREEDY 0
#define ANXIOUS 1

class Maxmeandp {
  protected:
    // Atributos básicos
    Graph workingGraph;
    std::vector<int> bestSolution;
    float bestSolutionValue;

    // Atributos de criterio de parada
    int iterationsWithOutImprove;
    int stopCriteria_;
    int iterationLimit;

    // Atributos para la búsqueda local
    int localType;
    int envirnomentType;

    float getMax(void);
    bool stopCriteria(int);

    void greedyLocalSearch();
    void anxiousLocalSearch();
    std::vector<int> generateNeighbour(int node);

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