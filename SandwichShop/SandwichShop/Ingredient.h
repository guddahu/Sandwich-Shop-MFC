/**
 * \file Ingredient.h
 *
 * \author 
 *
 * Represents a possible ingredient in a sandwich.
 */

#pragma once
#include <string>
#include <string.h>
#include <string>
class CSandwiches;
/**
 * Represents a possible ingredient in a sandwich.
 */
class CIngredient
{
public:

    /// Constructor
    CIngredient(std::wstring id, std::wstring description, int stock, std::wstring filename);

    /// Destructor
    virtual ~CIngredient() {}

    void SetSandwhiches(CSandwiches* sandwiches) { mSandwiches = sandwiches; }

    std::wstring GetId() { return mId; }
    std::wstring GetFilename() { return mFilename; }
    std::wstring GetDescription() { return mDescription; }
    int GetStock() { return mStock; }

private:
    std::wstring mId;
    std::wstring mDescription;
    std::wstring mFilename;
    CSandwiches* mSandwiches;
    int mStock;
};

