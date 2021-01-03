#include <test_runner.h>

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <stack>
#include <string>
#include <variant>

class EmptyContext {};

template <typename Parent>
class Object;
template <typename Parent>
class Array;

template <typename Parent>
class Value {
public:
  Value(std::ostream& out, Parent* parent = nullptr)
    : out_(out)
    , parent_(parent)
  {}

  ~Value() {
    if (!printed_) {
      Null();
    }
  }

  Parent& Number(int64_t value) {
    out_ << value;

    printed_ = true;
    return *parent_;
  }

  Parent& String(std::string_view value) {
    out_ << '\"';
    for (auto ch : value) {
      if (ch == '\"' || ch == '\\') {
        out_ << '\\';
      }
      out_ << ch;
    }
    out_ << '\"';

    printed_ = true;
    return *parent_;
  }

  Parent& Boolean(bool value) {
    out_ << std::boolalpha << value;

    printed_ = true;
    return *parent_;
  }

  Parent& Null() {
    out_ << "null";

    printed_ = true;
    return *parent_;
  }

  Array<Parent> BeginArray() {  printed_ = true; return {out_, this->parent_}; }
  Object<Parent> BeginObject() {  printed_ = true; return {out_, this->parent_}; }

private:
  std::ostream& out_;
  Parent* parent_ = nullptr;
  bool printed_ = false;
};

template <typename Parent, char BeginChar, char EndChar>
class Context {
public:
  Context(std::ostream& out, Parent* parent = nullptr)
    : out_(out)
    , parent_(parent)
  {
    Begin();
  }


  ~Context() {
    End();
  }
protected:
  Value<Context> AddValue() { Delimiter(); return Value<Context>{out_, this};  }

  void Begin() {
    out_ << BeginChar;
    opened_ = true;
  }

  void Delimiter() {
    if (!first_added_) {
      first_added_ = true;
    } else {
      out_ << ',';
    }
  }

  void End() {
    if (opened_) {
      out_ << EndChar;
      opened_ = false;
    }
  }

  std::ostream& out_;
  Parent* parent_ = nullptr;
  bool first_added_ = false;
  bool opened_ = false;
};

template <typename Parent>
class Array : public Context<Parent, '[', ']'> {
public:
  Array(std::ostream& out, Parent* parent = nullptr)
    : Context<Parent, '[', ']'>(out, parent)
  {}

  Array<Parent>& Number(int64_t value) {
    this->AddValue().Number(value);
    return *this;
  }

  Array<Parent>& String(std::string_view value) {
    this->AddValue().String(value);
    return *this;
  }

  Array<Parent>& Boolean(bool value) {
    this->AddValue().Boolean(value);
    return *this;
  }

  Array<Parent>& Null() {
    this->AddValue().Null();
    return *this;
  }

  Array<Array<Parent>> BeginArray() {
    this->Delimiter();
    return {this->out_, this};
  }

  Object<Array<Parent>> BeginObject() {
    this->Delimiter();
    return {this->out_, this};
  }

  Parent& EndArray() {
    this->End();
    return *this->parent_;
  }
};

template<typename Parent>
class Object : public Context<Parent, '{', '}'> {
public:
  Object(std::ostream& out, Parent* parent = nullptr)
    : Context<Parent, '{', '}'>(out, parent)
  {}

  Value<Object<Parent>> Key(std::string_view value) {
    this->Delimiter();
    Value<EmptyContext>(this->out_).String(value);
    this->out_ << ':';
    return {this->out_, this};
  }

  Parent& EndObject() {
    this->End();
    return *this->parent_;
  }
};

void PrintJsonString(std::ostream& out, std::string_view str) {
  Value<EmptyContext>{out}.String(str);
}

using ArrayContext = Array<EmptyContext>;
ArrayContext PrintJsonArray(std::ostream& out) {
  return {out};
}

using ObjectContext = Object<EmptyContext>;
ObjectContext PrintJsonObject(std::ostream& out) {
  return {out};
}

void TestArray() {
  std::ostringstream output;

  {
    auto json = PrintJsonArray(output);
    json
      .Number(5)
      .Number(6)
      .BeginArray()
        .Number(7)
      .EndArray()
      .Number(8)
      .String("bingo!");
  }

  ASSERT_EQUAL(output.str(), R"([5,6,[7],8,"bingo!"])");
}

void TestObject() {
  std::ostringstream output;

  {
    auto json = PrintJsonObject(output);
    json
      .Key("id1").Number(1234)
      .Key("id2").Boolean(false)
      .Key("").Null()
      .Key("\"").String("\\");
  }

  ASSERT_EQUAL(output.str(), R"({"id1":1234,"id2":false,"":null,"\"":"\\"})");
}

void TestAutoClose() {
  std::ostringstream output;

  {
    auto json = PrintJsonArray(output);
    json.BeginArray().BeginObject();
  }

  ASSERT_EQUAL(output.str(), R"([[{}]])");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestArray);
  RUN_TEST(tr, TestObject);
  RUN_TEST(tr, TestAutoClose);

  return 0;
}
