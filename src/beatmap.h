#ifndef BEATMAP_H
#define BEATMAP_H

#include <istream>
#include <rapidjson/document.h>
#include <vector>

#include "note.h"

namespace Randomizer {
	class Beatmap {
	public:
		Beatmap(std::istream &in);
		Beatmap(rapidjson::Document &doc);
	private:
		void ParseBeatmapJson(std::istream &in);
		void PrepareGroups();
	public:
		std::vector<Note> notes;
		std::vector<std::vector<Note *>> groups;
		std::string toJson(bool pretty = false);
		void arrange();
	};
}

#endif // !BEATMAP_H
