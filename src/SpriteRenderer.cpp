//
// Created by nicolas on 19/01/17.
//

#include "../include/SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(unsigned int width, unsigned int height) {
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile("../resources/default.png")) {
        exit(EXIT_FAILURE);
    }
    texture->setRepeated(true);
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

SpriteRenderer::SpriteRenderer(SpriteSheet sheet, int i, int j) {
    sprite.setTexture(sheet.texture);
    sprite.setTextureRect(sf::IntRect(
            sheet.tile_width * i,
            sheet.tile_height * j,
            sheet.tile_width,
            sheet.tile_height
    ));
}