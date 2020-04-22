/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase grafo
 */

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Clase que implementa un grafo básico
class Graph {
  private:
    std::vector<float> adjacencyMatrix;
    int numberOfNodes;

    void build(std::string fileName);
    void setData(int i, int j, float data);

  public:
    Graph();
    Graph(std::string fileName);
    ~Graph();

    float at(int i, int j);
    std::ostream& write(std::ostream& os);
};

