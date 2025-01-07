#include<string>
#include<vector>
#include <memory>
#include<list>
#include <map>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <sstream>
//#include "gtest/gtest.h"

using namespace std;
namespace Utils {
    vector<string> split(const std::string &request, const string &delim) {
        vector<string> result;
        std::istringstream iss(request);
        for (string str; iss >> str;) {
            result.push_back(str);
        }
        return result;
    }
};

namespace OB {
    const std::string SUB = "SUB";
    const std::string CXL = "CXL";
    const std::string BUY = "B";
    const std::string SELL = "S";
    const std::string MARKET = "MO";
    const std::string LIMIT = "LO";
    const std::string IOC = "IOC";
    const std::string FOK = "FOK";
    const std::string CRP = "CRP";
};

enum class Side {
    BUY,
    SELL
};

Side getSide(const std::string &side) {
    try {
        if (side == OB::BUY) {
            return Side::BUY;
        } else if (side == OB::SELL) {
            return Side::SELL;
        } else {
            throw std::runtime_error("invalid side=" + side);
        }
    } catch (std::exception &ex) {
        std::cout << __func__ << ":" << ex.what() << std::endl;
    }
}

enum class OrderType {
    LIMIT,
    MARKET,
    IOC,
    FOK
};

OrderType getOrderType(const std::string &orderType) {
    try {
        if (orderType == OB::LIMIT) {
            return OrderType::LIMIT;
        } else if (orderType == OB::MARKET) {
            return OrderType::MARKET;
        } else if (orderType == OB::IOC) {
            return OrderType::IOC;
        } else if (orderType == OB::FOK) {
            return OrderType::FOK;
        } else {
            throw std::runtime_error("invalid orderType=" + orderType);
        }
    } catch (std::exception &ex) {
        std::cout << __func__ << ":" << ex.what() << std::endl;
    }
}

enum class ActionType {
    SUB,
    CXL,
    CRP
};

ActionType getActionType(const std::string &action) {
    try {
        if (action == OB::SUB) {
            return ActionType::SUB;
        } else if (action == OB::CXL) {
            return ActionType::CXL;
        } else if (action == OB::CRP) {
            return ActionType::CRP;
        } else {
            throw std::runtime_error("invalid action=" + action);
        }
    } catch (std::exception &ex) {
        std::cout << __func__ << ":" << ex.what() << std::endl;
    }
}

using Quantity = u_int32_t;
using Price = u_int32_t;
using OrderId = std::string;
using Request = string;
using Requests = vector<Request>;

struct Order {
    OrderId orderId;
    Quantity quantity{0};
    Price price{0};
    Quantity leavesQuantity{quantity};
    Side side;

    Order(OrderId orderId, const Quantity &quantity, const Price &price, const Side &side)
            : orderId(std::move(orderId)), quantity(quantity), price(price), leavesQuantity(quantity), side(side) {}

    [[nodiscard]] bool isOrderClosed() const {
        return leavesQuantity == 0;
    }
};

using OrderHolder = shared_ptr<Order>;
// multimap with orderId
// OR
// map with list of orderId can be used
//using BuyBook = map<Price, list<OrderHolder>, std::greater<>>;

using BuyBook = map<Price, list<OrderHolder>, std::greater<>>;
using SellBook = map<Price, list<OrderHolder>, std::less<>>;
using Book = map<OrderId, OrderHolder>;

//ideally we can have different class for each book
//for now keeping simple and including books in single class
//Also Database class should be Singleton & thread safe
//For now making it static
class Database {
    static Book book;
    static BuyBook buyBook;
    static SellBook sellBook;

    static void addToBuyBook(const OrderHolder &_pOrder);

    static void addToSellBook(const OrderHolder &_pOrder);

    static void removeFromBuyBook(const OrderHolder &_pOrder);

    static void removeFromSellBook(const OrderHolder &_pOrder);

public:
    static void addToBook(const OrderHolder &_pOrder);

    static void removeFromBook(const OrderHolder &_pOrder);

    static bool isIdNotInDatabase(const OrderId &orderId) {
        return book.find(orderId) == book.end();
    }

    static const BuyBook &getBuyBook() { return buyBook; };

    static const SellBook &getSellBook() { return sellBook; };

    static OrderHolder getOrderDetailsById(const OrderId &id) {
        return book[id];
    }

