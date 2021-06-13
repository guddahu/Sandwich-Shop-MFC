/**
 * \file GrilledSandwich.h
 *
 * \author 
 *
 * Specialized version of a sandwich: Grilled!
 */

#pragma once

#include "Sandwich.h"
/**
 * Specialized version of a sandwich: Grilled!
 */
class CGrilledSandwich : public CSandwich
{
public:


    /// Constructor
    CGrilledSandwich(std::wstring name, double price, int time);

    /// Destructor
    ~CGrilledSandwich() {}


    std::vector<std::wstring> Images();

    int GetTime() { return mTime; }
private:
	int mTime = 0;
};

