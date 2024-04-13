#include "../Headers/s21_tsp.h"

namespace s21 {

// ------------AntAlgorithm------------

TsmResult Tsp::AntAlgorithm(const Graph& graph) {
  if (graph.GetAdjacencyMatrix().empty()) {
    throw std::exception();
  }
  AntAlgorithmOptimization AntAlgorithmOptimization(graph);
  return AntAlgorithmOptimization.AntAlgorithm();
}

Tsp::AntAlgorithmOptimization::AntAlgorithmOptimization(const Graph& graph)
    : graph_(graph), size_(graph.GetSize()) {
  std::vector<std::vector<double>> matrix(size_, std::vector<double>(size_));
  for (int i = 0; i != size_; i++) {
    for (int j = 0; j != size_; j++) {
      if (i != j) {
        matrix[i][j] = kPheromone_;
      }
    }
  }
  pheromone_ = std::move(matrix);
}

std::vector<Tsp::AntAlgorithmOptimization::Ant>
Tsp::AntAlgorithmOptimization::InitAnts() {
  std::vector<Ant> ants(size_);
  for (int i = 0, size = ants.size(); i != size; ++i) {
    ants[i] = Ant(i);
  }
  return ants;
}

TsmResult Tsp::AntAlgorithmOptimization::AntAlgorithm() {
  TsmResult result;
  int maxIteration = 5000;
  int count = 0;
  result.distance = imax_;
  while (count != maxIteration) {
    count++;
    std::vector<std::vector<double>> localPheromones(
        size_, std::vector<double>(size_, 0));
    std::vector<Ant> ants_ = InitAnts();
    for (auto& ant : ants_) {
      while (!ant.is_finished) {
        MakeChoice(ant);
      }
      CheckAnt(ant, result, &count, localPheromones);
    }
    UpdatePheromone(localPheromones);
  }
  return result;
}

void Tsp::AntAlgorithmOptimization::MakeChoice(Ant& ant) {
  if (ant.path.vertices.empty()) {
    ant.path.vertices.push_back(ant.current);
    ant.visited.push_back(ant.current);
  }

  std::vector<int> neighbours = InitNeighbours(ant);
  if (neighbours.empty()) {
    CheckNeighbours(ant);
    return;
  }

  std::vector<double> probabilities = InitProbabilities(ant, neighbours);
  double choice = InitChoice();
  int next = InitNext(choice, neighbours, probabilities);
  ant.path.vertices.push_back(next);
  ant.visited.push_back(next);
  ant.path.distance += graph_[ant.current][next];
  ant.current = next;
}

std::vector<int> Tsp::AntAlgorithmOptimization::InitNeighbours(Ant& ant) {
  std::vector<int> neighbours;
  for (int i = 0; i != size_; i++) {
    if (graph_[ant.current][i] != 0 &&
        std::find(ant.visited.begin(), ant.visited.end(), i) ==
            ant.visited.end()) {
      neighbours.push_back(i);
    }
  }
  return neighbours;
}

void Tsp::AntAlgorithmOptimization::CheckNeighbours(Ant& ant) {
  ant.is_finished = true;
  if (graph_[ant.current][ant.start] != 0) {
    ant.path.vertices.push_back(ant.start);
    ant.path.distance += graph_[ant.current][ant.start];
  }
}

void Tsp::AntAlgorithmOptimization::CheckAnt(
    Ant& ant, TsmResult& result, int* count,
    std::vector<std::vector<double>> localPheromones) {
  TsmResult ant_path = ant.path;
  if ((int)ant_path.vertices.size() == size_ + 1) {
    if (result.distance > ant.path.distance) {
      result = std::move(ant.path);
      *count = 0;
    }
    for (int v = 0; v != (int)ant_path.vertices.size() - 1; ++v) {
      localPheromones[ant_path.vertices[v]][ant_path.vertices[v + 1]] +=
          kQ_ / ant_path.distance;
    }
  }
}

double Tsp::AntAlgorithmOptimization::InitChoice() {
  std::uniform_real_distribution<> dist(0.0, 1.0);
  std::default_random_engine re(
      std::chrono::system_clock::now().time_since_epoch().count());
  return dist(re);
}

int Tsp::AntAlgorithmOptimization::InitNext(double choice,
                                            std::vector<int> neighbours,
                                            std::vector<double> probabilities) {
  int next;
  int size = neighbours.size();
  for (int i = 0; i != size; i++) {
    if (choice <= probabilities[i]) {
      next = neighbours[i];
      break;
    }
  }
  return next;
}

std::vector<double> Tsp::AntAlgorithmOptimization::InitProbabilities(
    Ant& ant, std::vector<int> neighbours) {
  std::vector<double> probabilities(neighbours.size());
  std::vector<double> wish;
  std::vector<double> probability;
  double summaryWish = 0.0f;
  for (auto neighbour : neighbours) {
    double pheremone = pheromone_[ant.current][neighbour];
    double weight = graph_[ant.current][neighbour];
    double inverseWeight = 1 / weight;
    wish.push_back(std::pow(pheremone, kAlpha_) *
                   std::pow(inverseWeight, kBeta_));
    summaryWish += wish.back();
  }
  int size = neighbours.size();
  for (int i = 0; i != size; i++) {
    probability.push_back(wish[i] / summaryWish);
    if (i == 0) {
      probabilities[i] = probability.back();
    } else {
      probabilities[i] = probabilities[i - 1] + probability.back();
    }
  }
  return probabilities;
}

void Tsp::AntAlgorithmOptimization::UpdatePheromone(
    const std::vector<std::vector<double>>& localPheromones) {
  for (int from = 0, size = localPheromones.size(); from != size; ++from) {
    for (int to = 0; to != size; ++to) {
      pheromone_[from][to] = (1 - kEvaporation_) * pheromone_[from][to] +
                             localPheromones[from][to];
      if (pheromone_[from][to] < 0.01 and from != to)
        pheromone_[from][to] = 0.01;
    }
  }
}

// ------------BruteForceAlgorithm------------

TsmResult Tsp::BruteForceAlgorithm(const Graph& graph) {
  if (graph.GetAdjacencyMatrix().empty()) {
    throw std::exception();
  }
  BruteForceOptimization bruteForceOptimization(graph);
  return bruteForceOptimization.BruteForceAlgorithm();
}

Tsp::BruteForceOptimization::BruteForceOptimization(const Graph& graph)
    : graph_(graph), size_(graph.GetSize()) {
  visited_ = std::vector<bool>(size_);
  visited_[0] = true;
  path_.push_back(0);
}

TsmResult Tsp::BruteForceOptimization::BruteForceAlgorithm() {
  TsmResult result;
  result.distance = imax_;
  BruteForce(0, 0, result);
  result.vertices.push_back(result.vertices[0]);
  return result;
}

void Tsp::BruteForceOptimization::BruteForce(int current, double cost,
                                             TsmResult& result) {
  if ((int)path_.size() == size_) {
    cost += graph_[current][0];
    if (cost < result.distance) {
      result.distance = cost;
      result.vertices = path_;
    }
    return;
  }
  for (int i = 0; i < size_; ++i) {
    if (!visited_[i] && graph_[current][i] > 0) {
      visited_[i] = true;
      path_.push_back(i);
      BruteForce(i, cost + graph_[current][i], result);
      visited_[i] = false;
      path_.pop_back();
    }
  }
}

// ------------BranchAndBoundAlgorithm------------

TsmResult Tsp::BranchAndBoundAlgorithm(const Graph& graph) {
  if (graph.GetAdjacencyMatrix().empty()) {
    throw std::exception();
  }
  BranchAndBoundOptimization branchAndBoundOptimization(graph);
  return branchAndBoundOptimization.BranchAndBoundAlgorithm();
}

Tsp::BranchAndBoundOptimization::BranchAndBoundOptimization(const Graph& graph)
    : graph_(graph), size_(graph.GetSize()) {
  visited_ = std::vector<bool>(size_);
}

TsmResult Tsp::BranchAndBoundOptimization::BranchAndBoundAlgorithm() {
  TsmResult result;
  result.distance = imax_;
  result.vertices.resize(size_ + 1);
  std::vector<int> curr_path;
  curr_path.assign(size_, -1);
  int curr_bound = 0;
  for (int i = 0; i < size_; ++i) curr_bound += (FirstMin(i) + SecondMin(i));
  curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;
  visited_[0] = true;
  curr_path[0] = 0;
  Rec(curr_bound, 0, 1, curr_path, result);
  return result;
}

void Tsp::BranchAndBoundOptimization::CopyToFinalPath(
    std::vector<int>& curr_path, TsmResult& result) {
  for (int i = 0; i < size_; ++i) result.vertices[i] = curr_path[i];
  result.vertices[size_] = curr_path[0];
}

int Tsp::BranchAndBoundOptimization::FirstMin(int i) {
  int min = imax_;
  for (int k = 0; k < size_; ++k) {
    if (visited_[k] || i == k) continue;
    if (graph_[i][k] < min) min = graph_[i][k];
  }
  return min;
}

int Tsp::BranchAndBoundOptimization::SecondMin(int i) {
  int first = imax_;
  int second = imax_;
  for (int k = 0; k < size_; ++k) {
    if (visited_[k] || i == k) continue;
    if (graph_[i][k] <= first) {
      second = first;
      first = graph_[i][k];
    } else if (graph_[i][k] <= second && graph_[i][k] != first) {
      second = graph_[i][k];
    }
  }
  return second;
}

void Tsp::BranchAndBoundOptimization::Rec(int curr_bound, int curr_weight,
                                          int level,
                                          std::vector<int>& curr_path,
                                          TsmResult& result) {
  if (level == size_) {
    if (graph_[curr_path[level - 1]][curr_path[0]] != 0) {
      int curr_res = curr_weight + graph_[curr_path[level - 1]][curr_path[0]];
      if (curr_res < result.distance) {
        CopyToFinalPath(curr_path, result);
        result.distance = curr_res;
      }
    }
    return;
  }
  for (int i = 0; i < size_; ++i) {
    if (graph_[curr_path[level - 1]][i] != 0 && visited_[i] == false) {
      int temp = curr_bound;
      curr_weight += graph_[curr_path[level - 1]][i];
      if (level == 1)
        curr_bound -= ((FirstMin(curr_path[level - 1]) + FirstMin(i)) / 2);
      else
        curr_bound -= ((SecondMin(curr_path[level - 1]) + FirstMin(i)) / 2);
      if (curr_bound + curr_weight < result.distance) {
        curr_path[level] = i;
        visited_[i] = true;
        Rec(curr_bound, curr_weight, level + 1, curr_path, result);
      }
      curr_weight -= graph_[curr_path[level - 1]][i];
      curr_bound = temp;
      visited_.assign(visited_.size(), false);
      for (int j = 0; j <= level - 1; ++j) visited_[curr_path[j]] = true;
    }
  }
}

}  // namespace s21