    static void removeFromBookById(const OrderId &id) {
        OrderHolder pOrder = getOrderDetailsById(id);
        if (pOrder != nullptr)
            removeFromBook(pOrder);
    }
};

Book Database::book;
BuyBook Database::buyBook;
SellBook Database::sellBook;


//pre-condition: order must be on this px already for all below functions
//in new C++ we can declare pointer of not null type
void Database::addToBook(const OrderHolder &_pOrder) {
    book.emplace(std::pair<OrderId, OrderHolder>(_pOrder->orderId, _pOrder));
    if (_pOrder->side == Side::BUY)
        addToBuyBook(_pOrder);
    else
        addToSellBook(_pOrder);
}

void Database::addToSellBook(const OrderHolder &_pOrder) {
    if (sellBook.find(_pOrder->price) == sellBook.end())
        sellBook[_pOrder->price] = list<OrderHolder>();
    sellBook[_pOrder->price].push_back(_pOrder);
}

void Database::addToBuyBook(const OrderHolder &_pOrder) {
    if (buyBook.find(_pOrder->price) == buyBook.end())
        buyBook[_pOrder->price] = list<OrderHolder>();
    buyBook[_pOrder->price].push_back(_pOrder);
}

void Database::removeFromBook(const OrderHolder &_pOrder) {
    auto itr = book.find(_pOrder->orderId);
    if (itr != book.end()) {
        removeFromBuyBook(_pOrder);
        removeFromSellBook(_pOrder);
        book.erase(itr);
    }
}

void Database::removeFromBuyBook(const OrderHolder &_pOrder) {
    auto &orders = buyBook[_pOrder->price];
    orders.remove(_pOrder);
    if (orders.empty())
        buyBook.erase(_pOrder->price);
}

void Database::removeFromSellBook(const OrderHolder &_pOrder) {
    auto &orders = sellBook[_pOrder->price];
    orders.remove(_pOrder);
    if (orders.empty())
        sellBook.erase(_pOrder->price);
}

//For simplicity keep all common under one class and making static
// in reality we may have multiple classes
//These are stateless functions
class MatchingEngine {
public:

    static bool mayBeFullyTradedWithMultipleOrders(OrderHolder &pOrder, OrderType &orderType);

    static bool mayBeFullyTraded(const OrderHolder &pOrder, const OrderHolder &fromOrderBook);

    static bool mayBeOnlyFullyTraded(const OrderHolder &pOrder, const OrderHolder &fromOrderBook);

    static bool mayBePartiallyTraded(const OrderHolder &pOrder, const OrderHolder &fromOrderBook);

    static Quantity calculateTotalTrade(const OrderHolder &pOrder,
                                        map<OrderId, Quantity> &tradedOrdersTracker,
                                        Quantity cumulativeQuantity,
                                        Quantity &leavesQuantity,
                                        const OrderHolder &fromOrderBook);

    static void
    checkTradeForBuy(const OrderHolder &pOrder, Quantity leavesQuantity, map<OrderId, Quantity> &tradedOrdersTracker,
                     Quantity &cumulativeQuantity);

    static void
    checkTradeForSell(const OrderHolder &pOrder, Quantity leavesQuantity, map<OrderId, Quantity> &tradedOrdersTracker,
                      Quantity &cumulativeQuantity);

    static void
    reportIfFullyTraded(OrderHolder &pOrder, map<OrderId, Quantity> &tradedOrdersTracker, Quantity cumulativeQuantity);
};

//printing format
auto print = [&](const OrderHolder &pOrder) {
    if (!pOrder->isOrderClosed())
        cout << " " << pOrder->leavesQuantity << "@" << pOrder->price << "#" << pOrder->orderId;
};

////printing lambda for buy and sell side map
auto report_collection = [&](const auto &collection, const string &side) {
    cout << "" << side << ":";
    for_each(collection.begin(), collection.end(), [&](auto &orders) {
        for_each(orders.second.begin(), orders.second.end(), print);
    });
    cout << endl;
};

class Report {

public:
    static void ReportTrading(Quantity quantity, Price price) {
        cout << quantity * price << endl;

    }

    static void ReportIfNoTrading(const OrderHolder &pOrder) {
        if (pOrder->leavesQuantity == pOrder->quantity)
            ReportTrading(0, 0);
    }

    static void ReportBook() {
        report_collection(Database::getBuyBook(), "B");
        report_collection(Database::getSellBook(), "S");
    }

};

