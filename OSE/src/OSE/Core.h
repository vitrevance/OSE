#ifndef CORE_H
#define CORE_H

	#ifdef OSE_BUILD
		#define OSE_API __declspec(dllexport)
	#else
		#define OSE_API __declspec(dllimport)
	#endif
#endif