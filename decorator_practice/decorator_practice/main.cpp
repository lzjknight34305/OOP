//
//  main.cpp
//  decorator_practice
//
//  Created by zijian.liu on 12/2/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#include <iostream>
using namespace std;

class Person {
public:
    string name;
    Person() {};
    
    Person(string name) {
        this->name = name;
    }
    virtual void introduce() {
        cout << "I'm " << name << ".\n";
    }
};

class Dress : public Person {
public:
    void decorate (Person * component) {
        this->component = component;
    }
    virtual void introduce() {
        if (component) {
            component->introduce();
        }
        cout << "I wear nothing.\n";
    }
protected:
    Person *component;
};

class Tshirt : public Dress {
public:
    void introduce() {
        if (component) {
            component->introduce();
        }
        cout << "I wear Tshirt.\n";
    }
};

class Suit : public Dress {
public:
    void introduce() {
        if (component) {
            component->introduce();
        }
        cout << "I wear Suit.\n";
    }
};

class Tank : public Dress {
public:
    void introduce() {
        if (component) {
            component->introduce();
        }
        cout << "I wear Tank.\n";
    }
};

class Sneaker : public Dress {
public:
    void introduce() {
        if (component) {
            component->introduce();
        }
        cout << "I wear Sneakers.\n";
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Person *p = new Person("Tom");
    Dress *dr = new Dress();
    Tshirt *ts = new Tshirt();
    Suit *su = new Suit();
    Tank *tk = new Tank();
    Sneaker *sk = new Sneaker();
    std::cout << "Way #1 of decoration: \n";
    dr->decorate(p);
    dr->introduce();
    
    std::cout << "Way #2 of decoration: \n";
    ts->decorate(p);
    tk->decorate(ts);
    sk->decorate(tk);
    sk->introduce();
    
    std::cout << "Way #3 of decoration: \n";
    su->decorate(p);
    ts->decorate(su);
    ts->introduce();
    
    return 0;
}
