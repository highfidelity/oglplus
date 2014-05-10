/**
 *  @file oglplus/buffer.hpp
 *  @brief Buffer wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_1107121519_HPP
#define OGLPLUS_BUFFER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error/object.hpp>
#include <oglplus/object/wrapper.hpp>
#include <oglplus/object/sequence.hpp>
#include <oglplus/buffer_binding.hpp>
#include <oglplus/buffer_usage.hpp>
#include <oglplus/buffer_storage_bit.hpp>
#include <oglplus/buffer_target.hpp>
#include <oglplus/buffer_map.hpp>
#include <oglplus/buffer_gpu_addr.hpp>
#include <oglplus/access_specifier.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/pixel_data.hpp>

#include <vector>
#include <cassert>

namespace oglplus {

/// Class wrapping buffer construction/destruction functions
/** @note Do not use this class directly, use Buffer instead.
 *
 *  @glsymbols
 *  @glfunref{GenBuffers}
 *  @glfunref{DeleteBuffers}
 *  @glfunref{IsBuffer}
 */
template <>
class ObjGenDelOps<tag::Buffer>
{
protected:
	static void Gen(GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(GenBuffers)(count, names);
		OGLPLUS_CHECK_SIMPLE(GenBuffers);
	}

	static void Delete(GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		OGLPLUS_GLFUNC(DeleteBuffers)(count, names);
		OGLPLUS_VERIFY_SIMPLE(DeleteBuffers);
	}

	static GLboolean IsA(GLuint name)
	{
		assert(name != 0);
		GLboolean result = OGLPLUS_GLFUNC(IsBuffer)(name);
		OGLPLUS_VERIFY_SIMPLE(IsBuffer);
		return result;
	}
};

/// Buffer binding operations
template <>
class ObjBindingOps<tag::Buffer>
{
private:
	static GLenum _binding_query(BufferTarget target);
	static GLenum _binding_query(BufferIndexedTarget target);
protected:
	static GLuint _binding(BufferTarget target);
	static GLuint _binding(BufferIndexedTarget target, GLuint index);
public:
	/// Buffer bind targets
	typedef BufferTarget Target;

	/// Buffer indexed bind targets
	typedef BufferIndexedTarget IndexedTarget;

	/// Returns the current Buffer bound to specified @p target
	/**
	 *  @glsymbols
	 *  @glfunref{GetIntegerv}
	 */
	static BufferName Binding(Target target)
	{
		return BufferName(_binding(target));
	}

	/// Binds the specified @p buffer to the specified @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BindBuffer}
	 */
	static void Bind(
		Target target,
		BufferName buffer
	)
	{
		OGLPLUS_GLFUNC(BindBuffer)(
			GLenum(target),
			GetGLName(buffer)
		);
		OGLPLUS_VERIFY(
			BindBuffer,
			ObjectError,
			Object(buffer).
			BindTarget(target)
		);
	}

	/// Returns the current Buffer bound to specified indexed @p target
	/**
	 *  @glsymbols
	 *  @glfunref{GetIntegerv}
	 */
	static BufferName Binding(IndexedTarget target, GLuint idx)
	{
		return BufferName(_binding(target, idx));
	}

	/// Bind the specified @p buffer to the specified indexed @p target
	/**
	 *  @throws Error
	 */
	static void BindBase(
		IndexedTarget target,
		GLuint index,
		BufferName buffer
	)
	{
		OGLPLUS_GLFUNC(BindBufferBase)(
			GLenum(target),
			index,
			GetGLName(buffer)
		);
		OGLPLUS_VERIFY(
			BindBufferBase,
			ObjectError,
			Object(buffer).
			BindTarget(target)
		);
	}

