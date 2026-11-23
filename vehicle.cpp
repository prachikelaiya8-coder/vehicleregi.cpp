#include <iostream>
#include <string>
using namespace std;

// ================= BASE CLASS =================

class Vehicle
{
protected:
    int id;
    string brand;
    string model;

public:
    static int totalVehicles;

    Vehicle()
    {
        id = 0;
        brand = "";
        model = "";
        totalVehicles++;
    }

    Vehicle(int id, string brand, string model)
    {
        this->id = id;
        this->brand = brand;
        this->model = model;
        totalVehicles++;
    }

    virtual ~Vehicle()
    {
        cout << "\nVehicle Destructor Called";
    }

    // Getters
    int getId()
    {
        return id;
    }

    string getBrand()
    {
        return brand;
    }

    string getModel()
    {
        return model;
    }

    // Setters
    void setId(int id)
    {
        this->id = id;
    }

    void setBrand(string brand)
    {
        this->brand = brand;
    }

    void setModel(string model)
    {
        this->model = model;
    }

    virtual void display()
    {
        cout << "\nID: " << id;
        cout << "\nBrand: " << brand;
        cout << "\nModel: " << model;
    }
};

int Vehicle::totalVehicles = 0;

// ================= SINGLE INHERITANCE =================

class Car : public Vehicle
{
protected:
    string fuelType;

public:
    Car(int id, string brand, string model, string fuelType)
        : Vehicle(id, brand, model)
    {
        this->fuelType = fuelType;
    }

    void display() override
    {
        cout << "\n----- CAR -----";
        Vehicle::display();
        cout << "\nFuel Type: " << fuelType << endl;
    }
};

// ================= MULTILEVEL INHERITANCE =================

class ElectricCar : public Car
{
protected:
    int batteryCapacity;

public:
    ElectricCar(int id, string brand, string model,
                string fuelType, int batteryCapacity)
        : Car(id, brand, model, fuelType)
    {
        this->batteryCapacity = batteryCapacity;
    }

    void display() override
    {
        cout << "\n----- ELECTRIC CAR -----";
        Vehicle::display();
        cout << "\nFuel Type: " << fuelType;
        cout << "\nBattery Capacity: "
             << batteryCapacity << " kWh\n";
    }
};

class SportsCar : public ElectricCar
{
private:
    int topSpeed;

public:
    SportsCar(int id,
              string brand,
              string model,
              string fuelType,
              int batteryCapacity,
              int topSpeed)
        : ElectricCar(id, brand, model,
                      fuelType, batteryCapacity)
    {
        this->topSpeed = topSpeed;
    }

    void display() override
    {
        cout << "\n----- SPORTS CAR -----";
        Vehicle::display();
        cout << "\nFuel Type: " << fuelType;
        cout << "\nBattery Capacity: "
             << batteryCapacity << " kWh";
        cout << "\nTop Speed: "
             << topSpeed << " KM/H\n";
    }
};

// ================= MULTIPLE INHERITANCE =================

class Aircraft
{
protected:
    int flightRange;

public:
    Aircraft(int range)
    {
        flightRange = range;
    }
};

class FlyingCar : public Car, public Aircraft
{
public:
    FlyingCar(int id,
              string brand,
              string model,
              string fuelType,
              int range)
        : Car(id, brand, model, fuelType),
          Aircraft(range)
    {
    }

    void display()
    {
        cout << "\n----- FLYING CAR -----";
        cout << "\nID: " << id;
        cout << "\nBrand: " << brand;
        cout << "\nModel: " << model;
        cout << "\nFuel Type: " << fuelType;
        cout << "\nFlight Range: "
             << flightRange << " KM\n";
    }
};

// ================= HIERARCHICAL =================

class Sedan : public Car
{
public:
    Sedan(int id,
          string brand,
          string model,
          string fuelType)
        : Car(id, brand, model, fuelType)
    {
    }

    void display() override
    {
        cout << "\n----- SEDAN -----";
        Vehicle::display();
        cout << "\nFuel Type: " << fuelType << endl;
    }
};

class SUV : public Car
{
public:
    SUV(int id,
        string brand,
        string model,
        string fuelType)
        : Car(id, brand, model, fuelType)
    {
    }

