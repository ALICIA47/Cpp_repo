#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<windows.h>
#include<conio.h>
using namespace std;
class Solution{
    public:
        void hiersort(vector<int>& num){ 
            int n = (int)num.size();
            // 1. 生成 Knuth 增量序列 1, 4, 13, 40, ...
            int h = 1;
            while (h < n / 3) h = 3 * h + 1;      // 最大增量不超过 n/3
    
            // 2. 递减增量做 g-排序（插入排序的变体）
            while (h >= 1) {
                for (int i = h; i < n; ++i) {     // 对每个元素，按增量 h 做插入
                    int temp = num[i];
                    int j = i - h;
                    while (j >= 0 && num[j] > temp) {
                        num[j + h] = num[j];
                        j -= h;
                    }
                    num[j + h] = temp;
                }
                h /= 3;                           // Knuth 减量
            }
        }
    };

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8); 
    cout<<"请输入一系列整数，以空格间隔回车结束：\n";
    string line;
    getline(cin,line);
    istringstream iss(line);
    vector<int> num;
    int x;
    while(iss>>x) num.push_back(x);
    cout<<"输入为：";
    int n=num.size();
    for(int i=0;i<n;i++){
        cout<<num[i]<<" ";
    }
    cout<<endl;
    Solution sol;
    sol.hiersort(num);
    cout<<"排序为：";
    int r=num.size();
    for(int i=0;i<r;i++){
        cout<<num[i]<<" ";
    }
    cout<<endl;
    cout<<"按 Enter 退出...";
    cin.get();
    return 0;
}