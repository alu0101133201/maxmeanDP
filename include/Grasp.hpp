/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase que implementará
 * el algoritmo GRASP
 */

#pragma once

#include <cfloat>
#include <stdlib.h>
#include <time.h>  
#include <utility> 

#include "Graph.hpp"
#include "Maxmeandp.hpp"



class Grasp : public Maxmeandp {
  private:
    std::vector<std::pair<int, float> > LRC;  // Atributo que almacena LRC
    int cardinality;  // Atributo que almacena la cardinalidad del LRC

    float construct();
    // Método que nos construye el LRC
    void buildLRC();
    // Método auxiliar que introduce un nodo al LRC
    void addLRC(int, float, int&, float&);
    
  public:
    Grasp(Graph workingGraph, int numberOfCardinality, int stopCriteria, int maxIterations,
        int typeLocal, int environment);
    ~Grasp();

    // Método principal de resolución
    float solve();
};