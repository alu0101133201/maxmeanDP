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
    std::vector<std::pair<int, float> > LRC;
    int cardinality;

    float construct();
    void buildLRC();
    void addLRC(int, float, int&, float&);
    // void preprocessing();
    
  public:
    Grasp(Graph workingGraph, int numberOfCardinality, int stopCriteria, int maxIterations,
        int typeLocal, int environment);
    ~Grasp();

    float solve();
};