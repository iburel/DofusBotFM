#pragma once

#include <map>

namespace DBF {

class Stat;
class Rune;
class Item;

class RuneApplicationInterface
{
public:
    virtual ~RuneApplicationInterface() = default;

    virtual void ApplyRune(Item* item, const Rune& rune) = 0;
};

} // namespace DBF
