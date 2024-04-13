#include <gtest/gtest.h>

#include "../Libs/Graph/Headers/s21_graph_algorithms.h"
#include "s21_test.h"

TEST(GraphAlgorithmTest, DepthFirstSearch_1) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  graph.LoadGraphFromFile(graphAlgorithmPath);
  EXPECT_TRUE(AreVectorsEqual(
      graphAlgorithm.DepthFirstSearch(graph, graphAlgorithmVertex),
      graphAlgorithmDepth));
}

TEST(GraphAlgorithmTest, DepthFirstSearch_2) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  EXPECT_THROW(graphAlgorithm.DepthFirstSearch(graph, graphAlgorithmVertex),
               std::exception);
}

TEST(GraphAlgorithmTest, DepthFirstSearch_3) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  graph.LoadGraphFromFile(graphAlgorithmPath);
  EXPECT_THROW(
      graphAlgorithm.DepthFirstSearch(graph, graphAlgorithmErrorVertex),
      std::out_of_range);
}

TEST(GraphAlgorithmTest, BreadthFirstSearch_1) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  graph.LoadGraphFromFile(graphAlgorithmPath);
  EXPECT_TRUE(AreVectorsEqual(
      graphAlgorithm.BreadthFirstSearch(graph, graphAlgorithmVertex),
      graphAlgorithmBreadth));
}

TEST(GraphAlgorithmTest, BreadthFirstSearch_2) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  EXPECT_THROW(graphAlgorithm.BreadthFirstSearch(graph, graphAlgorithmVertex),
               std::exception);
}

TEST(GraphAlgorithmTest, BreadthFirstSearch_3) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  graph.LoadGraphFromFile(graphAlgorithmPath);
  EXPECT_THROW(
      graphAlgorithm.BreadthFirstSearch(graph, graphAlgorithmErrorVertex),
      std::out_of_range);
}

TEST(GraphAlgorithmTest, GetShortestPathBetweenVertices_1) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  graph.LoadGraphFromFile(graphAlgorithmPath);
  EXPECT_EQ(graphAlgorithm.GetShortestPathBetweenVertices(
                graph, graphAlgorithmBetween1, graphAlgorithmBetween2),
            graphAlgorithmBetweenResult);
}

TEST(GraphAlgorithmTest, GetShortestPathBetweenVertices_2) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  EXPECT_THROW(graphAlgorithm.GetShortestPathBetweenVertices(
                   graph, graphAlgorithmBetween1, graphAlgorithmBetween2),
               std::exception);
}

TEST(GraphAlgorithmTest, GetShortestPathBetweenVertices_3) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  graph.LoadGraphFromFile(graphAlgorithmPath);
  EXPECT_THROW(graphAlgorithm.GetShortestPathBetweenVertices(
                   graph, graphAlgorithmErrorVertex, graphAlgorithmVertex),
               std::out_of_range);
  EXPECT_THROW(graphAlgorithm.GetShortestPathBetweenVertices(
                   graph, graphAlgorithmVertex, graphAlgorithmErrorVertex),
               std::out_of_range);
}

TEST(GraphAlgorithmTest, GetShortestPathsBetweenAllVertices_1) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  graph.LoadGraphFromFile(graphAlgorithmPath);
  EXPECT_TRUE(
      AreMatricesEqual(graphAlgorithm.GetShortestPathsBetweenAllVertices(graph),
                       graphAlgorithmBetweenAllResult));
}

TEST(GraphAlgorithmTest, GetShortestPathsBetweenAllVertices_2) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  EXPECT_THROW(graphAlgorithm.GetShortestPathsBetweenAllVertices(graph),
               std::exception);
}

TEST(GraphAlgorithmTest, GetLeastSpanningTree_1) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  graph.LoadGraphFromFile(graphAlgorithmLeastSpanningTreePath);
  EXPECT_TRUE(AreMatricesEqual(graphAlgorithm.GetLeastSpanningTree(graph),
                               graphAlgorithmLeastSpanningTreeResult));
}

TEST(GraphAlgorithmTest, GetLeastSpanningTree_2) {
  s21::GraphAlgorithm graphAlgorithm;
  s21::Graph graph;
  EXPECT_THROW(graphAlgorithm.GetLeastSpanningTree(graph), std::exception);
}
