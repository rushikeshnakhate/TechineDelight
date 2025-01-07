#include <iostream>
#include <memory>
#include <list>

using namespace std;


struct Order {
    string id{"1"};
    int size{10};
    string side;

    Order(string id, int size, string side) {
        this->id = id;
        this->size = size;
        this->side = side;
    }
};

auto print = [](shared_ptr<Order> &pOrder, string &side) {
    std::cout << pOrder->id << " " << pOrder->size << " " << side;

};

#include <map>
#include <algorithm>


int main() {
    auto pOrder1 = make_shared<Order>("1", 100, "B");
    auto pOrder2 = make_shared<Order>("2", 200, "B");
    auto pOrder3 = make_shared<Order>("3", 300, "S");
    auto pOrder4 = make_shared<Order>("4", 400, "S");

    map<string, list<shared_ptr<Order>>> bolder;
    map<string, list<shared_ptr<Order>>> sHolder;
    bolder.insert(std::pair<string, list<shared_ptr<Order>>>("1", {pOrder1}));
    bolder.insert(std::pair<string, list<shared_ptr<Order>>>("2", {pOrder2}));

    sHolder.insert(std::pair<string, list<shared_ptr<Order>>>("3", {pOrder3}));
    sHolder.insert(std::pair<string, list<shared_ptr<Order>>>("4", {pOrder4}));

    auto print = [](const shared_ptr<Order> &o) {
        cout << o->id << " " << o->size << " " << o->side << endl;
    };
    auto all_collection = [&](auto collection, const string &side) { ;
        cout << side;
        std::for_each(collection.begin(), collection.end(), [&](const auto &order) {
            for_each(order.second.begin(), order.second.end(), print);
        });
        cout << endl;
    };
    all_collection(bolder, "B");
    all_collection(sHolder, "S");
}