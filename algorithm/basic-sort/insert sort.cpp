#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<windows.h>
#include<conio.h>
using namespace std;
class solution{
public:
    vector<int>choosesort(vector<int>& num){
        int n=num.size();
        for(int i=1;i<n;i++){
            for(int j=i;j>0;j--){
                if(num[j]<num[j-1]){
                    int temp=num[j-1];
                    num[j-1]=num[j];
                    num[j]=temp;
                }   
            }
        }
        return num;
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
    solution sol;
    vector<int>res=sol.choosesort(num);
    cout<<"排序为：";
    int r=res.size();
    for(int i=0;i<r;i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
    cout<<"按 Enter 退出...";
    cin.get();
    return 0;
}