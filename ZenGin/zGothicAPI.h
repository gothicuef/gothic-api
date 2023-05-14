// Supported with union (c) 2018-2022 Union team
// Licence: GNU General Public License

#ifndef __ZGOTHIC_API_H__
#define __ZGOTHIC_API_H__

#define cexport extern "C" __declspec( dllexport )
#define cppimport __declspec( dllimport )
#define cppexport __declspec( dllexport )

// shw32 allocator
#if !defined(__UNION_MEMORY_H__) && !defined(_UNION_API_DLL) && !defined(_UNION_API_LIB)
#define shi_import extern "C" __declspec( dllimport )
#pragma comment (lib, "Shw32.lib")
shi_import void* shi_malloc( unsigned int sz );
shi_import void* shi_calloc( unsigned int num, unsigned int sz );
shi_import void* shi_realloc( void* mem, unsigned int sz );
shi_import void shi_free( void* mem );
shi_import void shi_delete( void* mem );
shi_import unsigned int shi_msize( void* mem );
shi_import int shi_MemInitDefaultPool();

// native engine operators
inline void* operator new (size_t sz) {
  return shi_malloc( sz );
}

inline void* operator new []( size_t sz ) {
  return shi_malloc( sz );
}

inline void  operator delete (void* mem) {
  shi_free( mem );
}

inline void  operator delete []( void* mem ) {
  shi_free( mem ); 
}
#endif

#define Engine_G1  1
#define Engine_G1A 2
#define Engine_G2  3
#define Engine_G2A 4

// gothic api for Gothic I v1.08k_mod
#undef ENGINE
#define ENGINE Engine_G1
#include "Gothic_I_Classic/G1.h"

// gothic api for Gothic Sequel v1.12f (bin)
#undef ENGINE
#define ENGINE Engine_G1A
#include "Gothic_I_Addon/G1A.h"

// gothic api for Gothic II classic v1.30
#undef ENGINE
#define ENGINE Engine_G2
#include "Gothic_II_Classic/G2.h"

// gothic api for Gothic II NOTR v2.6 (fix)
#undef ENGINE
#define ENGINE Engine_G2A
#include "Gothic_II_Addon/G2A.h"

#endif // __ZGOTHIC_API_H__