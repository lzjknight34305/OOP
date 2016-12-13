//
//  main.cpp
//  adaptor_practice
//
//  Created by zijian.liu on 12/12/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#include <iostream>
using namespace std;

class Player {
public:
    Player(string name_) {
        this->name = name_;
    }
    virtual void Attack() {
        cout << getType() << name << " attack!\n";
    }
    virtual void Defense() {
        cout << getType() << name << " defense!\n";
    }
    virtual string getType() {
        return "";
    }
    
private:
    string name;
};

class Forwards : public Player {
public:
    Forwards(string name) : Player(name) {};
    
    string getType() {
        return "Forwards: ";
    }
};

class Center : public Player {
public:
    Center(string name) : Player(name) {};
    string getType() {
        return "Center: ";
    }
};

class Guard : public Player {
public:
    string getType() {
        return "Guard: ";
    }
};

class InternationalPlayer {
public:
    InternationalPlayer(string name_) {
        this->name = name_;
    }
    void Jingong() {
        cout << name << " JinGong!\n";
    }
    void FangShou() {
        cout << name << " FangShou!\n";
    }
private:
    string name;
};

class Translator : public Player {
public:
    Translator(string name_) : Player(name_) {
        ip = new InternationalPlayer(name_);
    }
    void Attack () {
        ip->Jingong();
    }
    void Defense () {
        ip->FangShou();
    }
private:
    InternationalPlayer *ip;
};

int main(int argc, const char * argv[]) {
    Center *James = new Center("James");
    Translator *Ming = new Translator("Ming Yao");
    James->Attack();
    James->Defense();
    Ming->Attack();
    Ming->Defense();
    
    return 0;
}
