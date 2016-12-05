//
//  main.cpp
//  builder_practice
//
//  Created by zijian.liu on 12/4/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Dish {
public:
    Dish(string name_) {
        this->name = name_;
    }
    
    void add(string part) {
        parts.push_back(part);
    }
    
    void display() {
        cout << "The dish " << name << " is composed by the following parts as: \n";
        for (int i(0); i < parts.size(); i++) {
            cout << parts[i] << " \n";
        }
    }
private:
    string name;
    vector<string> parts;
};

class BaseCook {
public:
    virtual void setDish() = 0;
    virtual void AddNoodle() = 0;
    virtual void AddSoup() = 0;
    virtual void AddMeat() = 0;
    Dish *return_dish () {
        return ds;
    }
protected:
    Dish *ds;
};

class CookUdon : public BaseCook {
public:
    void setDish() {
        ds = new Dish("Udon noodle");
    }
    
    void AddNoodle() {
        ds->add("Udon");
    }
    
    void AddSoup() {
        ds->add("Miso soup");
    }
    
    void AddMeat() {
        ds->add("Park Chasiu");
    }
};

class CookBeefNoodle : public BaseCook {
public:
    void setDish() {
        ds = new Dish("Beef noodle");
    }
    
    void AddNoodle() {
        ds->add("Chinese noodle");
    }
    
    void AddSoup() {
        ds->add("Beef soup");
    }
    
    void AddMeat() {
        ds->add("Stewed beef");
    }
};

class CookDirector {
public:
    CookDirector (BaseCook *bc_) {
        this->bc = bc_;
    }
    
    Dish* Cook () {
        bc->setDish();
        bc->AddNoodle();
        bc->AddSoup();
        bc->AddMeat();
        return bc->return_dish();
    }
    
private:
    BaseCook *bc;
};

int main(int argc, const char * argv[]) {
    BaseCook *bc_udon = new CookUdon();
    BaseCook *bc_beef = new CookBeefNoodle();
    CookDirector *cd = new CookDirector(bc_udon);
    Dish *udon = cd->Cook();
    udon->display();
    
    delete cd;
    cd = new CookDirector(bc_beef);
    Dish *beef = cd->Cook();
    beef->display();
    
    return 0;
}
