#pragma once

#include <array>
#include <charconv>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace embeddedjson {

template <std::size_t U>
class Json {
 public:
  inline constexpr Json();
  inline constexpr Json(const Json&) = delete;
  inline constexpr Json& operator=(const Json&) = delete;
  inline ~Json();

  inline void clear();
  template <typename T>
  inline void add(const std::string_view key, const T value);
  template <typename T, std::size_t S>
  inline void add(const std::string_view key, const std::array<T, S>& values);
  std::pair<const char*, std::size_t> get_as_c_array();

 private:
  template <typename T, std::size_t S>
  class static_vector;
  static_vector<char, U> json_str;
  bool json_empty;

  inline void append_char(const char c);
  inline void append_string(const std::string_view str); // TODO: Optimise (use func push_back array)
  inline void append_key_prefix(const std::string_view key);

  inline std::string_view convert_to_chars(const float value);
  inline std::string_view convert_to_chars(const int value);
  inline std::string_view convert_to_chars(const bool value);
};

template <std::size_t U>
template <typename T, std::size_t S>
class Json<U>::static_vector {
 public:
  inline constexpr static_vector() : write_index{0} {}
  inline constexpr static_vector(const static_vector&) = delete;
  inline constexpr static_vector& operator=(const static_vector&) = delete;
  inline ~static_vector() {}

  // TODO: Add append array instead of push_back in for loop
  inline void push_back(const T val);
  inline void reset();
  inline const T* data();
  inline std::size_t size();

 private:
  std::size_t write_index;
  inline static std::array<T, S> buffer{0};
};

}  // namespace embeddedjson

// Json
namespace embeddedjson {

template <std::size_t U>
inline constexpr Json<U>::Json() : json_empty{true} {
  append_char('{');
}

template <std::size_t U>
inline Json<U>::~Json() {}

template <std::size_t U>
inline void Json<U>::clear() {
  json_empty = true;
  json_str.reset();
  append_char('{');
}

template <std::size_t U>
template <typename T>
inline void Json<U>::add(const std::string_view key, const T value) {
  // "key": value,
  append_key_prefix(key);
  append_string(convert_to_chars(value));
}

template <std::size_t U>
template <typename T, std::size_t S>
inline void Json<U>::add(const std::string_view key, const std::array<T, S>& values) {
  // "key":[value1, value2, value3]
  bool array_empty = true;
  append_key_prefix(key);
  append_char('[');
  for (const auto& v : values) {
    if (array_empty) {
      array_empty = false;
    } else {
      append_char(',');
    }
    append_string(convert_to_chars(v));
  }
  append_char(']');
}

template <std::size_t U>
inline std::pair<const char*, std::size_t> Json<U>::get_as_c_array() {
  append_char('}');
  append_char('\n');
  return std::make_pair(json_str.data(), json_str.size());
}

template <std::size_t U>
inline void Json<U>::append_char(const char c) {
  json_str.push_back(c);
}

template <std::size_t U>
inline void Json<U>::append_string(const std::string_view str) {
  for (auto c : str) {
    append_char(c);
  }
}

template <std::size_t U>
inline void Json<U>::append_key_prefix(const std::string_view key) {
  if (json_empty) {
    json_empty = false;
  } else {
    append_char(',');
  }
  append_char('"');
  append_string(key);
  append_char('"');
  append_char(':');
}

//TODO: Check for errors
template<std::size_t U>
inline std::string_view Json<U>::convert_to_chars(const float value){
  static std::array<char, 100> str; // TODO: Write directly to the buffer inside static_vector
  auto [ptr, ec] = std::to_chars(str.data(), str.data() + str.size(), value,std::chars_format::fixed, 3);
  return std::string_view{str.data(), ptr};
}

template<std::size_t U>
inline std::string_view Json<U>::convert_to_chars(const int value){
  static std::array<char, 100> str; // TODO: Write directly to the buffer inside static_vector
  auto [ptr, ec] = std::to_chars(str.data(), str.data() + str.size(), value);
  return std::string_view{str.data(), ptr};
}

template<std::size_t U>
inline std::string_view Json<U>::convert_to_chars(const bool value){
  return value == true ? "true" : "false";
}

}  // namespace embeddedjson

// Json::static_vector
namespace embeddedjson {

template <std::size_t U>
template <typename T, std::size_t S>
inline void Json<U>::static_vector<T, S>::push_back(const T val) {
  if (write_index > (S - 1)) {
    return; // TODO: Return error code
  }
  buffer[write_index] = val;
  write_index++;
}

template <std::size_t U>
template <typename T, std::size_t S>
inline void Json<U>::static_vector<T, S>::reset() {
  write_index = 0;
}

template <std::size_t U>
template <typename T, std::size_t S>
inline const T* Json<U>::static_vector<T, S>::data() {
  return buffer.data();
}

template <std::size_t U>
template <typename T, std::size_t S>
inline std::size_t Json<U>::static_vector<T, S>::size() {
  return write_index;
}

}  // namespace embeddedjson
