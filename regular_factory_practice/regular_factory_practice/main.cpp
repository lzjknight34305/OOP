//
//  main.cpp
//  regular_factory_practice
//
//  Created by zijian.liu on 12/3/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#include <iostream>
using namespace std;

/* Element classes family */
class Element {
public:
    Element(string name) {
        this->name = name;
    }
    virtual void SweepFloor() = 0;
    virtual void Cook() = 0;
    virtual void Talk() = 0;
protected:
    string name;
};

class Volunteer : public Element {
public:
    Volunteer (string name_) : Element(name_) {};
    
    void SweepFloor() {
        cout << "Volunteer " << name << " sweep floor. \n";
    }
    
    void Cook() {
        cout << "Volunteer " << name << " cook. \n";
    }
    
    void Talk() {
        cout << "Volunteer " <<  name << " talk with seniors. \n";
    }
};

class Student : public Element {
public:
    Student(string name_) : Element(name_) {};
    
    void SweepFloor() {
        cout << "Student " << name << " sweep floor. \n";
    }
    
    void Cook() {
        cout << "Student " << name << " cook. \n";
    }
    
    void Talk() {
        cout << "Student " <<  name << " talk with seniors. \n";
    }
    
};

/*Factory classes family */
class baseFactory {
public:
    virtual Element* CreateElement(string name) = 0;
};

class VolunteerFactory : public baseFactory {
public:
    Element* CreateElement(string name) {
        return new Volunteer(name);
    }
};

class StudentFactory : public baseFactory {
public:
    Element* CreateElement(string name) {
        return new Student(name);
    }
};

int main(int argc, const char * argv[]) {
    baseFactory *stf = new StudentFactory();
    baseFactory *vtf = new VolunteerFactory();
    Element *std1 = stf->CreateElement("Student #1");
    Element *std2 = stf->CreateElement("Student #2");
    Element *vt1 = vtf->CreateElement("Volunteer #1");
    Element *vt2 = vtf->CreateElement("Volunteer #2");
    
    std1->SweepFloor();
    std2->Talk();
    vt1->Cook();
    vt2->SweepFloor();
    
    return 0;
}
