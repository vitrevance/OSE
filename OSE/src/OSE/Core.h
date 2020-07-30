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

	#ifndef I_DIMENSIONS
		#define I_DIMENSIONS 3
	#endif

	
#define BIT(place) (1 << place)
#define ISBIT(num, place) ((bool)((num >> place) & 1))

#include <OSE/Logger.h>

#include <string>
#include <vector>
#include <map>
#include <set>

namespace OSE {
	using std::string;
}



#endif