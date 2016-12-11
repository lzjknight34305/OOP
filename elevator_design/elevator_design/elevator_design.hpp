//
//  elevator_design.hpp
//  elevator_design
//
//  Created by zijian.liu on 12/10/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#ifndef elevator_design_hpp
#define elevator_design_hpp

#include <stdio.h>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>

using namespace std;


enum Direction {Up, Down, Stop};

class User;

class Status {
public:
    int floor;
    Direction dir;
    Status(int floor, Direction dir) {
        this->floor = floor;
        this->dir = dir;
    }
};

class Elevator {
public:
    Elevator(int ind) {
        this->ind = ind;
        sta = new Status(0, Stop);
    }
    void MoveToFloor(int floor);
    void SetStop() {
        sta->dir = Stop;
    }
    Status *getStatus(){
        return sta;
    }
private:
    Status *sta;
    int ind;
};

class ControlSys {
private:
    ControlSys(int nfloors) {
        this->nfloors = nfloors;
        subject_list.resize(nfloors);
    }
    static ControlSys *instance;
    Elevator *elev;
    set<int> up_set;
    set<int> down_set;
    vector<unordered_set<User*>> subject_list;
    int nfloors;
    void NotifyUsers(int floor);
public:
    static ControlSys *getInstance(int nfloors) {
        if (!instance) {
            instance = new ControlSys(nfloors);
        }
        return instance;
    }
    
    //Advaned, what if multiple users are waiting at the same time?
    //Build a set and sort in order, every time move the elevator to closest place
    void SetPickUpRequest(User *usr, Direction dir);
    void SetDeliverRequest(User *usr, int dest);
    void PickNextRequest();
};

class User {
public:
    User(string name, ControlSys *cs, int floor) {
        this->name = name;
        this->cs = cs;
        this->floor = floor;
        in_elevator = false;
    }
    
    int GetFloor() {
        return floor;
    }
    
    //Wait for elevtor picking up
    void SendPickUpRequest(Direction dir);
    
    //Wait for elevator dilivering to destination
    void SendDelieverRequest(int dest);
    
    //Either step in or step out.
    void Action();
    
private:
    string name;
    ControlSys *cs;
    bool in_elevator;
    int floor;
};


#endif /* elevator_design_hpp */
