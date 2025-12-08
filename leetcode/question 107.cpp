class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        if(root==nullptr)return result;
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            vector<int> currentlevel;
            int levelsize=q.size();
            for(int i=0;i<levelsize;i++){
                TreeNode*node=q.front();
                q.pop();
                currentlevel.push_back(node->val);
                if(node->left!=nullptr)q.push(node->left);
                if(node->right!=nullptr)q.push(node->right);
            }
            result.insert(result.begin(),currentlevel);
        }
        //reverse(result.begin(),result.end());
        return result;
    }
};