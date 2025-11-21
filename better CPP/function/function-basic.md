---
marp: true
size: 16:9
paginate: true
---

## 1、函数组成部分

- **返回类型**：使用引用返回可以避免不必要的对象复制，可以利用auto关键字使得函数返回类型依赖于表达式的类型

- **函数名**：应该明确、简洁但不失一定描述性

- **参数列表**：函数的输入，使用默认参数、重载函数或参数包可以处理更多场景

- **函数体**：实现部分，保持精简，遵循单一职责原则

- **特别的**：内联函数(关键字**inline**)可以提示编译器将函数体嵌入每个调用点，减少函数调用开销
constexpr函数：在C++11及以后的版本，该函数允许在编译时进行函数调用，可以提高性能和资源利用率
consteval函数：在C++20引入的**consteval**关键字用于声明只在编译时调用的函数

---

## 2、参数传递

- 按值传递：简单安全，函数内部对参数任何修改都不会影响原始数据

```cpp

void increment(int value){
    value+=1;
}
int main(){
    int a=5;
    increment(a);//a本身没变
}

```

---

- 按引用传递：允许函数直接操作外部变量，如果需要修改传入数据或者传递大型对象且不想产生额外拷贝成本可以使用

```cpp

void increment(int& value){
    value+=1;//直接修改原始数据
}
int main(){
    int a=5;
    increment(a);//a变成6了
}

```

```cpp

void process(std::vector<int>&& data){
    //右值引用，用于绑定即将销毁的对象，从而允许从原始对象中移动资源而非复制，适合传递临时对象或需要转移所有权的大型数据结构
    std::vector<int>local_data=std::move(data;)//data现为空
}
int main(){
    std::vector<int>vec={1,2,3,4};
    process(std::move(vec));//vec内容已经被移动到local_data
}

```