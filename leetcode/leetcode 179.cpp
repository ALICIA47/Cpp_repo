/*class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string res;
        int n=nums.size();
        for(int j=8;j>0;j--){
            vector<int> currentnums(n,0);//记录位数数；
            int powernums=1;
            int m=j;
            while(m!=0){
                powernums*=10;
                m--;
            }
            for(int i=0;i<n;i++){
                int k=0;
                if(currentnums[i]!=nums[i]%powernums){
                    currentnums[i]=nums[i]%powernums;
                    k++;
                    }
                while(k!=0){
                    int midnums=0;
                    for(int i=0;i<n;i++){
                        if(currentnums[i]>midnums){
                            midnums=currentnums[i];
                        }
                    }
                    res.append(to_string(currentnums[i]));
                    k--;
                }
            }
        }
        return res;
    }
};*/
class Solution {
    public:
        string largestNumber(vector<int>& nums) {
            vector<string> numStrs;
            for (int num : nums) {
                numStrs.push_back(to_string(num));
            }
            
            // 自定义排序规则：比较字符串组合后的字典序
            sort(numStrs.begin(), numStrs.end(), [](const string& a, const string& b) {
                return a + b > b + a;
            });
            
            // 处理全0的特殊情况
            if (numStrs[0] == "0") {
                return "0";
            }
            
            string res;
            for (const string& s : numStrs) {
                res += s;
            }
            return res;
        }
    };