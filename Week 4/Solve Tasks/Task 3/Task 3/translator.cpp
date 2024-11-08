#include "test_runner.h"
#include <string>
#include <deque>
#include <map>
#include <algorithm>
#include <string_view>

using namespace std;

// Первый вариант с линейной сложностью 
//class Translator {
//public:
//    void Add(string_view source, string_view target){
//        CopyString(dictionary_source, source, target);
//        CopyString(dictionary_target, target, source);
//    }
//
//    string_view TranslateForward(string_view source) const{
//        auto it = dictionary_source.find(source);
//        return it != dictionary_source.end() ? it->second : "";
//
//    }
//    string_view TranslateBackward(string_view target) const{
//        auto it = dictionary_target.find(target);
//        return it != dictionary_target.end() ? it->second : "";
//    }
//
//private:
//    map<string_view, string_view> dictionary_source;
//    map<string_view, string_view> dictionary_target;
//    deque<string> unique_word;
//
//    void CopyString(map<string_view, string_view>& dictionary, string_view value_1, string_view value_2){
//        if(!dictionary.count(value_1)){
//            // добавляю ключ в дек если его нет там
//            auto it_key = find(unique_word.begin(), unique_word.end(), value_1);
//            if(it_key == unique_word.end()){
//                it_key = unique_word.emplace(unique_word.begin(), value_1);
//            }
//            // проверяю есть ли значение в деке
//            auto it_value = find(unique_word.begin(), unique_word.end(), value_2);
//            if( it_value == unique_word.end()){
//                // значит значения нет в деке, надо его добавить
//                it_value = unique_word.emplace(unique_word.begin(), value_2);
//            }
//            dictionary[*it_key] =  *it_value;
//        }
//        // иначе ключ в деке есть
//        else{
//            // проверяю есть ли значение в деке
//            if(dictionary[value_1] != value_2){
//                // значит значения нет в деке, надо его добавить
//                unique_word.emplace_back(value_2);
//                dictionary[value_1] = unique_word.back();
//            }
//        }
//    }
//};

// Второй вариант. Более продвинутый
class Translator{
public:
    void Add(string_view source, string_view target){
        string_view unic_source = CopyUnicWord(source);
        string_view unic_target = CopyUnicWord(target);
        dictionary_source[unic_source] = unic_target;
        dictionary_target[unic_target] = unic_source;
    }
    
    string_view TranslateForward(string_view source){
        return Translate(dictionary_source, source);
    }
    string_view TranslateBackward(string_view target){
        return Translate(dictionary_target, target);
    }
    
private:
    map<string_view, string_view> dictionary_source;
    map<string_view, string_view> dictionary_target;
    deque<string_view> deque_unic_word;
    
    string_view Translate(const map<string_view, string_view>& dictionary, const string_view word){
        auto it = dictionary.find(word);
        return  it != dictionary.end() ? it->second : "";
    }
    
    string_view CopyUnicWord(const string_view word){
        for(const auto* map : {&dictionary_source, &dictionary_target}){
            auto it = map->find(word);
            if(it != map->end()){
                return it->first;
            }
        }
        return deque_unic_word.emplace_back(word);
    }
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));
    cout << translator.TranslateForward("okno") << "\n";
    cout << translator.TranslateBackward("table") << "\n";
    cout << translator.TranslateBackward("stol") << "\n";
      ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
      ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
      ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
    translator.Add(string("stol"), string("table1"));
    cout << translator.TranslateForward("stol") << "\n";
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");

}

int main() {
      TestRunner tr;
      RUN_TEST(tr, TestSimple);
      return 0;
}
