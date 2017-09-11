#include "BufferLayout.h"

namespace Ablaze
{

	BufferLayout::BufferLayout() : Object()
	{

	}

	int BufferLayout::GetStride() const
	{
		return m_Stride;
	}

	int BufferLayout::IndexOf(const String& attributeName) const
	{
		return GetAttribute(attributeName).index;
	}

	int BufferLayout::CountOf(const String& attributeName) const
	{
		return GetAttribute(attributeName).count;
	}

	int BufferLayout::OffsetOf(const String& attributeName) const
	{
		return GetAttribute(attributeName).offset;
	}

	VertexAttrib& BufferLayout::GetAttribute(const String& attributeName)
	{
		return m_Attributes[attributeName];
	}

	const VertexAttrib& BufferLayout::GetAttribute(const String& attributeName) const
	{
		return m_Attributes.at(attributeName);
	}

	int BufferLayout::IndexOf(Attribute attributeName) const
	{
		return IndexOf(std::to_string((int)attributeName));
	}

	int BufferLayout::CountOf(Attribute attributeName) const
	{
		return CountOf(std::to_string((int)attributeName));
	}

	int BufferLayout::OffsetOf(Attribute attributeName) const
	{
		return OffsetOf(std::to_string((int)attributeName));
	}

	VertexAttrib& BufferLayout::GetAttribute(Attribute attributeName)
	{
		return GetAttribute(std::to_string((int)attributeName));
	}

	const VertexAttrib& BufferLayout::GetAttribute(Attribute attributeName) const
	{
		return GetAttribute(std::to_string((int)attributeName));
	}

	const std::vector<VertexAttrib>& BufferLayout::GetAllAttributes() const
	{
		std::vector<VertexAttrib> attribs;
		for (auto key : m_Attributes)
		{
			attribs.push_back(key.second);
		}
		return attribs;
	}

	void BufferLayout::AddAttribute(const String& attributeName, const VertexAttrib& attribute)
	{
		m_Attributes[attributeName] = attribute;
		m_Stride += attribute.count * sizeof(float); // TODO: create lookup for byte size of each data type
	}

	void BufferLayout::AddAttribute(const String& attributeName, int index, int count, GLenum dataType, bool normalized)
	{
		AddAttribute(attributeName, VertexAttrib(index, count, dataType, normalized, m_Stride));
	}

	void BufferLayout::AddAttribute(const String& attributeName, int index, int count, bool normalized)
	{
		AddAttribute(attributeName, index, count, GL_FLOAT, normalized);
	}

	void BufferLayout::AddAttribute(Attribute attributeName, const VertexAttrib& attribute)
	{
		AddAttribute(std::to_string((int)attributeName), attribute);
	}

	void BufferLayout::AddAttribute(Attribute attributeName, int index, int count, GLenum dataType, bool normalized)
	{
		AddAttribute(std::to_string((int)attributeName), index, count, dataType, normalized);
	}

	void BufferLayout::AddAttribute(Attribute attributeName, int index, int count, bool normalized)
	{
		AddAttribute(std::to_string((int)attributeName), index, count, normalized);
	}

	String BufferLayout::ToString() const
	{
		return "Buffer Layout";
	}

}