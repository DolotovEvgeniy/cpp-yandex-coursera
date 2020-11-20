#include "ini.h"

#include <iostream>

namespace Ini {

Section& Document::AddSection(string name) {
  return sections[move(name)];
}

const Section& Document::GetSection(const string& name) const {
  return sections.at(name);
}

size_t Document::SectionCount() const {
  return sections.size();
}

Document Load(istream& input) {
  Document doc;

  string name;
  Section section;
  for (string line; getline(input, line); ) {
    size_t last = line.find_last_not_of(' ');
    if (last == string::npos) {
      continue;
    }
    line = line.substr(0, last + 1);

    if (line.front() == '[' && line.back() == ']') {
      if (!name.empty()) {
        doc.AddSection(move(name)) = section;
        name.clear();
        section.clear();
      }
      name = line.substr(1, line.size() - 2);
    } else {
      size_t pos = line.find('=');
      string key = line.substr(0, pos);
      string value = line.substr(pos + 1);
      section[move(key)] = move(value);
    }
  }

  if (!name.empty()) {
    doc.AddSection(move(name)) = section;
  }

  return doc;
}

}
