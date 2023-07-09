#include "../G/GViewport.h"

namespace ConsoleRE
{
	GViewport::GViewport() :
		bufferWidth(0),
		bufferHeight(0),
		left(0),
		top(0),
		width(1),
		height(1),
		scissorLeft(0),
		scissorTop(0),
		scissorWidth(0),
		scissorHeight(0),
		scale(1.0),
		aspectRatio(1.0),
		flags(0),
		pad34(0)
	{}

	GViewport::GViewport(const GViewport& a_rhs) :
		bufferWidth(a_rhs.bufferWidth),
		bufferHeight(a_rhs.bufferHeight),
		left(a_rhs.left),
		top(a_rhs.top),
		width(a_rhs.width),
		height(a_rhs.height),
		scissorLeft(a_rhs.scissorLeft),
		scissorTop(a_rhs.scissorTop),
		scissorWidth(a_rhs.scissorWidth),
		scissorHeight(a_rhs.scissorHeight),
		scale(a_rhs.scale),
		aspectRatio(a_rhs.aspectRatio),
		flags(a_rhs.flags),
		pad34(0)
	{}

	GViewport::GViewport(int32_t a_bufW, int32_t a_bufH, int32_t a_left, int32_t a_top, int32_t a_width, int32_t a_height, int32_t a_scLeft, int32_t a_scTop, int32_t a_scW, int32_t a_scH, uint32_t a_flags) :
		bufferWidth(a_bufW),
		bufferHeight(a_bufH),
		left(a_left),
		top(a_top),
		width(a_width),
		height(a_height),
		scissorLeft(a_scLeft),
		scissorTop(a_scTop),
		scissorWidth(a_scW),
		scissorHeight(a_scH),
		scale(1.0),
		aspectRatio(1.0),
		flags(a_flags),
		pad34(0)
	{}

	GViewport::GViewport(int32_t a_bufW, int32_t a_bufH, int32_t a_left, int32_t a_top, int32_t a_width, int32_t a_height, int32_t a_scLeft, int32_t a_scTop, int32_t a_scW, int32_t a_scH, float a_scale, float a_ratio, uint32_t a_flags) :
		bufferWidth(a_bufW),
		bufferHeight(a_bufH),
		left(a_left),
		top(a_top),
		width(a_width),
		height(a_height),
		scissorLeft(a_scLeft),
		scissorTop(a_scTop),
		scissorWidth(a_scW),
		scissorHeight(a_scH),
		scale(a_scale),
		aspectRatio(a_ratio),
		flags(a_flags |= 4),
		pad34(0)
	{}

	GViewport::GViewport(int32_t a_bufW, int32_t a_bufH, int32_t a_left, int32_t a_top, int32_t a_width, int32_t a_height, uint32_t a_flags) :
		bufferWidth(a_bufW),
		bufferHeight(a_bufH),
		left(a_left),
		top(a_top),
		width(a_width),
		height(a_height),
		scissorLeft(0),
		scissorTop(0),
		scissorWidth(0),
		scissorHeight(0),
		scale(1.0),
		aspectRatio(1.0),
		flags(a_flags),
		pad34(0)
	{}
}