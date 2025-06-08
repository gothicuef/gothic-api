// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZNET__WIN32_H__VER3__
#define __ZNET__WIN32_H__VER3__

namespace Gothic_II_Addon {

  // sizeof 10h
  struct zTNetAddress {
    zOPERATORS_DECLARATION()

    unsigned short Protocol; // sizeof 02h    offset 00h
    union {
      struct {
        unsigned short Port; // sizeof 02h    offset 00h
        unsigned long IP;    // sizeof 04h    offset 04h
      } INET; // sizeof 08h    offset 04h
      struct {
        unsigned char Net[4];  // sizeof 04h    offset 00h
        unsigned char Node[6]; // sizeof 06h    offset 04h
        unsigned short Socket; // sizeof 02h    offset 0Ah
      } IPX; // sizeof 0Ch    offset 0Ch
    };

    zTNetAddress() {}

    // user API
    #if __has_include("zTNetAddress.inl")
    #include "zTNetAddress.inl"
    #endif
  };

  // sizeof 08h
  struct zTNetBufferInfo {
    zOPERATORS_DECLARATION()

    int inPackets; // sizeof 04h    offset 00h
    int inBytes;   // sizeof 04h    offset 04h

    zTNetBufferInfo() {}

    // user API
    #if __has_include("zTNetBufferInfo.inl")
    #include "zTNetBufferInfo.inl"
    #endif
  };

  // sizeof 18h
  struct zTNetPacket {
    zOPERATORS_DECLARATION()

    zTNetAddress From;       // sizeof 10h    offset 00h
    unsigned long timestamp; // sizeof 04h    offset 10h
    unsigned long size;      // sizeof 04h    offset 14h
    unsigned char* Data;     // sizeof 04h    offset 18h

    zTNetPacket() {}

    // user API
    #if __has_include("zTNetPacket.inl")
    #include "zTNetPacket.inl"
    #endif
  };

  // sizeof 10h
  struct zTNetTimeout {
    zOPERATORS_DECLARATION()

    unsigned long getHostAddress; // sizeof 04h    offset 00h
    unsigned long getHostName;    // sizeof 04h    offset 04h
    unsigned long getService;     // sizeof 04h    offset 08h
    unsigned long Connect;        // sizeof 04h    offset 0Ch

    zTNetTimeout() {}

    // user API
    #if __has_include("zTNetTimeout.inl")
    #include "zTNetTimeout.inl"
    #endif
  };

} // namespace Gothic_II_Addon

#endif // __ZNET__WIN32_H__VER3__