	/// Bind a range the specified buffer to the specified indexed @p target
	/**
	 *  @throws Error
	 */
	static void BindRange(
		IndexedTarget target,
		GLuint index,
		BufferName buffer,
		GLintptr offset,
		GLsizeiptr size
	)
	{
		OGLPLUS_GLFUNC(BindBufferRange)(
			GLenum(target),
			index,
			GetGLName(buffer),
			offset,
			size
		);
		OGLPLUS_VERIFY(
			BindBufferRange,
			ObjectError,
			Object(buffer).
			BindTarget(target)
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_multi_bind
	static void BindBase(
		BufferIndexedTarget target,
		GLuint first,
		GLsizei count,
		const GLuint* names
	)
	{
		OGLPLUS_GLFUNC(BindBuffersBase)(
			GLenum(target),
			first,
			count,
			names
		);
		OGLPLUS_VERIFY(
			BindBuffersBase,
			ObjectError,
			BindTarget(target)
		);
	}

	/// Sequentially binds @p buffers to @p target starting at @p first index
	/**
	 *  @glsymbols
	 *  @glfunref{BindBase}
	 *  @glvoereq{4,4,ARB,multi_bind}
	 */
	static void BindBase(
		BufferIndexedTarget target,
		GLuint first,
		const Sequence<BufferName>& buffers
	)
	{
		BindBase(
			target,
			first,
			GLsizei(buffers.size()),
			GetGLNames(buffers)
		);
	}

	static void BindRange(
		BufferIndexedTarget target,
		GLuint first,
		GLsizei count,
		const GLuint* names,
		const GLintptr* offsets,
		const GLsizeiptr* sizes
	)
	{
		OGLPLUS_GLFUNC(BindBuffersRange)(
			GLenum(target),
			first,
			count,
			names,
			offsets,
			sizes
		);
		OGLPLUS_VERIFY(
			BindBuffersRange,
			ObjectError,
			BindTarget(target)
		);
	}
#endif
};

/// Common buffer operations
/** @note Do not use this class directly, use Buffer
 *  or DefaultBuffer instead.
 */
template <>
class ObjCommonOps<tag::Buffer>
 : public BufferName
 , public ObjBindingOps<tag::Buffer>
{
protected:
	ObjCommonOps(void){ }
public:
	using ObjBindingOps<tag::Buffer>::Bind;
	using ObjBindingOps<tag::Buffer>::BindBase;
	using ObjBindingOps<tag::Buffer>::BindRange;

	/// Binds this buffer to the specified @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BindBuffer}
	 */
	void Bind(Target target) const
	{
		Bind(target, *this);
	}

	/// Binds this buffer to the specified indexed @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BindBuffer}
	 */
	void BindBase(IndexedTarget target, GLuint index) const
	{
		BindBase(target, index, *this);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_transform_feedback3
	/// Bind this buffer to the specified uniform buffer binding point
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,0,ARB,transform_feedback3}
	 */
	void BindBaseUniform(UniformBufferBindingPoint index) const
	{
		BindBase(IndexedTarget::Uniform, GLuint(index));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_transform_feedback3
	/// Bind this buffer to the specified TFB buffer binding point
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,0,ARB,transform_feedback3}
	 */
	void BindBaseTransformFeedback(
		TransformFeedbackBufferBindingPoint index
	) const
	{
		BindBase(IndexedTarget::TransformFeedback, GLuint(index));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2 || GL_ARB_shader_atomic_counters
	/// Bind this buffer to the specified atomic counter buffer binding point
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,2,ARB,shader_atomic_counters}
	 */
	void BindBaseAtomicCounter(AtomicCounterBufferBindingPoint index) const
	{
		BindBase(IndexedTarget::AtomicCounter, GLuint(index));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_shader_storage_buffer_object
	/// Bind this buffer to the specified shader storage buffer binding point
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,3,ARB,shader_storage_buffer_object}
	 */
	void BindBaseShaderStorage(ShaderStorageBufferBindingPoint index) const
	{
		BindBase(IndexedTarget::ShaderStorage, GLuint(index));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_invalidate_subdata
	/// Invalidate the buffer data
	/**
	 *  @see Data
	 *  @see ClearData
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,3,ARB,invalidate_subdata}
	 */
	void InvalidateData(void)
	{
		OGLPLUS_GLFUNC(InvalidateBufferData)(_name);
		OGLPLUS_CHECK(
			InvalidateBufferData,
			ObjectError,
			Object(*this)
		);
	}

	/// Invalidate a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see SubData
	 *  @see InvalidateData
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,3,ARB,invalidate_subdata}
	 */
	void InvalidateSubData(GLintptr offset, GLsizeiptr size)
	{
		OGLPLUS_GLFUNC(InvalidateBufferSubData)(
			_name,
			offset,
			size
		);
		OGLPLUS_CHECK(
			InvalidateBufferSubData,
			ObjectError,
			Object(*this)
		);
	}
#endif
};

/// Class wrapping buffer functions with explicit target selector
/** @note Do not use this class directly, use Buffer instead.
 */
template <>
class ObjectOps<tag::ExplicitSel, tag::Buffer>
 : public ObjZeroOps<tag::ExplicitSel, tag::Buffer>
{
protected:
	ObjectOps(void) { }
public:
	static GLint GetIntParam(Target target, GLenum query)
	{
		GLint value = 0;
		OGLPLUS_GLFUNC(GetBufferParameteriv)(
			GLenum(target),
			query,
			&value
		);
		OGLPLUS_VERIFY(
			GetBufferParameteriv,
			ObjectError,
			ObjectBinding(target).
			EnumParam(query)
		);
		return value;
	}

	/// Types related to Buffer
	struct Property
	{
		/// The Buffer usage mode
		typedef BufferUsage Usage;

		/// The buffer map access mode
		typedef BufferMapAccess MapAccess;
	};

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	/// Mapping of the buffer to the client address space
	typedef BufferTypedMap<GLubyte> Map;

	/// Returns true if the buffer is mapped
	/**
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_MAPPED}
	 *
	 *  @throws Error
	 */
	static bool Mapped(Target target)
	{
		return GetIntParam(target, GL_BUFFER_MAPPED) == GL_TRUE;
	}
#endif // GL_VERSION_3_0

	/// Uploads (sets) the buffer data
	/** This member function uploads @p count units of @c sizeof(GLtype)
	 *  from the location pointed to by @p data to the buffer bound
	 *  to the specified @p target using the @p usage as hint.
	 *
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	static void Data(
		Target target,
		GLsizei count,
		const GLtype* data,
		BufferUsage usage = BufferUsage::StaticDraw
	)
	{
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			count * sizeof(GLtype),
			data,
			GLenum(usage)
		);
		OGLPLUS_CHECK(
			BufferData,
			ObjectError,
			ObjectBinding(target).
			EnumParam(usage)
		);
	}

	template <typename GLtype, std::size_t Count>
	static void Data(
		Target target,
		const GLtype (&data)[Count],
		BufferUsage usage = BufferUsage::StaticDraw
	)
	{
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			Count * sizeof(GLtype),
			data,
			GLenum(usage)
		);
		OGLPLUS_CHECK(
			BufferData,
			ObjectError,
			ObjectBinding(target).
			EnumParam(usage)
		);
	}

	/// Uploads (sets) the buffer data
	/** This member function uploads @p data.size() units of @c sizeof(GLtype)
	 *  from the location pointed to by @p data.data() to the buffer bound
	 *  to the specified @p target using the @p usage as hint.
	 *
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	static void Data(
		Target target,
		const std::vector<GLtype>& data,
		BufferUsage usage = BufferUsage::StaticDraw
	)
	{
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			data.size() * sizeof(GLtype),
			data.data(),
			GLenum(usage)
		);
		OGLPLUS_CHECK(
			BufferData,
			ObjectError,
			ObjectBinding(target).
			EnumParam(usage)
		);
	}

	/// Uploads (sets) the buffer data
	/**
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype, std::size_t N>
	static void Data(
		Target target,
		const std::vector<Vector<GLtype, N> >& data,
		BufferUsage usage = BufferUsage::StaticDraw
	)
	{
		//TODO: is this a good idea ?
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			data.size() * sizeof(GLtype) * N,
			reinterpret_cast<const GLtype*>(data.data()),
			GLenum(usage)
		);
		OGLPLUS_CHECK(
			BufferData,
			ObjectError,
			ObjectBinding(target).
			EnumParam(usage)
		);
	}

	/// Uploads (sets) a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	static void SubData(
		Target target,
		GLintptr offset,
		GLsizei count,
		const GLtype* data
	)
	{
		OGLPLUS_GLFUNC(BufferSubData)(
			GLenum(target),
			offset * sizeof(GLtype),
			count * sizeof(GLtype),
			data
		);
		OGLPLUS_CHECK(
			BufferSubData,
			ObjectError,
			ObjectBinding(target)
		);
	}

	template <typename GLtype, std::size_t Count>
	static void SubData(
		Target target,
		GLintptr offset,
		const GLtype (&data)[Count]
	)
	{
		OGLPLUS_GLFUNC(BufferSubData)(
			GLenum(target),
			offset * sizeof(GLtype),
			Count * sizeof(GLtype),
			data
		);
		OGLPLUS_CHECK(
			BufferSubData,
			ObjectError,
			ObjectBinding(target)
		);
	}

	/// Uploads (sets) a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	static void SubData(
		Target target,
		GLintptr offset,
		const std::vector<GLtype>& data
	)
	{
		OGLPLUS_GLFUNC(BufferSubData)(
			GLenum(target),
			offset * sizeof(GLtype),
			data.size() * sizeof(GLtype),
			data.data()
		);
		OGLPLUS_CHECK(
			BufferSubData,
			ObjectError,
			ObjectBinding(target)
		);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1 || GL_ARB_copy_buffer
	/// Copy data between buffers
	/**
	 *  @see Data
	 *  @see SubData
	 *  @throws Error
	 *
	 *  @glvoereq{3,1,ARB,copy_buffer}
	 */
	static inline void CopySubData(
		BufferTarget readtarget,
		BufferTarget writetarget,
		GLintptr readoffset,
		GLintptr writeoffset,
		GLsizeiptr size
	)
	{
		OGLPLUS_GLFUNC(CopyBufferSubData)(
			GLenum(readtarget),
			GLenum(writetarget),
			readoffset,
			writeoffset,
			size
		);
		OGLPLUS_CHECK(
			CopyBufferSubData,
			ObjectPairError,
			SubjectBinding(readtarget).
			ObjectBinding(writetarget)
		);
	}
#endif // copy buffer

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
	/// Clear the buffer data
	/**
	 *  @see Data
	 *  @see ClearSubData
	 *  @see SubData
	 *  @see CopySubData
	 *
	 *  @throws Error
	 *
	 *  @glverreq{4,3}
	 */
	template <typename GLtype>
	static void ClearData(
		Target target,
		PixelDataInternalFormat internal_format,
		PixelDataFormat format,
		const GLtype* data
	)
	{
		OGLPLUS_GLFUNC(ClearBufferData)(
			GLenum(target),
			GLenum(internal_format),
			GLenum(format),
			GLenum(GetDataType<GLtype>()),
			data
		);
		OGLPLUS_CHECK(
			ClearBufferData,
			ObjectError,
			ObjectBinding(target)
		);
	}

	/// Clear a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see ClearData
	 *  @see SubData
	 *  @see CopySubData
	 *
	 *  @throws Error
	 *
	 *  @glverreq{4,3}
	 */
	template <typename GLtype>
	static void ClearSubData(
		Target target,
		PixelDataInternalFormat internal_format,
		GLintptr offset,
		GLsizeiptr size,
		PixelDataFormat format,
		const GLtype* data
	)
	{
		OGLPLUS_GLFUNC(ClearBufferSubData)(
			GLenum(target),
			GLenum(internal_format),
			offset,
			size,
			GLenum(format),
			GLenum(GetDataType<GLtype>()),
			data
		);
		OGLPLUS_CHECK(
			ClearBufferSubData,
			ObjectError,
			ObjectBinding(target).
			EnumParam(internal_format)
		);
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_buffer_storage
	/// Creates a data store for a buffer object
	/**
	 *  @see Data
	 *  @see SubData
	 *  @see CopySubData
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,buffer_storage}
	 *  @glsymbols
	 *  @glfunref{BufferStorage}
	 */
	template <typename GLtype>
	static void Storage(
		Target target,
		GLsizeiptr size,
		const void* data,
		Bitfield<BufferStorageBit> flags
	)
	{
		OGLPLUS_GLFUNC(BufferStorage)(
			GLenum(target),
			size,
			data,
			GLbitfield(flags)
		);
		OGLPLUS_CHECK(
			BufferStorage,
			ObjectError,
			ObjectBinding(target)
		);
	}

	/// Returns true if the buffer storage is immutable
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,buffer_storage}
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_IMMUTABLE_STORAGE}
	 */
	static bool ImmutableStorage(Target target)
	{
		return GetIntParam(
			target,
			GL_BUFFER_IMMUTABLE_STORAGE
		) == GL_TRUE;
	}

	/// Returns the buffer storage flags
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,buffer_storage}
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_STORAGE_FLAGS}
	 */
	static Bitfield<BufferStorageBit> StorageFlags(Target target)
	{
		return Bitfield<BufferStorageBit>(GLbitfield(
			GetIntParam(target, GL_BUFFER_STORAGE_FLAGS)
		));
	}
