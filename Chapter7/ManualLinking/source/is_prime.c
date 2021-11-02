
#include <emscripten.h>

int EMSCRIPTEN_KEEPALIVE IsPrime(int value)
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