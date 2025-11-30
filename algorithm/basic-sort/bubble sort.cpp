#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<windows.h>
#include<conio.h>
using namespace std;
class solution{
public:
    vector<int>bubblesort(vector<int>& num){
        int n=num.size();
        bool whetherswap;//优化冒泡判断是否交换
        for(int i=0;i<n-1;i++){//i=n-1时必然已经排序完成
            whetherswap=false;
            for(int j=0;j<n-i-1;j++){//若让j<n-i则可能会有j=n-i-1,j+1=n-i导致越界溢出 
                if(num[j+1]<num[j]){
                    int temp=num[j];
                    num[j]=num[j+1];
                    num[j+1]=temp;
                    whetherswap=true;
                };
            }
            if(!whetherswap)break;
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
    vector<int>res=sol.bubblesort(num);
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