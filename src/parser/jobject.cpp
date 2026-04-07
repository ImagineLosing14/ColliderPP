#include "jobject.h"

void JObject::check_error(const std::string& target) const {
    if (target != type)
        std::cerr << "Using " << type << " as " << target << "\n";
}

void JObject::clean_data() {
    if (type == "string") delete data.svalue;
    if (type == "list")   delete data.lvalues;
    if (type == "dict")   delete data.mvalues;
    type = "";
}

void JObject::deep_copy_data(const JObject& other) {
    type = other.type;
    if (type == "int") data.ivalue  = other.data.ivalue;
    else if (type == "float") data.fvalue  = other.data.fvalue;
    else if (type == "string") data.svalue  = new std::string(*other.data.svalue);
    else if (type == "list") data.lvalues = new std::vector<JObject>(*other.data.lvalues);
    else if (type == "dict") data.mvalues = new std::unordered_map<std::string, JObject>(*other.data.mvalues);
    else std::cerr << "Uninitialised JObject being copied\n";
}


JObject::JObject(int a){ 
    type = "int";    
    data.ivalue = a; 
}
JObject::JObject(float a){ 
    type = "float";  
    data.fvalue = a; 
}
JObject::JObject(const std::string& a){ 
    type = "string"; 
    data.svalue = new std::string(a); 
}
JObject::JObject(const std::vector<JObject>& a){ 
    type = "list";   
    data.lvalues = new std::vector<JObject>(a); 
}
JObject::JObject(const std::unordered_map<std::string,JObject>& a){ 
    type = "dict"; 
    data.mvalues = new std::unordered_map<std::string,JObject>(a); 
}

// Copy constructor
JObject::JObject(const JObject& other) {
    deep_copy_data(other);          
}

// Move constructor 
JObject::JObject(JObject&& other) noexcept {
    type = other.type;         
    data = other.data;         
    other.type = nullptr;                
}

// Copy assignment 
JObject& JObject::operator=(const JObject& other) {
    if (this == &other) return *this;   
    clean_data();                       
    deep_copy_data(other);            
    return *this;
}

//  Move assignment 
JObject& JObject::operator=(JObject&& other) noexcept {
    if (this == &other) return *this;
    clean_data();                       
    type = other.type;            
    data = other.data;
    other.type = nullptr;                   
    return *this;
}


JObject::~JObject() {
    clean_data();
}


JObject::operator int() const {
    check_error("int");
    return data.ivalue;
}

JObject::operator float() const {
    check_error("float");
    return data.fvalue;
}

JObject::operator std::string() const {
    check_error("string");
    return *data.svalue;
}

JObject::operator std::vector<JObject>() const {
    check_error("list");
    return *data.lvalues;
}

JObject::operator std::unordered_map<std::string, JObject>() const {
    check_error("dict");
    return *data.mvalues;
}

const JObject& JObject::operator[](int idx) const {
    check_error("list");
    return data.lvalues->at(idx);
}

const JObject& JObject::operator[](const std::string& key) const {
    check_error("dict");
    return data.mvalues->at(key);
}
