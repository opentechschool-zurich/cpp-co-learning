#include "color.h"
#include "libui/ui.h"
#include <cstdint>

#include <iostream>

/**
 * @brief set the brush in the parameter with the hex color.
 *
 * @todo:
 * - Probably rename it to getSolidBrush().
 */
void Color::setSolidBrush(uiDrawBrush *brush, uint32_t color, double alpha)
{
	uint8_t component;

	brush->Type = uiDrawBrushTypeSolid;
	component = (uint8_t) ((color >> 16) & 0xFF);
	brush->R = ((double) component) / 255;
	component = (uint8_t) ((color >> 8) & 0xFF);
	brush->G = ((double) component) / 255;
	
	brush->B = ((double) component) / 255;
	brush->A = alpha;
}

/**
 * @brief Set current class brush.
 */
void Color::setCurrentBrush(double r, double g, double b, double a) {
    std::cout << "in r " << r << std::endl;
    std::cout << "in g " << g << std::endl;
    std::cout << "in b " << b << std::endl;
    brush.R = r;
    brush.G = g;
    brush.B = b;
    brush.A = a;
}

void Color::setCurrentBrush(uiDrawBrush b)
{
    brush = b;
}
