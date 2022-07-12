//
// Created by Simone on 06/07/2022.
//

#pragma once


/**
             * RGB565 image
             * @tparam T
             * @tparam width
             * @tparam height
             */
template<uint16_t width, uint16_t height, typename T>
class Rgb565 : public AbstractImage<T, width, height, 3> {
public:

    /**
     * Update image data
     * @param data
     */
    void write(uint8_t *data) {
        uint16_t i = 0;

        for (uint16_t y = 0; y < height; y++) {
            const uint16_t rowOffset = y * width * 2;

            for (uint16_t x = 0, x < width * 2; x += 2) {
                uint16_t h = data[rowOffset + x];
                uint16_t l = data[rowOffset + x + 1];
                uint16_t p = (h << 8) | l;

                uint8_t r = (p & 0b1111100000000000) >> 11;
                uint8_t g = (p & 0b0000011111100000) >> 5;
                uint8_t b = (p & 0b0000000000011111);

                setAtIndex(i++, r, g, b);
            }
        }
    }

    /**
     * Set pixel at given index
     * @param index
     * @param r
     * @param g
     * @param b
     */
    void setAtIndex(uint16_t index, float r, float g, float b) {
        this->buffer[index + 0] = r;
        this->buffer[index + 1] = g;
        this->buffer[index + 2] = b;
    }

    /**
     * Set pixel at position (x, y)
     * @param x
     * @param y
     * @param r
     * @param g
     * @param b
     */
    void setAtCoords(uint16_t x, uint16_t y, float r, float g, float b) {
        setAtIndex(y * this->_width + x, r, g, b);
    }
};