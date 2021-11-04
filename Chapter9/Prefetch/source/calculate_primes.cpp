#include <vector>
#include <chrono>

#include <cstdio>

#include <emscripten.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
	using namespace std;

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

	void FindPrimes(int start, int end, vector<int>& primes_found)
	{
		for (int i = start; i <= end; i += 2)
		{
			if (IsPrime(i))
			{
				primes_found.push_back(i);
			}
		}
	}

	int main()
	{
		int start = 3, end = 1000000;

		printf("Prime numbers between %d and %d:\n", start, end);

		chrono::high_resolution_clock::time_point duration_start = chrono::high_resolution_clock::now();

		vector<int> primes_found;
		FindPrimes(3, 1000000, primes_found);

		chrono::high_resolution_clock::time_point duration_end = chrono::high_resolution_clock::now();

		chrono::duration<double, milli> duration = duration_end - duration_start;
		printf("FindsPrimes took %f milliseconds to execute\n", duration.count());

		printf("The Values found:\n");
		for (int n : primes_found)
		{
			printf("%d ", n);
		}
		printf("\n");

		return 0;
	}

#ifdef __cplusplus
}
#endif // __cplusplus