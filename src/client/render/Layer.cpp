#include "render/Layer.h"

#include <iostream>
using namespace render;

Layer::Layer() =default;

Layer::~Layer() = default;

void Layer::load_texture(sf::Texture& texture, const std::string& path) {
    if (!texture.loadFromFile(path))
        throw std::runtime_error("Texture unfound : " + path);
}

void Layer::load_font(sf::Font& font, const std::string& path) {
    if (font.loadFromFile(path))
        throw std::runtime_error("Font unfound : " + path);
}