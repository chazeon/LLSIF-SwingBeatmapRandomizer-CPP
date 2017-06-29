#include "note.h"
using namespace rapidjson;
using namespace Randomizer;

Note::Note(Value &note) {
	assert(note.IsObject());

	Value::ConstMemberIterator it;

	/*
	it = note.FindMember("note_id");
	assert(it != note.MemberEnd());
	assert(it->value.IsInt());
	note_id = it->value.GetInt();
	*/

	it = note.FindMember("timing_sec");
	assert(it != note.MemberEnd());
	assert(it->value.IsNumber());
	timing_sec = it->value.GetDouble();

	it = note.FindMember("notes_attribute");
	assert(it != note.MemberEnd());
	assert(it->value.IsInt());
	notes_attribute = static_cast<NoteAttribute>(it->value.GetInt());

	it = note.FindMember("notes_level");
	assert(it != note.MemberEnd());
	assert(it->value.IsInt());
	notes_level = it->value.GetInt();

	it = note.FindMember("effect_value");
	assert(it != note.MemberEnd());
	assert(it->value.IsNumber());
	effect_value = it->value.GetDouble();

	it = note.FindMember("effect");
	assert(it != note.MemberEnd());
	assert(it->value.IsInt());
	effect = static_cast<NoteType>(it->value.GetInt());

	it = note.FindMember("position");
	assert(it != note.MemberEnd());
	assert(it->value.IsInt());
	position = it->value.GetInt();
}

Value Note::toJson(Document &doc) {
	Value note;
	note.SetObject();

	Value val_notes_level;
	Value val_effect_value;
	Value val_effect;
	Value val_arranged_position;

	val_effect_value.SetDouble(effect_value);
	val_arranged_position.SetInt(arranged_position);

	auto &allocator = doc.GetAllocator();
	note.AddMember("timing_sec", Value().SetDouble(timing_sec), allocator);
	note.AddMember("notes_attribute", Value().SetInt(notes_attribute), allocator);
	note.AddMember("notes_level", Value().SetInt(notes_level), allocator);
	note.AddMember("effect", Value().SetInt(effect), allocator);
	if (IsHold() || effect_value != 2.0) note.AddMember("effect_value", Value().SetDouble(effect_value), allocator); // ?
	else note.AddMember("effect_value", Value().SetInt(effect_value), allocator);
	note.AddMember("position", Value().SetInt(arranged_position), allocator);

	return note;
}