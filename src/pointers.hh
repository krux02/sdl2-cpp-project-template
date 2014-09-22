#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

#define define_unique_pointer(NAME, TYPE, DESTRUCT)                                                \
    struct NAME : public std::unique_ptr<TYPE, void (*)(TYPE *)> {                                 \
        NAME(TYPE *surface) : std::unique_ptr<TYPE, void (*)(TYPE *)>{ surface, DESTRUCT } {}      \
    };

define_unique_pointer(UniqueFormat, SDL_PixelFormat, SDL_FreeFormat)
define_unique_pointer(UniqueCursor, SDL_Cursor, SDL_FreeCursor)
define_unique_pointer(UniquePalette, SDL_Palette, SDL_FreePalette)
define_unique_pointer(UniqueRWops, SDL_RWops, SDL_FreeRW)
define_unique_pointer(UniqueSurface, SDL_Surface, SDL_FreeSurface)

define_unique_pointer(UniqueTexture, SDL_Texture, SDL_DestroyTexture)
define_unique_pointer(UniqueRenderer, SDL_Renderer, SDL_DestroyRenderer)
define_unique_pointer(UniqueWindow, SDL_Window, SDL_DestroyWindow)

define_unique_pointer(UniqueFont, TTF_Font, TTF_CloseFont)

#undef define_unique_pointer
