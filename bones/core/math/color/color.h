#pragma once

#include <core/typedefs.h>

namespace bones
{
  struct Color
  {
    union
    {
      struct { float r, g, b, a; };
      float data[4];
    };

    Color() : r(0), g(0), b(0), a(0) {}
    Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}
    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

#pragma region "Color Constants"
    static const Color maroon;
    static const Color dark_red;
    static const Color brown;
    static const Color firebrick;
    static const Color crimson;
    static const Color red;
    static const Color tomato;
    static const Color coral;
    static const Color indian_red;
    static const Color light_coral;
    static const Color dark_salmon;
    static const Color salmon;
    static const Color light_salmon;
    static const Color orange_red;
    static const Color dark_orange;
    static const Color orange;
    static const Color gold;
    static const Color dark_goldenrod;
    static const Color goldenrod;
    static const Color pale_goldenrod;
    static const Color dark_khaki;
    static const Color khaki;
    static const Color olive;
    static const Color yellow;
    static const Color yellow_green;
    static const Color dark_olive_green;
    static const Color olive_drab;
    static const Color lawn_green;
    static const Color chart_reuse;
    static const Color green_yellow;
    static const Color dark_green;
    static const Color green;
    static const Color forest_green;
    static const Color lime;
    static const Color lime_green;
    static const Color light_green;
    static const Color pale_green;
    static const Color dark_sea_green;
    static const Color medium_spring_green;
    static const Color spring_green;
    static const Color sea_green;
    static const Color medium_aqua_marine;
    static const Color medium_sea_green;
    static const Color light_sea_green;
    static const Color dark_slate_gray;
    static const Color teal;
    static const Color dark_cyan;
    static const Color aqua;
    static const Color cyan;
    static const Color light_cyan;
    static const Color dark_turquoise;
    static const Color turquoise;
    static const Color medium_turquoise;
    static const Color pale_turquoise;
    static const Color aqua_marine;
    static const Color powder_blue;
    static const Color cadet_blue;
    static const Color steel_blue;
    static const Color corn_flower_blue;
    static const Color deep_sky_blue;
    static const Color dodger_blue;
    static const Color light_blue;
    static const Color sky_blue;
    static const Color light_sky_blue;
    static const Color midnight_blue;
    static const Color navy;
    static const Color dark_blue;
    static const Color medium_blue;
    static const Color blue;
    static const Color royal_blue;
    static const Color blue_violet;
    static const Color indigo;
    static const Color dark_slate_blue;
    static const Color slate_blue;
    static const Color medium_slate_blue;
    static const Color medium_purple;
    static const Color dark_magenta;
    static const Color dark_violet;
    static const Color dark_orchid;
    static const Color medium_orchid;
    static const Color purple;
    static const Color thistle;
    static const Color plum;
    static const Color violet;
    static const Color magenta;
    static const Color fuchsia;
    static const Color orchid;
    static const Color medium_violet_red;
    static const Color pale_violet_red;
    static const Color deep_pink;
    static const Color hot_pink;
    static const Color light_pink;
    static const Color pink;
    static const Color antique_white;
    static const Color beige;
    static const Color bisque;
    static const Color blanched_almond;
    static const Color wheat;
    static const Color corn_silk;
    static const Color lemon_chiffon;
    static const Color light_goldenrod_yellow;
    static const Color light_yellow;
    static const Color saddle_brown;
    static const Color sienna;
    static const Color chocolate;
    static const Color peru;
    static const Color sandy_brown;
    static const Color burly_wood;
    static const Color tan;
    static const Color rosy_brown;
    static const Color moccasin;
    static const Color navajo_white;
    static const Color peach_puff;
    static const Color misty_rose;
    static const Color lavender_blush;
    static const Color linen;
    static const Color old_lace;
    static const Color papaya_whip;
    static const Color sea_shell;
    static const Color mint_cream;
    static const Color slate_gray;
    static const Color light_slate_gray;
    static const Color light_steel_blue;
    static const Color lavender;
    static const Color floral_white;
    static const Color alice_blue;
    static const Color ghost_white;
    static const Color honeydew;
    static const Color ivory;
    static const Color azure;
    static const Color snow;
    static const Color black;
    static const Color dim_gray;
    static const Color dim_grey;
    static const Color gray;
    static const Color grey;
    static const Color dark_gray;
    static const Color dark_grey;
    static const Color silver;
    static const Color light_gray;
    static const Color light_grey;
    static const Color gainsboro;
    static const Color white_smoke;
    static const Color white;
    static const Color transparent;
#pragma endregion
    
    static Color hex_rgb(u32 hex);
    static Color hex_argb(u32 hex);

    // static Color hex_hsv(u32 hsv);
    // static Color hex_hsv(u32 hsv);

    // u32 hex() const;

    // Color hsv() const;
    // Vec3 hsv() const;

    // u8 h() const;
    // u8 s() const;
    // u8 v() const;

    // Color& operator=()

    Color& operator=(const Color& rhs);
    Color& operator+=(const Color& rhs);
    Color& operator-=(const Color& rhs);
    Color& operator*=(const Color& rhs);
    Color& operator*=(float rhs);
    Color& operator/=(const Color& rhs);
    Color& operator/=(float rhs);
  };

  Color operator+(const Color& rhs);
  Color operator-(const Color& rhs);

  Color operator+(const Color& lhs, const Color& rhs);
  Color operator-(const Color& lhs, const Color& rhs);
  Color operator*(const Color& lhs, const Color& rhs);
  Color operator*(const Color& lhs, float rhs);
  Color operator*(float lhs, const Color& rhs);
  Color operator/(const Color& lhs, const Color& rhs);
  Color operator/(const Color& lhs, float rhs);
  Color operator/(float lhs, const Color& rhs);

  bool operator==(const Color& lhs, const Color& rhs);
  bool operator!=(const Color& lhs, const Color& rhs);

  // std::ostream& operator<<(std::ostream& os, const Color& rhs)
}