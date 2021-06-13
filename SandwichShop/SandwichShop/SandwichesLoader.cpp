#include "pch.h"
#include "SandwichesLoader.h"
#include "Sandwiches.h"
#include "Sandwich.h"

using namespace std;
using namespace xmlnode;

/**
 * Load data from a sandwiches XML file into a CSandwiches object.
 * \param sandwiches The CSandwiches object to load
 * \param filename The source filename.
 */
void CSandwichesLoader::Load(CSandwiches* sandwiches, std::wstring filename)
{
    mSandwiches = sandwiches;

    try
    {
        shared_ptr<CXmlNode> root = xmlnode::CXmlNode::OpenDocument(filename);

        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"sandwiches")
            {
                LoadSandwiches(node);
            }
            else  if (node->GetType() == NODE_ELEMENT && node->GetName() == L"ingredients")
            {
                LoadIngredients(node);
            }
        }
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

}


/**
 * Load the contents of the sandwiches tag
 * \param node XML node
 */
void CSandwichesLoader::LoadSandwiches(std::shared_ptr<xmlnode::CXmlNode> node)
{
    for (auto child : node->GetChildren())
    {
        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"sandwich")
        {
            LoadSandwich(child);
        }
    }
}

/**
 * Load the contents of the ingredients tag
 * \param node XML node
 */
void CSandwichesLoader::LoadIngredients(std::shared_ptr<xmlnode::CXmlNode> node)
{

    for (auto child : node->GetChildren())
    {
        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"ingredient")
        {
            LoadIngredient(child);
        }
    }
}

/**
 * Load the contents of the ingredient tag
 * \param node XML node
 */
void CSandwichesLoader::LoadIngredient(std::shared_ptr<xmlnode::CXmlNode> node)
{
    auto id = node->GetAttributeValue(L"id", L"");
    auto description = node->GetAttributeValue(L"description", L"");
    auto stock = node->GetAttributeIntValue(L"stock", 0);
    auto image = node->GetAttributeValue(L"image", L"");

    mSandwiches->AddIngredient(id, description, stock, image);
}

/**
 * Load the contents of the sandwich tag
 * \param node XML node
 */
void CSandwichesLoader::LoadSandwich(std::shared_ptr<xmlnode::CXmlNode> node)
{
    auto name = node->GetAttributeValue(L"name", L"");
    auto price = node->GetAttributeDoubleValue(L"price", 0.0);
    auto grilled = node->GetAttributeIntValue(L"grilled", 0);
    auto sandwich = mSandwiches->AddSandwich(name, price, grilled);

    mNames.push_back(name);

    if (sandwich == nullptr)
    {
        return;
    }



    for (auto child : node->GetChildren())
    {
        if (child->GetType() == NODE_ELEMENT && child->GetName() == L"ingredient")
        {
            LoadSandwichIngredient(sandwich, child);
        }
    }
}

/**
 * Load the contents of the ingredient tag inside the sandwich tag
 * \param sandwich The sandwich we are loading
 * \param node XML node
 */
void CSandwichesLoader::LoadSandwichIngredient(std::shared_ptr<CSandwich> sandwich, std::shared_ptr<xmlnode::CXmlNode> node)
{
    auto id = node->GetAttributeValue(L"id", L"");
    auto quantity = node->GetAttributeIntValue(L"quantity", 0);

    // Add it to the sandwich
    sandwich->AddIngredient(id, quantity);
}