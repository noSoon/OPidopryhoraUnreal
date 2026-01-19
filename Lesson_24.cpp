#include <iostream>
#include <vector>

struct OnSaleProducts{
    std::string productName;
    float oldPrice;
    float newPrice;
};

class Observer {
    public:
        virtual void update(const std::vector<OnSaleProducts> &products) = 0;
};

class Subject {
    public:
        virtual void registerObserver(Observer* observer) = 0;
        virtual void removeObserver(Observer* observer) = 0;
        virtual void notifyObservers(const std::vector<OnSaleProducts> &products) = 0;
};

class Store: public Subject {
    private:
        std::vector<Observer*> observers;
        std::string productName;
        float oldPrice;
        float newPrice;
    public:
        void registerObserver(Observer* observer) override {
            observers.push_back(observer);
        }

        void removeObserver(Observer* observer) override {
            observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
        }

        void notifyObservers(const std::vector<OnSaleProducts> &products) override {
            for (auto &observer : observers){
                observer->update(products);
            }
        }

        void addProductsOnSale(const std::vector<OnSaleProducts> &products){
            notifyObservers(products);
        }

};

class SalesSubscriber: public Observer{
    public:
        void update(const std::vector<OnSaleProducts> &products) override {
            std::cout << "---Alarm customer!---" << std::endl;
            for (auto &product : products){
            std::cout << "We have a " << product.productName << " on sale!" << std::endl;
            std::cout << "Old price : " << product.oldPrice << std::endl;
            std::cout << "New price : " << product.newPrice << std::endl;
            }
        }
};

int main(){

    Store silpo;
    SalesSubscriber subscriber1;
    SalesSubscriber subscriber2;
    SalesSubscriber subscriber3;

    silpo.registerObserver(&subscriber1);
    silpo.registerObserver(&subscriber2);
    silpo.registerObserver(&subscriber3);

    std::vector<OnSaleProducts> newProducts = {
        {"Bananas", 24.90, 18.50},
        {"Apples", 12.60, 9.90},
        {"Kiwis", 15.0, 10.0}
    };

    silpo.addProductsOnSale(newProducts);
    silpo.removeObserver(&subscriber2);
    std::cout << "------------------------------" << std::endl;
    silpo.addProductsOnSale(newProducts);


    
    return 0;
}