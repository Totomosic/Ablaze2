#include "JSONloader.h"
#include "Utils\Filesystem\Filepath.h"
#include "Utils\Filesystem\Filesystem.h"
#include "Utils\Functions.h"

namespace Ablaze
{

	JSONnode* LoadJSONFile(const Filepath& filename)
	{
		File file = Filesystem::OpenFile(filename, OpenFlags::Read);
		String source = file.ReadText();
		file.Close();
		return LoadJSONSource(source);
	}

	JSONnode* LoadJSONSource(const String& src)
	{
		String source = CleanString(src);

		JSONnode* root = new JSONnode({ "", source });
		JSONnode* current = root;
		std::stringstream stream;

		for (int index = 0; index < source.length(); index++)
		{			
			if (source[index] == '\"')
			{
				continue;
			}
			else if (source[index] == '{')
			{
				// Enter new scope
				JSONnode* child = new JSONnode;
				current->AddChild(child);
				current = child;
			}
			else if (source[index] == '}')
			{
				// Leave scope
				current->Data() = stream.str();
				current = current->Parent();
			}
			else if (source[index] == ':')
			{
				// Switch from key to value
				current->Key() = stream.str();
				stream = std::stringstream();
			}
			else if (source[index] == ',')
			{
				// Move to next attribute
				current->Data() = stream.str();
				stream = std::stringstream();

				JSONnode* node = new JSONnode;
				current->Parent()->AddChild(node);
				current = node;
			}
			else if (source[index] == '[')
			{
				if (source[index + 1] != ']')
				{
					JSONnode* node = new JSONnode;
					current->AddChild(node);
					current = node;
				}
				else
				{
					index++;
				}
			}
			else if (source[index] == ']')
			{
				current->Data() = stream.str();
				current = current->Parent();
				stream.clear();
			}
			else
			{
				stream << source[index];
			}
		}

		return root;
	}

}