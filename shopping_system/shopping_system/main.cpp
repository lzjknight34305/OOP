//
//  main.cpp
//  shopping_system
//
//  Created by zijian.liu on 12/1/16.
//  Copyright © 2016 zijian.liu. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class Items {
public:
    string name;
    float unit_price;
    Items(string name, float unit_price) {
        this->name = name;
        this->unit_price = unit_price;
    }
};

class CashCompute {
public:
    CashCompute() {};
    ~CashCompute() {};
    virtual float get_result(vector<Items> &it) {
        float res(0.);
        for (int i(0); i < it.size(); i++) {
            res += it[i].unit_price;
        }
        return res;
    }
};

class CashDiscount {
public:
    CashDiscount() {};
    ~CashDiscount() {};
    virtual float get_result(float price) = 0;
};

class DiscountNormal : public CashDiscount {
public:
    DiscountNormal() {};
    
    void setDiscount(float minimum, float discount) {
        this->minimum = minimum;
        this->discount = discount;
    }
    
    float get_result(float price) {
        if (price > minimum) {
            return price * discount;
        } else {
            return price;
        }
    }
private:
    float minimum;
    float discount;
};

class DiscountRebate : public CashDiscount {
public:
    DiscountRebate() { };
    void setRebate(float condition, float rebate) {
        this->condition = condition;
        this->rebate = rebate;
    }
    float get_result(float price) {
        float deduct = (price / condition) * rebate;
        float res = price - deduct;
        return res > 0. ? res : 0.;
    }
private:
    float condition;
    float rebate;
};

class context {
public:
    context(string discount_method) {
        cc = new CashCompute();
        if ("No discount" == discount_method) {
            cd = new DiscountNormal();
            ((DiscountNormal*)cd)->setDiscount(0, 1.);
        } else if ("30% off" == discount_method) {
            cd = new DiscountNormal();
            ((DiscountNormal*)cd)->setDiscount(0, 0.7);
        } else if ("Buy 100 get 30 back" == discount_method) {
            cd = new DiscountRebate();
            ((DiscountRebate*)cd)->setRebate(100., 30.);
        }
    };
    
    ~context() {};
    float compute_final_prices(vector<Items> &it) {
        float original = compute_original_prices(it);
        return cd->get_result(original);
    }

private:
    CashCompute *cc;
    CashDiscount *cd;
    
    float compute_original_prices(vector<Items> &it) {
        return cc->get_result(it);
    }
};

int main(int argc, const char * argv[]) {
    /* build in test case down*/
    string discount = "30% off";
    vector<Items> it;
    it.push_back(Items("apple", 5.5));
    it.push_back(Items("banana", 2.5));
    it.push_back(Items("orange", 2.5));
    /* build in test case up*/
    context *ctx = new context(discount);
    float res = ctx->compute_final_prices(it);
    cout << "The final price is " << res << "\n";
    return 0;
}

