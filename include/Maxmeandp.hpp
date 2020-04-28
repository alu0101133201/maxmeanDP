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

    // Método de inicialización de la solución
    float getMax(void);
    // Método que comprueba la condición de parada
    bool stopCriteria(int);

    // Métodos relativos a la búsqueda local
    void greedyLocalSearch();
    void anxiousLocalSearch();
    std::vector<int> generateNeighbour(int node);
    void postProcessing();
    void generateRandom();


  public:
    Maxmeandp(Graph myGraph);
    ~Maxmeandp();

    // Getters básicos
    std::vector<int> getBestSolution();
    int getBestSoluctionValue();
    float getSolutionValue();
    std::vector<int> getSolution();

    // Funciones de cálculo de la función objetivo
    float md(float);
    float mdFromSet(std::vector<int>);
    float mdaddNode(float, std::vector<int>, int);
    float mdsubNode(float, std::vector<int>, int);

    // Método auxiliar para ver si un nodo pertenece a una solución
    bool isInSolution(int);

    // Método principal de resolución
    virtual float solve() = 0;

    // Método básico de impresión
    std::ostream& write(std::ostream&);
};