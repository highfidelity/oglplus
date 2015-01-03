//  File implement/oglplus/enums/framebuffer_buffer_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/framebuffer_buffer.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	FramebufferBuffer*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_FRAMEBUFFERBUFFER)
#define OGLPLUS_IMPL_EVN_FRAMEBUFFERBUFFER
{
switch(value)
{
#if defined GL_COLOR
	case GL_COLOR: return CStrRef("COLOR");
#endif
#if defined GL_DEPTH
	case GL_DEPTH: return CStrRef("DEPTH");
#endif
#if defined GL_STENCIL
	case GL_STENCIL: return CStrRef("STENCIL");
#endif
#if defined GL_DEPTH_STENCIL
	case GL_DEPTH_STENCIL: return CStrRef("DEPTH_STENCIL");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

