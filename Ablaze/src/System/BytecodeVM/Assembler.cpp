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
			File f = Filesystem::OpenFile(m_Filename, OpenFlags::Read);
			String fileData = f.ReadText();
			f.Close();

			File output = Filesystem::CreateNewFile(outputFile);
			output = Filesystem::OpenFile(outputFile);

			std::vector<String> lines = SplitString(fileData, ";");
			for (String line : lines)
			{
				std::vector<String> comps = SplitString(line, ",");
				if (comps.size() > 1)
				{
					String cStr = CleanString(comps[0]);
					if (!cStr.empty())
					{
						output << std::to_string(VirtualMachine::FindOperation(cStr).opCode);
						for (int i = 1; i < comps.size(); i++)
						{
							output << "," + comps[i];
						}
						output << ";";
					}
				}
				else
				{
					String cStr = CleanString(line);
					if (!cStr.empty())
					{
						output << std::to_string(VirtualMachine::FindOperation(cStr).opCode) << ";";
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