bool MatchingEngine::mayBeFullyTraded(const OrderHolder &pOrder, const OrderHolder &fromOrderBook) {
    if (mayBeOnlyFullyTraded(pOrder, fromOrderBook))
        return true;
    else if (pOrder->leavesQuantity < fromOrderBook->leavesQuantity) {
        //TODO updating order object is incorrect,need to have function for this Database class
        pOrder->leavesQuantity = 0;
        fromOrderBook->leavesQuantity -= pOrder->quantity;
        return true;
    }
    return false;
}

bool MatchingEngine::mayBeOnlyFullyTraded(const OrderHolder &pOrder, const OrderHolder &fromOrderBook) {
    if (pOrder->leavesQuantity == fromOrderBook->leavesQuantity) {
        //TODO updating order object is incorrect,need to have function for this Database class
        pOrder->leavesQuantity = 0;
        fromOrderBook->leavesQuantity = 0;
        return true;
    }
    return false;
}

bool MatchingEngine::mayBePartiallyTraded(const OrderHolder &pOrder, const OrderHolder &fromOrderBook) {
    if (pOrder->leavesQuantity > fromOrderBook->leavesQuantity) {
        //TODO updating order object is incorrect,need to have function for this Database class
        pOrder->leavesQuantity = pOrder->quantity - fromOrderBook->leavesQuantity;
        fromOrderBook->leavesQuantity = 0;
        return true;
    }
    return false;
}

bool MatchingEngine::mayBeFullyTradedWithMultipleOrders(OrderHolder &pOrder, OrderType &orderType) {
    if (pOrder != nullptr && orderType == OrderType::FOK) {
        map<OrderId, Quantity> tradedOrdersTracker;
        Quantity cumulativeQuantity = 0;
        Quantity leavesQuantity = pOrder->leavesQuantity;

        if (pOrder->side == Side::BUY) {
            checkTradeForBuy(pOrder, leavesQuantity, tradedOrdersTracker, cumulativeQuantity);
        } else if (pOrder->side == Side::SELL) {
            checkTradeForSell(pOrder, leavesQuantity, tradedOrdersTracker, cumulativeQuantity);
        }
        reportIfFullyTraded(pOrder, tradedOrdersTracker, cumulativeQuantity);
    }
    return false;
}

//TODO this function can should be refactored
void MatchingEngine::reportIfFullyTraded(OrderHolder &pOrder, map<OrderId, Quantity> &tradedOrdersTracker,
                                         Quantity cumulativeQuantity) {
    if (cumulativeQuantity >= pOrder->leavesQuantity && !tradedOrdersTracker.empty()) {
        Quantity totalTraded = 0;
        for (const auto &data : tradedOrdersTracker) {
            OrderId orderId = data.first;
            Quantity traded = data.second;
            OrderHolder oppositeOrder = Database::getOrderDetailsById(orderId);
            if (oppositeOrder != nullptr) {
                totalTraded += traded * oppositeOrder->price;
                oppositeOrder->leavesQuantity -= traded;
                pOrder->leavesQuantity -= traded;
            }
        }
        cout << totalTraded << endl;
    }
}


//TODO These checkTradeForBuy,checkTradeForSell functions are duplicates and can be refactored using lambda functions
void MatchingEngine::checkTradeForSell(const OrderHolder &pOrder, Quantity leavesQuantity,
                                       map<OrderId, Quantity> &tradedOrdersTracker,
                                       Quantity &cumulativeQuantity) {
    for (auto &fromBuyBook : Database::getBuyBook()) {
        for_each(fromBuyBook.second.begin(), fromBuyBook.second.end(), [&](const OrderHolder &oppositeOrder) {
            if ((!oppositeOrder->isOrderClosed() && cumulativeQuantity != pOrder->leavesQuantity)) {
                if (pOrder->price <= oppositeOrder->price) {
                    cumulativeQuantity = calculateTotalTrade(pOrder,
                                                             tradedOrdersTracker,
                                                             cumulativeQuantity,
                                                             leavesQuantity,
                                                             oppositeOrder);
                }
            }
        });
    }
}

