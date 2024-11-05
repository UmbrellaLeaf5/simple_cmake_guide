#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

inline void FirstExample() {
  std::cout << "------------- First Example -------------" << std::endl;

  json j = {{"name", "John Doe"}, {"age", 30}, {"city", "New York"}};

  std::cout << j.dump(2) << std::endl << std::endl;

  std::cout << "Name: " << j["name"] << std::endl;
  std::cout << "Age: " << j["age"] << std::endl;
  std::cout << "City: " << j["city"] << std::endl;

  std::cout << "------------- First Example -------------" << std::endl
            << std::endl;
}

inline void SecondExample() {
  std::cout << "------------- Second Example ------------" << std::endl;

  std::ifstream input("data.json");

  if (!input) throw std::runtime_error("File opening error!");

  json j;
  input >> j;

  input.close();

  for (auto& [key, value] : j.items())
    std::cout << key << ": " << value << std::endl;

  std::cout << "------------- Second Example ------------" << std::endl
            << std::endl;
}

inline void ThirdExample() {
  std::cout << "------------- Third Example -------------" << std::endl;

  json student = {{"name", "Dmitry"},
                  {"age", 19},
                  {"courses",
                   {
                       {{"course_name", "Differential equations"},
                        {"course_code", "DIFFEQ314"},
                        {"credits", 3}},
                       {{"course_name", "Physics"},
                        {"course_code", "PHYS314"},
                        {"credits", 4}},  // какие кредиты...
                   }}};

  std::string json_string = student.dump(2);

  std::cout << "Serialized JSON structure:\n" << json_string << std::endl;

  json deserialized_student = json::parse(json_string);

  std::cout << std::endl << "Deserialized Student Info:" << std::endl;
  std::cout << "Name: " << deserialized_student["name"] << std::endl;
  std::cout << "Age: " << deserialized_student["age"] << std::endl;

  std::cout << "Courses:" << std::endl;
  for (const auto& course : deserialized_student["courses"])
    std::cout << "- " << course["course_name"] << " (" << course["course_code"]
              << ") - " << course["credits"] << " credits" << std::endl;

  std::cout << "------------- Third Example -------------" << std::endl
            << std::endl;
}