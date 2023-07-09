#pragma once

#include <stdint.h>
#include <cstdio>
#include <memory>

namespace ConsoleRE
{
	class GMatrix3D
	{
	public:
		GMatrix3D& operator=(const GMatrix3D& a_rhs)
		{
			for (std::size_t i = 0; i < 4; i++)
			{
				for (std::size_t j = 0; j < 4; j++)	
				{
					data[i][j] = a_rhs.data[i][j];
				}
			}

			return *this;
		}
	public:
		GMatrix3D() : data{ {0.0f } } { }
	public:
		float data[4][4];
	};
}