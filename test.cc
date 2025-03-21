#include "tlist.cpp"
#include <stdio.h>

tlist<int> t;

int main() {
	t.append(33);
	t.insert(0, 16);
	printf("%d",t.query(0));
}

