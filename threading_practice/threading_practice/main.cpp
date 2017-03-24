//
//  main.cpp
//  threading_practice
//
//  Created by zijian.liu on 3/23/17.
//  Copyright © 2017 zijian.liu. All rights reserved.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>

using namespace std;
mutex m;

class BlockQueue {
public:
    BlockQueue () {
        capacity = -1;
    }
    
    int init(int capacity) {
        if (-1 != this->capacity) {
            cout << "ERROR: BlockQueue can only be initalized once.\n";
            return 1;
        }
        this->capacity = capacity;
        return 0;
    }
    
    int get() {
        if (q.empty()) {
            cout << "ERROR: Nothing in queue you can get.\n";
            return INT_MIN;
        }
        int res = q.front();
        q.pop();
        return res;
    }
    
    int set(int val) {
        m.lock();
        if (q.size() == capacity) {
            cout << "ERROR: q is full.\n";
            m.unlock();
            return 1;
        }
        q.push(val);
        m.unlock();
        return 0;
    }
    
    ~BlockQueue() {
    }
    
private:
    int capacity;
    queue<int> q;
};

int main(int argc, const char * argv[]) {
    BlockQueue *bq = new BlockQueue();
    bq->init(20);
    vector<thread*> thr;
    
    for (int i(0); i < 20; i++) {
        thr.push_back(new thread(&BlockQueue :: set, bq, i));
    }

    for (int i(0); i < 20; i++) {
        thr[i]->join();
    }
    
    cout << "Display the results:\n";
    for (int i (0); i < 20; i++) {
        cout << bq->get() << "\t";
    }
    cout << "\n";
    return 0;
}
