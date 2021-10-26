#include <stdlib.h>
#include <stdio.h>
#include <emscripten.h>

int IsPrime(int value)
{
	// 2�� 1 ����ó��, ¦���� �Ҽ��� �ƴ�
	if (value == 2) { return 1; }
	if (value < 1 || value % 2 == 0) { return 0; }

	// 3���� �Ű������� �����ٱ��� ������ �ݺ�, Ȧ���� üũ
	for (int i = 3; (i * i) <= value; i += 2)
	{
		if (value % i == 0) { return 0; }
	}

	return 1;
}

int main()
{
	int start = 3;
	int end = 100000;

	printf("Prime numbers between %d and %d:\n", start, end);

	for (int i = start; i <= end; i += 2)
	{
		if (IsPrime(i))
		{
			printf("%d ", i);
		}
	}
	printf("\n");

	return 0;
}