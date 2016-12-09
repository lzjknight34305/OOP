//
//  main.cpp
//  meeting_schedualer
//
//  Created by zijian.liu on 12/8/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

/*
 Please design a meeting reservation system
 At the heart of it is a service that takes it a set of users and a desired meeting duration, it returns a timeslot when
 that all the users are free to meet
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Users {
public:
    Users(string name) {
        this->name = name;
        avaliable.resize(8, true);
    }
    
    bool add_event(string event_name, pair<int, int> time) {
        for (int i(time.first); i <= time.second; i++) {
            if (!avaliable[i]) {
                return false;
            }
        }
        for (int i(time.first); i <= time.second; i++) {
            avaliable[i] = false;
        }
        
        event_table.insert(make_pair(event_name, time));
        return true;
    }
    
    bool remove_event(string event_name) {
        if (event_table.find(event_name) == event_table.end()) {
            return false;
        }
        int start = event_table[event_name].first;
        int end = event_table[event_name].second;
        for (int i(start); i <= end; i++) {
            avaliable[i] = true;
        }
        event_table.erase(event_name);
        return true;
    }
    
    vector<bool> get_avaliable() {
        return avaliable;
    }
private:
    vector<bool> avaliable;
    string name;
    unordered_map <string, pair<int, int>> event_table;
};

class Scheduler {
public:
    pair<int, int> getTimeSlot(vector<Users*> group, int duration) {
        if (group.empty()) {
            return {-1, -1};
        }
        vector<bool> time_slot(8, true);
        for (int i(0); i < group.size(); i++) {
            vector<bool> ava = group[i]->get_avaliable();
            for (int j(0); j < ava.size(); j++) {
                time_slot[j] = time_slot[j] && ava[j];
            }
        }
        
        int start(0), end(0);
        while (start < time_slot.size()) {
            while (start < time_slot.size() && !time_slot[start]) {
                start++;
            }
            for (end = start; end <= start + duration && end < time_slot.size();
                 end++) {
                if (!time_slot[end]) {
                    break;
                }
            }
            if (end > start + duration) {
                return {start, end - 1};
            }
            start = end;
        }
        
        return {-1, -1};
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Scheduler *sch = new Scheduler();
    Users *usr1 = new Users("Tom");
    Users *usr2 = new Users("Bruce");
    
    usr1->add_event("group_meeting", {1, 2});
    usr1->add_event("Seminar", {7, 8});
    
    usr2->add_event("dr appointment", {2, 3});
    usr1->add_event("dental", {5, 8});
    
    pair<int, int> time = sch->getTimeSlot({usr1, usr2}, 2);
    
    cout << "Avaliable meeting time can be between " << time.first << "to " << time.second
       << "\n";
}
