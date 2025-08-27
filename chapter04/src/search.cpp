#include <limits>
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

using BFSMap = std::unordered_map<const GraphNode*, const GraphNode*>;

bool BFS(const Graph& graph, const GraphNode* start, const GraphNode* goal, BFSMap& outMap) {
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

struct GameState {
    enum SquareState { Empty,
                       X,
                       O };
    SquareState mBoard[3][3];
};

struct GameTreeNode {
    std::vector<GameTreeNode*> mChildren;
    GameState mState;
};

float GetScore(const GameState& state) {
    // Are any of the rows the same?
    for (int i{ 0 }; i < 3; i++) {
        bool same{ true };
        GameState::SquareState v{ state.mBoard[i][0] };

        for (int j{ 1 }; j < 3; j++) {
            if (state.mBoard[i][j] != v) {
                same = false;
            }
        }

        if (same) {
            if (v == GameState::X) {
                return 1.0f;
            } else {
                return -1.0f;
            }
        }
    }

    // Are any of the columns the same?
    for (int j{ 0 }; j < 3; j++) {
        bool same{ true };
        GameState::SquareState v{ state.mBoard[0][j] };

        for (int i{ 1 }; i < 3; i++) {
            if (state.mBoard[j][i] != v) {
                same = false;
            }
        }

        if (same) {
            if (v == GameState::X) {
                return 1.0f;
            } else {
                return -1.0f;
            }
        }
    }

    // What about diagonals?
    if (((state.mBoard[0][0] == state.mBoard[1][1]) &&
         (state.mBoard[1][1] == state.mBoard[2][2])) ||
        ((state.mBoard[2][0] == state.mBoard[1][1]) &&
         (state.mBoard[1][1] == state.mBoard[0][2]))) {
        if (state.mBoard[1][1] == GameState::X) {
            return 1.0f;
        } else {
            return -1.0f;
        }
    }

    // It's a tie
    return 0.0f;
}

float MaxPlayer(const GameTreeNode* node) {
    if (node->mChildren.empty()) {
        return GetScore(node->mState);
    }

    float maxValue{ -std::numeric_limits<float>::infinity() };
    for (const GameTreeNode* child : node->mChildren) {
        maxValue = std::max(maxValue, MinPlayer(child));
    }

    return maxValue;
}

float MinPlayer(const GameTreeNode* node) {
    if (node->mChildren.empty()) {
        return GetScore(node->mState);
    }

    float minValue{ std::numeric_limits<float>::infinity() };
    for (const GameTreeNode* child : node->mChildren) {
        minValue = std::min(minValue, MaxPlayer(child));
    }

    return minValue;
}

const GameTreeNode* MinimaxDecider(const GameTreeNode* root) {
    const GameTreeNode* choice{ nullptr };
    float maxValue{ -std::numeric_limits<float>::infinity() };

    for (const GameTreeNode* child : root->mChildren) {
        float v{ MinPlayer(child) };
        if (v > maxValue) {
            maxValue = v;
            choice = child;
        }
    }

    return choice;
}

float AlphaBetaMax(const GameTreeNode* node, float alpha, float beta) {
    if (node->mChildren.empty()) {
        return GetScore(node->mState);
    }

    float maxValue{ -std::numeric_limits<float>::infinity() };
    for (const GameTreeNode* child : node->mChildren) {
        maxValue = std::max(maxValue, AlphaBetaMin(child, alpha, beta));
        if (maxValue >= beta) {
            return maxValue;
        }

        alpha = std::max(maxValue, alpha);
    }

    return maxValue;
}

float AlphaBetaMin(const GameTreeNode* node, float alpha, float beta) {
    if (node->mChildren.empty()) {
        return GetScore(node->mState);
    }

    float minValue{ std::numeric_limits<float>::infinity() };
    for (const GameTreeNode* child : node->mChildren) {
        minValue = std::min(minValue, AlphaBetaMax(child, alpha, beta));
        if (minValue <= alpha) {
            return minValue;
        }

        beta = std::min(minValue, beta);
    }

    return minValue;
}

const GameTreeNode* AlphaBetaDecider(const GameTreeNode* root, int depth, float alpha, float beta) {
    const GameTreeNode* choice{ nullptr };
    float maxValue{ -std::numeric_limits<float>::infinity() };
    float beta{ std::numeric_limits<float>::infinity() };

    for (const GameTreeNode* child : root->mChildren) {
        float v{ AlphaBetaMin(child, maxValue, beta) };
        if (v > maxValue) {
            maxValue = v;
            choice = child;
        }
    }

    return choice;
}
