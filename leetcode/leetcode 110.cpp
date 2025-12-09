class Solution {
    public:
        bool isBalanced(TreeNode* root) {
            if(root==nullptr)return true;
            int left=Treeheight(root->left);
            int right=Treeheight(root->right);
            if(left-right>1||left-right<-1){
                return false;
            }
            else{
                return isBalanced(root->left)&&isBalanced(root->right);
            }
        }
    private:
        int Treeheight(TreeNode*root){
            if(root==nullptr)return 0;
            int leftheight=Treeheight(root->left);
            int rightheight=Treeheight(root->right);
            return max(leftheight,rightheight)+1;
        }
    };
    