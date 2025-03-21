#include "tlist.cpp"
#include <stdio.h>

tlist<int> t;

int main() {
	t.append(888);
	t.append(666);
	t.append(999);
	t.insert(1, 33);
	//puts("kkkk");
	t.remove(0);
	printf("%d", t.query(1));
}

