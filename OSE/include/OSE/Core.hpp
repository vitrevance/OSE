#ifndef OSE_CORE_H
#define OSE_CORE_H

#ifdef OSE_BUILD
#define OSE_API __declspec(dllexport)
#else
#define OSE_API __declspec(dllimport)
#endif

#ifndef S_APP_NAME
#define S_APP_NAME "APP"
#endif

#ifdef OSE_USE_DOUBLE
typedef double t_float;
#else
typedef float t_float;
#endif

#define BIT(place) (1 << place)
#define ISBIT(num, place) ((bool)((num >> place) & 1))

#include <OSE/Logger.hpp>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <limits>

namespace OSE {
using std::string;
}

#include <OSE/DebugData.hpp>

#endif