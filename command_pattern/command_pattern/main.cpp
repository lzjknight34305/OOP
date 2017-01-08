//
//  main.cpp
//  command_pattern
//
//  Created by zijian.liu on 1/2/17.
//  Copyright © 2017 zijian.liu. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Guest;
class Servant;

class Kitchen {
public:
    Kitchen () {
        serv = NULL;
    }
    
    void SetServ(Servant *serv) {
        this->serv = serv;
    }
    
    void CookSteak() {
        cout << "Kitchen cook steak.\n";
    }
    
    void CookPasta() {
        cout << "Kitchen cook pasta.\n";
    }
    
    void CookChowder() {
        cout << "Kitchen cook chowder.\n";
    }
private:
    Servant *serv;
};

class Command {
public:
    Command(Kitchen *k, string name) {
        this->k = k;
        this->name = name;
    }
    
    string getName() {
        return name;
    }
    
    virtual void process();
    
protected:
    Kitchen *k;
private:
    string name;
};

class Steak : public Command {
public:
    Steak(Kitchen *k, string name) : Command(k, name) {};
    void process() {
        k->CookSteak();
    }
};

class Pasta : public Command {
public:
    Pasta(Kitchen *k, string name) : Command(k, name) {};
    void process() {
        k->CookPasta();
    }
};

class Chowder : public Command {
public:
    Chowder(Kitchen *k, string name) : Command(k, name) {};
    void process() {
        k->CookChowder();
    }
};

class Log {
public:
    void InsertRecord(string id, Command *cmd) {
        string dishName = cmd->getName();
        if (guest_table.find(id) == guest_table.end()) {
             guest_table.insert(make_pair(id, vector<Command*> ()));
        }
        guest_table[id].push_back(cmd);
        
        if (dish_table.find(dishName) == dish_table.end()) {
            dish_table.insert(make_pair(dishName, queue<string> ()));
        }
        dish_table[dishName].push(id);
    }
    
    vector<Command*> GetDishList(string id) {
        vector<Command*> res;
        if (guest_table.find(id) == guest_table.end()) {
            return res;
        }
        return guest_table[id];
    }
    
    string getFirstWaitingGuest(string dish) {
        if (dish_table.find(dish) == dish_table.end()) {
            return "";
        }
        string res = dish_table[dish].front();
        dish_table[dish].pop();
        return res;
    }
    
private:
    unordered_map<string, vector<Command*>> guest_table;
    unordered_map<string, queue<string>> dish_table;
};

class Menu {
public:
    Command *getDish(string dish) {
        if (table.find(dish) == table.end()) {
            return NULL;
        }
        return table[dish];
    }
    
    void AddNewDish(string dish, Command *cmd) {
        table.insert(make_pair(dish, cmd));
    }
    
private:
    unordered_map<string, Command*> table;
};

class Servant {
public:
    Servant(Menu *m, Log *l) {
        this->m = m;
        this->l = l;
    }
    
    bool GetDish(Guest *g, string dish) {
        Command *cmd = m->getDish(dish);
        if (!cmd) {
            return false;
        }
        l->InsertRecord(g->GetId(), cmd);
        return true;
    }
    
    void NotifyKitchen(Guest *g) {
        vector<Command*> vcmd = l->GetDishList(g->GetId());
        for (auto cmd : vcmd) {
            cmd->process();
        }
    }
    
    void NotifyGuest(string dish) {
        string name = l->getFirstWaitingGuest(dish);
        cout << "Dear " << name << ":\n";
        cout << "Your" << dish << "is ready!\n";
    }
    
private:
    Menu *m;
    Log *l;
};

class Guest {
public:
    Guest(string id) {
        this->id = id;
        serv = NULL;
    }
    
    void SetServant(Servant *serv) {
        this->serv = serv;
    }
    
    void TakeOrder(string dish) {
        if (!Check()) {
            return;
        }
        if (!serv->GetDish(this, dish)) {
            cout << "They don't have this dish!\n";
        }
    }
    
    void DoneOrder() {
        if (!Check()) {
            return;
        }
        serv->NotifyKitchen(this);
    }
    
    string GetId() {
        return id;
    }
    
private:
    string id;
    Servant *serv;
    
    bool Check() {
        if (!serv) {
            cout << "Guest haven't get servant, set the servant first!\n";
            return false;
        }
        return true;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
