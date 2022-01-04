#include "DummyRuneApplication.h"

#include <cstdlib>
#include <map>

#include "Stat.h"
#include "Rune.h"
#include "Item.h"
#include "RuneProperties.h"
#include "StatsDensity.h"

namespace DBF {

DummyRuneApplication::DummyRuneApplication(
    const std::function<int(int min, int max)>& randFunc)
    : m_RandFunction(randFunc)
{
}

void DummyRuneApplication::ApplyRune(Item* item, const Rune& rune)
{
    if (item == nullptr) {
        throw std::invalid_argument("Item cannot be null");
    }

    const auto& runeProperties = GetRuneProperties(rune);

    float densityToLoose = 0.0f;
    const int randomValue = m_RandFunction(0, 3);
    if (randomValue <= 1) {
        densityToLoose = runeProperties.density;
    }

    if (randomValue >= 1) {
        item->UpdateStat(runeProperties.stat, runeProperties.density);
    }

    while (densityToLoose > 0.0f) {
        const auto& statsMap = item->GetStats();
        std::vector<Stat> positiveStats;
        for (const auto& stat : statsMap) {
            const auto& statLine = stat.second;
            if (statLine.current > 0.0f) {
                positiveStats.push_back(stat.first);
            }
        }

        auto randomIndex = m_RandFunction(0, positiveStats.size() - 1);
        const auto& stat = positiveStats[randomIndex];
        const auto& statLine = statsMap.at(stat);
        const auto& statDensity = GetStatDensity(stat);

        auto density = std::min(
            statLine.current * statDensity,
            m_RandFunction(0, static_cast<int>(densityToLoose)));
    }
}

} // namespace DBF
