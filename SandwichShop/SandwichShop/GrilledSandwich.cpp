#include "pch.h"
#include "GrilledSandwich.h"
using namespace std;
CGrilledSandwich::CGrilledSandwich(std::wstring name, double price, int time) : CSandwich(name, price)
{
    mTime = time;
}

std::vector<std::wstring> CGrilledSandwich::Images()
{
    vector<wstring> image;
    image = CSandwich::Images();

    image.insert(image.begin(), L"grill.png");

    return image;
}
