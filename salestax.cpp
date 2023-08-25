#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <unordered_set>

class ExemptItems {
public:
    void insertItem(const std::string& category, const std::string& itemName) {
        itemCategories[itemName] = category;
    }

    bool isExempt(const std::string& itemName) const {
        auto it = itemCategories.find(itemName);
        return it != itemCategories.end();
    }

private:
    std::unordered_map<std::string, std::string> itemCategories; // Maps item name to its category
};

class Item {
public:
    Item(const std::string& name, double price, bool isImported)
        : name(name), price(price), isImported(isImported) {}

    double calculateTax(const ExemptItems& exemptItems) const {
        double tax = 0.0;
        if (isImported) {
            tax += price * 0.05;
        }
        if (!exemptItems.isExempt(name)) {
            tax += price * 0.1;
        }
        return roundTax(tax);
    }

    double getTotalPrice(const ExemptItems& exemptItems) const {
        return price + calculateTax(exemptItems);
    }

    void printReceipt(const ExemptItems& exemptItems) const {
        std::cout << "1 " << name << ": " << std::fixed << std::setprecision(2) << getTotalPrice(exemptItems) << std::endl;
    }

private:
    const std::string name;
    const double price;
    const bool isImported;

    double roundTax(double tax) const {
        return std::ceil(tax * 20) / 20;
    }
};

class ShoppingCart {
public:
    void addItem(const Item& item) {
        items.push_back(item);
    }

    void generateReceipt(const ExemptItems& exemptItems) const {
        double totalTax = 0.0;
        double totalPrice = 0.0;

        for (const Item& item : items) {
            item.printReceipt(exemptItems);
            totalTax += item.calculateTax(exemptItems);
            totalPrice += item.getTotalPrice(exemptItems);
        }

        std::cout << "Sales Taxes: " << std::fixed << std::setprecision(2) << totalTax << std::endl;
        std::cout << "Total: " << totalPrice << std::endl;
    }

private:
    std::vector<Item> items;
};

int main() {
    ExemptItems exemptItems;
    exemptItems.insertItem("food", "chocolate");
    exemptItems.insertItem("food", "food");
    exemptItems.insertItem("book", "book");
    exemptItems.insertItem("medical", "pill");

    ShoppingCart cart1;
    cart1.addItem(Item("book", 12.49, false));
    cart1.addItem(Item("music CD", 14.99, false));
    cart1.addItem(Item("chocolate bar", 0.85, false));

    std::cout << "Output 1:" << std::endl;
    cart1.generateReceipt(exemptItems);

    // Repeat the above for Input 2 and Input 3 using appropriate items and prices

    return 0;
}
