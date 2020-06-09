#ifndef INIT_H
#define INIT_H
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>

namespace Components {
class Init
{
public:
    template<class k, class t>
    static bool initVector(const nlohmann::json &init, const k &param, std::vector<t>& target){
        try {
            std::cout<<"INITPARAM: " << init << " param: " << param << std::endl;

            nlohmann::json paramJson = init.at(param);
            if(paramJson.is_array() == true){
                for(auto& item : paramJson){
                    target.push_back(item.get<t>());
                }
            }else{
                target.push_back(paramJson.get<t>());
            }
            return true;
        } catch (const nlohmann::detail::out_of_range &ex) {
            return false;
        }{}
    }
    template<class k, class t>
    static bool init(const nlohmann::json &initParam, const k &param,  t& target){
        try {
            std::cout<<"INITPARAM: " << initParam << " param: " << param << std::endl;
            nlohmann::json paramJson = initParam.at(param);
            target = paramJson.get<t>();
            return true;
        } catch (const nlohmann::detail::out_of_range &ex) {
            return false;
        }
    }
    template<class k, class t>
    static void init(const nlohmann::json &initParam, const k &param, t& target, const t& defaultValue){
        if(init(initParam, param, target) == false)
            target = defaultValue;
    }

};
}


#endif // INIT_H
