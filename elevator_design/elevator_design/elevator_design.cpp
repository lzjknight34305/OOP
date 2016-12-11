//
//  elevator_design.cpp
//  elevator_design
//
//  Created by zijian.liu on 12/10/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#include "elevator_design.hpp"
ControlSys* ControlSys :: p_instance = NULL;

//Advanced, what if multiple users are waiting at the same time?
//Build a set and sort in order, every time move the elevator to closest place
void ControlSys:: SetPickUpRequest(User *usr, Direction dir) {
    int usr_floor = usr->GetFloor();
    subject_list[usr_floor].insert(usr);
    if (Up == dir) {
        up_set.insert(usr_floor);
        
    } else {
        down_set.insert(usr_floor);
    }
}

void ControlSys:: SetDeliverRequest(User *usr, int dest) {
    int usr_floor = usr->GetFloor();
    Direction dir = usr_floor > dest ? Down : Up;
    subject_list[dest].insert(usr);
    if (Up == dir) {
        up_set.insert(dest);

    } else {
        down_set.insert(dest);
    }
};

void ControlSys:: PickNextRequest() {
    Status *sta = elev->getStatus();
    set<int> :: iterator itr_up = up_set.upper_bound(sta->floor);
    set<int> :: iterator itr_down = down_set.lower_bound(sta->floor);
    if (Up == sta->dir && itr_up != up_set.end()) {
        elev->MoveToFloor(*itr_up);
        NotifyUsers(*itr_up);
    } else if (itr_down != down_set.end()) {
        elev->MoveToFloor(*itr_down);
        NotifyUsers(*itr_down);
    } else {
        elev->SetStop();
    }
}

void ControlSys:: NotifyUsers(int floor) {
    if (subject_list[floor].empty()) {
        return;
    }
    for (auto itr : subject_list[floor]) {
        itr->Action();
    }
    subject_list[floor].clear();
}

void User:: SendPickUpRequest(Direction dir) {
    cs->SetPickUpRequest(this, dir);
    cout << name << " is waiting for elevator picking up ... \n";
}

void User :: SendDelieverRequest(int dest) {
    if (!in_elevator) {
        cout << "ERROR: User must stay in elevator first.\n";
    }
    cs->SetDeliverRequest(this, dest);
    cout << name << " is waiting for elevator arriving ... \n";
}

void User:: Action() {
    if (!in_elevator) {
        cout << name << " step into the elevator. \n";
        in_elevator = true;
    } else {
        cout << name << " step out the elevator. \n";
        in_elevator = false;
    }
}

void Elevator:: MoveToFloor(int dest) {
    int inc;
    if (dest == sta->floor) {
        return;
    }
    if (dest > sta->floor) {
        sta->dir = Up;
        inc = 1;
    } else {
        sta->dir = Down;
        inc = -1;
    }
    for (int i(sta->floor); i < dest; i += inc) {
        sta->floor = i;
    }
    sta->dir = Stop;
}
