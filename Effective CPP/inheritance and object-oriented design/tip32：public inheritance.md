---
marp: true
theme: default
paginate: true  
header: public inheritance
---

# Make sure public inheritance models "is-a"

### if you do:

```cpp

class Base{};

class Derived: public Base{};

```

### that means "D" is "B" but "B" is not "D"

---

### if we have :

```cpp

class Person{};

class Student:public Person{};

```

### we can :

```cpp

void eat(const Person&p);
void study(const Student&s);
Person p;
Student s;
eat(p);
eat(s);
study(s);
study(p);//error!only student can study!

```

---

### sometimes public inheritance is complex

---
