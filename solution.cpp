#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct NodeInfo {
    int depth;
    int parent;
};

class Solution {
private:
    unordered_map<int, NodeInfo> nodeMap;
    int index;
    
    void buildTree(const vector<int>& preorder, int depth, int parent) {
        if (index >= static_cast<int>(preorder.size())) {
            return;
        }
        
        int val = preorder[index];
        index++;
        
        if (val == -1) {
            return;
        }
        
        // Store node information
        nodeMap[val] = {depth, parent};
        
        // Recursively build left and right subtrees
        buildTree(preorder, depth + 1, val);
        buildTree(preorder, depth + 1, val);
    }
    
public:
    Solution() : index(0) {}
    
    void buildTreeFromPreorder(const vector<int>& preorder) {
        index = 0;
        nodeMap.clear();
        buildTree(preorder, 0, -1); // root has depth 0 and parent -1
    }
    
    bool areCousins(int x, int y) {
        if (nodeMap.find(x) == nodeMap.end() || nodeMap.find(y) == nodeMap.end()) {
            return false;
        }
        
        const NodeInfo& infoX = nodeMap[x];
        const NodeInfo& infoY = nodeMap[y];
        
        return (infoX.depth == infoY.depth) && (infoX.parent != infoY.parent);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Read all input from stdin
    vector<int> allNumbers;
    int num;
    while (cin >> num) {
        allNumbers.push_back(num);
    }
    
    if (allNumbers.empty()) {
        return 0;
    }
    
    // First number is the number of queries
    int q = allNumbers[0];
    
    // Extract queries (2 numbers per query)
    vector<pair<int, int>> queries;
    int idx = 1;
    for (int i = 0; i < q && idx + 1 < static_cast<int>(allNumbers.size()); i++) {
        queries.emplace_back(allNumbers[idx], allNumbers[idx + 1]);
        idx += 2;
    }
    
    // Remaining numbers are the tree preorder traversal
    vector<int> preorder;
    while (idx < static_cast<int>(allNumbers.size())) {
        preorder.push_back(allNumbers[idx]);
        idx++;
    }
    
    // Build tree and process queries
    Solution solution;
    solution.buildTreeFromPreorder(preorder);
    
    // Process each query
    for (const auto& query : queries) {
        int x = query.first;
        int y = query.second;
        cout << (solution.areCousins(x, y) ? 1 : 0) << '\n';
    }
    
    return 0;
}