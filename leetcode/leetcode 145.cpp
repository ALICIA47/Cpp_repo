class Solution {
    public:
        vector<int> postorderTraversal(TreeNode* root) {
            vector<int> res;
            if(root!=nullptr){
                vector<int> left=postorderTraversal(root->left);
                vector<int> right=postorderTraversal(root->right);
    
                res.insert(res.end(),left.begin(),left.end());
                res.insert(res.end(),right.begin(),right.end());
    
                res.push_back(root->val);
            }
            return res;
        }
    };