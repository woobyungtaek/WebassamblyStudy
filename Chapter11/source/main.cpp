#include<cstdlib>
#include<ctime>
#include<emscripten.h>

#ifdef __cplusplus
extern "C"{
#endif

	void EMSCRIPTEN_KEEPALIVE SeedRandomNumberGenerator() { srand(time(NULL)); }

	int EMSCRIPTEN_KEEPALIVE GetRandomNumber(int range) { return (rand() % range); }

#ifdef __cplusplus
}
#endif
