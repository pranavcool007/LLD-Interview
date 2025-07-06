#include <bits/stdc++.h>
using namespace std;

class Product{
private:
    int id;
    string name;
    int price;
    int quantity;

public:
    Product() = default;
    Product(int id, string name, int price, int qty) : name(name), id(id), price(price), quantity(qty) {};

    string getName() {
        return name;
    }
    int getPrice() {
        return price;
    }
    int getQty() {
        return quantity;
    }
    int getId() const {
        return id;
    }

    void decreaseQty(int n = 1) {
        quantity -= n;
    }
    void modifyQty(int qty) {
        quantity += qty;
    }
};

class InventoryManager {
private:
    unordered_map<int, Product> products;

public:

    Product& getProduct(int productId){
        return products[productId];
    }
    
    void addProduct(const Product &product) {
        int productId = product.getId();
        products[productId] = product;
    }

    void displayProducts() {
        // productId productName  price  qty
        cout<<"ProductId"<<"\tProductName"<<"\tPrice"<<"\tQty"<<endl;
        for(auto it : products){
            auto &product = it.second;
            cout<<product.getId()<<"\t\t\t"<<product.getName()<<"\t\t"<<product.getPrice()<<"\t\t"<<product.getQty()<<endl;
        }
    }

    bool isAvailable(int productId){
        // productid should be valid and its qty >= 0
        return (products.count(productId) && products[productId].getQty() > 0);
    }

    void dispenseProduct(int productId) {
        if(!isAvailable(productId)){
            throw runtime_error ("InValid Product Id entered");
        }
        products[productId].decreaseQty();
        return;
    }

    void restockProduct(int productId, int qty) {
        products.at(productId).modifyQty(qty);
    }

};

class PaymentProcessor {
private:
    vector<int> acceptedDenominations = {1,2,5,10,50,100};
    int currentAmount;
    int collectedAmount;

public:
    PaymentProcessor(){
        currentAmount = 0;
        collectedAmount = 0;
    }
    
    bool isAccepted(int amount) {
        return find(acceptedDenominations.begin(), acceptedDenominations.end(), amount) != acceptedDenominations.end();
    }

    void insertMoney(int amount) {
        if(!isAccepted(amount)){
            throw runtime_error("Denomination not supported");
        }
        currentAmount += amount;
    }

    int pay(int price) {        // return change or throws exception
        if(currentAmount < price){
            throw runtime_error("Insufficient Funds");
        }
        int change = currentAmount - price;
        collectedAmount += price;
        currentAmount = 0;
        return change;
    }          

    void resetCurrentAmount() {
        currentAmount = 0;
    }
    int collectAmount() {
        int amount = collectedAmount;
        collectedAmount = 0;
        return amount;
    }

};

class VendingMachine {
private:
    InventoryManager inventory;
    PaymentProcessor payment;

public:
    void loadProduct(const Product &product) {
        inventory.addProduct(product);
    }

    void displayInventory() {
        inventory.displayProducts();
    }

    void insertMoney(int money) {
        payment.insertMoney(money);
    }

    void selectProduct(int productId) {
        if(!inventory.isAvailable(productId)){
            throw runtime_error("Product out of stock");
        }
        Product &product = inventory.getProduct(productId);
        cout<<"You have selected : "<<product.getName()<<" Price : "<<product.getPrice()<<endl;
        int change = payment.pay(product.getPrice());
        inventory.dispenseProduct(productId);
        cout<<"Product Dispensed : "<<product.getName()<<endl;

        if(change){
            cout<<"Returned Change "<<change<<endl;
        }
    }

    //Admin
    int collectMoney() {};
    int restockItem() {};
};

int main()
{
    VendingMachine vm;
    vm.loadProduct(Product(1,"Biscuit",10,5));
    vm.loadProduct(Product(2,"Juice", 20, 3));
    vm.loadProduct(Product(3,"Lays", 20, 10));


    vm.displayInventory();
    // user 1 chose Biscuit
    vm.insertMoney(5);
    vm.insertMoney(10);
    vm.selectProduct(1);

    vm.displayInventory();

    // user 2 choose Lays buy pays less
    vm.insertMoney(10);
    vm.insertMoney(5);
    vm.selectProduct(3);

    return 0;
}