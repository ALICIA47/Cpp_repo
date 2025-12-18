class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int min=INT_MAX;
            int res=0;
            for(int price:prices){
                    if(price<min){
                        min=price;
                    }
                    else if(price-min>res){
                        res=price-min;
                    }
                }
        return res;
        } 
    };