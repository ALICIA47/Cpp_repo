class Solution {
    public:
        vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
            vector<vector<int>> res;
            vector<int> current;
            pathSumHelper(root, targetSum, current, res);
            return res;
        }
    
    private:
        void pathSumHelper(TreeNode* node, int targetSum, vector<int>& current, vector<vector<int>>& res) {
            if (node == nullptr) return;
    
            current.push_back(node->val);
            targetSum -= node->val;
    
            if (node->left == nullptr && node->right == nullptr && targetSum == 0) {
                res.push_back(current);
            } else {
                pathSumHelper(node->left, targetSum, current, res);
                pathSumHelper(node->right, targetSum, current, res);
            }
    
            current.pop_back();
        }
    };