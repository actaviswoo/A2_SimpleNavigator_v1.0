#include <gtest/gtest.h>

#include "../Libs/TSP/Headers/s21_tsp.h"
#include "s21_test.h"

TEST(TspTest, AntAlgorithm_1) {
  s21::Tsp tsp;
  s21::Graph graph;
  EXPECT_ANY_THROW(tsp.AntAlgorithm(graph));
}

TEST(TspTest, AntAlgorithm_2) {
  s21::Tsp tsp;
  s21::Graph graph;
  graph.LoadGraphFromFile(tspPath);
  s21::TsmResult result;
  result = tsp.AntAlgorithm(graph);
  EXPECT_TRUE(AreVectorsEqual(result.vertices, tspResult));
  EXPECT_EQ(result.distance, tspDistace);
}

TEST(TspTest, BruteForceAlgorithm_1) {
  s21::Tsp tsp;
  s21::Graph graph;
  EXPECT_ANY_THROW(tsp.BruteForceAlgorithm(graph));
}

TEST(TspTest, BruteForceAlgorithm_2) {
  s21::Tsp tsp;
  s21::Graph graph;
  graph.LoadGraphFromFile(tspPath);
  s21::TsmResult result;
  result = tsp.BruteForceAlgorithm(graph);
  EXPECT_TRUE(AreVectorsEqual(result.vertices, tspResult));
  EXPECT_EQ(result.distance, tspDistace);
}

TEST(TspTest, BranchAndBoundAlgorithm_1) {
  s21::Tsp tsp;
  s21::Graph graph;
  EXPECT_ANY_THROW(tsp.AntAlgorithm(graph));
}

TEST(TspTest, BranchAndBoundAlgorithm_2) {
  s21::Tsp tsp;
  s21::Graph graph;
  graph.LoadGraphFromFile(tspPath);
  s21::TsmResult result;
  result = tsp.BranchAndBoundAlgorithm(graph);
  EXPECT_TRUE(AreVectorsEqual(result.vertices, tspResult));
  EXPECT_EQ(result.distance, tspDistace);
}
