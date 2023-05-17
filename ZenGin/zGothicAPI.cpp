#include <Windows.h>
#include <crtversion.h>
#include <stdio.h>



static int GetGameVersion() {
  HMODULE module = GetModuleHandle( nullptr );
  const byte* bytecode = (byte*)module + 0x1000;

  const byte bytecodeForG1[]  = { 0xC7, 0x05, 0xEC, 0xE0, 0x85, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3 };
  const byte bytecodeForG1A[] = { 0xA1, 0xD4, 0x36, 0x81, 0x00, 0xA3, 0xFC, 0x24, 0x8A, 0x00, 0xC3 };
  const byte bytecodeForG2[]  = { 0xC7, 0x05, 0x5C, 0x38, 0x8B, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3 };
  const byte bytecodeForG2A[] = { 0xC7, 0x05, 0x14, 0x1E, 0x8C, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3 };

  if( memcmp( bytecode, bytecodeForG1,  sizeof( bytecodeForG1  ) ) == 0 ) return 1;
  if( memcmp( bytecode, bytecodeForG1A, sizeof( bytecodeForG1A ) ) == 0 ) return 2;
  if( memcmp( bytecode, bytecodeForG2,  sizeof( bytecodeForG2  ) ) == 0 ) return 3;
  if( memcmp( bytecode, bytecodeForG2A, sizeof( bytecodeForG2A ) ) == 0 ) return 4;

  return 0;
}


static const char* DynamicCastNamespace = nullptr;
static int DynamicCastNamespaceLength = 0;


static int DynamicCastStrcmp( const char* str1, const char* str2 ) {
  if( memcmp( str1, DynamicCastNamespace, DynamicCastNamespaceLength ) == 0 )
    str1 += DynamicCastNamespaceLength;

  if( memcmp( str2, DynamicCastNamespace, DynamicCastNamespaceLength ) == 0 )
    str2 += DynamicCastNamespaceLength;

  return strcmp( str1, str2 );
}


static void CallPatch( unsigned int address, unsigned int callTarget ) {
  unsigned int* offset = (unsigned int*)(address + 1);
  DWORD protection = PAGE_READWRITE;
  VirtualProtect( offset, 4, protection, &protection );
  *offset = callTarget - address - 5;
  VirtualProtect( offset, 4, protection, &protection );
}


static void SetJump( unsigned int address, unsigned int jumpTarget ) {
#pragma pack(push, 1)
  struct Jump {
    byte Instruction;
    unsigned int Offset;
  };
#pragma pack(pop)

  Jump* jump = (Jump*)address;

  DWORD protection = PAGE_READWRITE;
  VirtualProtect( jump, sizeof( Jump ), protection, &protection);
  jump->Instruction = 0xE9;
  jump->Offset = jumpTarget - address - 5;
  VirtualProtect( jump, sizeof( Jump ), protection, &protection );
}


#if _DLL == 1
static void* GetDynamicCastAddress() {
  HMODULE runtime = nullptr;
  GetModuleHandleEx(
    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
    (LPCTSTR)memset,
    &runtime );

  if( runtime == nullptr )
    return nullptr;

  return GetProcAddress( runtime, "__RTDynamicCast" );
}
#else
extern void* __RTDynamicCast( void*, long, void*, void*, int );
static void* GetDynamicCastAddress() {
  return __RTDynamicCast;
}
#endif


static void WriteLogMessage( const char* message ) {
  DWORD dw;
  WriteConsole( GetStdHandle( STD_OUTPUT_HANDLE ), message, strlen( message ), &dw, nullptr);
}


static bool DynamicCastPatch() {
  int gameVersion = GetGameVersion();
  if( gameVersion == 0 ) {
    WriteLogMessage( "Unsupported game version!" );
    return false;
  }

  void* rtDynamicCast = GetDynamicCastAddress();
  if( rtDynamicCast == nullptr ) {
    WriteLogMessage( "__RTDynamicCast not found!" );
    return false;
  }

  auto callTarget = (unsigned int)DynamicCastStrcmp;
  auto jumpFrom = (unsigned int)rtDynamicCast;
  if( gameVersion == 1 ) {
    CallPatch( 0x00777249, callTarget );
    CallPatch( 0x007772A9, callTarget );
    CallPatch( 0x007772DA, callTarget );
    CallPatch( 0x00777342, callTarget );
    CallPatch( 0x007773A5, callTarget );
    CallPatch( 0x007773DA, callTarget );
    CallPatch( 0x0077747A, callTarget );
    DynamicCastNamespace = "Gothic_I_Classic@@";
    DynamicCastNamespaceLength = strlen( DynamicCastNamespace );
    SetJump( jumpFrom, 0x0077709A );
  }
  else if( gameVersion == 2 ) {
    CallPatch( 0x007BB009, callTarget );
    CallPatch( 0x007BB069, callTarget );
    CallPatch( 0x007BB09A, callTarget );
    CallPatch( 0x007BB102, callTarget );
    CallPatch( 0x007BB165, callTarget );
    CallPatch( 0x007BB19A, callTarget );
    CallPatch( 0x007BB23A, callTarget );
    DynamicCastNamespace = "Gothic_I_Addon@@";
    DynamicCastNamespaceLength = strlen( DynamicCastNamespace );
    SetJump( jumpFrom, 0x007BAE5A );
  }
  else if( gameVersion == 3 ) {
    CallPatch( 0x007C4729, callTarget );
    CallPatch( 0x007C4789, callTarget );
    CallPatch( 0x007C47BA, callTarget );
    CallPatch( 0x007C4822, callTarget );
    CallPatch( 0x007C4885, callTarget );
    CallPatch( 0x007C48BA, callTarget );
    CallPatch( 0x007C495A, callTarget );
    DynamicCastNamespace = "Gothic_II_Classic@@";
    DynamicCastNamespaceLength = strlen( DynamicCastNamespace );
    SetJump( jumpFrom, 0x007C457A );
  }
  else if( gameVersion == 4 ) {
    CallPatch( 0x007D0BE9, callTarget );
    CallPatch( 0x007D0C49, callTarget );
    CallPatch( 0x007D0C7A, callTarget );
    CallPatch( 0x007D0CE2, callTarget );
    CallPatch( 0x007D0D45, callTarget );
    CallPatch( 0x007D0D7A, callTarget );
    CallPatch( 0x007D0E1A, callTarget );
    DynamicCastNamespace = "Gothic_II_Addon@@";
    DynamicCastNamespaceLength = strlen( DynamicCastNamespace );
    SetJump( jumpFrom, 0x007D0A3A );
  }

  return true;
}


bool DynamicCastPatchApplied = DynamicCastPatch();