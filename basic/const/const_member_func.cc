#include <iostream>
#include <string>

using namespace std;

class person_t {
public:
  person_t() {
    cout << "default ctor with empty args" << endl;
  };
  person_t(string name, string sur_name) : m_name{name}, m_sur_name{sur_name} {
    cout << "default ctor with two args" << endl;
  }
  person_t(const person_t& rhs) {
    m_name = rhs.m_name;
    m_sur_name = rhs.m_sur_name;
    cout << "copy ctor" << endl;
  }

  person_t(person_t&& rhs) {
    m_name = std::move(rhs.m_name);
    m_sur_name = std::move(rhs.m_sur_name);
    cout << "move ctor" << endl;
  }

  person_t(const person_t&& rhs) {
    m_name = std::move(rhs.m_name);
    m_sur_name = std::move(rhs.m_sur_name);
    cout << "const move ctor" << endl;
  }

  string name() const {
    return m_name;
  }

  string sur_name() const {
    return m_sur_name;
  }

  person_t with_name(const string& name) const& {
    cout << "with_name lvalue reference" << endl;
    person_t p(*this);
    p.m_name = name;
    return p;
  }

  // XXX: It's && instead of const&&. and if const&& is used,
  // `p(move(*this))` calls copy ctor instead of move ctor because
  // there's no ctor for (const person_t&&), so it will instead use
  // the implicit (const person_t&)
  // The cases are:
  // - const&& and ctor has (const person_t&&): expected
  // - && and ctor (person_t&&): expected
  // - const && and ctor (person_t&&): !!DO COPY INSTEAD OF MOVE!!
  person_t with_name(const string& name) && {
    cout << "with_name rvalue reference" << endl;
    person_t p(std::move(*this));
    p.m_name = name;
    return p;
  }

  person_t with_sur_name(const string& name) const& {
    cout << "with_sur_name lvalue reference" << endl;
    person_t p(*this);
    p.m_sur_name = name;
    return p;
  }

  person_t with_sur_name(const string& name) && {
    cout << "with_sur_name rvalue reference" << endl;
    person_t p(std::move(*this));
    p.m_sur_name = name;
    return p;
  }

  // XXX: duplicated with `string name() const`
  // const string& name() const {
  //   return m_name;
  // }

  // const string& sur_name() const {
  //   return m_sur_name;
  // }

private:
  string m_name;
  string m_sur_name;
};

int main() {
  cout << "---------------------" << endl;
  person_t p1{"a", "b"};
  cout << p1.name() << endl;
  cout << "=====================" << endl;

  cout << "---------------------" << endl;
  person_t p2(p1.with_name("c").with_sur_name("d"));
  cout << p2.name() << endl;
  cout << "=====================" << endl;

  cout << "---------------------" << endl;
  person_t p3(person_t().with_name("e").with_sur_name("f"));
  cout << p3.name() << endl;
  cout << "=====================" << endl;
}
