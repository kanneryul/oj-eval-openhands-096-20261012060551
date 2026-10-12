#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct NodeInfo {
    int depth;
    int parent;
    NodeInfo(int d, int p) : depth(d), parent(p) {}
};

class Solution {
private:
    unordered_map<int, NodeInfo*> nodeMap;
    int index;
    
    TreeNode* buildTree(const vector<int>& preorder, int depth, int parent) {
        if (index >= static_cast<int>(preorder.size())) {
            return nullptr;
        }
        
        int val = preorder[index];
        index++;
        
        if (val == -1) {
            return nullptr;
        }
        
        // Store node information
        nodeMap[val] = new NodeInfo(depth, parent);
        
        TreeNode* node = new TreeNode(val);
        node->left = buildTree(preorder, depth + 1, val);
        node->right = buildTree(preorder, depth + 1, val);
        
        return node;
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
        
        NodeInfo* infoX = nodeMap[x];
        NodeInfo* infoY = nodeMap[y];
        
        return (infoX->depth == infoY->depth) && (infoX->parent != infoY->parent);
    }
    
    ~Solution() {
        for (auto& pair : nodeMap) {
            delete pair.second;
        }
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