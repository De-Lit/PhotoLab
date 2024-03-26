#ifndef MODEL_IMAGE_RGB_H_
#define MODEL_IMAGE_RGB_H_

namespace image {
typedef unsigned int rgb_t;  // RGB triplet

const rgb_t RGB_MASK = 0x00ffffff;  // masks RGB values

inline int Red(rgb_t rgb)  // get red part of RGB
{
  return ((rgb >> 16) & 0xff);
}

inline int Green(rgb_t rgb)  // get green part of RGB
{
  return ((rgb >> 8) & 0xff);
}

inline int Blue(rgb_t rgb)  // get blue part of RGB
{
  return (rgb & 0xff);
}

inline int Alpha(rgb_t rgb)  // get alpha part of RGBA
{
  return rgb >> 24;
}

inline rgb_t Rgb(int r, int g, int b)  // set RGB value
{
  return (0xffu << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu);
}

inline rgb_t Rgba(int r, int g, int b, int a)  // set RGBA value
{
  return ((a & 0xffu) << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) |
         (b & 0xffu);
}

inline int Gray(int r, int g, int b)  // convert R,G,B to gray 0..255
{
  return (r * 11 + g * 16 + b * 5) / 32;
}

inline int Gray(rgb_t rgb)  // convert RGB to gray 0..255
{
  return Gray(Red(rgb), Green(rgb), Blue(rgb));
}

inline bool IsGray(rgb_t rgb) {
  return Red(rgb) == Green(rgb) && Red(rgb) == Blue(rgb);
}

inline rgb_t Premultiply(rgb_t x) {
  const unsigned int a = Alpha(x);
  unsigned int t = (x & 0xff00ff) * a;
  t = (t + ((t >> 8) & 0xff00ff) + 0x800080) >> 8;
  t &= 0xff00ff;
  x = ((x >> 8) & 0xff) * a;
  x = (x + ((x >> 8) & 0xff) + 0x80);
  x &= 0xff00;
  return x | t | (a << 24);
}

extern const unsigned int qt_inv_premul_factor[];

inline rgb_t qUnpremultiply(rgb_t p) {
  const unsigned int alpha = Alpha(p);
  if (alpha == 255) return p;
  if (alpha == 0) return 0;
  const unsigned int invAlpha = qt_inv_premul_factor[alpha];
  return Rgba((Red(p) * invAlpha + 0x8000) >> 16,
              (Green(p) * invAlpha + 0x8000) >> 16,
              (Blue(p) * invAlpha + 0x8000) >> 16, alpha);
}
}  // namespace image
#endif  // MODEL_IMAGE_RGB_H_
