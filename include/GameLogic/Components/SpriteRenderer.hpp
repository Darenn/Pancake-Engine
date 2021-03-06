//
// Created by Darenn on 17/01/2017.
//

#ifndef PANCAKE_SPRITERENDERER_HPP
#define PANCAKE_SPRITERENDERER_HPP

#include "Component.hpp"
#include "../../Graphics/SpriteSheet.hpp"
#include <SFML/Graphics.hpp>

class SpriteSheet;
namespace PancakeEngine {

    class SpriteRenderer : public Component {
    public:
        /**
         * Create sprite with default texture
         * @param width
         * @param height
         */
        SpriteRenderer(unsigned int width, unsigned int height);

        /**
         * Create sprite from a SpriteSheet 'sheet'
         * Take the sprite at the column i and row j
         * @param sheet the SpriteSheet
         * @param i the column index
         * @param j the row index
         */
        SpriteRenderer(SpriteSheet& sheet, unsigned int i, unsigned int j);

    private:
        friend class Window;

        sf::Sprite sprite;
    };
}

#endif //PANCAKE_SPRITERENDERER_HPP
