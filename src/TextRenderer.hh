#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>

#include "pointers.hh"

class TextObject {
protected:
    std::string text;
    UniqueTexture texture;
    glm::ivec2 size;
    TextObject(std::string text, UniqueTexture texture, glm::ivec2 size) :
        text(std::move(text)), texture(std::move(texture)), size(size) {}
public:
    std::string Text() const { return text; }
    SDL_Texture* Texture() const { return texture.get(); }
    glm::ivec2 Size() const { return size; }

    friend class TextRenderer;
};


class TextRenderer {
protected:
    SDL_Renderer* r;
    UniqueFont font;
public:
    TextRenderer(SDL_Renderer* renderer, std::string fontfile, int ptsize) : r(renderer), font(TTF_OpenFont(fontfile.c_str(), ptsize)) {}

    TextObject BakeString(std::string text) const {
        UniqueSurface surface = TTF_RenderUTF8_Solid(font.get(), text.c_str(), { 255, 255, 255, 255 });
        glm::ivec2 size(surface->w, surface->h);
        UniqueTexture texture = SDL_CreateTextureFromSurface(r, surface.get());
        return {std::move(text), std::move(texture), size};
    }

    void RenderBaked(const TextObject& to, glm::ivec2 pos) const {
        glm::ivec2 size = to.Size();
        SDL_Rect dst = {pos.x,pos.y,size.x,size.y};
        SDL_RenderCopy(r, to.Texture(), nullptr, &dst);
    }

    void RenderDirect(std::string text, glm::ivec2 pos) const {
        RenderBaked( BakeString(std::move(text)), pos);
    }
};
