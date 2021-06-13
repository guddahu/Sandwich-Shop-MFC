/**
 * \file Ingredient.cpp
 *
 * \author 
 */

#include "pch.h"
#include "Ingredient.h"

CIngredient::CIngredient(std::wstring id, std::wstring description, int stock, std::wstring filename)
{
	mId = id;
	mStock = stock;
	mDescription = description;
	mFilename = filename;
}
