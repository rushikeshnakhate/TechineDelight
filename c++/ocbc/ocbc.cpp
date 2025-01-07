// write a class BaseQuote with member function using macro GET_QUOTE impmement settter and getter for the following member variables
// write code
// Path: c%2B%2B/ocbc/ocbc.cpp
// write a class BaseQuote with member function using macro GET_QUOTE impmement settter and getter for the following member variables
class BaseQuote
{
    private:
        double price;
        double volume;
        double high;
        double low;
        double open;
        double close;
    public:
        void setPrice(double price)
        {
            this->price = price;
        }
        double getPrice()
        {
            return price;
        }
        void setVolume(double volume)
        {
            this->volume = volume;
        }
        double getVolume()
        {
            return volume;
        }
        void setHigh(double high)
        {
            this->high = high;
        }
        double getHigh()
        {
            return high;
        }
        void setLow(double low)
        {
            this->low = low;
        }
        double getLow()
        {
            return low;
        }
        void setOpen(double open)
        {
            this->open = open;
        }
        double getOpen()
        {
            return open;
        }
        void setClose(double close)
        {
            this->close = close;
        }
        double getClose()
        {
            return close;
        }
};


Nitin
