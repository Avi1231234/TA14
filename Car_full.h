#include <iostream>
#include <vector>
#include <exception>

#ifndef TA7_CAR_FULL_H
#define TA7_CAR_FULL_H

class Car
{
public:
    Car(const std::string& man = "",
        const std::string& model = "",
        const std::string& fuel_type = "",
        const std::string& color = "",
        const std::string& type = "")
        :
        _manufacturer(man), _model(model),
        _fuel_type(fuel_type), _color(color),
        _type(type), _fuel(0), _price(0)
    {
        std::cout << "I am a car! \n";
    }
    // DTR must be virtual in an abstract class
    virtual ~Car()
    {
        std::cout << "Car d'tr \n";
    }
    virtual Car* clone() const = 0;

    std::string get_manufacturer() const {return _manufacturer;}
    std::string get_model() const {return _model;}
    std::string get_fuel_type() const {return _fuel_type;}
    std::string get_color() const {return _color;}
    std::string get_type() const {return _type;}
    size_t get_price() const {return _price;}
protected:
    // type: Gasoline or electric
    std::string _manufacturer, _model, _fuel_type, _color, _type;
    size_t _price, _fuel;
};

class Tesla: public Car {
public:
    Tesla(const std::string& model="Model_S",
          const std::string& color="black",
          size_t battery_mAh=400)
          :
          Car("Tesla", model, "Electricity", color, "Electric"),
          _battery_mAh(battery_mAh)
    {
        std::cout << "I am a Tesla car! \n";
    }
    ~Tesla()
    {
        std::cout << "Tesla d'tr \n";
    }
protected:
    size_t _battery_mAh; // milli-ampere/hour
};

class ModelS final: public Tesla
{
public:
    ModelS(const std::string& color="white")
            :
            Tesla("Model_S", color, 600)
    {
        _price = 200000;
        std::cout << "I am the Model S! \n";
    }

    ~ModelS()
    {
        std::cout << "Model S d'tr \n";
    }

    Car* clone() const override
    {
        return new ModelS(*this);
    }
};

class Chevy: public Car {
public:
    Chevy(const std::string& model="Malibu",
          const std::string& color="white",
          float tank = 52.0,
          float km_per_liter=10.0)
          :
          Car("Chevy", model, "Petrol", color, "Gasoline"),
          _tank_capacity(tank), km_per_liter(km_per_liter)
    {
        std::cout << "I am a Chevrolet car! \n";
    }
    ~Chevy()
    {
        std::cout << "Chevy d'tr \n";
    }


    void set_km_per_liter(float n)
    {
        km_per_liter = n;
    }
protected:
    float _tank_capacity;
private:
    float km_per_liter;
};

class Spark final: public Chevy
{
public:
    Spark(const std::string& color="white")
          :
          Chevy("Spark", color, 32.0, 15.0)
    {
        _price = 80000;
        std::cout << "I am a Spark model! \n";
    }
    ~Spark()
    {
        std::cout << "Spark d'tr \n";
    }
    Car* clone() const override
    {
        return new Spark(*this);
    }
};


class CarDealer: public std::vector<Car*>
{
public:
    CarDealer() = default;

    void add(const Car& other)
    {
        push_back(other.clone());
    }

    // RULE OF 3
    ~CarDealer()
    {
        for(auto c : *this)
        {
            delete c;
        }
    }


    CarDealer(const CarDealer& other)
    {
        for(Car* c : other)
        {
            // create a new dynamic copy of CarT*
            this->push_back(c->clone());
        }
    }

    CarDealer& operator=(const CarDealer& other)
    {
        if (this != &other)
        {
            for(auto c : *this)
            {
                delete c;
            }
            this->clear();
            for(Car* c : other)
            {
                // create a new dynamic copy of CarT*
                this->push_back(c->clone());
            }
        }
        return *this;
    }

    void what_cars_do_you_have()
    {
        for (auto it = this->begin(); it != this->end(); it++)
        {
            std::cout << "I have a " << (*it)->get_manufacturer() <<  ", " << (*it)->get_model() <<  ", ";
            std::cout << "which costs: " << (*it)->get_price() <<  " Shekels." << std::endl;

        }
    }
};

#endif //TA7_CAR_FULL_H
