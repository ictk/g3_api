// g3_api_library.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "g3_api_library.h"

#pragma comment(lib,"libBASE.lib")
// ������ ������ �����Դϴ�.
G3_API_LIBRARY_API int ng3_api_library=0;

// ������ �Լ��� �����Դϴ�.
G3_API_LIBRARY_API int fng3_api_library(void)
{
	return 42;
}

// ������ Ŭ������ �������Դϴ�.
// Ŭ���� ���Ǹ� ������ g3_api_library.h�� �����Ͻʽÿ�.
Cg3_api_library::Cg3_api_library()
{
	return;
}
