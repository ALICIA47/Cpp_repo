class Solution {
    public:
        string convertToTitle(int columnNumber) {
            int info=columnNumber;
            string result;
            while(info>0){
                info--;
                int carry=info%26;
                info/=26;
                result+='A'+carry;
            }
            reverse(result.begin(),result.end());
            return result;
        }
    };