#include "Assembler.h"
#include "Utils\FileSystem\__FileSystem__.h"

namespace Ablaze
{
	namespace VM
	{

		VMassembler::VMassembler(const String& assemblyFile) : Object(),
			m_Filename(assemblyFile), m_Ops(VirtualMachine::GetOperations())
		{
			
		}

		const String& VMassembler::Assemble(const String& outputFile)
		{
			File f = FileSystem::Open(m_Filename, OpenMode::Read);
			String fileData = FileSystem::ReadText(f);
			f.Close();

			File output = FileSystem::CreateNew(outputFile);
			output = FileSystem::Open(outputFile, OpenMode::WriteAppend);

			std::vector<String> lines = SplitString(fileData, ";");
			for (String line : lines)
			{
				std::vector<String> comps = SplitString(line, ",");
				if (comps.size() > 1)
				{
					String cStr = CleanString(comps[0]);
					if (!cStr.empty())
					{
						FileSystem::WriteText(output, std::to_string(VirtualMachine::FindOperation(cStr).opCode));
						for (int i = 1; i < comps.size(); i++)
						{
							FileSystem::WriteText(output, "," + comps[i]);
						}
						FileSystem::WriteText(output, ";");
					}
				}
				else
				{
					String cStr = CleanString(line);
					if (!cStr.empty())
					{
						FileSystem::WriteText(output, std::to_string(VirtualMachine::FindOperation(cStr).opCode) + ";");
					}
				}
			}

			output.Close();
			return outputFile;
		}

		int* VMassembler::Assemble()
		{
			return nullptr;
		}

		String VMassembler::ToString() const
		{
			return "VMassembler";
		}

	}
}