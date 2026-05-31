#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    string name;
    double price;

public:
    Product(string n = "", double p = 0.0) {
        if (p < 0)
            throw 404;

        name = n;
        price = p;
    }

    virtual void display() {
        cout << "Name: " << name << endl;
        cout << "Price: " << price << endl;
    }

    friend void displayPrice(Product p);
};

void displayPrice(Product p) {
    cout << "Price = " << p.price << endl;
}

class Electronics : public Product {
private:
    int quantity;
    int size;
    int* ratings;

public:
    Electronics(string n = "", double p = 0.0,
        int q = 0, int s = 0)
        : Product(n, p)
    {
        if (q < 0)
            throw 404;

        quantity = q;
        size = s;

        ratings = new int[size];
    }

    void inputRatings() {
        for (int i = 0; i < size; i++) {
            cin >> ratings[i];
        }
    }

    void displayRatings() {
        for (int i = 0; i < size; i++) {
            cout << ratings[i] << " ";
        }
        cout << endl;
    }

    void display() override {
        Product::display();

        cout << "Quantity: " << quantity << endl;

        cout << "Ratings: ";
        displayRatings();
    }

    Electronics operator+(Electronics e) {

        Electronics temp;

        temp.price = price + e.price;

        return temp;
    }

    ~Electronics() {
        delete[] ratings;
    }
};

class Book : public Product {
private:
    string author;
    int pages;

public:
    Book(string n = "", double p = 0.0,
        string a = "", int pg = 0)
        : Product(n, p)
    {
        author = a;
        pages = pg;
    }

    void display() override {
        Product::display();

        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
    }
};

int main() {

    try {

        Electronics e[2]{
            Electronics("Laptop",15000,5,3),
            Electronics("Phone",10000,4,3)
        };

        for (int i = 0; i < 2; i++) {
            cout << "Enter ratings for product "
                << i + 1 << endl;

            e[i].inputRatings();
        }

        for (int i = 0; i < 2; i++) {
            e[i].display();
            cout << endl;
        }

        Electronics e3 = e[0] + e[1];

        cout << "After Adding Prices:";
        displayPrice(e3);

        Product* ptr;

        ptr = &e[0];

        cout << "Polymorphism:";
        ptr->display();
    }

    catch (int) {
        cout << "Error: Invalid data!" << endl;
    }

    return 0;
}