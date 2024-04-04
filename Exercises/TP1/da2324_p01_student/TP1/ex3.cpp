#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

// Helper function to reverse the edges of a directed graph
template <typename T>
void aux_reverseGraphEdges(Graph<T>* g) {
    stack<int> edge_stack;
    for (auto v : g->getVertexSet()) {
        for (auto & e : v->getAdj()) {
            auto w = e.getDest();
            edge_stack.push(w->getInfo());
            edge_stack.push(v->getInfo());
        }
    }

    while (!edge_stack.empty()) {
        int src;
        int dst;
        dst = edge_stack.top();
        edge_stack.pop();
        src = edge_stack.top();
        edge_stack.pop();
        g->removeEdge(dst, src);
        g->addEdge(src,dst,0);
    }
}

// Kosaraju-Sharir algorithm
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g) {
    vector<vector<T>> sccs;
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    stack<Vertex<T> *> vertexStack;
    for (auto v : g->getVertexSet()) {
        if(!v->isVisited()) {
            firstDFSKosarajuSharir(v, &vertexStack);
        }
    }
    aux_reverseGraphEdges(g);

    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    while(!vertexStack.empty()) {
        Vertex<T> * v = vertexStack.top();
        vertexStack.pop();
        if(!v->isVisited()) {
            vector<T> scc;
            secondDFSKosarajuSharir(v,scc);
            sccs.push_back(scc);
        }
    }
    return sccs;
}

template <typename T>
void firstDFSKosarajuSharir(Vertex<T> *v, stack<Vertex <T> *> *vertexStack) {
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        auto w = e.getDest();
        if(!w->isVisited()) {
            firstDFSKosarajuSharir(w,vertexStack);
        }
    }
    vertexStack->push(v);
}

template <typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, std::vector<int> & res) {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            secondDFSKosarajuSharir(w, res);
        }
    }
}