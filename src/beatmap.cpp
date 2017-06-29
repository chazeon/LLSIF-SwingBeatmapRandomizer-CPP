#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

#include <algorithm>

#include "beatmap.h"

using namespace std;
using namespace rapidjson;
using namespace Randomizer;

Beatmap::Beatmap(istream &is) {
	ParseBeatmapJson(is);
	PrepareGroups();
}

void Beatmap::ParseBeatmapJson(istream &is) {
	Document doc_notes;
	IStreamWrapper isw(is);
	doc_notes.ParseStream(isw);
	assert(doc_notes.IsArray());
	for (auto it = doc_notes.Begin(); it != doc_notes.End(); ++it) {
		assert(it->IsObject());
		Value note = it->GetObject();
		notes.push_back(Note(note));
	}
}

void Beatmap::PrepareGroups() {
	auto it = max_element(notes.begin(), notes.end(), [](Note &lhs, Note &rhs) { return lhs.GetGroupId() < rhs.GetGroupId(); });
	int group_cnt = it->GetGroupId() + 1;
	groups.assign(group_cnt, vector<Note *>());
	for (auto note : notes) {
		int group_id = note.GetGroupId();
		if (group_id != -1) groups[group_id].push_back(&note);
	}
}

string Beatmap::toJson(bool pretty) {
	Document doc;
	StringBuffer buffer(0, 1024);
	doc.SetArray();
	auto &allocator = doc.GetAllocator();
	for (auto note : notes) {
		doc.PushBack(note.toJson(doc), allocator);
	}
	if (pretty) {
		PrettyWriter<StringBuffer> writer(buffer);
		doc.Accept(writer);
	}
	else {
		Writer<StringBuffer> writer(buffer);
		doc.Accept(writer);
	}
	return std::string(buffer.GetString());
}

void Beatmap::arrange() {
	for (auto it = notes.begin(); it != notes.end(); ++it) {
		it->arranged_position = it->position;
	}
}