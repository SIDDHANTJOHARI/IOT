#include<iostream>
using namespace std;
class Whatever;
class Toy{
   private:
    int price;
    Whatever *user;
    public:
    Toy();
    void setPrice(int price);
    int getPrice();
    void notifyMeWhenPriceChanges(Whatever *user);
};
class Whatever
{
    private:
    Toy t1,t2,t3;
    public:
    void initializeThings();
    void doSomething();
     void doSomethingElse();
    void abcd();
};



  
 Toy::   Toy()
    {
        this->price=0;
        this->user=NULL;
    }
 void  Toy::   setPrice(int price)
    {
        if(price==this->price)return;

        this->price=price;
        if(this->user!=NULL)
        {
            this->user->abcd();
        }
    }
  int Toy::   getPrice()
    {
        return this->price;
    }
 void  Toy::  notifyMeWhenPriceChanges(Whatever *user)
    {
        this->user=user;
    }

   
  void  Whatever:: initializeThings()
    {
        t1.notifyMeWhenPriceChanges(this);
        t2.notifyMeWhenPriceChanges(this);
        t3.notifyMeWhenPriceChanges(this);
    }
 void  Whatever::  doSomething()
    {
        t1.setPrice(1000);
        t2.setPrice(2000);
        t3.setPrice(3000);
    }
  void Whatever::   doSomethingElse()
    {
        t1.setPrice(1000);
        t2.setPrice(2000);
        t3.setPrice(3000);
    }
  void  Whatever:: abcd()
    {
        cout<<"Price Changed\n";
    }

int main()
{
    Whatever w;
    w.initializeThings();
    w.doSomething();
    w.doSomethingElse();
    return 0;
}