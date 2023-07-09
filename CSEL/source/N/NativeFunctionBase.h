#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSFixedString.h"
#include "../I/IFunction.h"
#include "../T/TypeInfo.h"
#include "../N/NativeFunctionParameterInfo.h"

#include <stdio.h>
#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Internal
		{ 
			class VirtualMachine; 
		}

		class StackFrame;
		class Variable;

		namespace NF_util
		{
			class NativeFunctionBase : public IFunction
			{
			public:
				NativeFunctionBase() = delete;

				explicit NativeFunctionBase(const char* a_fnName, const char* a_className, bool a_isStatic, uint16_t a_numParams) : m_name(a_fnName), m_objectName(a_className), m_params(a_numParams, 0), m_isStatic(a_isStatic)
				{
					size_t num = 1;
					std::string param("param");
					for (auto& entry : m_params.m_entries)
					{
						auto combined = param + std::to_string(num);
						entry.first = combined.c_str();
						num++;
					}
				}

				
				~NativeFunctionBase() override = default;

				// override (IFunction)
				const BSFixedString&		GetName() override				
				{ 
					return m_name; 
				}

				const BSFixedString&		GetObjectTypeName() override
				{ 
					return m_objectName; 
				}

				const BSFixedString&		GetStateName() override
				{ 
					return m_stateName; 
				}

				TypeInfo					GetReturnType()	override		
				{ 
					return m_returnType; 
				}

				uint32_t					GetParamCount()	override		
				{ 
					return m_params.m_totalEntries; 
				}
				
				void						GetParam(uint32_t a_idx, BSFixedString& a_nameOut, TypeInfo& a_typeOut) override 
				{ 
					if (a_idx < m_params.m_paramCount)
					{
						auto& elem = m_params.m_entries[a_idx];
						a_nameOut = elem.first;
						a_typeOut = elem.second;
					}
					else
					{
						a_nameOut = "";
						a_typeOut.SetType(TypeInfo::RawType::kNone);
					}
				}
				
				uint32_t					GetStackFrameSize()	override 
				{ 
					return m_params.m_totalEntries;
				}
				
				bool						GetIsNative() override
				{ 
					return true;
				}

				bool						GetIsStatic() override
				{ 
					return m_isStatic;
				}

				bool						GetIsEmpty() override
				{ 
					return 0;																																																						  
				}

				uint32_t					GetFunctionType() override 
				{ 
					return 0;
				}

				uint32_t					GetUserFlags() override 
				{ 
					return m_flags;
				}

				BSFixedString&				GetDocString() override
				{
					return m_docString;
				}

				void						InsertLocals(StackFrame* a_frame) override
				{
				}

				uint32_t					Call(BSTSmartPointer<Stack>& a_stack, ErrorLogger* a_logger, Internal::VirtualMachine* a_vm, bool a_arg4) override
				{ 
					using func_t = uint32_t(NativeFunctionBase* const, BSTSmartPointer<Stack>& a_stack, ErrorLogger* a_logger, Internal::VirtualMachine* a_vm, bool a_arg4);
					Relocation<func_t*> func("", 0x154CE40);
					return func(this, a_stack, a_logger, a_vm, a_arg4);
				}

				BSFixedString&				GetSourceFilename()	override
				{ 
					static BSFixedString native("<native>");
					return native;
				}

				bool						TranslateIPToLineNumber(uint32_t, uint32_t& a_lineNumberOut) override
				{ 
					a_lineNumberOut = 0;
					return false;
				}

				bool						GetVarNameForStackIndex(uint32_t a_idx, BSFixedString& a_nameOut) override
				{
					if (a_idx < m_params.m_paramCount)
					{
						a_nameOut = m_params.m_entries[a_idx].first;
						return true;
					}
					else
					{
						a_nameOut = "";
						return false;
					}
				}


				bool						CanBeCalledFromTasklets() override 
				{ 
					return m_isCallableFromTasklet;
				}
				
				void						SetCallableFromTasklets(bool a_callable) override
				{ 
					m_isCallableFromTasklet = a_callable;
				}

				// add (NativeFunctionBase)
				virtual bool						HasFunc(void) = 0;
				virtual bool						Run(Variable& a_base, Internal::VirtualMachine& VM, uint32_t StackID, Variable& a_result, StackFrame& a_frame) = 0;
			public:
				BSFixedString								m_name;								// 0x10
				BSFixedString								m_objectName;						// 0x18
				BSFixedString								m_stateName{ "" };					// 0x20
				TypeInfo									m_returnType;						// 0x28
				Internal::NativeFunctionParameterInfo		m_params;							// 0x30
				bool										m_isStatic;							// 0x40
				bool										m_isCallableFromTasklet{ false };	// 0x41
				bool										m_isLatent{ false };				// 0x42
				uint8_t										m_pad43{ 0 };						// 0x43
				uint32_t									m_flags{ 0 };						// 0x44
				BSFixedString								m_docString;						// 0x48
			};
		}
	}
}