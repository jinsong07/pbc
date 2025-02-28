#include "map.h"

#include <stdio.h>
#include <stddef.h>

int 
main()
{
	struct map_kv kv[] = {
		{1,"alice"},
		{3,"bob" },
		{99,"carol"},
	};
	
	struct map_ip * map = _pbcM_ip_new(kv, sizeof(kv)/sizeof(kv[0]));
	struct map_si * map2 = _pbcM_si_new(kv, sizeof(kv)/sizeof(kv[0]));
	int i;

	for (i=0;i<100;i++) {
		void *p= _pbcM_ip_query(map,i);
		if (p) {
			int id = _pbcM_si_query(map2,p);
			printf("%d %s\n",id,(const char *)p);
		}
	}

	struct map_sp * map3 = _pbcM_sp_new();
	_pbcM_sp_insert(map3,"Alice","alice");
	_pbcM_sp_insert(map3,"Bob","bob");

	void ** r = _pbcM_sp_query_insert(map3, "Carol");
	*r = "carol";

	r = _pbcM_sp_query_insert(map3, "Alice");
	*r = "not alice";

	printf("%s\n",(const char *)_pbcM_sp_query(map3,"Alice"));
	printf("%s\n",(const char *)_pbcM_sp_query(map3,"Bob"));
	printf("%s\n",(const char *)_pbcM_sp_query(map3,"Carol"));

	return 0;
}
