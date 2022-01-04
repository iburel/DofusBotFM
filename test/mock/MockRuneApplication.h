#pragma once

#include <gmock/gmock.h>

#include <map>

#include "Stat.h"
#include "Rune.h"
#include "Item.h"
#include "RuneApplicationInterface.h"

class MockRuneApplication : public DBF::RuneApplicationInterface {
public:
    MOCK_METHOD(void, ApplyRune, (DBF::Item* item, const DBF::Rune& rune), (final));
};
