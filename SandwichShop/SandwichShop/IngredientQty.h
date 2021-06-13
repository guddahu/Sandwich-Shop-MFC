/**
 * \file IngredientQty.h
 *
 * \author 
 *
 * Represents the quantity of an ingredient for this sandwich.
 */

#pragma once
#include <memory>

class CSandwich;
class CIngredient;

/**
 * Represents the quantity of an ingredient for this sandwich.
 */
class CIngredientQty
{
public:
    /// Constructor
    CIngredientQty(std::shared_ptr<CIngredient> ingredient, CSandwich* sandwhich, double quantity);

    /// Destructor
    virtual ~CIngredientQty() {}

    /// Copy constructor (disabled)
    CIngredientQty(const CIngredientQty&) = delete;

    /// Assignment operator (disabled)
    void operator=(const CIngredientQty&) = delete;

    void SetIngredient(std::shared_ptr<CIngredient> ingredint) { mIngredint = ingredint; }
    void SetSandwich(CSandwich* ingredint) { mSandwhich = ingredint; }
    int GetQuantity() { return mQuantity; }

    std::shared_ptr<CIngredient> GetIngredient() { return mIngredint; }
private:
    CSandwich* mSandwhich;
	int mQuantity;
    std::shared_ptr<CIngredient> mIngredint;
};

