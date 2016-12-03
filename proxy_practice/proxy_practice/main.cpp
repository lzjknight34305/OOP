//
//  main.cpp
//  proxy_practice
//
//  Created by zijian.liu on 12/2/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#include <iostream>
using namespace std;

//Interface class
class Activity {
public:
    Activity() {};
    virtual void takeShow() = 0;
    virtual void loveWife() = 0;
};

class Star : public Activity {
public:
    Star(string name) : Activity() {
        this->name = name;
    }
    void takeShow () {
        cout << name << " takes the show.\n";
    }
    void loveWife () {
        cout << name << " loves wife.\n";
    }
private:
    string name;
};

class Proxy : public Activity {
public:
    Proxy(string name, bool good, Star *client) : Activity() {
        this->name = name;
        this->good = good;
        this->client = client;
    }
    void takeShow () {
        if (client) {
            client->takeShow();
        }
    }
    void loveWife () {
        if (good) {
            if (client) {
                client->loveWife();
            }
        } else {
            cout << name << " loves wife.\n";
        }
    }
private:
    string name;
    bool good;
    Star *client;
};

int main(int argc, const char * argv[]) {
    Star *bq = new Star("WangBaoQiang");
    Proxy *nm = new Proxy("Normal", true, bq);
    Proxy *js = new Proxy("JJSong", false, bq);
    cout << "Normal proxy does: \n";
    nm->takeShow();
    nm->loveWife();
    cout << "But what JJSong does: \n";
    js->takeShow();
    js->loveWife();
    return 0;
}
