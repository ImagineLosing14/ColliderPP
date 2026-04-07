#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class JObject {
private:
    std::string type;

    union {
        int ivalue;
        float fvalue;
        std::string* svalue;
        std::vector<JObject>* lvalues;
        std::unordered_map<std::string, JObject>* mvalues;
    } data;

    void check_error(const std::string& target) const;
    void clean_data();
    void deep_copy_data(const JObject& other);

public:
    
    JObject() = delete;
    JObject(int a);
    JObject(float a);
    JObject(const std::string& a);
    JObject(const std::vector<JObject>& a);
    JObject(const std::unordered_map<std::string, JObject>& a);

    JObject(const JObject& other);         
    JObject(JObject&& other) noexcept;
    JObject& operator=(const JObject& other);
    JObject& operator=(JObject&& other) noexcept;
    ~JObject();

    operator int() const;
    operator float() const;
    operator std::string() const;
    operator std::vector<JObject>() const;
    operator std::unordered_map<std::string, JObject>() const;

    const JObject& operator[](int idx) const;
    const JObject& operator[](const std::string& key) const;
};