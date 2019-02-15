#pragma once

#include <string>  // string

#include "RE/FormTypes.h"

class Script;
class ScriptLocals;
class ScriptLineBuffer;
class ScriptBuffer;


namespace RE
{
	struct SCRIPT_PARAMETER
	{
		enum class Type : UInt32
		{
			kString = 0x0,
			kInteger = 0x1,
			kFloat = 0x2,
			kObjectReference = 0x4,
			kActorValue = 0x5,
			kActor = 0x6,
			kSpellItem = 0x7,
			kAxis = 0x8,
			kCell = 0x9,
			kAnimationGroup = 0x0A,
			kMagicItem = 0x0B,
			kSound = 0x0C,
			kTopic = 0x0D,
			kQuest = 0x0E,
			kRace = 0x0F,
			kClass = 0x10,
			kFaction = 0x11,
			kSex = 0x12,
			kObject = 0x15,
			kVariableName = 0x16,
			kQuestStage = 0x17,
			kMapMarker = 0x18,
			kActorBase = 0x19,
			kCoontainer = 0x1A,
			kWorldSpace = 0x1B,
			kCrimeType = 0x1C,
			kPackage = 0x1D,
			kMagicEffect = 0x1F,
			kWeather = 0x21,
			kOwner = 0x23,
			kEffectShader = 0x24,
			kFormList = 0x25,
			kPerk = 0x27,
			kNote = 0x28,
			kMiscellaneousStat = 0x29,
			kImagespaceModifier = 0x2A,
			kEventFunction = 0x2E,
			kEventMember = 0x2F,
			kEventData = 0x30,
			kVoice = 0x31,
			kEncounterZone = 0x32,
			kMessage = 0x34,
			kObjectID = 0x35,
			kAlignment = 0x36,
			kEquipType = 0x37,
			kMusic = 0x39,
			kKeyword = 0x3B,
			kRefType = 0x3C,
			kLocation = 0x3D,
			kForm = 0x3E,
			kQuestAlias = 0x3F,
			kShout = 0x40,
			kWordOfPower = 0x41,
			kScene = 0x43,
			kHand = 0x44,	// right hand or left hand
			kAssociationType = 0x45,
			kWardState = 0x46,
			kPackageData_PossiblyNull = 0x47,
			kPackageData_Numeric = 0x48,
			kFurnitureAnimType = 0x49,
			kFurnitureEntryType = 0x4A,
			kVMVariableName = 0x4C,
			kPackageData = 0x4E,
			kKnowableForm = 0x51,
			kRegion = 0x52
		};


		const char*	typeStr;	// 00
		Type		typeID;		// 08 - ParamType
		UInt32		isOptional;	// 0C - do other bits do things?
	};


	struct CommandInfo
	{
		enum
		{
			kCommand_ConsoleCommandsBegin = 0x0000,
			kCommand_ConsoleCommandsend = 0x01B3,
			kCommand_ConsoleOpBase = 0x0100,

			kCommand_ScriptCommandsBegin = 0x01B4,
			kCommand_ScriptCommandsEnd = 0x02DF,
			kCommand_ScriptOpBase = 0x1000
		};


#pragma pack(push, 1)
		struct Chunk
		{};


		struct StringChunk : public Chunk
		{
			std::string	GetString() const;
			Chunk*		GetNext();


			// members
			UInt16	length;	// 00
			char	str[1];	// 02
		};


		struct IntegerChunk : public Chunk
		{
			int		GetInteger() const;
			Chunk*	GetNext();


			// members
			char	unk00;	// 00
			int		value;	// 01
		};
#pragma pack(pop)


		struct ScriptData
		{
			Chunk*	GetChunk();


			// members
			UInt16	opcode;		// 00
			UInt16	chunkSize;	// 02
			UInt16	numParams;	// 04
			UInt16	strLen;		// 06
			char	str[1];		// 08
		};


		typedef bool(*FnExecute)(const SCRIPT_PARAMETER* a_paramInfo, ScriptData* a_scriptData, TESObjectREFR* a_thisObj, TESObjectREFR* a_containingObj, Script* a_scriptObj, ScriptLocals* a_locals, double& a_result, UInt32& a_opcodeOffsetPtr);
		typedef bool(*FnParse)(UInt32 a_numParams, const SCRIPT_PARAMETER* a_paramInfo, ScriptLineBuffer* a_lineBuf, ScriptBuffer* a_scriptBuf);
		typedef bool(*FnEval)(TESObjectREFR* a_thisObj, void* a_arg1, void* a_arg2, double& a_result);


		// members
		const char*				longName;		// 00
		const char*				shortName;		// 08
		UInt32					opcode;			// 10
		UInt32					pad14;			// 14
		const char*				helpText;		// 18
		bool					isRefRequired;	// 20
		UInt8					pad21;			// 21
		UInt16					numParams;		// 22
		UInt32					pad24;			// 24
		const SCRIPT_PARAMETER*	params;			// 28

		// handlers
		FnExecute				execute;		// 30
		FnParse					parse;			// 38
		FnEval					eval;			// 40

		UInt32					flags;			// 48
		UInt32					pad4C;			// 4C

		template <std::size_t SIZE>
		void					SetParameters(const SCRIPT_PARAMETER(&a_params)[SIZE])
		{
			numParams = SIZE;
			params = a_params;
		}
		void					SetParameters();
		static CommandInfo*		GetFirstScriptCommand();
		static CommandInfo*		GetFirstConsoleCommand();
		static CommandInfo*		Locate(const char* a_longName);
		static bool				ExtractArgs(SCRIPT_PARAMETER* a_paramInfo, void* a_scriptData, UInt32* a_arg2, TESObjectREFR* a_thisObj, TESObjectREFR* a_containingObj, Script* a_script, ScriptLocals* a_eventList, ...);
		static bool				Cmd_Default_Execute(const SCRIPT_PARAMETER* a_paramInfo, const char* a_scriptData, TESObjectREFR* a_thisObj, TESObjectREFR* a_containingObj, Script* a_scriptObj, ScriptLocals* a_locals, double& a_result, UInt32& a_opcodeOffsetPtr);
		static bool				Cmd_Default_Parse(UInt32 a_numParams, const SCRIPT_PARAMETER* a_paramInfo, ScriptLineBuffer* a_lineBuf, ScriptBuffer* a_scriptBuf);
		static bool				Cmd_Default_Eval(TESObjectREFR* a_thisObj, void* a_arg1, void* a_arg2, double* a_result);
	};
	STATIC_ASSERT(sizeof(CommandInfo) == 0x50);
}