#endif

	/// Returns the buffer size
	/**
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_SIZE}
	 *
	 *  @throws Error
	 */
	static GLsizei Size(Target target)
	{
		return GLsizei(GetIntParam(target, GL_BUFFER_SIZE));
	}

	/// Returns the buffer usage
	/**
	 *  @see Access
	 *
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_USAGE}
	 *
	 *  @throws Error
	 */
	static BufferUsage Usage(Target target)
	{
		return BufferUsage(GetIntParam(target, GL_BUFFER_USAGE));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	/// Returns the buffer usage
	/**
	 *  @see Usage
	 *
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_ACCESS}
	 *
	 *  @throws Error
	 */
	static Bitfield<BufferMapAccess> Access(Target target)
	{
		return Bitfield<BufferMapAccess>(
			GLbitfield(GetIntParam(target, GL_BUFFER_ACCESS))
		);
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_NV_shader_buffer_load
	/// Makes buffer currently bound to target accessible to GLSL shaders
	/**
	 *  @glextreq{NV,shader_buffer_load}
	 *  @glsymbols
	 *  @glfunref{MakeBufferResidentNV}
	 *
	 *  @throws Error
	 */
	static void MakeResident(Target target, AccessSpecifier access)
	{
		OGLPLUS_GLFUNC(MakeBufferResidentNV)(
			GLenum(target),
			GLenum(access)
		);
		OGLPLUS_CHECK(
			MakeBufferResidentNV,
			ObjectError,
			ObjectBinding(target)
		);
	}

	/// Makes buffer currently bound to target inaccessible to GLSL shaders
	/**
	 *  @glextreq{NV,shader_buffer_load}
	 *  @glsymbols
	 *  @glfunref{MakeBufferNonResidentNV}
	 *
	 *  @throws Error
	 */
	static void MakeNonResident(Target target)
	{
		OGLPLUS_GLFUNC(MakeBufferNonResidentNV)(GLenum(target));
		OGLPLUS_CHECK(
			MakeBufferNonResidentNV,
			ObjectError,
			ObjectBinding(target)
		);
	}

	/// Returns the GPU address of the buffer currently bound to target
	/**
	 *  @glextreq{NV,shader_buffer_load}
	 *  @glsymbols
	 *  @glfunref{GetBufferParameterui64vNV}
	 *  @gldefref{BUFFER_GPU_ADDRESS_NV}
	 *
	 *  @throws Error
	 */
	static BufferGPUAddress GPUAddress(Target target)
	{
		GLuint64EXT value = 0;
		OGLPLUS_GLFUNC(GetBufferParameterui64vNV)(
			GLenum(target),
			GL_BUFFER_GPU_ADDRESS_NV,
			&value
		);
		OGLPLUS_CHECK(
			GetBufferParameterui64vNV,
			ObjectError,
			ObjectBinding(target)
		);
		return BufferGPUAddress(value);
	}
#endif
};

/// The buffer operations with explicit selector
typedef ObjectOps<tag::ExplicitSel, tag::Buffer>
	BufferOps;

// Helper class for syntax sugar operators
struct BufferTargetAndUsage
{
	BufferTarget target;
	BufferUsage usage;

	BufferTargetAndUsage(BufferTarget t, BufferUsage u)
	 : target(t)
	 , usage(u)
	{ }
};

inline BufferTargetAndUsage operator << (
	BufferTarget target,
	BufferUsage usage
)
{
	return BufferTargetAndUsage(target, usage);
}

// Helper class for syntax sugar operators
struct BufferOpsAndIdxTgt
{
	const BufferOps& buf;
	BufferIndexedTarget target;

	BufferOpsAndIdxTgt(const BufferOps& b, BufferIndexedTarget t)
	 : buf(b)
	 , target(t)
	{ }
};

inline BufferOpsAndIdxTgt operator << (
	const BufferOps& buf,
	BufferIndexedTarget target
)
{
	return BufferOpsAndIdxTgt(buf, target);
}

// Helper class for syntax sugar operators
struct BufferTargetAndOffset
{
	BufferTarget target;
	GLintptr offset;

	BufferTargetAndOffset(BufferTarget t, GLintptr o)
	 : target(t)
	 , offset(o)
	{ }
};

inline BufferTargetAndOffset operator + (
	BufferTarget target,
	GLintptr offset
)
{
	return BufferTargetAndOffset(target, offset);
}

// Bind
inline BufferTarget operator << (
	const BufferOps& buf,
	BufferTarget target
)
{
	buf.Bind(target);
	return target;
}

// BindBase
inline const BufferOps& operator << (
	const BufferOpsAndIdxTgt& bat,
	GLuint index
)
{
	bat.buf.BindBase(bat.target, index);
	return bat.buf;
}

// Data
template <typename GLtype>
inline BufferTarget operator << (
	BufferTarget target,
	const std::vector<GLtype>& data
)
{
	BufferOps::Data(target, data);
	return target;
}

// Data
template <typename GLtype>
inline BufferTarget operator << (
	BufferTargetAndUsage&& tau,
	const std::vector<GLtype>& data
)
{
	BufferOps::Data(tau.target, data, tau.usage);
	return tau.target;
}

// Data
template <typename GLtype, std::size_t Count>
inline BufferTarget operator << (
	BufferTarget target,
	const GLtype (&data)[Count]
)
{
	BufferOps::Data(target, data);
	return target;
}

// Data
template <typename GLtype, std::size_t Count>
inline BufferTarget operator << (
	BufferTargetAndUsage&& tau,
	const GLtype (&data)[Count]
)
{
	BufferOps::Data(tau.target, data, tau.usage);
	return tau.target;
}

// SubData
template <typename GLtype>
inline BufferTarget operator << (
	BufferTargetAndOffset&& tao,
	const std::vector<GLtype>& data
)
{
	BufferOps::SubData(tao.target, tao.offset, data);
	return tao.target;
}

// SubData
template <typename GLtype, std::size_t Count>
inline BufferTarget operator << (
	BufferTargetAndOffset&& tao,
	const GLtype (&data)[Count]
)
{
	BufferOps::SubData(tao.target, tao.offset, data);
	return tao.target;
}

/// Class that can be used to unbind the currently bound buffers
/**
 *  @ingroup oglplus_objects
 */
typedef ObjectZero<ObjZeroOps<tag::ExplicitSel, tag::Buffer>>
	NoBuffer;

/// An @ref oglplus_object encapsulating the OpenGL buffer functionality
/**
 *  @ingroup oglplus_objects
 */
typedef Object<BufferOps> Buffer;

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/buffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
