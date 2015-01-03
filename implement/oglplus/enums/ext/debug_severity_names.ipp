//  File implement/oglplus/enums/ext/debug_severity_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/ext/debug_severity.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	DebugSeverity*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_DEBUGSEVERITY)
#define OGLPLUS_IMPL_EVN_DEBUGSEVERITY
{
switch(value)
{
#if defined GL_DEBUG_SEVERITY_HIGH
	case GL_DEBUG_SEVERITY_HIGH: return CStrRef("DEBUG_SEVERITY_HIGH");
#endif
#if defined GL_DEBUG_SEVERITY_MEDIUM
	case GL_DEBUG_SEVERITY_MEDIUM: return CStrRef("DEBUG_SEVERITY_MEDIUM");
#endif
#if defined GL_DEBUG_SEVERITY_LOW
	case GL_DEBUG_SEVERITY_LOW: return CStrRef("DEBUG_SEVERITY_LOW");
#endif
#if defined GL_DEBUG_SEVERITY_NOTIFICATION
	case GL_DEBUG_SEVERITY_NOTIFICATION: return CStrRef("DEBUG_SEVERITY_NOTIFICATION");
#endif
#if defined GL_DONT_CARE
	case GL_DONT_CARE: return CStrRef("DONT_CARE");
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

