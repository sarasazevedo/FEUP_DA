#include <stdexcept>
#include <algorithm>
#include "Edmonskarp.h"
#include "Network.h"
#include "Pipe.h"
#include "Node.h"
#include <queue>
#include <limits>


void Edmonskarp::testAndVisit(std::queue<Node *> &q, Pipe *pipe, Node *dest, double residual) {
    if (!dest->isVisited() && residual > 0) {
        dest->setVisited(true);
        dest->setPath(pipe);
        q.push(dest);
    }
}

bool Edmonskarp::findAugmentingPath(Network &network, Node *s, Node *t, bool improvedBalance) {
    for (auto &[_, node]: network.getNodeSet()) {
        node->setVisited(false);
    }

    s->setVisited(true);
    queue<Node *> q;
    q.push(s);

    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();

        // Sort the pipes by their load (flow/capacity)
        auto adj = v->getAdj();
        if (improvedBalance) {
            std::sort(adj.begin(), adj.end(), [](const Pipe *a, const Pipe *b) {
                return (a->getFlow() / a->getCapacity()) < (b->getFlow() / b->getCapacity());
            });
        }

        for (const auto pipe: adj) {
            testAndVisit(q, pipe, pipe->getDest(), pipe->getCapacity() - pipe->getFlow());
        }

        auto incoming = v->getIncoming();
        if (improvedBalance) {
            std::sort(incoming.begin(), incoming.end(), [](const Pipe *a, const Pipe *b) {
                return (a->getFlow() / a->getCapacity()) < (b->getFlow() / b->getCapacity());
            });
        }

        for (const auto pipe: incoming) {
            testAndVisit(q, pipe, pipe->getSrc(), pipe->getFlow());
        }
    }

    return t->isVisited();
}

double Edmonskarp::findMinResidualAlongPath(Node *s, Node *t) {
    int f = std::numeric_limits<int>::max();

    for (auto v = t; v != s;) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = min(f, e->getCapacity() - e->getFlow());
            v = e->getSrc();
        } else {
            f = min(f, e->getFlow());
            v = e->getDest();
        }
    }

    return f;
}

void Edmonskarp::augmentFlowAlongPath(Node *s, Node *t, double f) {
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getSrc();
        } else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

void Edmonskarp::edmondsKarp(Network &network, const std::string &sourceCode, const std::string &targetCode,
                             bool improvedBalance) {
    Node *s = network.findVertex(sourceCode);
    Node *t = network.findVertex(targetCode);

    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target node");

    for (auto &[_, node]: network.getNodeSet()) {
        node->setPath(nullptr);
        for (auto &pipe: node->getAdj()) {
            pipe->setFlow(0);
        }
    }

    while (findAugmentingPath(network, s, t, improvedBalance)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}
