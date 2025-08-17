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