//TODO These checkTradeForBuy,checkTradeForSell functions are duplicates and can be refactored using lambda functions
void MatchingEngine::checkTradeForBuy(const OrderHolder &pOrder, Quantity leavesQuantity,
                                      map<OrderId, Quantity> &tradedOrdersTracker, Quantity &cumulativeQuantity) {
    for (auto &fromBuyBook : Database::getSellBook()) {
        for_each(fromBuyBook.second.begin(), fromBuyBook.second.end(), [&](const OrderHolder &oppositeOrder) {
            if ((!oppositeOrder->isOrderClosed() && cumulativeQuantity != pOrder->leavesQuantity)) {
                if (pOrder->price >= oppositeOrder->price) {
                    cumulativeQuantity = calculateTotalTrade(pOrder,
                                                             tradedOrdersTracker,
                                                             cumulativeQuantity,
                                                             leavesQuantity,
                                                             oppositeOrder);
                }
            }
        });
    }
}

Quantity MatchingEngine::calculateTotalTrade(const OrderHolder &pOrder,
                                             map<OrderId, Quantity> &tradedOrdersTracker,
                                             Quantity cumulativeQuantity,
                                             Quantity &leavesQuantity,
                                             const OrderHolder &fromOrderBook) {
    try {
        int tradedQuantity = min(fromOrderBook->leavesQuantity, leavesQuantity);
        cumulativeQuantity += tradedQuantity;
        tradedOrdersTracker.insert(pair<OrderId, Quantity>(fromOrderBook->orderId, tradedQuantity));
        leavesQuantity -= tradedQuantity;
        return cumulativeQuantity;
    } catch (std::exception &ex) {
        std::cout << __func__ << ":" << ex.what() << std::endl;
    }
    return 0;
}


// I am assuming that in feature many such orderType can be added
// also processing for each order type can be complex
//so preferred to keep different classes for each order type

class OrderTypeProcessor {
public:
    virtual bool match(const OrderHolder &pOrder, const OrderHolder &oppositeOrder) = 0;

    ~OrderTypeProcessor() = default;

};

class LimitOrderTypeProcessor : public OrderTypeProcessor {
public:
    bool match(const OrderHolder &pOrder, const OrderHolder &oppositeOrder) override {
        if ((pOrder->side == Side::BUY && pOrder->price >= oppositeOrder->price) ||
            (pOrder->side == Side::SELL && pOrder->price <= oppositeOrder->price)) {
            MatchingEngine::mayBeFullyTraded(pOrder, oppositeOrder);
            MatchingEngine::mayBePartiallyTraded(pOrder, oppositeOrder);
            Report::ReportTrading(oppositeOrder->quantity, oppositeOrder->price);
            return true;
        }
        return false;
    }

};

//Ideally no need to create a different class for Limit & Market
// and we could just pass price as 0 with for Market order and mimic limit
//keeping in mind behaviour can change ,prefer to add new class
class MarketOrderTypeProcessor : public OrderTypeProcessor {
public:
    bool match(const OrderHolder &pOrder, const OrderHolder &oppositeOrder) override {
        MatchingEngine::mayBeFullyTraded(pOrder, oppositeOrder);
        MatchingEngine::mayBePartiallyTraded(pOrder, oppositeOrder);
        Report::ReportTrading(oppositeOrder->quantity, oppositeOrder->price);
        return true;
    }

};

class IocOrderTypeProcessor : public OrderTypeProcessor {
public:
    bool match(const OrderHolder &pOrder, const OrderHolder &oppositeOrder) override {
        if ((pOrder->side == Side::BUY && pOrder->price >= oppositeOrder->price) ||
            (pOrder->side == Side::SELL && pOrder->price <= oppositeOrder->price)) {
            if (MatchingEngine::mayBeFullyTraded(pOrder, oppositeOrder))
                Report::ReportTrading(oppositeOrder->leavesQuantity, oppositeOrder->price);
            else if (MatchingEngine::mayBePartiallyTraded(pOrder, oppositeOrder)) {
                Report::ReportTrading(oppositeOrder->quantity - oppositeOrder->leavesQuantity, pOrder->price);
            }
        }
        return true;
    }
};

class FokOrderTypeProcessor : public OrderTypeProcessor {
public:
    bool match(const OrderHolder &pOrder, const OrderHolder &oppositeOrder) override {
        if ((pOrder->side == Side::BUY && pOrder->price >= oppositeOrder->price) ||
            (pOrder->side == Side::SELL && pOrder->price <= oppositeOrder->price)) {
            if (MatchingEngine::mayBeOnlyFullyTraded(pOrder, oppositeOrder))
                Report::ReportTrading(oppositeOrder->quantity, oppositeOrder->price);
            return true;
        }
        return false;
    }
};

