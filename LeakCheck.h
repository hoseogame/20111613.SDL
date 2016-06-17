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
	// ???에 발견된 오류 번호를 넣은후 다시 디버깅 한다.

	
	_CrtDumpMemoryLeaks();
}