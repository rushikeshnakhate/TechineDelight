
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::string simplify_orders(const std::string &orders) {
    std::stringstream ss(orders);
    std::vector<std::string> tokens;

    // Tokenize the orders string
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    for (auto x: tokens) {
        std::cout << x << std::endl;
    }
    // Simplify the orders
    std::string simplified_orders;
    std::string current_order;
    int current_count = 0;
    for (const auto &token : tokens) {
        if (token == current_order) {
            current_count++;
        } else {
            if (current_count > 0) {
                simplified_orders += current_order[0];
                if (current_count > 1) {
                    simplified_orders += std::to_string(current_count);
                }
                current_count = 0;
            }
            current_order = token;
        }
    }

    // Add the last order if there was a repetition
    if (current_count > 0) {
        simplified_orders += current_order[0];
        if (current_count > 1) {
            simplified_orders += std::to_string(current_count);
        }
    }

    // Convert the orders to the simplified format
    std::replace(simplified_orders.begin(), simplified_orders.end(), 'u', '^');
    std::replace(simplified_orders.begin(), simplified_orders.end(), 'd', 'v');
    std::replace(simplified_orders.begin(), simplified_orders.end(), 'l', '<');
    std::replace(simplified_orders.begin(), simplified_orders.end(), 'r', '>');

    return simplified_orders;
}

int main() {

    std::string orders = "up up right down left";
    std::cout << simplify_orders(orders) << std::endl; // Output: "^2>-<"

    return 0;
}