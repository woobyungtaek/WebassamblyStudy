#include <cstdlib>
#include <cstring>
#include <emscripten.h>

#ifdef  __cplusplus
extern "C"
{
#endif
	extern int  ValidateValueProvided(const char* value, const char* error_message);
	extern int  IsIdInArray(char* selected_id, int* valid_ids, int array_length);

	extern void UpdateHostAboutError	(const char* error_message);


	int	EMSCRIPTEN_KEEPALIVE ValidateName(char* name, int maximum_length)
	{
		if (ValidateValueProvided(name, "The Product Name must be provided") == 0)
		{
			return 0;
		}

		if (strlen(name) > maximum_length)
		{
			UpdateHostAboutError("The Product Name is too long");
			return 0;
		}

		return 1;
}

	int	EMSCRIPTEN_KEEPALIVE ValidateCategory(char* category_id, int* valid_category_ids, int array_length)
	{
		if (ValidateValueProvided(category_id, "A Product Category must be selected.") == 0)
		{
			return 0;
		}

		if ((valid_category_ids == NULL) || (array_length == 0))
		{
			UpdateHostAboutError("There are no Product Categories available.");
			return 0;
		}

		if (IsIdInArray(category_id, valid_category_ids, array_length) == 0)
		{
			UpdateHostAboutError("The selected Product Category is not valid.");
			return 0;
		}

		return 1;
	}

#ifdef __cplusplus
}
#endif

