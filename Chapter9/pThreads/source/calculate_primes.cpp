#include <vector>
#include <chrono>
#include <pthread.h>
#include <cstdio>
#include <emscripten.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
	using namespace std;

	struct thread_args {
		int start;
		int end;
		vector<int> primes_found;
	};

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
		if (start % 2 == 0) { start++; }

		for (int i = start; i <= end; i += 2)
		{
			if (IsPrime(i))
			{
				primes_found.push_back(i);
			}
		}
	}

	void* Thread_Func(void* arg)
	{
		struct thread_args* args = (struct thread_args*)arg;

		FindPrimes(args->start, args->end, args->primes_found);
		return arg;
	}

	int main()
	{
		int start = 3, end = 1000000;

		printf("Prime numbers between %d and %d:\n", start, end);

		chrono::high_resolution_clock::time_point duration_start = chrono::high_resolution_clock::now();

		pthread_t thread_ids[4];
		struct thread_args args[5];

		int args_index = 1;
		int args_start = 200000;

		for (int i = 0; i < 4; i++)
		{
			args[args_index].start = args_start;
			args[args_index].end = args_start + 199999;

			if (pthread_create(&thread_ids[i], NULL, Thread_Func, &args[args_index]))
			{
				perror("thread create failed");
				return 1;
			}

			args_index += 1;
			args_start += 200000;
		}

		FindPrimes(3, 199999, args[0].primes_found);

		for (int j = 0; j < 4; j++)
		{
			pthread_join(thread_ids[j], NULL);
		}

		chrono::high_resolution_clock::time_point duration_end = chrono::high_resolution_clock::now();

		chrono::duration<double, milli> duration = duration_end - duration_start;
		printf("FindsPrimes took %f milliseconds to execute\n", duration.count());

		printf("The Values found:\n");
		for (int k = 0; k < 5; k++)
		{
			for (int n : args[k].primes_found)
			{
				printf("%d ", n);
			}
		}
		printf("\n");

		return 0;
	}

#ifdef __cplusplus
}
#endif // __cplusplus