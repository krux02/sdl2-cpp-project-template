// NO INCLUDE GUARDS ON PURPOSE

#include <memory>


#define define_unique_pointer(NAME, TYPE, DESTRUCT)                                                \
    struct NAME : public std::unique_ptr<TYPE, void (*)(TYPE *)> {                                 \
        NAME(TYPE *surface) : std::unique_ptr<TYPE, void (*)(TYPE *)>{ surface, DESTRUCT } {}      \
    };

// define unique pointers only when corresponding sdl_header is already included

#ifdef _SDL_H
#ifndef _SDL_H_PTR
#define _SDL_H_PTR

define_unique_pointer(UniqueFormat, SDL_PixelFormat, SDL_FreeFormat)
define_unique_pointer(UniqueCursor, SDL_Cursor, SDL_FreeCursor)
define_unique_pointer(UniquePalette, SDL_Palette, SDL_FreePalette)
define_unique_pointer(UniqueRWops, SDL_RWops, SDL_FreeRW)
define_unique_pointer(UniqueSurface, SDL_Surface, SDL_FreeSurface)
define_unique_pointer(UniqueTexture, SDL_Texture, SDL_DestroyTexture)
define_unique_pointer(UniqueRenderer, SDL_Renderer, SDL_DestroyRenderer)
define_unique_pointer(UniqueWindow, SDL_Window, SDL_DestroyWindow)

#endif // _SDL_H_PTR
#endif // _SDL_H

#ifdef _SDL_TTF_H
#ifndef _SDL_TTF_H_PTR
#define _SDL_TTF_H_PTR

define_unique_pointer(UniqueFont, TTF_Font, TTF_CloseFont)

#endif // _SDL_TTH_H_PTR
#endif // _SDL_TTF_H

#ifdef _SDL_MIXER_H
#ifndef _SDL_MIXER_H_PTR
#define _SDL_MIXER_H_PTR

define_unique_pointer(UniqueChunk, Mix_Chunk, Mix_FreeChunk)
define_unique_pointer(UniqueMusic, Mix_Music, Mix_FreeMusic)

#endif // _SDL_MIXER_H_PTR
#endif // _SDL_MIXER_H

// clean global namespace from macros that should only be used within this file
#undef define_unique_pointer
