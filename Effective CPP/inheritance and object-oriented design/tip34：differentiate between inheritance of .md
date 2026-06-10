---
marp: true
theme: default
paginate: true  
header: public inheritance
---

# 区分接口继承和实现继承

```cpp

class Shape{
public:
    virtual void draw() const=0;
    virtual void error(const std::string&msg);
    int objectID() const;

};

class Retangle:public Shape{};
class Ellipse:public Shape{};

```

##### 显然Shape是个抽象类无法被实例化只能实例化其继承类，但是我们仍然可以给其中的pure virtual函数提供定义，只是调用的时候必须明确指出类名称
