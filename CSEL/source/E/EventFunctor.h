#pragma once
//
//#include "../../source/I/IFunctionArguments.h"
//#include "../../source/V/VirtualMachine.h"
//#include "../../source/V/VirtualMachine_Info.h"
//
//namespace ConsoleRE
//{
//	template <typename T1, typename T2>
//	class EQF2 : public IFunctionArguments
//	{
//	public:
//
//		EQF2(BSFixedString& a_name, T1 a_a1, T2 a_a2)
//		{
//			this->name = a_name.data;
//			this->A1 = a_a1;
//			this->A2 = a_a2;
//		}
//
//		virtual bool Unk_02(UNKIFUC<Arguments>* a_dst)
//		{
//			auto* VM = BSScript::Internal::VirtualMachine::GetSingleton();
//
//			a_dst->Resize(2);
//			Pack(a_dst->Get(1), this->A1, VM);
//			Pack(a_dst->Get(2), this->A2, VM);
//		}
//
//		void Queue(uint64_t Handle, BSFixedString& EventName)
//		{
//			BSScript::Internal::VirtualMachine::GetSingleton()->SendEvent(Handle, EventName, this);
//		}
//	private:
//		BSFixedString name;
//		T1			  A1;
//		T2			  A2;
//	};
//
//	template <typename T1, typename T2, typename T3>
//	class EQF3 : public IFunctionArguments
//	{
//	public:
//		void INIT(BSFixedString& a_name, T1 a_a1, T2 a_a2, T3 a_a3)
//		{
//			this->name = a_name.data;
//		
//			this->A1 = a_a1;
//			this->A2 = a_a2;
//			this->A3 = a_a3;
//		}
//
//		virtual bool Unk_02(UNKIFUC<Arguments>* a_dst)
//		{
//			auto* VM = BSScript::Internal::VirtualMachine::GetSingleton();
//
//			a_dst->Resize(3);
//			Pack(a_dst->Get(1), this->A1, VM);
//			Pack(a_dst->Get(2), this->A2, VM);
//			Pack(a_dst->Get(3), this->A3, VM);
//		}
//
//		void Queue(uint64_t Handle, BSFixedString& EventName)
//		{
//			BSScript::Internal::VirtualMachine::GetSingleton()->SendEvent(Handle, EventName, this);
//		}
//
//	private:
//		BSFixedString name;
//		T1			  A1;
//		T2			  A2;
//		T3			  A3;
//	};
//
//	template <typename T1, typename T2, typename T3, typename T4>
//	class EQF4 : public IFunctionArguments
//	{
//	public:
//		EQF4(BSFixedString& a_name, T1 a_a1, T2 a_a2, T3 a_a3, T4 a_a4)
//		{
//			this->name = a_name.data;
//			this->A1 = a_a1;
//			this->A2 = a_a2;
//			this->A3 = a_a3;
//			this->A4 = a_a4;
//		}
//
//		virtual bool Unk_02(UNKIFUC<Arguments>* a_dst)
//		{
//			auto* VM = BSScript::Internal::VirtualMachine::GetSingleton();
//
//			a_dst->Resize(4);
//			Pack(a_dst->Get(1), this->A1, VM);
//			Pack(a_dst->Get(2), this->A2, VM);
//			Pack(a_dst->Get(3), this->A3, VM);
//			Pack(a_dst->Get(4), this->A4, VM);
//		}
//
//		void Queue(uint64_t Handle, BSFixedString& EventName)
//		{
//			BSScript::Internal::VirtualMachine::GetSingleton()->SendEvent(Handle, EventName, this);
//		}
//	private:
//		BSFixedString name;
//		T1			  A1;
//		T2			  A2;
//		T3			  A3;
//		T4			  A4;
//	};
//}