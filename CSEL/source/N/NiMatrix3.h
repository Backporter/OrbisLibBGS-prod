#pragma once

#include "NiMath.h"
#include <math.h>

namespace ConsoleRE
{
	class NiMatrix3
	{
	public:
		void GetEulerAngles(float& h, float& a, float& b)
		{
			if (entry[1][0] > 0.998)
			{
				h = atan2(entry[0][2], entry[2][2]);
				a = NI_PI / 2;
				b = 0;
			}
			else if (entry[1][0] < -0.998)
			{
				h = atan2(entry[0][2], entry[2][2]);
				a = -NI_PI / 2;
				b = 0;
			}
			else
			{
				h = atan2(-entry[2][0], entry[0][0]);
				b = atan2(-entry[1][2], entry[1][1]);
				a = asin(entry[1][0]);
			}
		}

		void SetEulerAngles(float heading, float attitude, float bank)
		{
			double ch = cos(heading);
			double sh = sin(heading);
			double ca = cos(attitude);
			double sa = sin(attitude);
			double cb = cos(bank);
			double sb = sin(bank);

			entry[0][0] = ch * ca;
			entry[0][1] = sh * sb - ch * sa * cb;
			entry[0][2] = ch * sa * sb + sh * cb;
			entry[1][0] = sa;
			entry[1][1] = ca * cb;
			entry[1][2] = -ca * sb;
			entry[2][0] = -sh * ca;
			entry[2][1] = sh * sa * cb + ch * sb;
			entry[2][2] = -sh * sa * sb + ch * cb;
		}
	public:
		float entry[3][3];
	};
}