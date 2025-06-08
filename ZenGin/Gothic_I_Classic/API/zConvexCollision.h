﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZCONVEX_COLLISION_H__VER0__
#define __ZCONVEX_COLLISION_H__VER0__

namespace Gothic_I_Classic {

  // sizeof 08h
  class zCCacheIndex {
  public:
    zOPERATORS_DECLARATION()

    zCVob* voba; // sizeof 04h    offset 00h
    zCVob* vobb; // sizeof 04h    offset 04h

    zCCacheIndex() {}

    // user API
    #if __has_include("zCCacheIndex.inl")
    #include "zCCacheIndex.inl"
    #endif
  };

  // sizeof 10h
  class zCConvexCollisionCache {
  public:
    zMEMPOOL_DECLARATION( zCConvexCollisionCache, 0x0087367C )

    zVEC3 planeNormal; // sizeof 0Ch    offset 00h
    int invert;        // sizeof 04h    offset 0Ch

    zCConvexCollisionCache() {}
    void zCConvexCollisionCache_OnInit( zCCacheIndex const& ) zCall( 0x005406D0 );
    zCConvexCollisionCache( zCCacheIndex const& a0 )          zInit( zCConvexCollisionCache_OnInit( a0 ));

    // user API
    #if __has_include("zCConvexCollisionCache.inl")
    #include "zCConvexCollisionCache.inl"
    #endif
  };

  // sizeof 1Ch
  class zCConvexPrimitive {
  public:
    zOPERATORS_DECLARATION()

    zTBBox3D bbox3Dlocal; // sizeof 18h    offset 04h

    zDefineInheritableCtor( zCConvexPrimitive ) {}
    zCConvexPrimitive() {}
    void PointNearestToPlane( zVEC3&, zVEC3 const&, zMAT4 const&, zMAT3 const& ) const                                                                           zCall( 0x0053F810 );
    void PointNearestToPlane( zVEC3&, zVEC3 const&, zMAT4 const& ) const                                                                                         zCall( 0x00540290 );
    void Draw( zMAT4 const&, zCOLOR, zCCamera const* ) const                                                                                                     zCall( 0x00540720 );
    static int CheckCollision( zCConvexPrimitive const*, zCConvexPrimitive const*, zMAT4 const&, zMAT4 const&, zCConvexCollisionCache*, zVEC3&, float&, zVEC3& ) zCall( 0x0053F8C0 );
    static float Distance( zCConvexPrimitive const*, zCConvexPrimitive const*, zMAT4 const&, zMAT4 const&, zVEC3 const&, zVEC3&, zVEC3& )                        zCall( 0x00540360 );
    static zCConvexCollisionCache* GetCache( void const*, void const* )                                                                                          zCall( 0x00540520 );
    static void DrawLine( zVEC3 const&, zVEC3 const& )                                                                                                           zCall( 0x00540800 );
    static void DrawLineStrip( zVEC3 const& )                                                                                                                    zCall( 0x00540940 );
    virtual ~zCConvexPrimitive()                                                                                                                                 zCall( 0x00540E40 );
    virtual void PointNearestToPlaneLocal( zVEC3 const&, zVEC3& ) const                                                                                          zPureCall;
    virtual void GetCenterLocal( zVEC3& ) const                                                                                                                  zCall( 0x00540C80 );
    virtual int PointIsInLocal( zVEC3 const& ) const                                                                                                             zPureCall;
    virtual int SymetrySphere() const                                                                                                                            zCall( 0x00540DD0 );
    virtual int SymetryRotation( zVEC3& ) const                                                                                                                  zCall( 0x00540DE0 );
    virtual void UpdateBBox()                                                                                                                                    zCall( 0x00540DF0 );
    virtual void DrawVirtual() const                                                                                                                             zCall( 0x00540A00 );

    // user API
    #if __has_include("zCConvexPrimitive.inl")
    #include "zCConvexPrimitive.inl"
    #endif
  };

  // sizeof 1Ch
  class zCConvexPrimitiveUnitSphere : public zCConvexPrimitive {
  public:
    zOPERATORS_DECLARATION()


