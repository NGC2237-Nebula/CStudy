#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void UnsignedConvert() {
	short a = -4321;
	unsigned short b = (unsigned short)a;
	printf("short a = %d , unsigned b = %d\n\n", a, b);
}

void LongConvertShort() {
	int x = 165537, u = -34991;
	short y = (short)x, v = (short)u;
	printf("long = %d , short = %d\n", x, y);
	printf("long = %d , short = %d\n\n", u, v);
}

void ShortConvertLong() {
	// 有符号数 -> 符号扩展
	short x = -4321;
	int y = (short)x;
	// 无符号数 -> 零扩展
	unsigned short u = (unsigned short)x;
	unsigned int v = u;
	printf("short = %d , long = %d\n", x, y);
	printf("short = %d , long = %d\n", u, v);
}

int main() {
	UnsignedConvert();
	LongConvertShort();
	ShortConvertLong();
	return 0;
}