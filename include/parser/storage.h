#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

class JObject{
private:
    std::string type;
    union {
        int ivalue;
        float fvalue;
        std::string* svalue;
        std::vector<JObject>* lvalues;
        std::unordered_map<std::string,JObject>* mvalues;
    } data;

    void check_error(const std::string& target) const {
        if(target!=type){
            std::cerr << "Using "<<type<<" as "<<target<<"\n";
        }
    }

    void clean_data(){
        if (type == "string") delete data.svalue;
        if (type == "list") delete data.lvalues;
        if (type == "dict") delete data.mvalues; 

        type = "";
    }
    void deep_copy_data(const JObject& other){
        type = other.type;
        if (type == "int") data.ivalue = other.data.ivalue;
        else if (type == "float") data.fvalue = other.data.fvalue;
        else if (type == "string") data.svalue = new std::string(*other.data.svalue);
        else if (type == "list") data.lvalues = new std::vector<JObject>(*other.data.lvalues);
        else if (type == "dict") data.mvalues = new std::unordered_map<std::string, JObject>(*other.data.mvalues);
        else std::cerr<<"Uninitialed JObject being copied\n";
    }

public:
    JObject() = delete;
    JObject(int a) {
        type = "int";
        data.ivalue = a;
    }

    JObject(float a) {
        type = "float";
        data.fvalue = a;
    }

    JObject(const std::string &a) {
        type = "string";
        data.svalue = new std::string(a);
    }

    JObject(const std::vector<JObject>& a) {
        type = "list";
        data.lvalues = new std::vector(a);
    }

    JObject(const std::unordered_map<std::string, JObject>& a) {
        type = "dict";
        data.mvalues = new std::unordered_map(a);
    }

    ~JObject () {
        clean_data();
    }




    operator int() const {
        check_error("int");
        return data.ivalue;
    }
    operator float() const {
        check_error("float");
        return data.fvalue;
    }
    operator std::string() const {
        check_error("string");
        return *data.svalue;
    }
    operator std::vector<JObject>() const{
        check_error("list");
        return *data.lvalues;
    }
    operator std::unordered_map<std::string,JObject>() const{
        check_error("dict");
        return *data.lvalues;   
    }

    const JObject& operator[](int idx) const {
        check_error("list");
        return data.lvalues->at(idx);
    }
    const JObject& operator[](const std::string& key) const {
        check_error("dict");
        return data.mvalues->at(key);
    }
    
};