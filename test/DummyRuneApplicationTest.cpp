#include <gtest/gtest.h>

#include "DummyRuneApplication.h"

#include <nlohmann/json.hpp>

#include "Rune.h"
#include "Item.h"
#include "FM.h"

TEST(DummyRuneApplication, ApplyRune_NullItem)
{
    auto dummyRuneApplication = std::make_unique<DBF::DummyRuneApplication>();
    try {
        dummyRuneApplication->ApplyRune(nullptr, DBF::Rune::DoAir);
        FAIL();
    } catch (...) {
    }
}

TEST(DummyRuneApplication, ApplyRune_Valid)
{
    const auto json =
        R"({
            "stats":
            {
                "Ine":
                {
                    "min": 40,
                    "max": 70,
                    "value": 50
                },
                "Cri":
                {
                    "min": 4,
                    "max": 7,
                    "value": 0
                },
                "DoAir":
                {
                    "min": 10,
                    "max": 15,
                    "value": 20
                }
            }
        })"_json;

    try {
        DBF::Item item(json);
        auto dummyRuneApplication =
            std::make_unique<DBF::DummyRuneApplication>();
        dummyRuneApplication->ApplyRune(&item, DBF::Rune::DoAir);
        EXPECT_TRUE(item.GetStat(DBF::Stat::Ine).current == 50);
        EXPECT_TRUE(item.GetStat(DBF::Stat::Cri).current == 0);
        EXPECT_TRUE(
            item.GetStat(DBF::Stat::DoAir).current >= 19 &&
            item.GetStat(DBF::Stat::DoAir).current <= 21);

    } catch (...) {
        FAIL();
    }
}

TEST(DummyRuneApplication, ApplyRune_FromFM)
{
    const auto json =
        R"({
            "stats":
            {
                "Ine":
                {
                    "min": 40,
                    "max": 70,
                    "value": 50
                },
                "Cri":
                {
                    "min": 4,
                    "max": 7,
                    "value": 0
                },
                "DoAir":
                {
                    "min": 10,
                    "max": 15,
                    "value": 20
                }
            }
        })"_json;

    try {
        DBF::Item item(json);
        std::map<DBF::Stat, float> wantedStats = {
            {DBF::Stat::Ine, 70},
            {DBF::Stat::Cri, 7},
            {DBF::Stat::DoAir, 15},
            {DBF::Stat::DoNeutre, 2},
        };

        auto runeApplication = std::make_shared<DBF::DummyRuneApplication>();
        DBF::FM fm(item, wantedStats, runeApplication);
        fm.Run();

    } catch (...) {
        FAIL();
    }
}
