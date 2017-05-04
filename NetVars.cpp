#include "NetVars.h"
#include "ClientRecvProps.h"
#include "CRC32.h"
#include "Utilities.h"

#include "Header.h"

CNetVar NetVar;

const char* AlignText(int align)
{
	static char buffer[256];
	int i = 0;
	for (i = 0; i < align; i++)
	{
		buffer[i] = ' ';
	}
	buffer[i + 1] = 0;
	return buffer;
}

void CNetVar::RetrieveClasses()
{
	//Utilities::EnableLogFile(NETVAR_FILENAME);

	ClientClass *clientClass = Interfaces::Client->GetAllClasses();

	if (!clientClass)
		return;

	//Clear netvar vector incase of another call, not necesarry as it doesnt add duplicates

	vars.clear();

	while (clientClass != 0)
	{
		if (clientClass == 0)
			break;

		LogNetVar(clientClass->m_pRecvTable, 0);

		clientClass = clientClass->m_pNext;
	}
}

void CNetVar::LogNetVar(RecvTable *table, int align)
{
	if (table->m_nProps < 0)
		return;

	for (auto i = 0; i < table->m_nProps; ++i)
	{
		RecvProp *prop = &table->m_pProps[i];

		if (!prop)
			continue;

		char szCRC32[150];

		sprintf_s(szCRC32, "%s%s", table->m_pNetTableName, prop->m_pVarName);

		DWORD_PTR dwCRC32 = CRC32((void*)szCRC32, strlen(szCRC32));

		//Dont add duplicates

		bool bAddNetVar = true;

		for (auto netvar = 0; netvar < (int)vars.size(); ++netvar)
		{
			netvar_info_s *netvars = &vars[netvar];

			if (netvars->dwCRC32 == dwCRC32)
				bAddNetVar = false;


			if (netvars->dwCRC32 == dwCRC32 && netvars->dwOffset != prop->m_Offset) //just a test if any crc collide with another (didnt happen obviously)
			{
			}
		}

		if (bAddNetVar) //avoid adding duplicates (faster lookup)
		{
			netvar_info_s tmp;
			strcpy_s(tmp.szTableName, table->m_pNetTableName);
			strcpy_s(tmp.szPropName, prop->m_pVarName);
			tmp.dwCRC32 = dwCRC32;

			tmp.dwOffset = prop->m_Offset;

			vars.push_back(tmp);
		}

		if (prop->m_pDataTable)
			LogNetVar(prop->m_pDataTable, 5);
	}
}

DWORD_PTR CNetVar::GetNetVar(DWORD_PTR dwCRC32) //returns 0xFFFFFFFF (-1) if not found (ex: if(GetNetVar(0xD34DB33F)==-1) return false;
{
	for (auto i = 0; i < (int)vars.size(); ++i)
	{
		if (vars[i].dwCRC32 == dwCRC32)
			return vars[i].dwOffset;
	}

	return 0xFFFFFFFF;
}