#include "color.h"

#include <limits.h>

#include <algorithm>
#include <cmath>

#include "rgb.h"

image::Color::Color(rgb_t color) noexcept {
  cspec_ = Rgb;
  ct_.argb.alpha = 0xffff;
  ct_.argb.red = image::Red(color) * 0x101;
  ct_.argb.green = image::Green(color) * 0x101;
  ct_.argb.blue = image::Blue(color) * 0x101;
  ct_.argb.pad = 0;
}

int image::Color::Red() const noexcept {
  if (cspec_ != Invalid && cspec_ != Rgb) return ToRgb().Red();
  return Div257(ct_.argb.red);
}

int image::Color::Green() const noexcept {
  if (cspec_ != Invalid && cspec_ != Rgb) return ToRgb().Green();
  return Div257(ct_.argb.green);
}

int image::Color::Blue() const noexcept {
  if (cspec_ != Invalid && cspec_ != Rgb) return ToRgb().Blue();
  return Div257(ct_.argb.blue);
}

image::Color image::Color::ToRgb() const noexcept {
  if (!IsValid() || cspec_ == Rgb) return *this;
  Color color;
  color.cspec_ = Rgb;
  if (cspec_ != ExtendedRgb) color.ct_.argb.alpha = ct_.argb.alpha;
  color.ct_.argb.pad = 0;
  switch (cspec_) {
    case Hsv: {
      if (ct_.ahsv.saturation == 0 || ct_.ahsv.hue == USHRT_MAX) {
        // achromatic case
        color.ct_.argb.red = color.ct_.argb.green = color.ct_.argb.blue =
            ct_.ahsv.value;
        break;
      }
      // chromatic case
      const double h = ct_.ahsv.hue == 36000 ? 0 : ct_.ahsv.hue / 6000.;
      const double s = ct_.ahsv.saturation / double(USHRT_MAX);
      const double v = ct_.ahsv.value / double(USHRT_MAX);
      const int i = int(h);
      const double f = h - i;
      const double p = v * (double(1.0) - s);
      if (i & 1) {
        const double q = v * (double(1.0) - (s * f));
        switch (i) {
          case 1:
            color.ct_.argb.red = std::round(q * USHRT_MAX);
            color.ct_.argb.green = std::round(v * USHRT_MAX);
            color.ct_.argb.blue = std::round(p * USHRT_MAX);
            break;
          case 3:
            color.ct_.argb.red = std::round(p * USHRT_MAX);
            color.ct_.argb.green = std::round(q * USHRT_MAX);
            color.ct_.argb.blue = std::round(v * USHRT_MAX);
            break;
          case 5:
            color.ct_.argb.red = std::round(v * USHRT_MAX);
            color.ct_.argb.green = std::round(p * USHRT_MAX);
            color.ct_.argb.blue = std::round(q * USHRT_MAX);
            break;
        }
      } else {
        const double t = v * (double(1.0) - (s * (double(1.0) - f)));
        switch (i) {
          case 0:
            color.ct_.argb.red = std::round(v * USHRT_MAX);
            color.ct_.argb.green = std::round(t * USHRT_MAX);
            color.ct_.argb.blue = std::round(p * USHRT_MAX);
            break;
          case 2:
            color.ct_.argb.red = std::round(p * USHRT_MAX);
            color.ct_.argb.green = std::round(v * USHRT_MAX);
            color.ct_.argb.blue = std::round(t * USHRT_MAX);
            break;
          case 4:
            color.ct_.argb.red = std::round(t * USHRT_MAX);
            color.ct_.argb.green = std::round(p * USHRT_MAX);
            color.ct_.argb.blue = std::round(v * USHRT_MAX);
            break;
        }
      }
      break;
    }
    case Hsl: {
      if (ct_.ahsl.saturation == 0 || ct_.ahsl.hue == USHRT_MAX) {
        // achromatic case
        color.ct_.argb.red = color.ct_.argb.green = color.ct_.argb.blue =
            ct_.ahsl.lightness;
      } else if (ct_.ahsl.lightness == 0) {
        // lightness 0
        color.ct_.argb.red = color.ct_.argb.green = color.ct_.argb.blue = 0;
      } else {
        // chromatic case
        const double h = ct_.ahsl.hue == 36000 ? 0 : ct_.ahsl.hue / 36000.;
        const double s = ct_.ahsl.saturation / double(USHRT_MAX);
        const double l = ct_.ahsl.lightness / double(USHRT_MAX);
        double temp2;
        if (l < double(0.5))
          temp2 = l * (double(1.0) + s);
        else
          temp2 = l + s - (l * s);
        const double temp1 = (double(2.0) * l) - temp2;
        double temp3[3] = {h + (double(1.0) / double(3.0)), h,
                           h - (double(1.0) / double(3.0))};
        for (int i = 0; i != 3; ++i) {
          if (temp3[i] < double(0.0))
            temp3[i] += double(1.0);
          else if (temp3[i] > double(1.0))
            temp3[i] -= double(1.0);
          const double sixtemp3 = temp3[i] * double(6.0);
          if (sixtemp3 < double(1.0))
            color.ct_.array[i + 1] =
                std::round((temp1 + (temp2 - temp1) * sixtemp3) * USHRT_MAX);
          else if ((temp3[i] * double(2.0)) < double(1.0))
            color.ct_.array[i + 1] = std::round(temp2 * USHRT_MAX);
          else if ((temp3[i] * double(3.0)) < double(2.0))
            color.ct_.array[i + 1] =
                std::round((temp1 + (temp2 - temp1) *
                                        (double(2.0) / double(3.0) - temp3[i]) *
                                        double(6.0)) *
                           USHRT_MAX);
          else
            color.ct_.array[i + 1] = std::round(temp1 * USHRT_MAX);
        }
        color.ct_.argb.red = color.ct_.argb.red == 1 ? 0 : color.ct_.argb.red;
        color.ct_.argb.green =
            color.ct_.argb.green == 1 ? 0 : color.ct_.argb.green;
        color.ct_.argb.blue =
            color.ct_.argb.blue == 1 ? 0 : color.ct_.argb.blue;
      }
      break;
    }
    case Cmyk: {
      const double c = ct_.acmyk.cyan / double(USHRT_MAX);
      const double m = ct_.acmyk.magenta / double(USHRT_MAX);
      const double y = ct_.acmyk.yellow / double(USHRT_MAX);
      const double k = ct_.acmyk.black / double(USHRT_MAX);
      color.ct_.argb.red =
          std::round((double(1.0) - (c * (double(1.0) - k) + k)) * USHRT_MAX);
      color.ct_.argb.green =
          std::round((double(1.0) - (m * (double(1.0) - k) + k)) * USHRT_MAX);
      color.ct_.argb.blue =
          std::round((double(1.0) - (y * (double(1.0) - k) + k)) * USHRT_MAX);
      break;
    }
    case ExtendedRgb:
      color.ct_.argb.alpha =
          std::round(USHRT_MAX * double(CastF16(ct_.argb_extended.alpha_f16)));
      color.ct_.argb.red = std::round(
          USHRT_MAX *
          std::max(double(0.0),
                   std::min(double(CastF16(ct_.argb_extended.red_f16)),
                            double(1.0))));
      color.ct_.argb.green = std::round(
          USHRT_MAX *
          std::max(double(0.0),
                   std::min(double(CastF16(ct_.argb_extended.green_f16)),
                            double(1.0))));
      color.ct_.argb.blue = std::round(
          USHRT_MAX *
          std::max(double(0.0),
                   std::min(double(CastF16(ct_.argb_extended.blue_f16)),
                            double(1.0))));
      break;
    default:
      break;
  }
  return color;
}

image::rgb_t image::Color::Rgba() const noexcept {
  if (cspec_ != Invalid && cspec_ != Rgb) return ToRgb().Rgba();
  return image::Rgba(Div257(ct_.argb.red), Div257(ct_.argb.green),
                     Div257(ct_.argb.blue), Div257(ct_.argb.alpha));
}
