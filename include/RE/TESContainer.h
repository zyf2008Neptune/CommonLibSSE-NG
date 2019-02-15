#pragma once

#include "skse64/GameFormComponents.h"  // BaseFormComponent

#include "RE/FormTypes.h"


namespace RE
{
	class TESContainer : public BaseFormComponent
	{
	public:
		struct Entry	// CNTO
		{
			struct ExtraData // COED
			{
				TESForm*	owner;			// 00
				SInt32		requiredRank;	// 08
				UInt32		pad0C;			// 0C
				float		condition;		// 10
				UInt32		pad14;			// 14
			};
			STATIC_ASSERT(sizeof(ExtraData) == 0x18);


			UInt32		count;	// 00
			UInt32		pad04;	// 04
			TESForm*	form;	// 08
			ExtraData*	data;	// 10
		};
		STATIC_ASSERT(sizeof(Entry) == 0x18);


		template <class Op>
		UInt32 CountIf(Op& a_op) const
		{
			UInt32 count = 0;
			for (UInt32 n = 0; n < numEntries; n++) {
				Entry* pEntry = entries[n];
				if (pEntry && a_op.Accept(pEntry)) {
					count++;
				}
			}
			return count;
		}

		template <class Op>
		Entry* Find(Op& a_op) const
		{
			bool bFound = false;
			UInt32 n = 0;
			Entry* pEntry = 0;
			for (UInt32 n = 0; n < numEntries && !bFound; n++) {
				pEntry = entries[n];
				if (pEntry) {
					bFound = a_op.Accept(pEntry);
				}
			}
			return (bFound && pEntry) ? pEntry : 0;
		}

		template <class Op>
		void Visit(Op& a_op) const
		{
			bool bContinue = true;
			for (UInt32 n = 0; n < numEntries && bContinue; n++) {
				Entry* pEntry = entries[n];
				if (pEntry) {
					bContinue = a_op.Accept(pEntry);
				}
			}
		}

		bool	GetContainerItemAt(UInt32 a_idx, Entry*& a_entry) const;
		bool	GetContainerLevItemAt(UInt32 a_idx, Entry*& a_entry) const;
		UInt32	CountItem(TESForm* a_item) const;


		// members
		Entry**	entries;	// 08
		UInt32	numEntries;	// 10
	};
	STATIC_ASSERT(sizeof(TESContainer) == 0x18);
}