class RouterBySide {
public:
    static void route(const OrderHolder &pOrder, const OrderType &orderType);

    static void sellProcessing(const OrderHolder &pOrder, const OrderType &orderType);

    static void buyProcessing(const OrderHolder &pOrder, const OrderType &orderType);
};


//Below code may look verbose , but prefer to keep as
//it would help to add support for new orderType ,
//Remember open close principle
class OrderTypeProcessorDriver {
public:
    static unique_ptr<OrderTypeProcessor> get(const OrderType &orderType) {
        try {
            if (orderType == OrderType::LIMIT)
                return make_unique<LimitOrderTypeProcessor>();
            else if (orderType == OrderType::MARKET)
                return make_unique<MarketOrderTypeProcessor>();
            else if (orderType == OrderType::IOC)
                return make_unique<IocOrderTypeProcessor>();
            else if (orderType == OrderType::FOK)
                return make_unique<FokOrderTypeProcessor>();
            else {
                throw std::runtime_error("invalid orderType");
            }
        } catch (std::exception &ex) {
            std::cout << __func__ << ":" << ex.what() << std::endl;
        }
        return nullptr;
    }
};


class Action {
public:
    virtual bool validate(const Requests &request) = 0;

    virtual bool process(const Requests &requests) = 0;

    virtual ~Action() = default;

};

class SubAction : public Action {
    static const int MINIMUM_EXPECTED_FIELDS = 5;
public:
    bool validate(const Requests &requests) override {
        return (requests.size() >= MINIMUM_EXPECTED_FIELDS);
    }

    bool process(const Requests &requests) override;
};

bool SubAction::process(const Requests &requests) {
    try {
        if (!validate(requests))
            return false;
        OrderId orderId = requests[3];
        if (!Database::isIdNotInDatabase(orderId)) {
            return false;
        }
        auto newOrder = make_shared<Order>(orderId,
                                           stoi(requests[4]),//quantity
                                           stoi(requests[5]),//price
                                           getSide(requests[2]));
        OrderType orderType = getOrderType(requests[1]);
        RouterBySide::route(newOrder, orderType);
        MatchingEngine::mayBeFullyTradedWithMultipleOrders(newOrder, orderType);
        Report::ReportIfNoTrading(newOrder);

        //IOC and Market Type add to book if fully traded,
        //TODO seems incorrect place to have this check , it should be in OrderType classes
        if (!newOrder->isOrderClosed() && orderType == OrderType::LIMIT)
            Database::addToBook(newOrder);

        return true;
    } catch (std::exception &ex) {
        std::cout << __func__ << ":" << ex.what() << std::endl;
    }
}


void RouterBySide::route(const OrderHolder &pOrder, const OrderType &orderType) {
    if (pOrder != nullptr) {
        if (pOrder->side == Side::BUY)
            buyProcessing(pOrder, orderType);
        else if (pOrder->side == Side::SELL)
            sellProcessing(pOrder, orderType);
    }
}

//TODO sellProcessing & buyProcessing seems duplicates, can be generalized using lambda, example Print function above
void RouterBySide::sellProcessing(const OrderHolder &pOrder, const OrderType &orderType) {
    for (auto &fromBuyBook : Database::getBuyBook()) {
        for_each(fromBuyBook.second.begin(), fromBuyBook.second.end(), [&](const OrderHolder &oppositeOrder) {
            if (!pOrder->isOrderClosed() && !oppositeOrder->isOrderClosed())
                OrderTypeProcessorDriver::get(orderType)->match(pOrder, oppositeOrder);
        });
    }
}

//TODO sellProcessing & buyProcessing seems duplicates, can be generalized using lambda, example Print function above
void RouterBySide::buyProcessing(const OrderHolder &pOrder, const OrderType &orderType) {
    for (auto &fromBuyBook : Database::getSellBook()) {
        for_each(fromBuyBook.second.begin(), fromBuyBook.second.end(), [&](const OrderHolder &oppositeOrder) {
            if (!pOrder->isOrderClosed() && !oppositeOrder->isOrderClosed())
                OrderTypeProcessorDriver::get(orderType)->match(pOrder, oppositeOrder);
        });
    }
}


