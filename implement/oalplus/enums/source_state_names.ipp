//  File implement/oalplus/enums/source_state_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oalplus/source_state.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OALPLUS_LIB_FUNC CStrRef ValueName_(
	SourceState*,
	ALenum value
) noexcept
#if (!OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OALPLUS_IMPL_EVN_SOURCESTATE)
#define OALPLUS_IMPL_EVN_SOURCESTATE
{
switch(value)
{
#if defined AL_INITIAL
	case AL_INITIAL: return CStrRef("INITIAL");
#endif
#if defined AL_PLAYING
	case AL_PLAYING: return CStrRef("PLAYING");
#endif
#if defined AL_PAUSED
	case AL_PAUSED: return CStrRef("PAUSED");
#endif
#if defined AL_STOPPED
	case AL_STOPPED: return CStrRef("STOPPED");
#endif
	default:;
}
OALPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

