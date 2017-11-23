#include "JSONloader.h"
#include "Utils\FileSystem\__FileSystem__.h"
#include "Utils\Functions.h"

namespace Ablaze
{

	JSONnode* LoadJSONFile(const String& filename)
	{
		File file = Filesystem::OpenFile(filename, OpenFlags::Read);
		String source = file.ReadText();
		file.Close();
		return LoadJSONSource(source);
	}

	JSONnode* LoadJSONSource(String source)
	{
		source = CleanString(source);

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
				JSONnode* node = new JSONnode;
				current->AddChild(node);
				current = node;
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