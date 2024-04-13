#include <gtest/gtest.h>

#include "../Libs/Graph/Headers/s21_graph.h"
#include "s21_test.h"

TEST(GraphTest, Constructor_default_1) {
  s21::Graph graph;
  EXPECT_EQ(graph.GetSize(), 0);
  EXPECT_TRUE(graph.GetAdjacencyMatrix().empty());
}

TEST(GraphTest, LoadGraphFromFile_1) {
  s21::Graph graph;
  EXPECT_EQ(graph.LoadGraphFromFile(graphPath), true);
  EXPECT_EQ(graph.GetSize(), graphSize);
}

TEST(GraphTest, LoadGraphFromFile_2) {
  s21::Graph graph;
  EXPECT_EQ(graph.LoadGraphFromFile(doesntExistPath), false);
}

TEST(GraphTest, LoadGraphFromFile_3) {
  s21::Graph graph;
  EXPECT_EQ(graph.LoadGraphFromFile(graphPath), true);
  EXPECT_EQ(graph.GetSize(), graphSize);
  EXPECT_TRUE(AreMatricesEqual(graph.GetAdjacencyMatrix(), graphMatrix));
}

TEST(GraphTest, LoadGraphFromFile_4) {
  s21::Graph graph;
  EXPECT_EQ(graph.LoadGraphFromFile(incorrectPath), false);
}

TEST(GraphTest, ExportGraphToDot_1) {
  s21::Graph graph;
  EXPECT_EQ(graph.LoadGraphFromFile(graphPath), true);
  EXPECT_TRUE(graph.ExportGraphToDot(exportPath));
}

TEST(GraphTest, ExportGraphToDot_2) {
  s21::Graph graph;
  EXPECT_EQ(graph.LoadGraphFromFile(graphPath), true);
  EXPECT_TRUE(graph.ExportGraphToDot(emptyPath));
}

TEST(GraphTest, ExportGraphToDot_3) {
  s21::Graph graph;
  EXPECT_FALSE(graph.ExportGraphToDot(emptyPath));
}

TEST(GraphTest, Operator_1) {
  s21::Graph graph;
  EXPECT_EQ(graph.LoadGraphFromFile(graphPath), true);
  EXPECT_TRUE(AreVectorsEqual(graph[0], graphMatrix[0]));
  EXPECT_EQ(graph[0][3], graphMatrix[0][3]);
}
