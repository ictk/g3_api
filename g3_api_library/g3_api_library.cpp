// g3_api_library.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "g3_api_library.h"

#pragma comment(lib,"libBASE.lib")
// 내보낸 변수의 예제입니다.
G3_API_LIBRARY_API int ng3_api_library=0;

// 내보낸 함수의 예제입니다.
G3_API_LIBRARY_API int fng3_api_library(void)
{
	return 42;
}

// 내보낸 클래스의 생성자입니다.
// 클래스 정의를 보려면 g3_api_library.h를 참조하십시오.
Cg3_api_library::Cg3_api_library()
{
	return;
}
