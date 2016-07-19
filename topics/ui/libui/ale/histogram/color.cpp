#include "color.h"
#include "libui/ui.h"
#include <cstdint>

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
    brush.R = r;
    brush.G = g;
    brush.B = b;
    brush.A = a;

    std::cout << "alpha " << brush.A << std::endl;
}

void Color::setCurrentBrush(uiDrawBrush b)
{
    brush = b;
}
