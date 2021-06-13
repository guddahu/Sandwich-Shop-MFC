/**
 * \file Sandwich.cpp
 *
 * \author 
 */

#include "pch.h"
#include "Sandwich.h"
#include <memory>
#include "IngredientQty.h"
#include "Sandwiches.h"
#include "Ingredient.h"
using namespace std;


/**
 * Add an ingredient to a sandwich.
 * 
 * Ingredients are added to the sandwich in stacking order,
 * from the bottom to the top. 
 * 
 * If the ingredient ID does not exist, do not add it.
 * 
 * \param id The ingredient ID
 * \param quantity Quantity of ingredient to add.
 */
/**
 * 
 * \param id 
 * \param quantity 
 */
CSandwich::CSandwich(std::wstring name, double price)
{
    mName = name;
    mPrice = price;
}
void CSandwich::AddIngredient(std::wstring id, int quantity)
{
    auto IfIngFound = mSandwiches->FindIngredient(id);
    if (IfIngFound == nullptr) {
        
    }
    else {
        auto IngrdientQuantity = make_shared<CIngredientQty>(IfIngFound, this, quantity);
        mIngredients.push_back(IngrdientQuantity);
        IngrdientQuantity->SetSandwich(this);
    }
}


/**
 * Get all images that make up the sandwich from the bottom up.
 * 
 * These are the filenames for the images as provided to the function AddIngredient.
 * If an ingredient occurs multiple times, it should appear multiple times in this array.
 * 
 * \return Array of strings
 */
std::vector<std::wstring> CSandwich::Images()
{
    vector<wstring> image;
    for (auto ingrdients : mIngredients) {
        for (int i = 0; i < ingrdients->GetQuantity(); i++) {
            image.push_back(ingrdients->GetIngredient()->GetFilename());
        }
    }
    return image;
}
