#pragma once

#include "RuneApplicationInterface.h"

#include <map>
#include <functional>
#include <cmath>

namespace {

int DefaultRandom(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

} // namespace

namespace DBF {

class Rune;
class Stat;

class DummyRuneApplication : public RuneApplicationInterface {
public:
    DummyRuneApplication(
        const std::function<int(int min, int max)>& randFunc = ::DefaultRandom);

    void ApplyRune(Item* item, const Rune& rune) final;

private:
    std::function<int(int min, int max)> m_RandFunction;
};

} // namespace DBF
