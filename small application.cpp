#include <iostream>
#include <vector>

using namespace std;  

class InventoryItem {
protected:
    string name;
    double price;
    int quantity;

public:
    InventoryItem(string name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    //virtual ~InventoryItem() {}

    virtual void display() const {
        cout << name << ": $" << price << " each, Quantity: " << quantity << endl;
    }
    
    string getName() const {
        return name;
    }
};
class ProductItem : public InventoryItem {
private:
    string sku;  // SKU (Stock Keeping Unit) specific to ProductItem

public:
    ProductItem(string name, double price, int quantity, string sku)
        : InventoryItem(name, price, quantity), sku(sku) {}

    void display() const override {
        cout << name << " (code: " << sku << "): $" << price << " each, Quantity: " << quantity << endl;
    }
};

class InventoryManager {
private:
    vector<InventoryItem*> items;
public:
    void addItem(InventoryItem* item) {
        items.push_back(item);
    }

    void removeItem(const string& itemName) {
        for (vector<InventoryItem*>::iterator it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getName() == itemName) {
                delete *it;
                items.erase(it);
                cout << "Item '" << itemName << "' removed from inventory.\n";
                return;
            }
        }
        cout << "Item '" << itemName << "' not found in inventory.\n";
    }

    void displayInventory() const {
        if (items.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }
        cout << "\nCurrent Inventory:\n";
        for (vector<InventoryItem*>::const_iterator it = items.begin(); it != items.end(); ++it) {
            (*it)->display();
        }
    }

};

int main() {
    InventoryManager inventoryManager;
    string name,productcode;
    float price;
    int stockquantity,ch;
    cout<<"\n\n\tInventory Management\n1.Add Item\n2.Delete Item\n3.Display Items\n0.Exit\n";
    do{
        cout<<"\nEnter your choice : ";
        cin>>ch;
        switch(ch){
            case 1: cout<<"Enter Product Details (Name,Price,StockQuantity,ProductCode) : ";
                    cin>>name>>price>>stockquantity>>productcode;
                    inventoryManager.addItem(new ProductItem(name,price,stockquantity,productcode));
                    break;
            case 2: cout<<"Enter the name os product to remove : ";
                    cin>>name;
                    inventoryManager.removeItem(name);
                    break;
            case 3: inventoryManager.displayInventory();
                    break;
            case 0: cout<<"Exiting...";return 0;
            deafult : cout<<"Invalid choice!!";break;
                    
        }
    }while(ch!=0);
    return 0;
}
