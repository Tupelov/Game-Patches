//Hamo Lib hasnt realeased yet but may as well
#include "lib/hamolib.h"
hook_ptr(getFieldMajor, 0x007b93c0)

hook_ptr(getFieldMinor, 0x007b93c8)

func(scrSetIntReturn, 0x0035f060, 0x007d2cf0, void, int)

int getFieldMajor() {
	int majorID = *((int*)0x0095afc0);
	scrSetIntReturn(majorID);
	return 1;
}

int getFieldMinor() {
	int minorID = *((int*)0x0095afc4);
	scrSetIntReturn(minorID);
	return 1;
}
