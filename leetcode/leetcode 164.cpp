class Solution {
    public:
        int maximumGap(vector<int>& nums) {
            int n = nums.size();
            if (n < 2) return 0;
    
            // 找到数组中的最大值和最小值
            int minVal = *min_element(nums.begin(), nums.end());
            int maxVal = *max_element(nums.begin(), nums.end());
    
            // 计算每个桶的大小
            int bucketSize = max(1, (maxVal - minVal) / (n - 1));
            int bucketCount = (maxVal - minVal) / bucketSize + 1;
    
            // 初始化桶
            vector<int> bucketMin(bucketCount, INT_MAX);
            vector<int> bucketMax(bucketCount, INT_MIN);
    
            // 将每个元素放入桶中
            for (int num : nums) {
                int bucketIndex = (num - minVal) / bucketSize;
                bucketMin[bucketIndex] = min(bucketMin[bucketIndex], num);
                bucketMax[bucketIndex] = max(bucketMax[bucketIndex], num);
            }
    
            // 计算最大间隔
            int maxGap = 0;
            int prevMax = minVal;
            for (int i = 0; i < bucketCount; ++i) {
                if (bucketMin[i] == INT_MAX) continue; // 跳过空桶
                maxGap = max(maxGap, bucketMin[i] - prevMax);
                prevMax = bucketMax[i];
            }
    
            return maxGap;
        }
    };