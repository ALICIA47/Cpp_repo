#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<windows.h>
#include<conio.h>
using namespace std;

class Solution{
public:
    void guibingsort(vector<int>& num){  
        mergeSort(num,0,(int)num.size()-1);
    }
private:
    void mergeSort(vector<int>& num,int l,int r){
        if(l>=r) return;
        int mid = l + (r-l)/2;               // 防溢出
        mergeSort(num,l,mid);                // 左半
        mergeSort(num,mid+1,r);              // 右半
        merge(num,l,mid,r);                  // 合并
    }
    void merge(vector<int>& num,int l,int mid,int r){
        vector<int> tmp(r-l+1);              // 一次性申请
        int i = l, j = mid+1, k = 0;
        while(i<=mid && j<=r)
            tmp[k++] = (num[i]<=num[j]) ? num[i++] : num[j++];
        while(i<=mid) tmp[k++] = num[i++];
        while(j<=r)   tmp[k++] = num[j++];
        for(k=0;k<tmp.size();++k)            // 拷回原数组
            num[l+k] = tmp[k];
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
    sol.guibingsort(num); 
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