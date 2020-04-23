/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe las clases que implementarán
 * los planteamientos greedy del algorimot maxmeandp
 */

#pragma once

#include <climits>
#include <stdlib.h>
#include <time.h>  
#include <vector>    

#include "Graph.hpp"
#include "Maxmeandp.hpp"

class SecondGreedy : public Maxmeandp{
  private:
    void buildInitialSolution();
    float deleteWorstNode();

  public:
    SecondGreedy(Graph);
    ~SecondGreedy();
    
    float solve();
};