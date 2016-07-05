#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include "libui/ui.h"

#include <iostream>

/**
 * @brief A set of colors.
 */
class Color {
    public:
        Color()
        {
            setSolidBrush(&brush, white, 1.0);
        }
        static const int white{0xFFFFFF};
        static const int black{0x000000};
        static const int dodgerBlue{0x1E90FF};

        static void setSolidBrush(uiDrawBrush *brush, uint32_t color, double alpha);
        void setCurrentBrush(uiDrawBrush brush);
        void setCurrentBrush(double r, double g, double b, double a);
        uiDrawBrush getCurrentBrush() {
            std::cout << "get r" << brush.R << std::endl;
            return brush;
        }
    private:
        uiDrawBrush brush{uiDrawBrushTypeSolid,0,0,0};
};

#endif
