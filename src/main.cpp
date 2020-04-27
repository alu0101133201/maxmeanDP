/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa el programa principal que realizará las 
 * ejecuciones de los diferentes algoritmos y realizará su estudio
 */

#include <iostream> 
#include <string>

#include "Graph.hpp"
#include "FirstGreedy.hpp"
#include "SecondGreedy.hpp"
#include "Grasp.hpp"
#include "Maxmeandp.hpp"
#include "MaxmeandpCalculator.hpp"
#include "multiBooting.hpp"
#include "VNS.hpp"

#define ITERATIONS 0
#define WITHOUTIMPROVE 1
#define GRASPITERATIONS 3
#define MULTIBOOTITERATIONS 100
#define CARDINALITY 4
#define OPEN 0
#define CLOSE 1
#define GREEDY 0
#define ANXIOUS 1

int main(int argc, char *argv[]) {

  try {
    if (argc <= 1) {
      throw "Argumentos suministrados insuficientes\n";
    }
    std::string fileName(argv[1]);
    std::string base_filename = fileName.substr(fileName.find_last_of("/") + 1);

      Graph firstGraph(fileName);
      Maxmeandp* alg1 = new FirstGreedy(firstGraph);
      Maxmeandp* alg2 = new SecondGreedy(firstGraph);
      Maxmeandp* grasp = new Grasp(firstGraph, CARDINALITY, ITERATIONS,
          GRASPITERATIONS, GREEDY, CLOSE);
      Maxmeandp* multiBooting = new MultiBooting(firstGraph, ITERATIONS,
          MULTIBOOTITERATIONS, GREEDY, CLOSE);
      Maxmeandp* myVNS = new VNS(firstGraph, CARDINALITY, ITERATIONS,
          MULTIBOOTITERATIONS, GREEDY, CLOSE);
      MaxmeandpCalculator algorithmInterface(alg1);
      std::cout << "FIRST GREEDY: " << "\n";
      algorithmInterface.solve();   
      algorithmInterface.write(std::cout);
      std::cout << "\nSECOND GREEDY: " << "\n";
      algorithmInterface.setStrategy(alg2);
      algorithmInterface.solve();   
      algorithmInterface.write(std::cout);
      std::cout << "\nGRASP: " << "\n";
      algorithmInterface.setStrategy(grasp);
      algorithmInterface.solve();
      algorithmInterface.write(std::cout);
      std::cout << "\nMULTIBOOTING: \n";
      algorithmInterface.setStrategy(multiBooting);
      algorithmInterface.solve();
      algorithmInterface.write(std::cout); 
      std::cout << "\nBVNS: \n";
      algorithmInterface.setStrategy(myVNS);
      algorithmInterface.solve();
      algorithmInterface.write(std::cout); 
      
  } catch(const char* e) {
    std::cout << e;
    return(1);
  }
  return (0);
}