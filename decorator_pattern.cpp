/**
 * Pattern: Decorator
 * 
 * Short Story:
 * Starbuzz is in trouble for calculating cost of a
 *  coffee properly. They do not know how to add cost of 
 *   condiments to the cost in an elegant way. They are really
 *     tired of creating so many combinations of coffee objects.
 * */

#include <iostream>
#include <string>

class Beverage
{
public:
    Beverage() = default;
    virtual ~Beverage() = default;

    virtual std::string getDescription()
    {
        return _description;
    }

    virtual double cost() = 0;

protected:
    std::string _description = "Unknown Beverage";
};

class CondimentDecorator : public Beverage
{
public:    
    CondimentDecorator() = default;
    virtual ~CondimentDecorator() = default;

protected:
     Beverage *_beverage;
};

class Espresso : public Beverage
{
public:    
    Espresso()
    {
        _description = "Espresso";
    }

    double cost()
    {
        return 1.99;
    }
};

class Latte : public Beverage
{
public:    
    Latte()
    {
        _description = "Latte";
    }

    double cost()
    {
        return 2.20;
    }
};

class Mocha : public CondimentDecorator
{
public :
    Mocha(Beverage *beverage)
    {
        _beverage = beverage;
    }

    ~Mocha()
    {
        if(_beverage)
            delete _beverage;
    }

    std::string getDescription()
    {
        return _beverage->getDescription() + ", Mocha";
    }

    double cost()
    {
        return .20 + _beverage->cost();
    }

};

class Milk : public CondimentDecorator
{
public :
    Milk(Beverage *beverage)
    {
        _beverage = beverage;
    }

    ~Milk()
    {
        if(_beverage)
            delete _beverage;
    }

    std::string getDescription()
    {
        return _beverage->getDescription() + ", Milk";
    }

    double cost()
    {
        return .10 + _beverage->cost();
    }

};

int main()
{
    Beverage *espresso = new Espresso();
    std::cout << espresso->getDescription() << " $" << espresso->cost() << std::endl;

    Beverage *latteMocha = new Mocha(new Latte());
    std::cout << latteMocha->getDescription() << " $" << latteMocha->cost() << std::endl;

    Beverage *mix = new Milk(new Mocha(new Espresso()));
    std::cout << mix->getDescription() << " $" << mix->cost() << std::endl;

    delete mix;
    delete latteMocha;
    delete espresso;

    return 0;
}



