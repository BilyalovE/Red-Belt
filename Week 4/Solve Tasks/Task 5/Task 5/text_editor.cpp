#include <string>
#include <string_view>
#include <list>
#include "profailer.h"
#include "test_runner.h"
using namespace std;

class Editor {
public:
    Editor() {}
    // Реализуйте конструктор по умолчанию и объявленные методы
    void Left(){   // сдвинуть курсор влево     //O(1)
        // Проверяем, что курсор не находится в начале списка
        if (pos_cursor != str.begin()) {
            pos_cursor = str.erase(pos_cursor);
            --pos_cursor;
            pos_cursor = str.insert(pos_cursor, cursor);
            --length_before_cursor;
        }
    }
    
    void Right(){  // сдвинуть курсор вправо    //O(1)
        if (pos_cursor != --str.end()) {
            pos_cursor = str.erase(pos_cursor);
            ++pos_cursor;
            pos_cursor = str.insert(pos_cursor, cursor);
            ++length_before_cursor;
        }
    }
    void Insert(char token){    // вставить символ token
        str.insert(pos_cursor, token);   //O(1)
        ++current_length;
        ++length_before_cursor;
    }
    
    void Copy(size_t tokens){  // cкопировать   O(N)
        buffer_str.clear();
        if(tokens != 0){
            size_t length_after_cursor = current_length - length_before_cursor;
            if(length_after_cursor >= tokens){
                buffer_str.insert(next(pos_cursor), tokens + 1);
            }
            else{
                buffer_str.insert(next(pos_cursor), length_after_cursor + 1);
            }
        }
    }
    void Cut(size_t tokens){  // вырезать не более tokens символов,
        buffer_str.clear();
        size_t length_after_cursor = current_length - length_before_cursor;
        if(length_after_cursor >= tokens){
            buffer_str.splice(buffer_str.begin(), str, next(pos_cursor), next(pos_cursor, tokens + 1));
        }
        else{
            buffer_str.splice(buffer_str.begin(), str, next(pos_cursor), str.end());
        }
        current_length = str.size() - 1;
    }
    void Paste(){
        str.insert(pos_cursor, buffer_str.begin(), buffer_str.end());
        current_length += buffer_str.size();
        length_before_cursor += buffer_str.size();
    }
    
    string GetText() const {
        string currentText = "";
        //currentText.reserve(current_length);
        if(str.size() == 1){
            return "";
        }
        for(const auto ch : str){
            if (ch != cursor){
                currentText += ch;
            }
        }
        return currentText;
    }
    
private:
    char cursor = '|';
    list<char> str = {cursor};
    list<char> buffer_str;
    size_t current_length = 0;
    size_t length_before_cursor = 0;
    list<char>::iterator pos_cursor = str.begin();
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
    cout << editor.GetText();
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
