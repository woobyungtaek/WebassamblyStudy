#include <cstdlib>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
	extern void EMSCRIPTEN_KEEPALIVE FindPrimes(int start, int end);

	int main()
	{
		FindPrimes(3, 99);

		return 0;
	}

#ifdef __cplusplus
}
#endif // __cplusplus