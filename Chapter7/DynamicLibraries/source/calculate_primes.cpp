#include <cstdio>

#include <emscripten.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	int IsPrime(int value)
	{
		// 2와 1 예외처리, 짝수는 소수가 아님
		if (value == 2) { return 1; }
		if (value < 1 || value % 2 == 0) { return 0; }

		// 3부터 매개변수의 제곱근까지 루프를 반복, 홀수만 체크
		for (int i = 3; (i * i) <= value; i += 2)
		{
			if (value % i == 0) { return 0; }
		}

		return 1;
	}

	void EMSCRIPTEN_KEEPALIVE FindPrimes(int start, int end)
	{
		printf("Prime numbers between %d and %d:\n", start, end);

		for (int i = start; i <= end; i += 2)
		{
			if (IsPrime(i))
			{
				printf("%d ", i);
			}
		}
		printf("\n");
	}

	int main()
	{
		FindPrimes(3, 100000);

		return 0;
	}

#ifdef __cplusplus
}
#endif // __cplusplus