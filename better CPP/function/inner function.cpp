#include<iostream>

//预处理检测编译器类型
#if defined(_GNUC_)//GCC编译器
//示例：_builtin_popcount,计算一个无符号整数中位为1的数量
unsigned int countBits(unsigned int value){
    return _builtin_popcount(value);
}
#elif defined(_MSC_VER)//VS编译器
#include<intrin.h>//包含MSVC内建函数所需
//示例：_popcnt,计算一个无符号整数中二进制位为1的数量
unsigned int countBits(unsigned int value){
    return _popcnt(value);
}
#else
//通用回退
unsigned int countBits(unsigned int value){
    unsigned int count=0;
    while(value){
        count+=value&1;
        value>>=1;
    }
    return count;
}

#endif
int main(){
    unsigned int value=0b10101010;
    std::cout<<"The number of set bits in "<<value<<" is "<<countBits(value)<<"."<<std::endl;
    return 0;
}