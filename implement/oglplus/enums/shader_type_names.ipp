//  File implement/oglplus/enums/shader_type_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/shader_type.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	ShaderType*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_SHADERTYPE)
#define OGLPLUS_IMPL_EVN_SHADERTYPE
{
switch(value)
{
#if defined GL_VERTEX_SHADER
	case GL_VERTEX_SHADER: return CStrRef("VERTEX_SHADER");
#endif
#if defined GL_TESS_CONTROL_SHADER
	case GL_TESS_CONTROL_SHADER: return CStrRef("TESS_CONTROL_SHADER");
#endif
#if defined GL_TESS_EVALUATION_SHADER
	case GL_TESS_EVALUATION_SHADER: return CStrRef("TESS_EVALUATION_SHADER");
#endif
#if defined GL_GEOMETRY_SHADER
	case GL_GEOMETRY_SHADER: return CStrRef("GEOMETRY_SHADER");
#endif
#if defined GL_FRAGMENT_SHADER
	case GL_FRAGMENT_SHADER: return CStrRef("FRAGMENT_SHADER");
#endif
#if defined GL_COMPUTE_SHADER
	case GL_COMPUTE_SHADER: return CStrRef("COMPUTE_SHADER");
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

