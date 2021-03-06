#pragma once

#include "cstdint.h"
#include "status_with.h"
#include "string_data.h"

namespace QBson {

struct Date_t {
  // TODO: make signed (and look for related TODO's)
  unsigned long long millis;
  Date_t() : millis(0) {}
  Date_t(unsigned long long m) : millis(m) {}
  operator unsigned long long&() { return millis; }
  operator const unsigned long long&() const { return millis; }
  std::string toString() const;
  time_t toTimeT() const;
  int64_t asInt64() const { return static_cast<int64_t>(millis); }
};

StatusWith<Date_t> dateFromISOString(const StringData& dateString);

}  // namespace QBson
