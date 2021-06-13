/**
 * \file IngredientQty.cpp
 *
 * \author 
 */

#include "pch.h"
#include "IngredientQty.h"
#include "Ingredient.h"

CIngredientQty::CIngredientQty(std::shared_ptr<CIngredient> ingredient, CSandwich* sandwhich, double quantity)
{
	mIngredint = ingredient;
	mSandwhich = sandwhich;
	mQuantity = quantity;
}
