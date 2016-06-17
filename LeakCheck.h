#include <cstdlib>
#include <crtdbg.h>
#include <iostream>

#ifdef _DEBUG
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__ )
#endif

void LeakCheck( int _nLeakNumber = NULL )
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#ifdef _DEBUG
	_crtBreakAlloc = _nLeakNumber;
#endif
	// ???�� �߰ߵ� ���� ��ȣ�� ������ �ٽ� ����� �Ѵ�.

	
	_CrtDumpMemoryLeaks();
}