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

---

- 按指针传递：与引用传递类似，但明确表达了内存地址的概念，在与旧的C语言代码互操作或者要处理NULL指针的情况下合适

```cpp

void increment(int* value){
    if(value){
        *value+=1;//修改指向的值
    }
}
int main(){
    int a=5;
    increment(&a);//a变成6了
}

```

---

- 传递方式选择

|目的|按值传递|按引用传递|按右值引用传递|按指针传递|
|-|-|-|-|-|
|参数|需要复制实参|不需要复制实参|不需要复制实参|不需要复制实参|
|内存消耗|可能较大(取决于实参大小)|较小(只传递引用)|较小(避免数据复制)|较小(只传递指针大小)|
|修改|不影响实参|直接影响实参|直接影响实参|直接影响实参|
|安全性|较高(不会修改实参)|较低(可能修改实参)|确保不再使用移动后的数据较低|空指针检查可以增加安全性|
|特殊用途|适用于小型数据或不修改实参的情况|修改实参或避免大对象拷贝的场景|处理临时对象或需要所有权移动的大型对象|可处理空值或与C程序接口互操作|

---

## 3、默认实参的使用与注意事项

在C++中，可以为函数参数设置默认值，这种参数被称为默认实参，调用对应函数时若没有提供某个默认实参的值，那么将使用该参数的默认值

```cpp

int power(int base,int exponent=2){
    int result=1;
    for(int i=0;i<exponent;++i){
        result*=base;
    }
    return result;
}
int main(){
    int a=power(3);//得9
    int b=power(3,3)//得27
}
```

---

### 使用默认参数要注意

- 默认实参的规定性：默认参数只能在函数声明里面指定一次(定义的时候省略)

- 参数默认值的连续性：只有当函数参数位于参数列表的最右侧时才能为它指定默认值，这意味着一旦某个参数设定为默认值则其右侧的所有参数都必须设定默认值

- 默认实参的值的限制：默认参数值必须是编译时可知的常量表达式，即不能使用局部变量、非静态成员变量或者任何运算时需要计算结果的表达式

---

### 类成员作为默认实参的限制

- 非静态成员变量：由于这些变量的值与具体的类实例相关，且不是编译时常量，因此不能用作默认参数

- 成员函数：可以用作默认实参，但通通常需要指向特定对象的成员函数的指针，这种用法较少

- 静态成员：静态成员变量和函数由于在编译时具有确定的值，可以作为默认参数

- 版本差异：不同编译器和C++版本可能在实施这些规则时有所不同

---

## 4、函数参数的类型匹配与转换

- 函数参数的类型匹配：实参必须与形参类型匹配

```cpp

void display(int value){
    std::cout<<value<<std::endl;
}
int main(){
    int num=10;
    display(num);//类型匹配无须转换
}

```

---

- 自动类型转换

```cpp

void display(double value){
    std::cout<<value<<std::endl;
}
int main(){
    int num=10;
    display(num);//int自动转换为double
}

```

---

- 强制类型转换

```cpp

void display(double value){
    std::cout<<value<<std::endl;
}
int main(){
    char ch='A';
    display(static_cast<double>(ch));//显式转换
}

```

- 模板和函数重载中的类型转换：C++的模板和函数重载机制允许相同名称的函数处理不同类型的参数，这些情况下编译器根据传递的参数类型来选择最合适的函数版本

---

## 5、main函数传参

main函数可以接收:int argc和char* argv[]

- argc(argument count)表示命令行参数的数量，至少为1

- argv(argument vector)字符指针数组，每个元素指向一个字符串，即命令行传递给程序的一个参数，其中argv[0]为程序名称，argv[1]是传递给程序的第一个参数，直到argv[argv-1]

- 通过命令行参数用户可以在启动程序时传递配置信息、文件路径或其他数据

需要接收参数执行特定任务的情况：

- 配置控制：程序行为可能需要根据用户或环境提供的配置进行调整

- 功能选择：若程序包含多个功能，可以通过命令行参数来选择执行哪个功能

- 数据输入：需要处理的数据文件或值可以通过命令行参数传入，避免硬编码这些

---

## 6、参数的生命周期和存储位置

- 命令行输入：当用户在命令行中输入命令并执行程序时，OS会将整个命令行字符串(包括程序名称和参数)处理为一系列字符串。每个参数为一个字符串由空格分隔

- 内存分配：OS为这些字符串及其数组分配内存空间，通常它们位于堆栈区域，它们在程序开始前执行分配并且随着程序结束而被释放

- 参数传递：OS将命令行参数的数量(argc)和指向这些参数的指针数组(argv)传递给程序的main函数，argv是一个指向字符指针的数组，其中每个元素都指向一个参数字符串，argv[0]通常是程序的名称而argv[1]~argv[argc-1]是命令行提供的参数

- 生命周期管理：从main函数开始到程序结束，这些命令行参数都是可访问的，它们在程序整个运行周期内都位于内存中，程序一旦终止OS就会清理这些分配的内存空间

---

## 7、函数传参的高阶应用

**函数作为参数传递**

```cpp
//函数指针
#include<iostream>
void display(int x){
    std::cout<<"Value"<<x<<std::endl;
}
void executeFunction(void(*func)(int),int value){
    func(value);
}
int main(){
    executeFunction(display,5);
    return 0;
}
```

---

**std::function**：一种允许封装几乎任何类型的可调用实体

```cpp
#include<functional>
#include<iostream>
void executeFunction(std::function<void(int)>func,int value){
    func(value);
}
int main(){
    std::function<void(int)>func=[(int x)]{std::cout<<"Lambda:"<<x<<std::endl;};
    execute(func,10);
    return 0;
}
```

---
**容器作为参数传递**

- 传统数组

```cpp

#include<iostream>
void processArray(int *arr,int size){
    for(int i=0;i<size;++i){
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}
int main(){
    int data[]={1,2,3,4,5};
    processArray(data,5);
    return 0;
} 

```

简单但是没有边界检查

---

- 使用std::array

```cpp
#include<array>
#include<iostream>

void processArray(const std::array<int, 5>&arr){
    for(int i:arr){
        std::cout<<i<<" ";
    }
    std::cout<<endl;
}
int main(){
    std::array<int, 5>data={1,2,3,4,5};
    processArray(data);
    return 0;
}
```
数组大小被固定

---

- 使用std::vector

```cpp
#include<vector>
#include<iostream>
void processVector(const std::vectro<int>&vec){
    for(int i:vec){
        std::cout<<i<<" ";
    }
    std::cout<<endl;
}
int main(){
    std::vector<int> data={1,2,3,4,5};
    processVector(data);
    return 0;
}
```
有动态大小的管理

---

- 使用std::span

```cpp

#include<span>
#include<iostream>
#include<vector>

void processSpan(const std::span<int> data){
    for(int i:data){
        std::cout<<i<<" "；
    }
    std::cout<<endl;
}
int main(){
    std::vector<int> vec={1,2,3,4,5};
    std::span<int> span=vec;
    processSpan(span);
    return 0;
}
```
C++20的新特性span(视图)：易创建、有范围检查、传递成本低