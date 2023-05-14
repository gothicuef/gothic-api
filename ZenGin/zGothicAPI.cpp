#include <Windows.h>
#include <stdio.h>
#include "zGothicAPI.h"

// static RTTI DynamicCast pointer
#if _DLL != 1
extern void* __cdecl __RTDynamicCast( void*, long, void*, void*, int );
cexport void* RTDynamicCast_MT = (void*)__RTDynamicCast;
#endif


const char* GothicNamespace = nullptr;
int GothicNamespaceLength = 0;


__declspec(noinline) int strcmp_dcast( const char* str1, const char* str2 ) {
  printf( "> %s  %s", str1, str2 );
  if( memcmp( str1, GothicNamespace, GothicNamespaceLength ) == 0 )
    str1 += GothicNamespaceLength;

  if( memcmp( str2, GothicNamespace, GothicNamespaceLength ) == 0 )
    str2 += GothicNamespaceLength;

  return strcmp( str1, str2 );
  while( true ) {
    int value = *str1 - *str2;
    if( value != 0 )
      return value;

    if( *str1 == 0 )
      break;

    str1++;
    str2++;
  }

  return 0;
}


bool ApplyRTTIPatch() {
#if _DEBUG
  HMODULE ucrtbase = GetModuleHandle( "ucrtbased.dll" );
#else
  HMODULE ucrtbase = GetModuleHandle( "ucrtbase.dll" );
#endif
  if( !ucrtbase ) {
    printf( "ucrtbase.dll not found\n" );
    return false;
  }

  void* imp_strcmp = GetProcAddress( ucrtbase, "strcmp" );
  if( !imp_strcmp ) {
    printf( "strcmp not found\n" );
    return false;
  }

  GothicNamespace = "Gothic_II_Addon@@";
  GothicNamespaceLength = strlen( GothicNamespace );

  DWORD protection = PAGE_READWRITE;
  VirtualProtect( imp_strcmp, 6, protection, &protection );
  byte* bytecode = (byte*)imp_strcmp;
  bytecode[0] = 0xFF;
  bytecode[1] = 0x25;
  *(DWORD*)&bytecode[2] = (DWORD)&strcmp_dcast;
  VirtualProtect( imp_strcmp, 6, protection, &protection );

  printf( "rtti patch successfully applied\n" );
  return true;
}

bool RTTIPatchWasApplied = ApplyRTTIPatch();