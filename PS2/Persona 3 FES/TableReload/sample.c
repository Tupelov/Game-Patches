//Hamo Lib hasnt realeased yet but may as well
#include "lib/hamolib.h"
hook_ptr(btlTableReload, 0x007b9338)

func(reloadBattleTables, 0x0027e270, 0x007d2cf0, void, ptr)

func(dds3SearchProcessName, 0x00195340, 0x007d2cf0, ptr, char*)



int btlTableReload() {

	ptr id = dds3SearchProcessName("rootProc");
	reloadBattleTables(id);

	return 1;
}
