//
//  main.cpp
//  template_practice
//
//  Created by zijian.liu on 12/4/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#include <iostream>
using namespace std;

class basePaper {
public:
    basePaper(string name_) {
        name = name_;
    }
    
    void Question1() {
        cout << "This is question #1.\n";
        cout << name << " answer is " << answer1() << "\n";
    }
    
    void Question2() {
        cout << "This is question #2.\n";
        cout << name << " answer is " << answer2() << "\n";
    }
    
private:
    string name;
    
protected:
    virtual string answer1() {
        return "";
    }
    
    virtual string answer2() {
        return "";
    }
};

class Paper1 : public basePaper {
public:
    Paper1(string name_) : basePaper(name_) { };
protected:
    string answer1() {
        return "A";
    }
    
    string answer2() {
        return "B";
    }
};

class Paper2 : public basePaper {
public:
    Paper2(string name_) : basePaper(name_) { };
protected:
    string answer1() {
        return "C";
    }
    
    string answer2() {
        return "D";
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    basePaper *std1 = new Paper1("Student #1");
    basePaper *std2 = new Paper2("Student #2");
    std1->Question1();
    std1->Question2();
    std2->Question1();
    std2->Question2();
    
    return 0;
}
