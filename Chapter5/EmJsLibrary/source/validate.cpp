#include <cstdlib>
#include <cstring>

//#ifdef  __EMSCRIPTEN_
#include<emscripten.h>
//#endif //  __EMSCRIPTEN_

#ifdef  __cplusplus
//�����Ϸ��� ���� �ͱ۸��� ���� �ʴ´�.
extern "C"
{
#endif
	// �ڹ� ��ũ��Ʈ �Լ� ����
	extern void UpdateHostAboutError(const char* error_message);


	//Webassambly �Լ� ����

	/// <summary>
	/// ValidateName, Category �Լ��� ���޵� ���� �ִ��� Ȯ���ϴ� ��
	/// </summary>
	/// <param name="value"> ���� �� ��</param>
	/// <param name="error_message"> ���� ���� �� ��ȯ�� �޽���</param>
	/// <param name="return_error_message"> ���� ���� �� ���� �޽����� ���� ���� </param>
	/// <returns></returns>
	int ValidateValueProvided(const char* value, const char* error_message)
	{
		if ((value == NULL) || (value[0] == '\0'))
		{
			UpdateHostAboutError(error_message);
			return 0; // ���� ����
		}

		return 1;	// ���� ����
	}

	/// <summary>
	/// ī�װ� Id�� �ùٸ��� üũ
	/// </summary>
	/// <param name="selected_category_id"></param>
	/// <param name="valid_category_ids"></param>
	/// <param name="array_length"></param>
	/// <returns></returns>
	int IsCategoryIdInArray(char* selected_category_id, int* valid_category_ids, int array_length)
	{
		int category_id = atoi(selected_category_id);

		for (int index = 0; index < array_length; index++)
		{
			if (valid_category_ids[index] == category_id) { return 1; }
		}

		return 0;
	}


	/// <summary>
	/// ��ǰ�� ����
	/// </summary>
	/// <param name="name"></param>
	/// <param name="maximum_length"></param>
	/// <param name="return_error_message"></param>
	/// <returns></returns>

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

		if (IsCategoryIdInArray(category_id, valid_category_ids, array_length) == 0)
		{
			UpdateHostAboutError("The selected Product Category is not valid.");
			return 0;
		}

		return 1;
	}

#ifdef __cplusplus
}
#endif //  __cplusplus

