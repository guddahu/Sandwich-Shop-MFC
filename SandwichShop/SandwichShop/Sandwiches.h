/**
 * \file Sandwiches.h
 *
 * \author 
 *
 * Represents a collection of sandwiches
 */
#pragma once

#include <string>
#include <memory>
#include <vector>

class CIngredient;
class CSandwich;
class CGrilledSandwich;
class CIngredientQty;
/**
 * Represents a collection of sandwiches
 */
class CSandwiches
{
public:

    std::shared_ptr<CIngredient> AddIngredient(std::wstring id, std::wstring description, int stock, std::wstring filename);
    std::shared_ptr<CIngredient> FindIngredient(std::wstring id);

    std::shared_ptr<CSandwich> AddSandwich(std::wstring name, double price, int grilled=0);
    std::shared_ptr<CSandwich> FindSandwich(std::wstring name);

    int NumIngredients();
    int NumSandwiches();

    void SetName(std::wstring name) { mName = name; }
    std::wstring GetName() { return mName; }
    std::vector <std::shared_ptr<CIngredientQty>> GetIngQty() { return mIngquantity; }
private:
    std::vector <std::shared_ptr<CIngredient>> mIngredients;
    std::vector <std::shared_ptr<CSandwich>> mSandwiches;
    std::vector <std::shared_ptr<CIngredientQty>> mIngquantity;

    std::wstring mName;
    //std::vector <std::shared_ptr<CMotor>> mMotors;

};

