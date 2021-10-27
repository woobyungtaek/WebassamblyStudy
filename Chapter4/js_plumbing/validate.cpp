#include <cstdlib>
#include <cstring>

#ifdef  __EMSCRIPTEN_
#include<emscripten.h>
#endif //  __EMSCRIPTEN_

#ifdef  __cplusplus
//컴파일러가 네임 맹글링을 하지 않는다.
extern "C"
{
#endif
	//Webassambly 함수 구현

	/// <summary>
	/// ValidateName, Category 함수에 전달된 값이 있는지 확인하는 값
	/// </summary>
	/// <param name="value"> 전달 된 값</param>
	/// <param name="error_message"> 검증 오류 시 반환할 메시지</param>
	/// <param name="return_error_message"> 검증 오류 시 오류 메시지를 담을 버퍼 </param>
	/// <returns></returns>
	int ValidateValueProvided(const char* value, const char* error_message, char* return_error_message)
	{
		if ((value == NULL) || (value[0] == '\0'))
		{
			strcpy(return_error_message, error_message);
			return 0; // 오류 없음
		}

		return 1;	// 오류 있음
	}

	/// <summary>
	/// 카테고리 Id가 올바른지 체크
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

#ifdef  __EMSCRIPTEN
	EMSCRIPTEN_KEEPAWLIVE
#endif //  따로 Export옵션을 주지 않아도 자동으로 익스포트 함수 목록에 추가 된다.

		/// <summary>
		/// 상품명 검증
		/// </summary>
		/// <param name="name"></param>
		/// <param name="maximum_length"></param>
		/// <param name="return_error_message"></param>
		/// <returns></returns>
		int ValidateName(char* name, int maximum_length, char* return_error_message)
	{
		if (ValidateValueProvided(name, "The Product Name must be provided", return_error_message) == 0)
		{
			return 0;
		}

		if (strlen(name) > maximum_length)
		{
			strcpy(return_error_message, "The Product Name is too long");
			return 0;
		}

		return 1;
	}


#ifdef  __EMSCRIPTEN
	EMSCRIPTEN_KEEPAWLIVE
#endif //  따로 Export옵션을 주지 않아도 자동으로 익스포트 함수 목록에 추가 된다.
		int ValidateCategory(char* category_id, int* valid_category_ids, int array_length, char* return_error_message)
	{
		if (ValidateValueProvided(category_id, "A Product Category must be selected.", return_error_message) == 0)
		{
			return 0;
		}

		if ((valid_category_ids == NULL) || (array_length == 0))
		{
			strcpy(return_error_message, "There are no Product Categories available.");
			return 0;
		}

		if (IsCategoryIdInArray(category_id, valid_category_ids, array_length) == 0)
		{
			strcpy(return_error_message, "The selected Product Category is not valid.");
			return 0;
		}

		return 1;
	}

#ifdef __cplusplus
}
#endif //  __cplusplus

