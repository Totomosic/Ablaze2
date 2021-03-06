#pragma once
#include "Common.h"
#include "VertexAttrib.h"

namespace Ablaze
{

	enum class Attribute
	{
		Position,
		Normal,
		TexCoord,
		Color,
		Tangent
	};

	enum class DataType : GLenum
	{
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
		Float = GL_FLOAT,
		Double = GL_DOUBLE
	};

	class AB_API BufferLayout : public Object
	{
	private:
		std::unordered_map<String, VertexAttrib> m_Attributes;
		int m_Stride;
		int m_AttribCount;

	public:
		BufferLayout();

		int GetStride() const;
		int OffsetOf(const String& attributeName) const;
		int IndexOf(const String& attributeName) const;
		int CountOf(const String& attributeName) const;
		VertexAttrib& GetAttribute(const String& attributeName);
		const VertexAttrib& GetAttribute(const String& attributeName) const;
		int OffsetOf(Attribute attributeName) const;
		int IndexOf(Attribute attributeName) const;
		int CountOf(Attribute attributeName) const;
		VertexAttrib& GetAttribute(Attribute attributeName);
		const VertexAttrib& GetAttribute(Attribute attributeName) const;
		std::vector<VertexAttrib> GetAllAttributes() const;
		int GetAttribCount() const;

		void AddAttribute(const String& attributeName, const VertexAttrib& attribute);
		void AddAttribute(const String& attributeName, int index, int count, DataType dataType, bool normalized = false);
		void AddAttribute(const String& attributeName, int index, int count, bool normalized = false);
		void AddAttribute(Attribute attributeName, const VertexAttrib& attribute);
		void AddAttribute(Attribute attributeName, int index, int count, DataType dataType, bool normalized = false);
		void AddAttribute(Attribute attributeName, int index, int count, bool normalized = false);
		void AddAttribute(const String& attributeName, int count, DataType dataType, bool normalized = false);
		void AddAttribute(const String& attributeName, int count, bool normalized = false);
		void AddAttribute(Attribute attributeName, int count, DataType dataType, bool normalized = false);
		void AddAttribute(Attribute attributeName, int count, bool normalized = false);

		String ToString() const override;

	public:
		static BufferLayout Default();
		static BufferLayout Vertex();

	};

}