#include<iostream>
class Account{
public:
    Account(double balance) : balance_(balance){}
    double getBalance()const{//const成员函数不修改任何成员变量
        return balance_;
    }
    void deposit(double amount){
        balance_+=amount;
    }
private:
    double balance_;
};

int main(){
    const Account myAccount(1000.0);
    double myBalance=myAccount.getBalance();//const对象可以调用const成员函数
    std::cout<<"Balance: $"<<myBalance<<std::endl;
    //myAccount.deposit(500.0);//非const对象不可调用
    return 0;
}