    void display() override
    {
        cout << "\n----- SUV -----";
        Vehicle::display();
        cout << "\nFuel Type: " << fuelType << endl;
    }
};

// ================= VEHICLE REGISTRY =================

class VehicleRegistry
{
private:
    Vehicle* vehicles[100];
    int count;

public:
    VehicleRegistry()
    {
        count = 0;
    }

    void addVehicle(Vehicle* vehicle)
    {
        vehicles[count++] = vehicle;
        cout << "\nVehicle Added Successfully!\n";
    }

    void displayVehicles()
    {
        if(count == 0)
        {
            cout << "\nNo Vehicles Found!\n";
            return;
        }

        for(int i=0;i<count;i++)
        {
            cout << "\n========================";
            vehicles[i]->display();
            cout << "\n========================\n";
        }
    }

    void searchById(int searchId)
    {
        bool found = false;

        for(int i=0;i<count;i++)
        {
            if(vehicles[i]->getId() == searchId)
            {
                cout << "\nVehicle Found:\n";
                vehicles[i]->display();
                found = true;
                break;
            }
        }

        if(!found)
        {
            cout << "\nVehicle Not Found!\n";
        }
    }
};

// ================= MAIN =================

int main()
{
    VehicleRegistry registry;

    int choice;

    do
    {
        cout << "\n\n====== VEHICLE REGISTRY ======";
        cout << "\n1. Add Car";
        cout << "\n2. Add Electric Car";
        cout << "\n3. Add Sports Car";
        cout << "\n4. Add Sedan";
        cout << "\n5. Add SUV";
        cout << "\n6. View All Vehicles";
        cout << "\n7. Search By ID";
        cout << "\n8. Show Total Vehicles";
        cout << "\n9. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        int id;
        string brand, model, fuel;

        switch(choice)
        {
        case 1:
            cout<<"ID: ";
            cin>>id;
            cout<<"Brand: ";
            cin>>brand;
            cout<<"Model: ";
            cin>>model;
            cout<<"Fuel Type: ";
            cin>>fuel;

            registry.addVehicle(
                new Car(id,brand,model,fuel));
            break;

        case 2:
        {
            int battery;

            cout<<"ID: ";
            cin>>id;
            cout<<"Brand: ";
            cin>>brand;
            cout<<"Model: ";
            cin>>model;
            cout<<"Fuel Type: ";
            cin>>fuel;
            cout<<"Battery Capacity: ";
            cin>>battery;

            registry.addVehicle(
               new ElectricCar(id,brand,model,
                               fuel,battery));
            break;
        }

        case 3:
        {
            int battery,speed;

            cout<<"ID: ";
            cin>>id;
            cout<<"Brand: ";
            cin>>brand;
            cout<<"Model: ";
            cin>>model;
            cout<<"Fuel Type: ";
            cin>>fuel;
            cout<<"Battery Capacity: ";
            cin>>battery;
            cout<<"Top Speed: ";
            cin>>speed;

            registry.addVehicle(
                new SportsCar(id,brand,model,
                              fuel,battery,speed));
            break;
        }

        case 4:
            cout<<"ID: ";
            cin>>id;
            cout<<"Brand: ";
            cin>>brand;
            cout<<"Model: ";
            cin>>model;
            cout<<"Fuel Type: ";
            cin>>fuel;

            registry.addVehicle(
                new Sedan(id,brand,model,fuel));
            break;

        case 5:
            cout<<"ID: ";
            cin>>id;
            cout<<"Brand: ";
            cin>>brand;
            cout<<"Model: ";
            cin>>model;
            cout<<"Fuel Type: ";
            cin>>fuel;

            registry.addVehicle(
                new SUV(id,brand,model,fuel));
            break;

        case 6:
            registry.displayVehicles();
            break;

        case 7:
        {
            int searchId;
            cout<<"Enter ID: ";
            cin>>searchId;

            registry.searchById(searchId);
            break;
        }

        case 8:
            cout<<"\nTotal Vehicles: "
                << Vehicle::totalVehicles
                << endl;
            break;

        case 9:
            cout<<"\nProject Exited Successfully!";
            break;

        default:
            cout<<"\nInvalid Choice!";
        }

    }while(choice != 9);

    return 0;
}