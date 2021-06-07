#include<iostream>
using namespace std;
class Toy;
class ToyEvent
{
private:
int oldPrice,newPrice;
Toy *t;
public:
ToyEvent(Toy *t,int oldPrice,int newPrice)
{
this->t=t;
this->oldPrice=oldPrice;
this->newPrice=newPrice;
}
Toy* getToy()
{
    return this->t;
}
int getOldPrice()
{
    return this->oldPrice;
}
int getNewPrice()
{
    return this->newPrice;
}

};
class ToyUser
{
    public:
     virtual  void priceChanged(ToyEvent *e)=0;
};
class Toy{
   private:
    int price;
    ToyUser *user;
    public:
    Toy();
    void setPrice(int price);
    int getPrice();
    void notifyMeWhenPriceChanges(ToyUser *user);
};
 Toy::   Toy()
    {
        this->price=0;
        this->user=NULL;
    }
 void  Toy::   setPrice(int price)
    {
        if(price==this->price)return;
    int oldPrice=this->price;
        this->price=price;
        if(this->user!=NULL)
        {
            ToyEvent ev(this,oldPrice,this->price);
            
          this->user->priceChanged(&ev);
        }
    }
  int Toy::   getPrice()
    {
        return this->price;
    }
 void  Toy::  notifyMeWhenPriceChanges(ToyUser *user)
    {
        this->user=user;
    }
   
class Whatever:ToyUser
{
    private:
    Toy t1,t2,t3;
    public:
    void initializeThings();
    void doSomething();
     void doSomethingElse();
    void priceChanged(ToyEvent *);
};
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
  void  Whatever:: priceChanged(ToyEvent *ev)
    {
        if(&t1==ev->getToy())
        {
            cout<<"TOY1  "<<" OLD PRICE "<<ev->getOldPrice()<<"NEW PRICE"<<ev->getNewPrice()<<"\n";
        }
        else if(&t2==ev->getToy())
        {
            cout<<"TOY2  "<<" OLD PRICE  "<<ev->getOldPrice()<<"NEW PRICE"<<ev->getNewPrice()<<"\n";
        }
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