/*Khalid Aldawood*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>

using namespace std;
class Animal;
class Observer;
class ZooAnnouncer;
class Subject;
class Canine;
class Feline;
class Pachydrem;
class CatNoiseStrategy;
class Dog;
class Rhino;
class Wolf;
class CatNoiseNormal;
class CatNoiseAbnormal;
class Zookeeper;
class Cat;

/* sources
https://cpppatterns.com/patterns/observer.html
https://www.codeproject.com/Articles/328365/Understanding-and-Implementing-Observer-Pattern-2
https://www.robertlarsononline.com/2017/01/27/strategy-pattern-using-cplusplus/
*/

class Animal{
    private:
        string animalName;
    
    public:
        void setName(string name){animalName = name;}
        string getName(){return animalName;}
        string getName(string add){return animalName + add;}
        string wakeup(){return " woke up\n";}
        string eat(){return " is eating\n";}
        string sleep(){return" is sleeping\n";}
};

//interface
class Observer{
    public:
    virtual void update(string name,string action)=0;
};

class ZooAnnouncer: public Observer{
    string name;
    public: 
    void update(string name,string action){
        cout<<name + action;
    }
    
    ZooAnnouncer(string name){
        this->name = name;    
    }
};

//interface
class Subject{
    public:
        vector<Observer*> observers;
        virtual void register_observer(Observer *o) = 0; 
        virtual void remove_observer(Observer *o) = 0;
        virtual void notify_observers(string name,string action) = 0;
        
};

class Canine: public Animal{
    public: string roam(){return " is running\n";}
};

class Feline: public Animal{
    public: string roam(){return " is roaming\n";}
};

class Pachydrem: public Animal{
    public: string roam(){return " is traveling\n";}
};

//interface
class CatNoiseStrategy{
    public: virtual string makeNoise()=0;
};

class Dog: public Canine{
    public: string makeNoise(){return" 'woof-woof!'\n";}
};

class Rhino: public Pachydrem{
    public: string makeNoise(){return " Loud Rhino sounds!\n";}
};

class Wolf: public Canine{
    public: string makeNoise(){return " 'Ahhhh Wooooooooooo!'\n";}
};


class CatNoiseNormal: public CatNoiseStrategy{
    public: string makeNoise(){return " 'Mooooooooooo!'\n";}
};


class CatNoiseAbnormal: public CatNoiseStrategy{
    public: string makeNoise(){return " 'Meow!'\n";}
};

class Cat: public Feline{
    public: string performNoise(CatNoiseStrategy *strategy){
        return strategy->makeNoise();
    }
};


class Zookeeper: public Subject{
      
      public:
        vector<Observer*> observers;
        void register_observer(Observer *o){observers.push_back(o);}
        void remove_observer(Observer *o){observers.pop_back();}
        void notify_observers(string name,string action){for(Observer *o : observers){ o->update(name,action);}}
        
        void wakeupAnimal(Animal animal){
            notify_observers(animal.getName(),animal.wakeup());
        }
        
        void feedAnimal(Animal animal){
            notify_observers(animal.getName(),animal.eat());
        }
        
        void putToSleepAnimal(Animal animal){
            notify_observers(animal.getName(),animal.sleep());
        }
        
        template <typename T> // t for any subclass (Canine etc)
        void roamAnimal(T t){
            notify_observers(t.getName(),t.roam());
        }
        
        template <typename T> // t for any subclass (Cat , Dog etc)
        void soundAnimal(T t){
            notify_observers(t.getName(),t.makeNoise());
        }
        
        void soundAnimalWithStrategy(Cat cat, CatNoiseStrategy *strategy){
            notify_observers(cat.getName(),cat.performNoise(strategy));
        }
};

int main()
{
    list<Animal> animalList;
    
    Dog dog1;
    dog1.setName("Doggie");
    animalList.push_back(dog1);
    
    Dog dog2;
    dog2.setName("Douglas");
    animalList.push_back(dog2);
    
    Cat cat1;
    cat1.setName("Charmer");
    animalList.push_back(cat1);
    
    Cat cat2;
    cat2.setName("Cathy");
    animalList.push_back(cat2);
    
    Rhino rhino1;
    rhino1.setName("Ryan");
    animalList.push_back(rhino1);
    
    Rhino rhino2;
    rhino2.setName("Ramdan");
    animalList.push_back(rhino2);
    
    Wolf wolf1;
    wolf1.setName("Waleed");
    animalList.push_back(wolf1);
    
    Wolf wolf2;
    wolf2.setName("Will");
    animalList.push_back(wolf2);
    
    Zookeeper zookeeper;
    ZooAnnouncer zooAnnouncer1("abu50");
    zookeeper.register_observer(&zooAnnouncer1);
    list<Animal>::iterator i;
    
    for(i = animalList.begin(); i != animalList.end(); i++){
        zookeeper.wakeupAnimal(*i);
    }
    
    for(i = animalList.begin(); i != animalList.end(); i++){
        zookeeper.feedAnimal(*i);
    }
    
    zookeeper.roamAnimal(dog1);
    zookeeper.roamAnimal(dog2);
    zookeeper.roamAnimal(cat1);
    zookeeper.roamAnimal(cat2);
    zookeeper.roamAnimal(rhino1);
    zookeeper.roamAnimal(rhino2);
    zookeeper.roamAnimal(wolf1);
    zookeeper.roamAnimal(wolf2);
    
    zookeeper.soundAnimal(dog1);
    zookeeper.soundAnimal(dog2);
    zookeeper.soundAnimal(rhino1);
    zookeeper.soundAnimal(rhino2);
    zookeeper.soundAnimal(wolf1);
    zookeeper.soundAnimal(wolf2);

    CatNoiseAbnormal abnormal;
    CatNoiseNormal normal;
    
    zookeeper.soundAnimalWithStrategy(cat1,&abnormal);
    zookeeper.soundAnimalWithStrategy(cat2,&normal);
    
    for(i = animalList.begin(); i != animalList.end(); i++){
        zookeeper.putToSleepAnimal(*i);
    }
    
    zookeeper.remove_observer(&zooAnnouncer1);
    
    return 0;
}