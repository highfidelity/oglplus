//  File implement/oglplus/enums/ext/compat_matrix_mode_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/compat_matrix_mode.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	CompatibilityMatrixMode*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_COMPATIBILITYMATRIXMODE)
#define OGLPLUS_IMPL_EVN_COMPATIBILITYMATRIXMODE
{
switch(value)
{
#if defined GL_PROJECTION
	case GL_PROJECTION: return CStrRef("PROJECTION");
#endif
#if defined GL_MODELVIEW
	case GL_MODELVIEW: return CStrRef("MODELVIEW");
#endif
#if defined GL_TEXTURE
	case GL_TEXTURE: return CStrRef("TEXTURE");
#endif
#if defined GL_COLOR
	case GL_COLOR: return CStrRef("COLOR");
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

