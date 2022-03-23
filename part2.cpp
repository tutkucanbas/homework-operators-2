#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class Item{
    // name
    // unit net price
    // VAT tax type ("A" – 23%, "B" – 8%, "C" – 0%)
    // the amount sold
private:
    string name;
    double unit_per_price;
    char VATtype;
    int amount_sold;
public:
    Item(string n, double upp, char type, int amount){
        name = n;
        unit_per_price = upp;
        VATtype = type;
        amount_sold = amount;
    }

    string getName(){
        return name;
    }

    double getUnitperprice(){
        return unit_per_price;
    }

    char getType(){
        return VATtype;
    }

    int getAmountsold(){
        return amount_sold;
    }
};

class Invoice{
private:
    string seller, buyer;
    vector<Item> items;
public:
    Invoice(string s, string b){
        seller = s;
        buyer = b;
    }

    void add_item(Item element){
        items.push_back(element);
    }

    string getSeller(){
        return seller;
    }

    string getBuyer(){
        return buyer;
    }

    vector<Item> getItems(){
        return items;
    }

    /*
------------------VAT invoice------------------
===============================================
Seller: 7770003699      Buyer: 0123456789

                  c.j. VAT   il.    net   total
1. M3 screw     | 0.37  A | 100 | 37.00 | 45.51
2. 2 mm drill   | 2.54  B |   2 |  5.08 |  5.49

------------------------------------ TOTAL ----
                                  42.08 | 51.00
    */

};

ostream& operator<<(ostream& out, Invoice ivc){
    out << "------------------VAT invoice------------------" << endl;
    cout << "===============================================" << endl;
    cout << "Seller: " << ivc.getSeller() << "      " << "Buyer: " << ivc.getBuyer() << endl;
    cout << endl;
    cout << "                  c.j. VAT   il.    net   total" << endl;

    double netsum = 0;
    double total = 0;
    for(int i = 0;i<(ivc.getItems()).size();i++){
        double tax;
        if(ivc.getItems()[i].getType() == 'A'){
            tax = ivc.getItems()[i].getUnitperprice() * ivc.getItems()[i].getAmountsold() * 0.23;
        }else if(ivc.getItems()[i].getType() == 'B'){
            tax = ivc.getItems()[i].getUnitperprice() * ivc.getItems()[i].getAmountsold() * 0.08;
        }else if(ivc.getItems()[i].getType() == 'C'){
            tax = 0;
        }else tax = 0;

        printf("2. %-13s|%5.2f  %c | %3d | %5.2f | %5.2f\n",
               ivc.getItems()[i].getName().c_str(),
               ivc.getItems()[i].getUnitperprice(),
               ivc.getItems()[i].getType(),
               ivc.getItems()[i].getAmountsold(),
               ivc.getItems()[i].getUnitperprice() * ivc.getItems()[i].getAmountsold(),
               ivc.getItems()[i].getUnitperprice() * ivc.getItems()[i].getAmountsold() + tax);

        netsum += ivc.getItems()[i].getUnitperprice() * ivc.getItems()[i].getAmountsold();
        total += ivc.getItems()[i].getUnitperprice() * ivc.getItems()[i].getAmountsold() * tax;
    }
    out << endl;
    out << "------------------------------------ TOTAL ----" << endl;
    printf("                                  %4.2f | %4.2f", netsum, total);

    return out;
}

int main(){
    Invoice inv("7770003699", "0123456789");
    inv.add_item(Item("M3 screw", 0.37, 'A', 100));
    inv.add_item(Item("2 mm drill", 2.54, 'B', 2));
    cout << inv << std::endl;
}
