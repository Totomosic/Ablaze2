#include "XMLloader.h"
#include "Utils\Filesystem\Filepath.h"
#include "Utils\Filesystem\Filesystem.h"
#include "Utils\Functions.h"

namespace Ablaze
{

	XMLnode* LoadXMLFile(const Filepath& path)
	{
		File f = Filesystem::OpenFile(path, OpenFlags::Read);
		return LoadXMLSource(f.ReadText());
	}

	XMLnode* LoadXMLSource(const String& src)
	{
		String source = CleanString(src, { '\n', '\r', '\t' });
		XMLnode* root = nullptr;
		XMLnode* current = root;
		std::stringstream stream;

		bool isBeginTag = false;

		for (int index = 0; index < source.length(); index++)
		{
			if (source[index] == '<' && source[index + 1] != '/')
			{
				// Begin Tag
				XMLnode* node = new XMLnode;
				if (root == nullptr && source[index + 1] != '?')
				{
					root = node;
				}
				else if (source[index + 1] != '?')
				{
					node->SetParent(current);
					current->AddChild(node);
				}
				current = node;
				isBeginTag = true;
				stream = std::stringstream();
			}
			else if (source[index] == '<')
			{
				// Begin of ending tag
				String data = stream.str();
				current->SetData(data);
				stream = std::stringstream();
				isBeginTag = false;
			}
			else if (source[index] == '>')
			{
				// End of tag
				String tagData = stream.str();
				// Split attributes and names and add them to current
				if (isBeginTag)
				{
					std::vector<String> parts = SplitString(tagData, " ");
					String& name = parts[0];
					current->SetName(name);

					String attributes = "";
					for (int i = 1; i < parts.size(); i++)
					{
						attributes += parts[i] + " ";
					}
					if (attributes.length() != 0)
					{
						std::stringstream ss;
						String name;
						String value;
						bool isValue = false;
						if (attributes.find('=') != String::npos)
						{
							for (int i = 0; i < attributes.length(); i++)
							{
								char thisChar = attributes[i];
								if (thisChar == '=')
								{
									name = ss.str();
									isValue = false;
									ss = std::stringstream();
								}
								else if (thisChar == '"')
								{
									isValue = !isValue;
									if (isValue == false)
									{
										value = ss.str();
										current->AddAttribute(name, value);
										isValue = false;
										ss = std::stringstream();
									}
								}
								else if (thisChar == ' ')
								{
									if (isValue)
									{
										ss << ' ';
									}
								}
								else
								{
									ss << thisChar;
								}
							}
						}
					}
					if (source[index - 1] == '/')
					{
						current = current->Parent();
					}
					stream = std::stringstream();
				}
				else
				{
					// Maybe validate that the closing tag is correct
					current = current->Parent();
					stream = std::stringstream();
				}
			}
			else
			{
				if (source[index] != '/')
				{
					stream << source[index];
				}
			}

		}

		return root;
	}

}