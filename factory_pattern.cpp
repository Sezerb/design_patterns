/**
 * Pattern: Factory
 * 
 * Short Story:
 * A pizza brand wants to give franchise service.
 *  They have a contract and pizza store structure.
 *   They provide an orderPizza method and an abstract createPizza method.
 *    createPizza is abstract because they want some customized pizzas according to local aspects. 
 * 
 * */
#include <iostream>
#include <string>
#include <memory>

/// Pizza interface
class Pizza 
{
    
protected:
    std::string _name;
    std::string _dough;
    std::string _sauce;

public:
    Pizza()=default;
    virtual ~Pizza()=default;

    virtual void prepare()
    {
        std::cout << "Prepare " << _name << std::endl;
        std::cout << "Tossing dough...";
        std::cout << "Adding sauce...";
    }

    virtual void bake() 
    {
	    std::cout << "Bake for 25 minutes at 350" << std::endl;
    }

    virtual void cut()
    {
        std::cout << "Cut the pizza into diagonal slices" << std::endl;
    }

    virtual void box()
    {
        std::cout << "Place pizza in official PizzaStore box" << std::endl;
    }

    std::string getName()
    {
        return _name;
    }

    friend std::ostream &operator<<(std::ostream &os, const Pizza &other);
};

std::ostream &operator<<(std::ostream &os, const Pizza &pizza)
{
    os << "---- " << pizza._name <<" ----" << std::endl;
    os << pizza._dough << std::endl;
    os << pizza._sauce << std::endl;

    return os;
}

/// Pizza implementations
class NYStyleCheesePizza : public Pizza
{
public:    
    NYStyleCheesePizza()
    {
        _name = "NY Style Sauce and Cheese Pizza";
        _dough = "Thin Crust Dough";
        _sauce = "Marinara Sauce";
    }
};

class NYStylePepperoniPizza : public Pizza
{
public:
    NYStylePepperoniPizza()
    {
        _name = "NY Style Pepperoni Pizza";
        _dough = "Thin Crust Dough";
        _sauce = "Marinara Sauce";
    }
};

class ChicagoStyleCheesePizza : public Pizza
{
public:
    ChicagoStyleCheesePizza()
    {
		_name = "Chicago Style Deep Dish Cheese Pizza";
		_dough = "Extra Thick Crust Dough";
		_sauce = "Plum Tomato Sauce";
    }

    void cut() override
    {
        std::cout << "Cutting the pizza into square slices" << std::endl;
    }
};

class ChicagoStylePepperoniPizza : public Pizza
{
public:
    ChicagoStylePepperoniPizza()
    {
		_name = "Chicago Style Pepperoni Pizza";
		_dough = "Extra Thick Crust Dough";
		_sauce = "Plum Tomato Sauce";
    }

    void cut() override
    {
        std::cout << "Cutting the pizza into square slices" << std::endl;
    }
};



/// Pizza Store interface
class PizzaStore
{
public:
    virtual Pizza* createPizza(std::string item)=0;

    Pizza* orderPizza(std::string type)
    {
        /// Creating pizza may change over time so separate and encapsulate it.    
        Pizza* pizza = createPizza(type);
        std::cout << "--- Making a " << pizza->getName() << " ---" << std::endl;
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }

};

/// Pizza Store implementations
class NYPizzaStore : public PizzaStore
{
public:
    Pizza* createPizza(std::string item)
    {
        if(item == "cheese")
        {
            return new NYStyleCheesePizza();
        }
        else if(item == "pepperoni")
        {
            return new NYStylePepperoniPizza();
        }
        else
        {
            return nullptr;
        }
        
    }
};

class ChicagoPizzaStore : public PizzaStore
{
public:
    Pizza* createPizza(std::string item)
    {
        if(item == "cheese")
        {
            return new ChicagoStyleCheesePizza();
        }
        else if(item == "pepperoni")
        {
            return new ChicagoStylePepperoniPizza();
        }
        else
        {
            return nullptr;
        }
        
    }
};

int main()
{
    std::unique_ptr<PizzaStore> nyStore(new NYPizzaStore());
    std::unique_ptr<PizzaStore> chicagoStore(new ChicagoPizzaStore());
 
    std::unique_ptr<Pizza> pizza1(nyStore->orderPizza("cheese"));
    std::cout << "Baris ordered a " << pizza1->getName() << std::endl; 
 
    std::unique_ptr<Pizza> pizza2(chicagoStore->orderPizza("pepperoni"));
    std::cout << "Kemal ordered a " << pizza2->getName() << std::endl;

    std::unique_ptr<Pizza> pizza3(nyStore->orderPizza("pepperoni"));
    std::cout << "Ali ordered a " << pizza3->getName() << std::endl; 

    return 0;
}