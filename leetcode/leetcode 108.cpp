class Solution {
    public:
        TreeNode* sortedArrayToBST(vector<int>& nums) {
            if(nums.empty())return nullptr;
            return buildBalance(nums,0,nums.size()-1);
        }
    private:
        TreeNode*buildBalance(const vector<int>& nums,int left,int right){
            if(left>right)return nullptr;
            int mid=left+(right-left)/2;
            TreeNode*node=new TreeNode(nums[mid]);
            node->left=buildBalance(nums,left,mid-1);
            node->right=buildBalance(nums,mid+1,right);
            return node;
        }
    };