#ifndef A2_SIMPLENAVIGATOR_SRC_LIBS_TSP_HEADERS_S21_TSP_H
#define A2_SIMPLENAVIGATOR_SRC_LIBS_TSP_HEADERS_S21_TSP_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <memory>
#include <random>

#include "../../Graph/Headers/s21_graph.h"

namespace s21 {

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

enum Algorithm { Ant, BruteForce, BranchAndBound };

class Tsp {
 public:
  Tsp() {}
  ~Tsp() {}
  enum Algorithm { Ant, BruteForce, BranchAndBound };

  TsmResult AntAlgorithm(const Graph& graph);
  TsmResult BruteForceAlgorithm(const Graph& graph);
  TsmResult BranchAndBoundAlgorithm(const Graph& graph);

 private:
  class AntAlgorithmOptimization {
   public:
    AntAlgorithmOptimization() = delete;
    AntAlgorithmOptimization(const Graph& graph);
    ~AntAlgorithmOptimization() {}
    TsmResult AntAlgorithm();

   private:
    struct Ant {
      Ant(int start_vertex = 0)
          : start(start_vertex), current(start_vertex), is_finished(false) {}
      TsmResult path;
      std::vector<int> visited;
      int start = 0;
      int current = 0;
      bool is_finished = false;
    };
    const double kAlpha_ = 1.0;
    const double kBeta_ = 2.0;
    const double kPheromone_ = 1;
    const double kQ_ = 5.0;
    const double kEvaporation_ = 0.2;
    std::vector<std::vector<double>> pheromone_;
    std::vector<Ant> InitAnts();
    std::vector<int> InitNeighbours(Ant& ant);
    std::vector<double> InitProbabilities(Ant& ant, std::vector<int> neigbhors);
    double InitChoice();
    int InitNext(double choice, std::vector<int> neighbours,
                 std::vector<double> probabilities);
    void CheckNeighbours(Ant& ant);
    void CheckAnt(Ant& ant, TsmResult& result, int* count,
                  std::vector<std::vector<double>> localPheromones);
    void MakeChoice(Ant& ant);
    void UpdatePheromone(
        const std::vector<std::vector<double>>& localPheromones);
    const Graph& graph_;
    const int size_;
    const int imax_ = std::numeric_limits<int>::max();
  };
  class BruteForceOptimization {
   public:
    BruteForceOptimization() = delete;
    BruteForceOptimization(const Graph& graph);
    ~BruteForceOptimization() {}
    TsmResult BruteForceAlgorithm();

   private:
    void BruteForce(int current, double cost, TsmResult& result);
    std::vector<int> path_;
    std::vector<bool> visited_;
    const Graph& graph_;
    const int size_;
    const int imax_ = std::numeric_limits<int>::max();
  };
  class BranchAndBoundOptimization {
   public:
    BranchAndBoundOptimization() = delete;
    BranchAndBoundOptimization(const Graph& graph);
    ~BranchAndBoundOptimization() {}
    TsmResult BranchAndBoundAlgorithm();

   private:
    void CopyToFinalPath(std::vector<int>& curr_path, TsmResult& result);
    int FirstMin(int i);
    int SecondMin(int i);
    void Rec(int curr_bound, int curr_weight, int level,
             std::vector<int>& curr_path, TsmResult& result);
    std::vector<bool> visited_;
    const Graph& graph_;
    const int size_;
    const int imax_ = std::numeric_limits<int>::max();
  };
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_SRC_LIBS_TSP_HEADERS_S21_TSP_H
