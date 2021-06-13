/**
 * \file Sandwiches.cpp
 *
 * \author 
 */

#include "pch.h"
#include "Sandwiches.h"
#include "Ingredient.h"
#include <memory>
#include "Sandwich.h"
#include "GrilledSandwich.h"
using namespace std;

/**
 * Add an ingredient to the inventory of available ingredients.
 * \param id A string inventory ID for the ingredient. 
 * \param description Description of the ingredient
 * \param stock How many there are in stock
 * \param filename Filename for the ingredient image
 * \return Pointer to the allocated ingredient object
 */
std::shared_ptr<CIngredient> CSandwiches::AddIngredient(std::wstring id, std::wstring description, int stock, std::wstring filename)
{
    auto ingredient = make_shared<CIngredient>(id, description, stock, filename);
    mIngredients.push_back(ingredient);
    ingredient->SetSandwhiches(this);
    return ingredient;

}



/**
 * Find an ingredient.
 * \param id The ingredient ID.
 * \return Ingredient object or nullptr if not found.
 */
std::shared_ptr<CIngredient> CSandwiches::FindIngredient(std::wstring id)
{
    for (auto ingrdient : mIngredients) {
        if (ingrdient->GetId() == id) {
            return ingrdient;
        }
    }
    return nullptr;
}


/**
 * Return the number of different ingredients in the inventory.
 *
 * This is the number of Ingredient items, not the count of the
 * total stock.
 * \return Number of ingredients available
 */
int CSandwiches::NumIngredients()
{
    return mIngredients.size();
}


/**
 * Add a new sandwich to the system.
 * \param name Name of the sandwich
 * \param price Price in dollars
 * \param grilled Grilling time or zero if not grilled
 * \return CSandwich object
 */
std::shared_ptr<CSandwich> CSandwiches::AddSandwich(std::wstring name, double price, int grilled)
{
    if (grilled == 0) {
        auto sandwich = make_shared<CSandwich>(name, price);
        sandwich->SetSandwiches(this);
        mSandwiches.push_back(sandwich);
        return sandwich;
    }
    else {
        auto Grilledsandwhich = make_shared<CGrilledSandwich>(name, price, grilled);
        mSandwiches.push_back(Grilledsandwhich);
        Grilledsandwhich->SetSandwiches(this);
        return Grilledsandwhich;
    }
}


/**
 * Final a sandwich by name.
 * \param name Name to search for.
 * \return CSandwich object or nullptr if not found.
 */
std::shared_ptr<CSandwich> CSandwiches::FindSandwich(std::wstring name)
{
    for (auto sandwich : mSandwiches) {
        if (sandwich->GetName() == name) {
            return sandwich;
        }
    }
    return nullptr;
}



/**
 * Return the number of different sandwiches in the system.
 * \return Number of possible sandwiches.
 */
int CSandwiches::NumSandwiches()
{
    return mSandwiches.size();
}
