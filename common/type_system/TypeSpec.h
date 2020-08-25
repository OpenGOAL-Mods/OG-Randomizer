/*!
 * @file TypeSpec.h
 */

#ifndef JAK_TYPESPEC_H
#define JAK_TYPESPEC_H

#include <vector>
#include <string>
#include <cassert>

class Type;

/*!
 * A TypeSpec is a reference to a Type, or possible a compound type.  This is the best way to
 * refer to a type, as it supports compound types and also will work correctly after a type has been
 * redefined. Doing sane things after types change will make debugging GOAL code more pleasant.
 *
 * A compound type contains a "root type", which must by a Type, and a list of "type
 * arguments", which are TypeSpecs.
 */
class TypeSpec {
 public:
  // create a typespec for a single type
  TypeSpec() = default;
  TypeSpec(std::string type);
  TypeSpec(std::string type, std::vector<TypeSpec> arguments);

  bool operator!=(const TypeSpec& other) const;
  bool operator==(const TypeSpec& other) const;
  std::string print() const;

  void add_arg(const TypeSpec& ts) { m_arguments.push_back(ts); }

  const std::string base_type() const { return m_type; }
  const TypeSpec& get_single_arg() const {
    assert(m_arguments.size() == 1);
    return m_arguments.front();
  }

 private:
  std::string m_type;
  std::vector<TypeSpec> m_arguments;
};

#endif  // JAK_TYPESPEC_H