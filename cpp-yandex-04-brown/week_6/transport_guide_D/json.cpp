#include "json.h"
#include <sstream>

using namespace std;

namespace Json {

  Document::Document(Node root) : root(move(root)) {
  }

  const Node& Document::GetRoot() const {
    return root;
  }

  Node LoadNode(istream& input);

  Node LoadArray(istream& input) {
    vector<Node> result;

    for (char c; input >> c && c != ']'; ) {
      if (c != ',') {
        input.putback(c);
      }
      result.push_back(LoadNode(input));
    }

    return Node(move(result));
  }

  Node LoadNumber(istream& input) {
    stringstream ss;
    bool isDouble = false;
    for (char c; input >> c; ) {
      if (isdigit(c) || c == '-' || c == '.') {
        if (c == '.') {
          isDouble = true;
        }
        ss << c;
      } else {
        input.putback(c);
        break;
      }
    }

    if (isDouble) {
      return Node(stod(ss.str()));
    } else {
      return Node(stoi(ss.str()));
    }
  }

  Node LoadBool(istream& input) {
    stringstream ss;
    for (char c; input >> c; ) {
      if (isalpha(c)) {
        ss << c;
      } else {
        input.putback(c);
        break;
      }
    }
    if (ss.str() == "true") {
      return Node(true);
    } else {
      return Node(false);
    }
  }

  Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    return Node(move(line));
  }

  Node LoadDict(istream& input) {
    map<string, Node> result;

    for (char c; input >> c && c != '}'; ) {
      if (c == ',') {
        input >> c;
      }

      string key = LoadString(input).AsString();
      input >> c;
      result.emplace(move(key), LoadNode(input));
    }

    return Node(move(result));
  }

  Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
      return LoadArray(input);
    } else if (c == '{') {
      return LoadDict(input);
    } else if (c == '"') {
      return LoadString(input);
    } else if (isdigit(c) || c == '-') {
      input.putback(c);
      return LoadNumber(input);
    } else {
      input.putback(c);
      return LoadBool(input);
    }
  }

  Document Load(istream& input) {
    return Document{LoadNode(input)};
  }

}