class CxlAction : public Action {
    static const int MINIMUM_EXPECTED_FIELDS = 2;
public:
    bool validate(const Requests &requests) override {
        return (requests.size() >= MINIMUM_EXPECTED_FIELDS);
    }

    bool process(const Requests &requests) override {
        if (!validate(requests))
            return false;
        Database::removeFromBookById(requests[1]);
        return true;
    };
};

class CrpAction : public Action {
    static const int MINIMUM_EXPECTED_FIELDS = 4;
public:
    bool validate(const Requests &requests) override {
        return (requests.size() >= MINIMUM_EXPECTED_FIELDS);
    }

    bool process(const Requests &requests) override;
};

bool CrpAction::process(const Requests &requests) {
    if (!validate(requests))
        return false;
    OrderId orderId = requests[1];
    Quantity newQuantity = stoi(requests[2]);
    Price newPrice = stoi(requests[3]);
    OrderHolder pOrder = Database::getOrderDetailsById(orderId);
    if (pOrder != nullptr) {
        //TODO - corner conditions for size changes
        pOrder->quantity = pOrder->leavesQuantity = newQuantity;
        if (pOrder->price != newPrice) {
            OrderHolder copyOfOrder = pOrder;
            Database::removeFromBook(pOrder);
            copyOfOrder->price = newPrice;
            Database::addToBook(copyOfOrder);
            copyOfOrder->price = newPrice;
        }
    }
    return true;
}

unique_ptr<Action> getAction(const ActionType &actionType) {
    try {
        if (actionType == ActionType::SUB) {
            return std::make_unique<SubAction>();
        } else if (actionType == ActionType::CXL) {
            return std::make_unique<CxlAction>();
        } else if (actionType == ActionType::CRP) {
            return std::make_unique<CrpAction>();
        }
        throw std::runtime_error("invalid actionType");
    } catch (std::exception &ex) {
        std::cout << __func__ << ":" << ex.what() << std::endl;
        throw;
    }
}

class Processor {
public:
    static void getRequest(Request &request);
};

void Processor::getRequest(Request &request) {
    try {
        static const string SPACE_DELIMITER{" "};
        static const int MINIMUM_EXPECTED_FIELDS_IN_REQUEST = 2;
        Requests requestParameters = Utils::split(request, SPACE_DELIMITER);
        if (requestParameters.size() < MINIMUM_EXPECTED_FIELDS_IN_REQUEST) {
            return;
        }
        getAction(getActionType(requestParameters[0]))->process(requestParameters);
    } catch (std::exception &ex) {
        std::cout << __func__ << ":" << ex.what() << std::endl;
        throw;
    }
}


//TEST(TestSuiteName, TestName) {
//    Requests part1{
//            {"SUB LO B Ffuj 200 13"},
//            {"SUB LO B Yy7p 150 11"},
//            {"SUB LO B YuFU 100 13"},
//            {"SUB LO S IpD8 150 14"},
//            {"SUB LO S Y93N 190 15"},
//            {"SUB LO B Y5wb 230 14"},
//            {"SUB MO B IZLO 250"},
//            {"CXL Ffuj"},
//            {"CXL 49Ze"},
//    };
//    Requests part2{
//            {"SUB LO B N1Eh 300 12"},
//            {"SUB LO B OGxb 250 11"},
//            {"SUB LO S JSuV 350 14"},
//            {"SUB LO S uH6w 320 15"},
//            {"SUB IOC S ckMR 150 10"},
//            {"SUB IOC B DVeP 500 14"},
//            {"SUB FOK S enjR 200 12"},
//            {"SUB FOK S 8uGs 200 9"},
//            {"SUB LO B 2va9 250 12"},
//            {"SUB LO B 9zS1 300 11"},
//            {"CRP 2va9 480 11"},
//            {"CRP 9zS1 170 11"}
//    };
//    for (auto part1Request : part2) {
//        Processor::getRequest(part1Request);
//    }
//    Report::ReportBook();
//}


//The input consists of a sequence of commands ,The input will terminate with a single line, END
//I am assuming
//When request is received Then programme can process it
//And END is received Then programme can be terminated printing OrderBook details.
int main(int argc, char *argv[]) {
    Request request;
    while (getline(cin, request) && request != "END") {
        Processor::getRequest(request);
    }
    Report::ReportBook();
//    ::testing::InitGoogleTest(&argc, argv);
//    RUN_ALL_TESTS();
}

