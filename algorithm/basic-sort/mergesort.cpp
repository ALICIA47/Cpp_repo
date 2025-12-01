#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<windows.h>
#include<conio.h>
using namespace std;
class Solution{
public:
    void quicksort(vector<int>& num){
        qsort(num,0,(int)num.size()-1);
    }
private:
    void qsort(vector<int>&num,int l,int r){
        if(l>=r)return;
        int i=l,j=r,pos=num[l];
        while(i<j){
            while(i<j&&num[j]>=pos)j--;
            if(i<j){
                num[i]=num[j];
                i++;
            }
            while(i<j&&num[i]<=pos)i++;
            if(i<j){
                num[j]=num[i];
                j--;
            }    
        }
        num[i]=pos;
        qsort(num,l,i-1);
        qsort(num,i+1,r);
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
    sol.quicksort(num);
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