#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

class SalesTax {
public:
    double calculateTax(double price, double taxRate) {
        return price * taxRate / 100.0; // Calculate tax amount
    }

    double roundUpToNearest0_05(double value) {
        return ceil(value * 20) / 20.0;
    }
};

class Item {
    vector<string> exemptItems = {"book", "medicine", "pills", "syrup", "food", "icecream", "chocolate"};

public:
    void addToExemptItemsList(string exemptItem) {
        exemptItems.push_back(exemptItem);
    }

    bool isItemExempt(const string& itemLine) {
        // Convert itemLine to lowercase for case-insensitive comparison
        string lowerItemLine = itemLine;
        transform(lowerItemLine.begin(), lowerItemLine.end(), lowerItemLine.begin(), ::tolower);

        for (const string& exemptItem : exemptItems) {
            // Convert exemptItem to lowercase for case-insensitive comparison
            string lowerExemptItem = exemptItem;
            transform(lowerExemptItem.begin(), lowerExemptItem.end(), lowerExemptItem.begin(), ::tolower);

            if (lowerItemLine.find(lowerExemptItem) != string::npos) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    SalesTax stax;
    Item item;
    vector<string> inputLines;
    string line;

    // Reading input lines until end-of-file
    while (getline(cin, line)) {
        if (line.empty()) break;
        inputLines.push_back(line);
    }

    double basketTotal = 0.0;
    double basketTax = 0.0; // Accumulator for total tax

    for (const string& input : inputLines) {
        istringstream iss(input);
        int quantity;
        double price;
        string itemName;

        // Parsing input
        iss >> quantity;
        string unit;
        string at;
        string token;
        while (iss >> token) {
            if (token == "at") {
                break;
            }
            itemName += token;
            itemName += " ";
        }
        iss >> price;

        // Checking if item is imported
        bool isImported = (itemName.find("imported") != string::npos);

        // Checking for exemptions
        bool isExempt = item.isItemExempt(itemName);

        // Calculating basic sales tax
        double basicTax = 0.0;
        if (!isExempt) {
            basicTax += stax.calculateTax(price, 10);
        }

        // Calculating import duty
        double importTax = 0.0;
        if (isImported) {
            importTax += stax.calculateTax(price, 5);
        }

        // Total tax for the item
        double totalTax = basicTax + importTax;

        // Rounding tax to nearest 0.05
        totalTax = stax.roundUpToNearest0_05(totalTax);

        // Total price for the item including tax
        double totalPrice = price + totalTax;

        // Accumulating total tax and total cost for the basket
        basketTax += totalTax;
        basketTotal += totalPrice;

        // Printing the output for each item
        cout << quantity << " " << itemName << ": " << fixed << setprecision(2) << totalPrice << endl;
    }

    // Printing total taxes and total cost of the basket
    cout << "Sales Taxes: " << fixed << setprecision(2) << basketTax << endl;
    cout << "Total: " << fixed << setprecision(2) << basketTotal << endl;

    return 0;
}
