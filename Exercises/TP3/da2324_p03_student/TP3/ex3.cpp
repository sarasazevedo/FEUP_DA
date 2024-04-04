// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "MSTTestAux.h"
#include "../data_structures/UFDS.h"

template <class T>
void dfsKruskalPath(Vertex<T> *v) {
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        if (e->isSelected() && !e->getDest()->isVisited()) {
            e->getDest()->setPath(e);
            dfsKruskalPath(e->getDest());
        }
    }
}

template <class T>
std::vector<Vertex<T> *> kruskal(Graph<T> *g) {
    if (g->getVertexSet().empty()) {
        return g->getVertexSet();
    }
    UFDS ufds(g->getVertexSet().size());
    {
        int id = 0;
        for (auto v: g->getVertexSet()) {
            v->setInfo(id++);
        }
    }
    std::vector<Edge<T> *> allEdges;
    for (auto v: g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setSelected(false);
            if (e->getOrig()->getInfo() < e->getDest()->getInfo()) {
                allEdges.push_back(e);
            }
        }
    }
    sort(allEdges.begin(), allEdges.end(), [](Edge<T> *a, Edge<T> *b) { return a->getWeight() < b->getWeight(); });
    unsigned selectedEdges = 0;
    for (auto e: allEdges) {
        auto orig = e->getOrig();
        auto dest = e->getDest();
        if (!ufds.isSameSet(orig->getInfo(), dest->getInfo())) {
            ufds.linkSets(orig->getInfo(), dest->getInfo());
            e->setSelected(true);
            e->getReverse()->setSelected(true);
            if (++selectedEdges == g->getVertexSet().size() - 1) {
                break;
            }
        }
    }

    for (auto v: g->getVertexSet()) {
        v->setVisited(false);
    }
    g->getVertexSet()[0]->setPath(nullptr);
    dfsKruskalPath(g->getVertexSet()[0]);
    return g->getVertexSet();
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex3, test_kruskal) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = kruskal(&graph);

    std::stringstream ss;
    for(const auto v : res) {
        ss << v->getInfo() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}