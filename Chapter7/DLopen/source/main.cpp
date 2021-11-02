#include <cstdlib>
#include <cstdio>

#include <dlfcn.h>
#include <emscripten.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
	
	typedef void(*FindPrimes)(int, int);

	void CalculatePrimes(const char* file_name)
	{
		void* handle = dlopen(file_name, RTLD_NOW); // 사이드 모듈 오픈
		if (handle == NULL) { return; }

		FindPrimes find_primes = (FindPrimes)dlsym(handle, "FindPrimes"); // FindPrimes 함수의 래퍼런스를 얻는다.

		if (find_primes == NULL) { return; }
		find_primes(3, 1000000);

		dlclose(handle);
	}

	int main()
	{
		printf("메인 입니다.");

		emscripten_async_wget(
			"calculate_primes.wasm", // 내려받을 파일
			"calculate_primes.wasm", //시스템상의 파일명
			CalculatePrimes,		 // 성공 콜백 함수
			NULL					 //실패 콜백 함수
		);

		return 0;
	}


#ifdef __cplusplus
}
#endif // __cplusplus