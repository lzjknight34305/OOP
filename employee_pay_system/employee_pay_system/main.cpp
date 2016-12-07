//
//  main.cpp
//  employee_pay_system
//
//  Created by zijian.liu on 12/6/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <utility>

using namespace std;

enum pay_period {month, year, hour};
enum type {regular, sale, contractor};

class BasePayOption {
public:
    BasePayOption(int rate) {
        this->rate = rate;
    }
    void display () {
        cout << "The payment method is: " << show_method() << "\n.";
    }
    virtual void set_rise(int rise_) {};
    virtual string show_method() {
        return "UNDEFINED";
    }
protected:
    pay_period pp;
    int rate;
};

class Employee {
public:
    Employee(string name_, type tp_, BasePayOption *pay_) {
        this->name = name_;
        this->pay = pay_;
        this->tp = tp_;
    }
    
    void getInfo() {
        cout << "Employee name: " << name << "\n";
        cout << "Payment method: " << "\n";
        pay->display();
    }
    
    type getType() {
        return tp;
    }
    
protected:
    string name;
    BasePayOption *pay;
    type tp;
};

class RegularPay : public BasePayOption {
public:
    RegularPay(int rate_) : BasePayOption(rate_) {
        pp = month;
    }
    string show_method () {
        string res = "regular month pay as" + to_string(rate);
        return res;
    }
};

class RegularRisePay : public BasePayOption {
public:
    RegularRisePay(int rate_) : BasePayOption(rate_) {
        pp = month;
        rise = 0;
    }
    
    void set_rise(int rise_) {
        rise = rise_;
    }
    
    string show_method () {
        string res = "regular month pay as " + to_string(rate);
        res += " and rise as" + to_string(rise);
        return res;
    }
private:
    int rise;
};

class HourlyPay : public BasePayOption {
public:
    HourlyPay(int rate_) : BasePayOption(rate_) {
        pp = hour;
    }
    string show_method () {
        string res = "hourly pay as " + to_string(rate);
        return res;
    }
};

class BassPayFactory {
public:
    virtual BasePayOption* Create_PayOption(int rate) = 0;
};

class RegularPayFactory : public BassPayFactory {
public:
    BasePayOption* Create_PayOption(int rate) {
        return new RegularPay(rate);
    }
};

class RegularRisePayFactory : public BassPayFactory {
public:
    BasePayOption* Create_PayOption(int rate) {
        return new RegularRisePay(rate);
    }
};

class HourlyPayFactory : public BassPayFactory {
public:
    BasePayOption* Create_PayOption(int rate) {
        return new HourlyPay(rate);
    }
};

class context {
public:
    context () {
        rpf = new RegularPayFactory();
        rrf = new RegularRisePayFactory();
        hpf = new HourlyPayFactory();
    }
    
    void insert(string name_, type tp_, int rate_, int rise_) {
        BasePayOption *pay;
        switch (tp_) {
            case regular:
                pay = rpf->Create_PayOption(rate_);
                table.insert(make_pair(name_, new Employee(name_, tp_, pay)));
                break;
            case sale:
                pay = rrf->Create_PayOption(rate_);
                pay->set_rise(rise_);
                break;
            case contractor:
                pay = hpf->Create_PayOption(rate_);
            default:
                break;
        }
        table.insert(make_pair(name_, new Employee(name_, tp_, pay)));
    }
    
    void show_list () {
        for (auto itr : table) {
            (itr.second)->getInfo();
            cout << "****************************\n";
        }
    }
    
private:
    RegularPayFactory *rpf;
    RegularRisePayFactory *rrf;
    HourlyPayFactory *hpf;
    unordered_map<string, Employee*> table;
};

int main(int argc, const char * argv[]) {
    context *ct = new context;
    ct->insert("Tom", regular, 1500, 0);
    ct->insert("Jin", contractor, 50, 0);
    ct->insert("Susan", sale, 750, 200);
    
    ct->show_list();
    return 0;
}
