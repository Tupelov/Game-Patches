//Hamo Lib hasnt realeased yet but may as well
#include "lib/hamolib.h"


func(scePrintf, 0x5225a8, 0x007d2cf0, int, const char* format, ...)



func(getFilePath, 0x00100d80, 0x007d2cf0, void*, void* format, ...)

func(datCheckAnswer, 0x0017d800, 0x007d2cf0, int, void)



#define EnemyAI ((void*)0x007ce4cc)

#define BossAI ((void*)0x007ce4d0)

#pragma hook_ovr(ai_loader,0x0027de38)

int ai_loader() {
	scePrintf("Tupe's AI Loader v0.21\n");
		
	//ptr address=""
	//scePrintf("Starting Tupelov's custom AI loader.\n");
	scePrintf("Loading Custom AI!\n");
	ptr file;
	ptr address;

	if (datCheckAnswer() == 0) {
		scePrintf("Loading AI for The Journey!\n");

		scePrintf("Loading Enemy AI!\n");
		file = getFilePath("model/persona/ps0f0.rmd", 1);
		scePrintf("getFilePath() Worked!\n");
		scePrintf("Address: %x\n", file);

		address = *((ptr*)(file + 0x110));

		if (address == 0) {
			scePrintf("AI not loaded\n");
		}
		else
		{
			scePrintf("Loaded AI at: %x\n", address);
			*((ptr*)EnemyAI) = address;

		}


		scePrintf("Loading Boss AI!\n");
		file = getFilePath("model/persona/ps0f1.rmd", 1);
		scePrintf("getFilePath() Worked!\n");
		scePrintf("Address: %x\n", file);

		address = *((ptr*)(file + 0x110));

		if (address == 0) {
			scePrintf("AI not loaded\n");
		}
		else
		{
			scePrintf("Loaded AI at: %x\n", address);
			*((ptr*)BossAI) = address;

		}
	}
	else
	{
		scePrintf("Loading AI for The Answer!\n");

		scePrintf("Loading Enemy AI!\n");
		file = getFilePath("model/persona/ps0f2.rmd", 1);
		scePrintf("getFilePath() Worked!\n");
		scePrintf("Address: %x\n", file);

		address = *((ptr*)(file + 0x110));

		if (address == 0) {
			scePrintf("AI not loaded\n");
		}
		else
		{
			scePrintf("Loaded AI at: %x\n", address);
			*((ptr*)EnemyAI) = address;

		}


		scePrintf("Loading Boss AI!\n");
		file = getFilePath("model/persona/ps0f3.rmd", 1);
		scePrintf("getFilePath() Worked!\n");
		scePrintf("Address: %x\n", file);

		address = *((ptr*)(file + 0x110));

		if (address == 0) {
			scePrintf("AI not loaded\n");
		}
		else
		{
			scePrintf("Loaded AI at: %x\n", address);
			*((ptr*)BossAI) = address;

		}
	}
	scePrintf("Survived\n");
		
	return 1;
}
