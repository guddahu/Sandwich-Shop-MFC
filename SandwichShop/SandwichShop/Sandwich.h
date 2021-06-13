/**
 * \file Sandwich.h
 *
 * \author 
 *
 * Class that represents a sandwich in our system.
 */
#pragma once

#include <string>
#include <vector>
#include <memory>
class CSandwiches;
class CIngredientQty;


/**
 * Class that represents a sandwich in our system.
 */
class CSandwich
{
public:

    /// Constructor
    CSandwich(std::wstring name, double price);

    /// Destructor
    virtual ~CSandwich() {}

    void AddIngredient(std::wstring id, int quantity);

    virtual std::vector<std::wstring> Images();

    void SetSandwiches(CSandwiches* Sandwiches) { mSandwiches = Sandwiches; }

    std::wstring GetName() { return mName; }

    double GetPrice() { return mPrice; }

private:
    std::vector <std::shared_ptr<CIngredientQty>> mIngredients;

    std::wstring mName;
    double mPrice;

    CSandwiches* mSandwiches;

    std::vector<std::wstring>mImage;
};

