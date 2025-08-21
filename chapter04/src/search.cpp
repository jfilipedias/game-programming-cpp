#include <queue>
#include <unordered_map>
#include <vector>

// Unweighted graph

struct GraphNode {
    std::vector<GraphNode*> mAdjacents;
};

struct Graph {
    std::vector<GraphNode*> nodes;
};

// Weighted graph

struct WeightedEdge {
    struct WeightedGraphNode* mFrom;
    struct WeightedGraphNode* mTo;
    float mWeight;
};

struct WeightedGraphNode {
    std::vector<WeightedEdge*> mEdges;
};

struct WeightedGraph {
    std::vector<WeightedGraphNode*> mNodes;
};

using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

bool BFS(const Graph& graph, const GraphNode* start, const GraphNode* goal, NodeToParentMap& outMap) {
    bool pathFound{ false };

    std::queue<const GraphNode*> q;
    q.push(start);

    while (!q.empty()) {
        const GraphNode* current{ q.front() };
        q.pop();

        if (current == goal) {
            pathFound = true;
            break;
        }

        for (const GraphNode* node : current->mAdjacents) {
            const GraphNode* parent{ outMap[node] };
            if (parent == nullptr && current != start) {
                outMap[node] = current;
                q.push(node);
            }
        }
    }

    return pathFound;
}

float ComputeHeuristic(const WeightedGraphNode* a, const WeightedGraphNode* b) {
    return 0.0f;
}

struct GBFSScratch {
    const WeightedEdge* mParentEdge = nullptr;
    float mHeuristic = 0.0f;
    bool mInOpenSet = false;
    bool mInClosedSet = false;
};

using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

bool GBFS(const WeightedGraph& graph, const WeightedGraphNode* start, const WeightedGraphNode* goal, GBFSMap& outMap) {
    std::vector<const WeightedGraphNode*> openSet;

    const WeightedGraphNode* current{ start };
    outMap[current].mInClosedSet = true;

    while (current != goal) {
        for (const WeightedEdge* edge : current->mEdges) {
            const WeightedGraphNode* neighbor{ edge->mTo };
            GBFSScratch& data{ outMap[neighbor] };

            if (data.mInClosedSet) {
                continue;
            }

            data.mParentEdge = edge;
            if (data.mInOpenSet) {
                continue;
            }

            data.mHeuristic = ComputeHeuristic(neighbor, goal);
            data.mInOpenSet = true;
            openSet.push_back(neighbor);
        }

        if (openSet.empty()) {
            break;
        }

        std::vector<const WeightedGraphNode*>::iterator iter{
            std::min_element(
                openSet.begin(),
                openSet.end(),
                [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
                    return outMap[a].mHeuristic < outMap[b].mHeuristic;
                })
        };

        current = *iter;
        openSet.erase(iter);
        outMap[current].mInOpenSet = false;
        outMap[current].mInClosedSet = true;
    };

    return current == goal;
}

struct AStarScratch {
    const WeightedEdge* mParentEdge = nullptr;
    float mHeuristic = 0.0f;
    float mActualFromStart = 0.0f;
    bool mInOpenSet = false;
    bool mInClosedSet = false;
};

using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;

bool AStar(const WeightedGraph& graph, const WeightedGraphNode* start, const WeightedGraphNode* goal, AStarMap& outMap) {
    std::vector<const WeightedGraphNode*> openSet;

    const WeightedGraphNode* current{ start };
    outMap[current].mInClosedSet = true;

    while (current != goal) {
        for (const WeightedEdge* edge : current->mEdges) {
            const WeightedGraphNode* neighbor{ edge->mTo };
            AStarScratch& data{ outMap[current] };

            if (data.mInClosedSet) {
                continue;
            }

            if (data.mInOpenSet) {
                float newG{ outMap[current].mActualFromStart + edge->mWeight };
                if (newG >= data.mActualFromStart) {
                    continue;
                }

                data.mParentEdge = edge;
                data.mActualFromStart = newG;
            } else {
                data.mParentEdge = edge;
                data.mHeuristic = ComputeHeuristic(neighbor, goal);
                data.mActualFromStart = outMap[current].mActualFromStart + edge->mWeight;
                data.mInOpenSet = true;
                openSet.push_back(neighbor);
            }
        }

        if (openSet.empty()) {
            break;
        }

        std::vector<const WeightedGraphNode*>::iterator iter{
            std::min_element(
                openSet.begin(),
                openSet.end(),
                [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
                    float fOfA{ outMap[a].mHeuristic + outMap[a].mActualFromStart };
                    float fOfB{ outMap[b].mHeuristic + outMap[b].mActualFromStart };
                    return fOfA < fOfB;
                })
        };

        current = *iter;
        openSet.erase(iter);
        outMap[current].mInOpenSet = false;
        outMap[current].mInClosedSet = true;
    };

    return current == goal;
}
