#pragma once

#include "../../../OrbisUtil/include/Macro.h"

#include <stdint.h>

namespace ConsoleRE
{
	class Color1
	{
	public:
		Color1(int8_t a_r) :r(a_r) { }
		Color1(Color1& a_rhs) { r = a_rhs.r; }
	public:
		operator int8_t() { return *reinterpret_cast<int8_t*>(this); }
	private:
		int8_t r;
	};

	class Color2
	{
	public:
		Color2(int8_t a_r, int8_t a_g) :r(a_r), g(a_g) { }
		Color2(Color2& a_rhs) { r = a_rhs.r; g = a_rhs.g; }
	public:
		operator int16_t() { return *reinterpret_cast<int16_t*>(this); }
	private:
		int8_t r;
		int8_t g;
	};

	class Color3
	{
	public:
		Color3(int8_t a_r, int8_t a_g, int8_t a_b) :r(a_r),g(a_g),b(a_b) { }
		Color3(Color3& a_rhs) { r = a_rhs.r; g = a_rhs.g; b = a_rhs.b; }
	private:
		int8_t r;
		int8_t g;
		int8_t b;
	};

	class Color4
	{
	public:
		Color4(int8_t a_r, int8_t a_g, int8_t a_b, int8_t a_a) :r(a_r), g(a_g), b(a_b), a(a_a) { }
		Color4(Color4& a_rhs) { r = a_rhs.r; g = a_rhs.g; b = a_rhs.b; a = a_rhs.a; }
		Color4(int32_t a_color) { *reinterpret_cast<int32_t*>(this) = a_color; }
	public:
		void SetHue(double a_hue)			{ double s_hue, s_sat, s_val; GetHSV(s_hue, s_sat, s_val); SetHSV(a_hue, s_sat, s_val); }
		void SetSaturation(double a_sat)	{ double s_hue, s_sat, s_val; GetHSV(s_hue, s_sat, s_val); SetHSV(s_hue, a_sat, s_val); }
		void SetValue(double a_val)			{ double s_hue, s_sat, s_val; GetHSV(s_hue, s_sat, s_val); SetHSV(s_hue, s_sat, a_val); }

		double GetHue()						{ double s_hue, s_sat, s_val; GetHSV(s_hue, s_sat, s_val); return s_hue; }
		double GetSaturation()				{ double s_hue, s_sat, s_val; GetHSV(s_hue, s_sat, s_val); return s_sat; }
		double GetValue()					{ double s_hue, s_sat, s_val; GetHSV(s_hue, s_sat, s_val); return s_val; }

		void GetHSV(double& a_hue, double& a_sat, double& a_value)
		{
			double s_r, s_g, s_b, s_rgb_max, s_rgb_min, s_delta, s_h, s_s;
			
			s_r = r / 255.0;
			s_g = g / 255.0;
			s_b = b / 255.0;

			s_rgb_max = MAX3(r, g, b);
			s_rgb_min = MIN3(r, g, b);
			
			s_delta = s_rgb_max - s_rgb_min;

			s_h = 0;
			s_s = 0;

			if (s_rgb_max != 0.0)
				s_s = s_delta / s_rgb_max;

			if (s_s != 0.0)
			{
				double s_rc = (s_rgb_max - s_r) / s_delta;
				double s_gc = (s_rgb_max - s_g) / s_delta;
				double s_bc = (s_rgb_max - s_b) / s_delta;

				if (s_r == s_rgb_max)
					s_h = s_bc - s_gc;

				else if (s_g == s_rgb_max)
					s_h = 2.0f + s_rc - s_bc;

				else if (s_b == s_rgb_max)
					s_h = 4.0f + s_gc - s_rc;

				s_h *= 60.0f;

				if (s_h < 0.0)
					s_h += 360.0f;
			}

			a_hue	= s_h;
			a_sat	= s_s;
			a_value = s_rgb_max;
		}

		void SetHSV(double a_hue, double a_sat, double a_value)
		{
			double s_h, s_s, s_v;
			double s_r, s_g, s_b;

			s_h = a_hue;
			s_s = a_sat;
			s_v = a_value;

			if (a_hue < 0.0)
				a_hue += 360.0;

			if (s_s != 0.0) 
			{
				double s_f, s_p, s_q, s_t;

				if (s_h == 360.0)
					s_h = 0.0;

				s_h /= 60.0;


				s_f = s_h - (int)s_h;
				s_p = s_v * (1.0 - s_s);
				s_q = s_v * (1.0 - (s_s * s_f));
				s_t = s_v * (1.0 - (s_s * (1.0 - s_f)));

				switch ((int)s_h)
				{
				case 0: s_r = s_v;	s_g = s_t;	s_b = s_p;	break;
				case 1: s_r = s_q;	s_g = s_v;	s_b = s_p;	break;
				case 2: s_r = s_p;	s_g = s_v;	s_b = s_t;	break;
				case 3: s_r = s_p;	s_g = s_q;	s_b = s_v;	break;
				case 4: s_r = s_t;	s_g = s_p;	s_b = s_v;	break;
				case 5: s_r = s_v;	s_g = s_p;	s_b = s_q;	break;
				}
			}
			else 
			{
				s_r = s_v;
				s_g = s_v;
				s_b = s_v;
			}

			r = s_r * 255;
			g = s_g * 255;
			b = s_b * 255;
		}
public:
		operator int32_t() { return *reinterpret_cast<int32_t*> (this); }
		operator uint32_t() { return *reinterpret_cast<uint32_t*> (this); }
public:
		int8_t r;
		int8_t g;
		int8_t b;
		int8_t a;
	};

	using Color = Color4;
}