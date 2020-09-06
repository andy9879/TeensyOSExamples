/*
Author: William Redenbaugh
Last Edit Date: 7/20/2020
*/

#include "hsv_rgb_conv.hpp"

HsvColor RgbToHsv(RgbColor rgb);
RgbColor HsvToRgb(HsvColor hsv);

// CREDIT FOR HSV TO RGB CONVERSTION GOES TO THIS GUY: https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
// STACKOVERFLOW POSTERS ARE OUR OVERLOARDS. 

/**************************************************************************/
/*!
    @brief Converts RGB data into HSV data
    @param rgb struct. 
    @returns hsv struct. 
*/
/**************************************************************************/
HsvColor RgbToHsv(RgbColor rgb)
{
    HsvColor hsv;
    unsigned char rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.v = rgbMax;
    if (hsv.v == 0){
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = 255 * long(rgbMax - rgbMin) / hsv.v;
    if (hsv.s == 0){
        hsv.h = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}

/**************************************************************************/
/*!
    @brief Converts HSV data into RGB data
    @param hsv struct. 
    @returns rgb struct. 
*/
/**************************************************************************/
RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0){
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region){
    case 0:
        rgb.r = hsv.v; rgb.g = t; rgb.b = p;
    break;
    case 1:
        rgb.r = q; rgb.g = hsv.v; rgb.b = p;
    break;
    case 2:
        rgb.r = p; rgb.g = hsv.v; rgb.b = t;
    break;
    case 3:
        rgb.r = p; rgb.g = q; rgb.b = hsv.v;
    break;
    case 4:
        rgb.r = t; rgb.g = p; rgb.b = hsv.v;
    break;
    default:
        rgb.r = hsv.v; rgb.g = p; rgb.b = q;
    break;
    }

    return rgb;
}