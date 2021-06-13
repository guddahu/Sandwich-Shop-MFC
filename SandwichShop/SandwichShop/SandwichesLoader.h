#pragma once

#include <vector>
#include <string>
#include "XmlNode.h"

class CSandwiches;
class CSandwich;

/**
 * Class that loads a file into a CSandwiches object.
 */
class CSandwichesLoader
{
public:
    void Load(CSandwiches* sandwiches, std::wstring filename);

    /** Get all of the Sandwich names 
     * \return Array of sandwich names */
    std::vector<std::wstring> Names() { return mNames; }

private:
    /// Currently loading sandwiches object
    CSandwiches* mSandwiches = nullptr;

    void LoadSandwiches(std::shared_ptr<xmlnode::CXmlNode> node);
    void LoadIngredients(std::shared_ptr<xmlnode::CXmlNode> node);
    void LoadIngredient(std::shared_ptr<xmlnode::CXmlNode> node);
    void LoadSandwich(std::shared_ptr<xmlnode::CXmlNode> node);
    void LoadSandwichIngredient(std::shared_ptr<CSandwich> sandwich, std::shared_ptr<xmlnode::CXmlNode> node);

    /// All sandwich names
    std::vector<std::wstring> mNames;
};

