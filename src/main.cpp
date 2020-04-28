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
#include <chrono>

#include "Graph.hpp"
#include "FirstGreedy.hpp"
#include "SecondGreedy.hpp"
#include "Grasp.hpp"
#include "Maxmeandp.hpp"
#include "MaxmeandpCalculator.hpp"
#include "multiBooting.hpp"
#include "VNS.hpp"
#include "mod.hpp"

#define ITERATIONS 0
#define WITHOUTIMPROVE 1
#define GRASPITERATIONS 100
#define MULTIBOOTITERATIONS 100
#define CARDINALITY 2
#define OPEN 0
#define CLOSE 1
#define GREEDY 0
#define ANXIOUS 1

// Programa principal que instancia todos los algoritmos y realiza una 
// Ejecución con cada uno de ellos
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
      Maxmeandp* myMod = new Mod(firstGraph, CARDINALITY, ITERATIONS,
          MULTIBOOTITERATIONS, GREEDY, CLOSE);
      MaxmeandpCalculator algorithmInterface(alg1);
      // std::cout << "FIRST GREEDY: " << "\n";
      // algorithmInterface.solve();  
      // algorithmInterface.write(std::cout);
      // std::cout << "\nSECOND GREEDY: " << "\n";
      // algorithmInterface.setStrategy(alg2);
      // algorithmInterface.solve(); 
      // algorithmInterface.write(std::cout);
      // std::cout << "\nGRASP: " << "\n";
      // algorithmInterface.setStrategy(grasp);
      // algorithmInterface.solve();
      // algorithmInterface.write(std::cout);
      // std::cout << "\nMULTIBOOTING: \n";
      // algorithmInterface.setStrategy(multiBooting);
      // algorithmInterface.solve();
      // algorithmInterface.write(std::cout); 
      // std::cout << "\nBVNS: \n";
      // algorithmInterface.setStrategy(myVNS);
      // algorithmInterface.solve();
      // algorithmInterface.write(std::cout); 
      std::cout << "\nMod: \n";
      algorithmInterface.setStrategy(myMod);
      std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
      algorithmInterface.solve();
      std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);  
      algorithmInterface.write(std::cout); 
      std::cout << "Duración de la ejecución " << time_span.count() * 1000 << " miliseconds.\n";

      // Cronómetro
  } catch(const char* e) {
    std::cout << e;
    return(1);
  }
  return (0);
}