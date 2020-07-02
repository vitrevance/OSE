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
	
#define BIT(place) (1 << place)
#define ISBIT(num, place) ((bool)((num >> place) & 1))

namespace OSE {
#include <string>
#include <vector>
#include <map>
	using std::string;
}

#endif