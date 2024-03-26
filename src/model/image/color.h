#ifndef MODEL_IMAGE_COLOR_H_
#define MODEL_IMAGE_COLOR_H_

#include <limits.h>

#include <algorithm>
#include <cmath>

#include "rgb.h"

namespace image {

typedef unsigned short ushort;
typedef unsigned int uint;

class Color {
 public:
  enum Spec { Invalid, Rgb, Hsv, Cmyk, Hsl, ExtendedRgb };
  enum NameFormat { HexRgb, HexArgb };

  explicit Color() noexcept : cspec_(Invalid), ct_(USHRT_MAX, 0, 0, 0, 0) {}
  explicit Color(rgb_t rgb) noexcept;
  Color(int r, int g, int b, int a = 255) noexcept
      : cspec_(IsRgbaValid(r, g, b, a) ? Rgb : Invalid),
        ct_(static_cast<ushort>(cspec_ == Rgb ? a * 0x0101 : 0),
            static_cast<ushort>(cspec_ == Rgb ? r * 0x0101 : 0),
            static_cast<ushort>(cspec_ == Rgb ? g * 0x0101 : 0),
            static_cast<ushort>(cspec_ == Rgb ? b * 0x0101 : 0), 0) {}

  bool IsValid() const noexcept;

  int Red() const noexcept;
  int Green() const noexcept;
  int Blue() const noexcept;

  Color ToRgb() const noexcept;
  image::rgb_t Rgba() const noexcept;

  bool operator==(const Color &c) const noexcept;
  bool operator!=(const Color &c) const noexcept;

 private:
  Spec cspec_;
  union CT {
    CT() {}
    explicit CT(ushort a1, ushort a2, ushort a3, ushort a4, ushort a5) noexcept
        : array{a1, a2, a3, a4, a5} {}
    struct {
      ushort alpha;
      ushort red;
      ushort green;
      ushort blue;
      ushort pad;
    } argb;
    struct {
      ushort alpha;
      ushort hue;
      ushort saturation;
      ushort value;
      ushort pad;
    } ahsv;
    struct {
      ushort alpha;
      ushort cyan;
      ushort magenta;
      ushort yellow;
      ushort black;
    } acmyk;
    struct {
      ushort alpha;
      ushort hue;
      ushort saturation;
      ushort lightness;
      ushort pad;
    } ahsl;
    struct {
      ushort alpha_f16;
      ushort red_f16;
      ushort green_f16;
      ushort blue_f16;
      ushort pad;
    } argb_extended;
    ushort array[5];
  } ct_;

  static bool IsRgbaValid(int r, int g, int b, int a = 255) noexcept {
    return static_cast<uint>(r) <= 255 && static_cast<uint>(g) <= 255 &&
           static_cast<uint>(b) <= 255 && static_cast<uint>(a) <= 255;
  }
};

static inline uint Div257Floor(uint x) { return (x - (x >> 8)) >> 8; }
static inline uint Div257(uint x) { return Div257Floor(x + 128); }

static inline const float &CastF16(const ushort &v) {
  return *reinterpret_cast<const float *>(&v);
}

inline bool Color::IsValid() const noexcept { return cspec_ != Invalid; }

}  // namespace image
#endif  // MODEL_IMAGE_COLOR_H_
