#ifndef NOTE_H
#define NOTE_H

#include <rapidjson/document.h>

namespace Randomizer {
	class Note {
		enum NoteType {
			TYPE_RANDOM = 0,
			TYPE_NORMAL = 1,
			TYPE_EVENT = 2,
			TYPE_HOLD = 3,
			TYPE_BOMB_1 = 4,
			TYPE_BOMB_3 = 5,
			TYPE_BOMB_5 = 6,
			TYPE_BOMB_9 = 7,
			TYPE_SWING = 11,
			TYPE_SWING_EVENT = 12,
			TYPE_SWING_HOLD = 13
		};

		enum NoteAttribute {
			ATTRIBUTE_RANDOM = 0,
			ATTRIBUTE_SMILE = 1,
			ATTRIBUTE_CUTE = 2,
			ATTRIBUTE_COOL = 3
		};

		friend class Beatmap;
	private:
		Note(rapidjson::Value &note);

		int note_id;
		double timing_sec;
		NoteAttribute notes_attribute;
		int notes_level;
		double effect_value;
		NoteType effect;
		int position;
		int arranged_position;

	public:
		int GetNoteId() { return note_id; }
		int GetPosition() { return position; }
		double GetAppearTime() { return timing_sec; }
		NoteType GetNoteType() { return effect; }
		bool IsHold() { return GetNoteType() == NoteType::TYPE_HOLD || GetNoteType() == NoteType::TYPE_SWING_HOLD; }
		bool IsSwing() { return GetNoteType() == NoteType::TYPE_SWING || GetNoteType() == NoteType::TYPE_SWING_EVENT || GetNoteType() == NoteType::TYPE_SWING_HOLD; }
		double GetHoldTimeLength() { return IsHold() ? effect_value : 0.0; }
		double GetDisappearTime() { return GetAppearTime() + GetHoldTimeLength(); }
		void SetArrangedPosition(int val) { arranged_position = val; }
		int GetArrangedPosition() { return arranged_position; }
		int GetGroupId() { return IsSwing() ? notes_level : -1; }

		rapidjson::Value toJson(rapidjson::Document &doc);
	};
}

#endif