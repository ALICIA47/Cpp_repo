---
marp: true
theme: default
paginate: true  
header: public inheritance
---

# 名称遮掩：对于一个变量编译器会先
# 去找本地作用域是否存在该变量声明，如果没有再找上层作用域

### 如果进行了集成并且重载了函数，此时不得不遮掩名称应该使用using进行声明