#include <cstdlib>
#include <emscripten.h>

#ifdef  __cplusplus
extern "C"
{
#endif
	extern void UpdateHostAboutError(const char* error_message);

	int EMSCRIPTEN_KEEPALIVE ValidateValueProvided(const char* value, const char* error_message)
	{
		if ((value == NULL) || (value[0] == '\0'))
		{
			UpdateHostAboutError(error_message);
			return 0; // 오류 없음
		}

		return 1;	// 오류 있음
	}

	int EMSCRIPTEN_KEEPALIVE IsIdInArray(char* selected_id, int* valid_ids, int array_length)
	{
		int id = atoi(selected_id);

		for (int index = 0; index < array_length; index++)
		{
			if (valid_ids[index] == id) { return 1; }
		}

		return 0;
	}


#ifdef __cplusplus
}
#endif

