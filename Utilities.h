#pragma once

// Includes
#include "CommonIncludes.h"
#include <time.h>

// Utilities Namespace
// Purpose: Contains misc functionality for memory related functionality
namespace Utilities
{
	// Memory utils
	// Purpose: Provides memeory related functionality (pattern scanning ect)
	namespace Memory
	{
		// Waits for a module to be available, before returning it's base address
		DWORD WaitOnModuleHandle(std::string moduleName);

		// Attempts to locate the given signature and mask in a memory range
		// Returns the address at which it has been found
		DWORD FindPattern(std::string moduleName, BYTE* Mask, char* szMask);

		// Attempts to locate the given text in a memory range
		// Returns the address at which it has been found
		DWORD FindTextPattern(std::string moduleName, char* string);

		DWORD FindPatternV2(std::string moduleName, std::string pattern);
		template <typename T>
		T* CaptureInterface(std::string strModule, std::string strInterface)
		{
			typedef T* (*CreateInterfaceFn)(const char* szName, int iReturn);
			CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(strModule.c_str()), "CreateInterface");

			return CreateInterface(strInterface.c_str(), 0);
		}

		class VMTManager
		{
		private:
			DWORD	*CustomTable;
			bool	initComplete;
			DWORD	*OriginalTable;
			DWORD	*Instance;

			int		MethodCount(DWORD* InstancePointer);

		public:
			bool	Initialise(DWORD* InstancePointer); // Pass a &class

			DWORD	HookMethod(DWORD NewFunction, int Index);
			void	UnhookMethod(int Index);

			void	RestoreOriginal();
			void	RestoreCustom();

			template<typename T>
			T GetMethod(size_t nIndex)
			{
				return (T)OriginalTable[nIndex];
			}

			DWORD	GetOriginalFunction(int Index);
		};
	};
};

