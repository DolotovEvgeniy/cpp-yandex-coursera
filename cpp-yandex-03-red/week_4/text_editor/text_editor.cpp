#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor()
    : it_(data_.begin())
  {}

  void Left() {
    if (it_ != data_.begin()) {
      it_--;
    }
  }

  void Right() {
    if (it_ != data_.end()) {
      it_++;
    }
  }

  void Insert(char token) {
    it_ = data_.insert(it_, token);
    Right();
  }

  void Cut(size_t tokens = 1) {
    list<char>::iterator end = it_;
    for (size_t i = 0; i < tokens; i++) {
      if (end == data_.end()) { break; }
      end++;
    }
    buffer_.assign(it_, end);
    it_ = data_.erase(it_, end);
  }

  void Copy(size_t tokens = 1) {
    list<char>::iterator end = it_;
    for (size_t i = 0; i < tokens; i++) {
      if (end == data_.end()) { break; }
      end++;
    }
    buffer_.assign(it_, end);
  }

  void Paste() {
     size_t count = distance(buffer_.begin(), buffer_.end());
     it_ = data_.insert(it_, buffer_.begin(), buffer_.end());
     it_ = next(it_, count);
  }

  string GetText() const {
    return {data_.begin(), data_.end()};
  }

private:
  list<char> data_;
  list<char>::iterator it_;

  list<char> buffer_;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
