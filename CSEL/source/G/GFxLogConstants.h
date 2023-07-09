#pragma once

namespace ConsoleRE
{
	class GFxLogConstants
	{
	public:
		enum class LogMessageType
		{
			Log_Channel_General		= 0x10,
			Log_Channel_Script		= 0x20,
			Log_Channel_Parse		= 0x30,
			Log_Channel_Action		= 0x40,
			Log_Channel_Debug		= 0x50,
			Log_Channel_Mask		= 0xF0,
			Log_MessageType_Error	= 0,
			Log_MessageType_Warning = 1,
			Log_MessageType_Message = 2,
			Log_Error				= Log_Channel_General | Log_MessageType_Error,
			Log_Warning				= Log_Channel_General | Log_MessageType_Warning,
			Log_Message				= Log_Channel_General | Log_MessageType_Message,
			Log_ScriptError			= Log_Channel_Script | Log_MessageType_Error,
			Log_ScriptWarning		= Log_Channel_Script | Log_MessageType_Warning,
			Log_ScriptMessage		= Log_Channel_Script | Log_MessageType_Message,
			Log_Parse				= Log_Channel_Parse | 0,
			Log_ParseShape			= Log_Channel_Parse | 1,
			Log_ParseMorphShape		= Log_Channel_Parse | 2,
			Log_ParseAction			= Log_Channel_Parse | 3,
			Log_Action				= Log_Channel_Action | 0,
		};
	};
}