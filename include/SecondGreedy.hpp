/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe las clases que implementarán
 * los planteamientos greedy del algorimot maxmeandp
 */

#pragma once

#include <cfloat>
#include <stdlib.h>
#include <time.h>  
#include <vector>    

#include "Graph.hpp"
#include "Maxmeandp.hpp"

// Clase que implementa el método voraz destructivo
class SecondGreedy : public Maxmeandp{
  private:
    // Método que construye la solución inicial
    void buildInitialSolution();
    // Método que elimina el pero nodo de la solución
    float deleteWorstNode();

  public:
    SecondGreedy(Graph);
    ~SecondGreedy();
    
    // Método principal de resolución
    float solve();
};