    void zCConvexPrimitiveUnitSphere_OnInit()                           zCall( 0x00540C30 );
    zCConvexPrimitiveUnitSphere() : zCtor( zCConvexPrimitive )          zInit( zCConvexPrimitiveUnitSphere_OnInit() );
    virtual ~zCConvexPrimitiveUnitSphere()                              zCall( 0x00540DC0 );
    virtual void PointNearestToPlaneLocal( zVEC3 const&, zVEC3& ) const zCall( 0x00540CC0 );
    virtual int PointIsInLocal( zVEC3 const& ) const                    zCall( 0x00540FA0 );
    virtual int SymetrySphere() const                                   zCall( 0x00540CE0 );
    virtual int SymetryRotation( zVEC3& ) const                         zCall( 0x00540CF0 );
    virtual void UpdateBBox()                                           zCall( 0x00540D30 );
    virtual void DrawVirtual() const                                    zCall( 0x00540E80 );

    // static properties
    static zCConvexPrimitiveUnitSphere& s_unitSphere;

    // user API
    #if __has_include("zCConvexPrimitiveUnitSphere.inl")
    #include "zCConvexPrimitiveUnitSphere.inl"
    #endif
  };

  // sizeof 38h
  class zCConvexPrimitiveScaleTrans : public zCConvexPrimitive {
  public:
    zOPERATORS_DECLARATION()

    zVEC3 scale;                 // sizeof 0Ch    offset 1Ch
    zVEC3 translation;           // sizeof 0Ch    offset 28h
    zCConvexPrimitive* original; // sizeof 04h    offset 34h

    zDefineInheritableCtor( zCConvexPrimitiveScaleTrans ) : zCtor( zCConvexPrimitive ) {}
    zCConvexPrimitiveScaleTrans() : zCtor( zCConvexPrimitive ) {}
    void zCConvexPrimitiveScaleTrans_OnInit( zCConvexPrimitive*, zVEC3 const&, zVEC3 const& )                              zCall( 0x00540FE0 );
    zCConvexPrimitiveScaleTrans( zCConvexPrimitive* a0, zVEC3 const& a1, zVEC3 const& a2 ) : zCtor( zCConvexPrimitive )    zInit( zCConvexPrimitiveScaleTrans_OnInit( a0, a1, a2 ));
    virtual ~zCConvexPrimitiveScaleTrans()                                                                                 zCall( 0x00541090 );
    virtual void PointNearestToPlaneLocal( zVEC3 const&, zVEC3& ) const                                                    zCall( 0x005410A0 );
    virtual void GetCenterLocal( zVEC3& ) const                                                                            zCall( 0x005411B0 );
    virtual int PointIsInLocal( zVEC3 const& ) const                                                                       zCall( 0x00541160 );
    virtual void UpdateBBox()                                                                                              zCall( 0x005411F0 );
    virtual void DrawVirtual() const                                                                                       zCall( 0x00541240 );

    // user API
    #if __has_include("zCConvexPrimitiveScaleTrans.inl")
    #include "zCConvexPrimitiveScaleTrans.inl"
    #endif
  };

  // sizeof 3Ch
  class zCConvexPrimitiveEllipsoid : public zCConvexPrimitiveScaleTrans {
  public:
    zOPERATORS_DECLARATION()

    int symetric; // sizeof 04h    offset 38h

    zCConvexPrimitiveEllipsoid() : zCtor( zCConvexPrimitiveScaleTrans ) {}
    void zCConvexPrimitiveEllipsoid_OnInit( zTBBox3D const&, int )                                        zCall( 0x005412F0 );
    zCConvexPrimitiveEllipsoid( zTBBox3D const& a0, int a1 ) : zCtor( zCConvexPrimitiveScaleTrans )       zInit( zCConvexPrimitiveEllipsoid_OnInit( a0, a1 ));
    void Snap()                                                                                           zCall( 0x005414C0 );
    virtual ~zCConvexPrimitiveEllipsoid()                                                                 zCall( 0x005414B0 );
    virtual int SymetryRotation( zVEC3& ) const                                                           zCall( 0x00541440 );

    // user API
    #if __has_include("zCConvexPrimitiveEllipsoid.inl")
    #include "zCConvexPrimitiveEllipsoid.inl"
    #endif
  };

} // namespace Gothic_I_Classic

#endif // __ZCONVEX_COLLISION_H__VER0__