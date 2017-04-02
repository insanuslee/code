#include <stdio.h>

int int_function() {
	int x = 1;
	printf("地址是%p,数据是%d\n", &x, x);
	return x;
}

int main(void) {
	printf("数据是%d\n", int_function());
	//提示int不可以获取地址
	return 0;
}
