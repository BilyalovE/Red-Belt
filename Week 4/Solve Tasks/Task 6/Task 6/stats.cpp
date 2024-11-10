#include "stats.h"

string_view SearchHalfRequest(string_view& line, const vector<string>& possible_values){
    string_view result = "unknown";
    size_t pos_half_request;
    pos_half_request = line.find(' ');
    string_view possible_half_request = line.substr(0, pos_half_request);
    for(const auto& method : possible_values){
        if(possible_half_request == method){
            result = possible_half_request;
            break;
        }
    }
    line.remove_prefix(pos_half_request + 1);
    return result;
}

HttpRequest ParseRequest(string_view line){
    HttpRequest result;
    result.method = SearchHalfRequest(line, {"GET", "POST", "PUT", "DELETE"});
    result.method == "unknown" ? result.method = "UNKNOWN" : result.method;
    result.uri = SearchHalfRequest(line, {"/", "/order", "/product", "/basket", "/help"});
    result.uri == "unknown" ? result.uri = "unknown" : result.uri;
    result.protocol = line;
    return result;
}

Stats::Stats():
    methodStats({{"GET", 0}, {"POST", 0}, {"PUT", 0}, {"DELETE", 0}, {"UNKNOWN", 0}}),
    uriStats({{"/", 0}, {"/order", 0}, {"/product", 0}, {"/basket", 0}, {"/help", 0}, {"unknown", 0}})
{
}

void Stats::AddMethod(string_view method){
    ++methodStats.at(method);
}

void Stats::AddUri(string_view uri){
    ++uriStats.at(uri);
}
const map<string_view, int>& Stats::GetMethodStats() const {
    return methodStats;
}

const map<string_view, int>& Stats::GetUriStats() const{
    return uriStats;
}
