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
		const std::vector<VertexAttrib>& GetAllAttributes() const;
		int GetAttribCount() const;

		void AddAttribute(const String& attributeName, const VertexAttrib& attribute);
		void AddAttribute(const String& attributeName, int index, int count, GLenum dataType, bool normalized = false);
		void AddAttribute(const String& attributeName, int index, int count, bool normalized = false);
		void AddAttribute(Attribute attributeName, const VertexAttrib& attribute);
		void AddAttribute(Attribute attributeName, int index, int count, GLenum dataType, bool normalized = false);
		void AddAttribute(Attribute attributeName, int index, int count, bool normalized = false);
		void AddAttribute(const String& attributeName, int count, GLenum dataType, bool normalized = false);
		void AddAttribute(const String& attributeName, int count, bool normalized = false);
		void AddAttribute(Attribute attributeName, int count, GLenum dataType, bool normalized = false);
		void AddAttribute(Attribute attributeName, int count, bool normalized = false);

		String ToString() const override;

	public:
		static BufferLayout Default();
		static BufferLayout Vertex();

	};

}