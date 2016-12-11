//
//  main.cpp
//  elevator_design
//
//  Created by zijian.liu on 12/10/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//
#include "elevator_design.hpp"


int main(int argc, const char * argv[]) {
    ControlSys *cs = ControlSys :: getInstance(10);
    User *Tom = new User("Tom", cs, 3);
    User *Tony = new User("Tony", cs, 2);
    
    
    /*void SendPickUpRequest(Direction dir);
     
     //Wait for elevator dilivering to destination
     void SendDelieverRequest(int dest);*/
    
    Tom->SendPickUpRequest(Up);
    
    return 0;
}
