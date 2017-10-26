#pragma once
#include "VirtualMachine.h"

namespace Ablaze
{
	namespace VM
	{

		class VMassembler : public Object
		{
		private:
			String m_Filename;
			VMoperation** m_Ops;

		public:
			VMassembler(const String& assemblyFile);

			const String& Assemble(const String& outputFile);
			int* Assemble();

			String ToString() const override;

		};

	}
}