#include "XMLwriter.h"
#include "Utils\Filesystem\Filesystem.h"

namespace Ablaze
{

	XMLwriter::XMLwriter(const Filepath& path) : Object(),
		m_Filepath(path), m_OpenedFile(), m_Current(nullptr)
	{	
		m_OpenedFile = Filesystem::OpenFile(m_Filepath, OpenFlags::Override);
		m_OpenedFile.Close();
		m_OpenedFile = Filesystem::OpenFile(m_Filepath, OpenFlags::Append);

		m_OpenedFile.WriteText("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	}

	XMLwriter::~XMLwriter()
	{
		m_OpenedFile.Close();
	}

	const Filepath& XMLwriter::Path() const
	{
		return m_Filepath;
	}

	void XMLwriter::BeginNode(const String& name)
	{
		XMLnode* parent = m_Current;
		XMLnode* newNode = new XMLnode;
		newNode->SetName(name);
		newNode->SetParent(parent);
		newNode->SetData("");
		if (parent != nullptr)
		{
			parent->AddChild(newNode);
		}
		m_Current = newNode;
	}

	void XMLwriter::EndNode()
	{
		XMLnode* prev = m_Current;
		m_Current = prev->Parent();
		if (m_Current == nullptr)
		{
			// Node is finished
			WriteNode(prev, 0);
			delete prev;
		}
	}

	void XMLwriter::AddAttribute(const String& attributeName, const String& attributeValue)
	{
		m_Current->AddAttribute(attributeName, attributeValue);
	}

	void XMLwriter::AddAttribute(const String& attributeName, float value)
	{
		AddAttribute(attributeName, std::to_string(value));
	}

	void XMLwriter::AddAttribute(const String& attributeName, int value)
	{
		AddAttribute(attributeName, std::to_string(value));
	}

	void XMLwriter::AddAttribute(const String& attributeName, const Object& value)
	{
		AddAttribute(attributeName, value.ToString());
	}

	void XMLwriter::AddData(const String& data)
	{
		m_Current->SetData(m_Current->Data() + data);
	}

	void XMLwriter::AddData(float data)
	{
		AddData(std::to_string(data));
	}

	void XMLwriter::AddData(int data)
	{
		AddData(std::to_string(data));
	}

	void XMLwriter::AddData(const Object& data)
	{
		AddData(data.ToString());
	}

	String XMLwriter::ToString() const
	{
		return "XMLwriter";
	}

	void XMLwriter::WriteNode(XMLnode* node, int depth)
	{
		String line = "";
		for (int i = 0; i < depth; i++)
		{
			line += "\t";
		}
		m_OpenedFile.WriteText(line + "<" + node->Name() + AttributesToString(node) + ">" + node->Data());
		if (node->ChildCount() > 0)
		{
			m_OpenedFile.WriteText("\n");
		}
		for (XMLnode* child : node->Children())
		{
			WriteNode(child, depth + 1);
		}
		if (node->ChildCount() > 0)
		{
			m_OpenedFile.WriteText(line + "</" + node->Name() + ">" + "\n");
		}
		else
		{
			m_OpenedFile.WriteText("</" + node->Name() + ">" + "\n");
		}
	}

	String XMLwriter::AttributesToString(XMLnode* node)
	{
		String line = "";
		for (auto& pair : node->Attributes())
		{
			line += " ";
			line += pair.first + "=\"";
			line += pair.second + "\"";
		}
		if (line.length() == 1)
		{
			return "";
		}
		return line;
	}

}