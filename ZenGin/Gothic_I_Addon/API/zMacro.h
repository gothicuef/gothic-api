﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZMACRO_H__VER1__
#define __ZMACRO_H__VER1__
#include <stdexcept>
#include <crtversion.h>

namespace Gothic_I_Addon {
#define zRELEASE( obj ) { (obj)->Release(); obj = NULL; }
#define zADDREF( obj )  (obj)->AddRef()
#define zNEW( obj ) new obj
#define zDELETE( obj ) delete obj
#ifndef SAFE_DELETE
#define SAFE_DELETE( obj ) if( obj ) { delete obj; obj = 0; }
#endif
#ifdef UNION_MULTIPLATFORM
#define zCall( address )                        \
{                                               \
    __asm { mov eax, 0x00401000 }               \
    __asm { cmp dword ptr[eax], 0x8136D4A1 }    \
    __asm { jne endp }                          \
    XCALL( address )                            \
  endp:;                                        \
}
#else
#define zCall( address ) { XCALL( address ); }
#endif
#define zInit( call ) { call; }
#define zRTTI( type ) { return type; }
#ifndef __DONT_USE_VTABLE__
#define zPureCall = 0;
#else
#define zPureCall ;
#define virtual
#endif
#define RGBA(r,g,b,a)   ((zUINT32)(zUINT8)(a)|(zUINT32)(zUINT8)(b)<<8|(zUINT32)(zUINT8)(g)<<16|(zUINT32)(zUINT8)(r)<<24)
#define EXTRACT_R(rgba) (rgba		& 0xff)
#define EXTRACT_G(rgba) (rgba >> 8	& 0xff)
#define EXTRACT_B(rgba) (rgba >> 16 & 0xff)
#define EXTRACT_A(rgba) (rgba >> 24 & 0xff)

#define zMEMPOOL_VOLATILE_DECLARATION(classname)                                                    \
private:                                                                                            \
    static zCVolatileMemory<classname>& s_MemMan;                                                   \
public:                                                                                             \
    void *operator new( [[maybe_unused]] size_t s ) {                                               \
        return s_MemMan.Alloc();                                                                    \
    }                                                                                               \
                                                                                                    \
    void operator delete( void *p ) noexcept(false) {                                               \
       throw std::runtime_error("Can't delete an object of class " #classname  ".");                    \
    }                                                                                               \
                                                                                                    \
    void* operator new( unsigned int size , const char *classn , const char *file, int l ) {        \
        return shi_malloc( size );                                                                  \
    }                                                                                               \
                                                                                                    \
    void operator delete( void *ptr, const char *classn, const char *file, int line ) {             \
        shi_free( ptr );                                                                            \
    }                                                                                               \
                                                                                                    \
    static size_t PoolMark() { return s_MemMan.Mark(); }                                            \
    static void PoolRestore( size_t m=0 ) { s_MemMan.Restore(m); }                                  \
    static classname &PoolElement( int i ) { return s_MemMan.Element(i); }                          \
    static int PoolIndex( classname *o ) { return s_MemMan.Index(o); }                              \
    static int PoolLastAllocatedIndex() { return s_MemMan.LastAllocatedIndex(); }                   \
    void* operator new[]( size_t size ) {                                                           \
      return shi_malloc( size );                                                                    \
    }                                                                                               \
    void operator delete[]( void* mem ) {                                                           \
      shi_free( mem );                                                                              \
    }      

#define XCALL(uAddr)          \
	__asm { mov esp, ebp } 	    \
	__asm { pop ebp }           \
	__asm { mov eax, uAddr }    \
	__asm { jmp eax }


#define SafeDiv( a, b ) \
    ( b == 0.0 ? 0.0 : a / b )


#define sqr(a) (a * a)


#define CalcAngle(a, b)                     \
    if( b == 0.0f ) {                       \
      if( a == 0.0f )                       \
        return 0.0f;                        \
                                            \
      if( a > 0 )                           \
        return RAD90;                       \
      return RAD270;                        \
     }                                      \
                                            \
    if( a == 0.0f ) {                       \
      if( b > 0.0f )                        \
        return 0.0f;                        \
      return RAD180;                        \
    }                                       \
                                            \
    float angle = atan( SafeDiv( a, b ) );  \
    if( b < 0.0f )                          \
      angle += RAD180;                      \
    else if( a < 0.0f )                     \
      angle += RAD360;                      \
                                            \
    return angle;


#define RotAngle(a, b, c)                     \
    float radAngle = GetAngle##c();           \
    float length   = sqrt(sqr(a) + sqr(b));   \
    radAngle      += rad;                     \
    a              = sin(radAngle) * length;  \
    b              = cos(radAngle) * length;  \
    return *this;




    // ZMEMPOOL INTERFACE
    // memory pool declaration for gothic api containers
#define zMEMPOOL_DECLARATION_TEMPLATE( classname, address )                                \
    void *operator new( [[maybe_unused]] size_t s ) {                                      \
      return ((zCMemPoolBase*)address)->Alloc();                                           \
    }                                                                                      \
    void operator delete( void *p ) {                                                      \
      ((zCMemPoolBase*)address)->Free( p );                                                \
    }                                                                                      \
    void* operator new( unsigned int size, const char* classn, const char *file, int l ) { \
      zCMemPoolBase::SetMemDebug( classn, file, l );                                       \
      return shi_malloc( size );                                                           \
    }                                                                                      \
    void operator delete( void* ptr, const char* classn, const char* file, int line ) {    \
      shi_free( ptr );                                                                     \
    }                                                                                      \
    static void PreAlloc( size_t num, zBOOL force_oneblock = FALSE ) {                     \
      ((zCMemPoolBase*)address)->PreAlloc( num, force_oneblock );                          \
    }                                                                                      \
    void* operator new[]( size_t size ) {                                                  \
      return shi_malloc(size);                                                             \
    }                                                                                      \
    void operator delete[]( void* mem ) {                                                  \
      shi_free(mem);                                                                      \
    }                    



  // memory pool declaration for gothic api classes
#define zMEMPOOL_DECLARATION( classname, address )                                         \
    void* operator new( [[maybe_unused]] size_t s ){                                       \
      return ((zCMemPoolBase*)address)->Alloc();                                           \
    }                                                                                      \
    void operator delete( void* p ) {                                                      \
      ((zCMemPoolBase*)address)->Free( p );                                                \
    }                                                                                      \
    void* operator new( unsigned int size, const char* classn, const char* file, int l ) { \
      zCMemPoolBase::SetMemDebug( classn, file, l );                                       \
      return shi_malloc( size );                                                           \
    }                                                                                      \
    void  operator delete( void* ptr, const char *classn , const char *file ,int line ) {  \
      shi_free( ptr );                                                                     \
    }                                                                                       \
    static void PreAlloc( size_t num, int force_oneblock = FALSE ) {                       \
      ((zCMemPoolBase*)address)->PreAlloc( num, force_oneblock );                          \
    }                                                                                      \
    static void PoolAdd( classname *mem, int num_objects, int free = FALSE ) {             \
      ((zCMemPoolBase*)address)->PoolAdd( mem, num_objects, free );                        \
    }                                                                                      \
    void* operator new[]( size_t size ) {                                                  \
      return shi_malloc( size );                                                           \
    }                                                                                      \
    void operator delete[]( void* mem ) {                                                  \
      shi_free( mem );                                                                     \
    }



  // ZOBJECT INTERFACE
  // class declaration for gothic api zobject classes
#define zCLASS_DECLARATION( className )                               \
  static zCClassDef* classDef;                                        \
  void* operator new( size_t size ) {                                 \
    void* mem = shi_malloc( size );                                   \
    zCClassDef::ObjectCreated( (zCObject*)mem, className::classDef ); \
    return mem;                                                       \
  };                                                                  \
  void operator delete( void* mem ) {                                 \
    zCClassDef::ObjectDeleted( (zCObject*)mem, className::classDef ); \
    shi_free( mem );                                                  \
  };                                                                  \
  void* operator new[]( size_t size ) = delete;                       \
  void operator delete[]( void* mem ) = delete;                       



  // class declaration for union zobject classes
#define zCLASS_UNION_DECLARATION( className )     \
  static zCClassDef* classDef;                    \
  static zCObject* _CreateNewInstance( void );    \
  virtual zCClassDef* _GetClassDef( void ) const; \
  void* operator new( size_t size );              \
  void operator delete( void* mem );              \
  void* operator new[]( size_t size ) = delete;   \
  void operator delete[]( void* mem ) = delete;    


  // class definition for union zobject classes
#define zCLASS_UNION_DEFINITION( className, baseClassName, classFlags, archiveVersion )                                                         \
  zCClassDef* className::classDef = new zCClassDef( #className, #baseClassName, className::_CreateNewInstance, sizeof(className), 0, 0, "" ); \
  zCObject* className::_CreateNewInstance( void ) {                                                                                             \
    return new className;                                                                                                                       \
  }                                                                                                                                             \
  zCClassDef* className::_GetClassDef( void ) const {                                                                                           \
    return className::classDef;                                                                                                                 \
  };                                                                                                                                            \
  void* className::operator new( size_t size ) {                                                                                                \
    void* mem = shi_malloc( size );                                                                                                         \
    zCClassDef::ObjectCreated( (zCObject*)mem, className::classDef );                                                                           \
    return mem;                                                                                                                                 \
  };                                                                                                                                            \
  void className::operator delete( void* mem ) {                                                                                                \
    zCClassDef::ObjectDeleted( (zCObject*)mem, className::classDef );                                                                           \
    shi_free( mem );                                                                                                                   \
  };



  // COLLISION INTERFACE
  // class declaration for gothic api collision object classes
#define zCOLLISION_OBJECT_DECLARATION( className )         \
    static zCCollisionObjectDef* S_GetCollObjClass(void) { \
      return className::s_oCollObjClass;                   \
    };                                                     \
    static zCCollisionObjectDef* s_oCollObjClass; 


  // class declaration for union collision object classes
#define zCOLLISION_OBJECT_UNION_DECLARATION( className )                                                \
  static  zCCollisionObjectDef* S_GetCollObjClass(void)      { return &(className::s_oCollObjClass); }; \
  virtual zCCollisionObjectDef* GetCollObjClass(void) const  { return &(className::s_oCollObjClass); }; \
  static  zCCollisionObjectDef  s_oCollObjClass;                                                        \
  static  zCCollisionObject*    _CreateNewInstance(void);


  // class definition for union collision object classes
#define zCOLLISION_OBJECT_UNION_DEFINITION( className, isVolatile )                           \
  zCCollisionObjectDef className::s_oCollObjClass(isVolatile, className::_CreateNewInstance); \
  zCCollisionObject* className::_CreateNewInstance(void) {                                    \
    return new className;                                                                     \
  }

#if defined(_VC_CRT_MAJOR_VERSION) && defined(_MSVC_LANG) && _VC_CRT_MAJOR_VERSION > 10 && _MSVC_LANG > 199711L
#define InheritableInterfaceObject zIInheritableInterfaceObject&&
#else
#define InheritableInterfaceObject zIInheritableInterfaceObject
#endif

    struct zIInheritableInterfaceObject {};
#define zDefineInheritableCtor(className) className(InheritableInterfaceObject) 
#define zCtor(baseClassName) baseClassName(zIInheritableInterfaceObject())

#define zOPERATORS_DECLARATION()        \
  void* operator new( size_t size ) {   \
    return shi_malloc( size );          \
  };                                    \
  void operator delete( void* mem ) {   \
    shi_free( mem );                    \
  };                                    \
  void* operator new[]( size_t size ) { \
    return shi_malloc( size );          \
  };                                    \
  void operator delete[]( void* mem ) { \
    shi_free( mem );                    \
  };
} // namespace Gothic_I_Addon

#endif // __ZMACRO_H__VER1__