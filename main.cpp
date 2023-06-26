#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

/*
counts number of occurences in a string when passed the string, the start and end index*/
int countOccurrences(const string& str, char target, int start, int end) {
    int count = 0;
    for (int i = start; i < end; ++i) {
        if (str[i] == target) {
            count++;
        }
    }
    return count;
}
/*takes in an unordered map which is the orginal containing all values,
* when the test string is passed recursively, the test string is basically the value
* of the parent object as this function is used to handle the nesting of objects and arrays,
* the passed_key is the key of the parent object which gets appended to the front of the child 
* key so it is easier to look up the value of related and specific objects
*/
void parseObject(unordered_map<string, string>& value_map, string test_string, string passed_key) {
    int start = 0;
    while (true) {
        int end = test_string.find(':', start);
        int comma_position = test_string.find(',', start);
        if (end == string::npos) {
            break;
        }
        string key = test_string.substr(start+1, end - start - 2);
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        key = passed_key + '_' + key;
        string value;
        switch (test_string[end + 1]) {
        case '{': {
            int close_brac = test_string.find('}', end + 1);
            value = test_string.substr(end + 2, close_brac - end - 2);
            value_map[key] = value;
            parseObject(value_map, value, key);
            start = close_brac + 2;
            break;
        }
        case '[': {
            int occur = 0;
            int close_paran = test_string.find(']', end + 2);
            char target = ']';
            occur = countOccurrences(test_string, target, end + 1, test_string.size());
            if (occur >= 2) {
                int c = 1;
                while (c != occur) {
                    close_paran = test_string.find(']', close_paran + 1);
                    if (close_paran == string::npos) {
                        break;
                    }
                    c++;
                }
            }
            value = test_string.substr(end + 2, close_paran - end - 2);
            value_map[key] = value;
            vector<string> arrayValues;
            size_t pos = 0;
            while (pos != string::npos) {
                size_t commaPos = value.find(",", pos);
                string token = value.substr(pos, commaPos - pos);
                arrayValues.push_back(token);
                pos = commaPos != string::npos ? commaPos + 1 : commaPos;
            }
            for (string& val : arrayValues) {
                size_t curly_bracket_position = val.find('{');
                if (curly_bracket_position != string::npos) {
                    size_t curly_end_bracket_position = value.find('}');
                    size_t substring_length = curly_end_bracket_position - curly_bracket_position;
                    value = value.substr(curly_bracket_position, substring_length + 1);
                    parseObject(value_map, val, key);
                }
            }
            start = close_paran + 2;
            break;
        }
        case '"': {
            int close_paran = test_string.find('"', end + 2);
            value = test_string.substr(end + 2, close_paran - end - 2);
            value_map[key] = value;
            start = close_paran + 2;
            break;
        }
        default: {
            int counter = end + 1;
            while (test_string[counter] != '}' && test_string[counter] != ',' && test_string[counter] != '\0') {
                value += test_string[counter];
                counter++;
            }
            value_map[key] = value;
            start = counter + 1;
        }
        }
        if (comma_position == string::npos) {
            break;
        }
    }
}
int main() {
    //test your desired string by changing the variable test_string
    string test_string_1 = "{\"name\":\"abcd\",\"age\":\"123456\"}";
    string test_string_2 = "{\"RadioInformation\":{\"Group\":{\"hghgh\":\"sample\"},\"User\":4},\"Report\":{\"RSSI\":\"-124.3\",\"Call\":\"Up\"},\"Time\":\"2022,1888147\",\"CallState\":{\"CallStateValue\":\"HDU\"},\"RecordNumber\":84,\"array\":[\"123\",1,true,null],\"Recordvalue\":84,\"RadioArray\":{\"tom\":[\"123\",{\"jerry\":78},true,null]},\"normalObject\":{\"val\":987}";
    string test_string = "{\"RadioArray\":{\"tom\":[\"123\",{\"tom_2\":78},{\"tom_3\":78},{\"tom_4\":{\"tom_5\":78}},true,null]}}";
    string test_string_3 = "{\"ab\":{\"bc\":[12345,[256,78]]}}";
    unordered_map<string, string> value_map;
    int start = 1;
    while (true) {
        int end = test_string.find(':', start);
        int comma_position = test_string.find(',', start);
        if (end == string::npos) {
            break;
        }
        string key = test_string.substr(start + 1, end - start - 2);
        string value;
        switch (test_string[end + 1]) {
        case '{': {
            int close_brac = test_string.find('}', end + 1);
            char target = '{';
            int occur = 0;
            occur = countOccurrences(test_string, target, end + 1, test_string.size());
            if (occur >= 2) {
                int c = 1;
                while (c != occur) {
                    close_brac = test_string.find('}', close_brac + 1);
                    if (close_brac == string::npos) {
                        cout << "ERROR";
                        break; 
                    }
                    c++;
                }
            }
            if (test_string[close_brac + 1] == '}') {
                value = test_string.substr(end + 2, close_brac - end - 1);
            }
            else {
                value = test_string.substr(end + 2, close_brac - end - 2);
            }
            value_map[key] = value;
            parseObject(value_map, value, key);
            start = close_brac + 2;
            break;
        }
        case '[': {
            int occur = 0;
            int close_paran = test_string.find(']', end + 2);
            char target = ']';
            occur = countOccurrences(test_string, target, end + 1, test_string.size());
            if (occur >= 2) {
                int c = 1;
                while (c != occur) {
                    close_paran = test_string.find(']', close_paran + 1);
                    if (close_paran == string::npos) {
                        break;
                    }
                    c++;
                }
            }
            value = test_string.substr(end + 2, close_paran - end - 2);
            value_map[key] = value;
            size_t curly_bracket_position = value.find('{');
            if (curly_bracket_position != string::npos) {
                size_t curly_end_bracket_position = value.find('}');
                size_t substring_length = curly_end_bracket_position - curly_bracket_position;
                value = value.substr(curly_bracket_position, substring_length + 1);
                parseObject(value_map, value, key);
            }
            start = close_paran + 2;
            break;
        }
        case '"': {
            int close_paran = test_string.find('"', end + 2);
            value = test_string.substr(end + 2, close_paran - end - 2);
            value_map[key] = value;
            start = close_paran + 2;
            break;
        }
        default: {
            int counter = end + 1;
            while (test_string[counter] != '}' && test_string[counter] != ',') {
                value += test_string[counter];
                counter++;
            }
            value_map[key] = value;
            start = counter + 1;
        }
        }
        if (comma_position == string::npos) {
            break;
        }
    }
    int menuoption = 0;
    while (menuoption != 3) {
        cout << "welcome to json parser c++" << endl;
        cout << "please choose an option below" << endl;
        cout << "1: view all available fields" << endl;
        cout << "2: view a specific field" << endl;
        cout << "3: Exit" << endl;
        cin >> menuoption;
        if (menuoption == 1) {
            for (const auto& pair : value_map) {
                cout << "key: " << pair.first << ", value: " << pair.second << endl;
            }
        }
        if (menuoption == 2) {
            cout << "Enter a string: ";
            string searchString;
            cin >> searchString;
            for (const auto& pair : value_map) {
                if (pair.first.find(searchString) != string::npos) {
                    cout << "key : " << pair.first << " value : " << pair.second << endl;
                }
            }

        }
        if(menuoption == 3) {
            break;
        }
    }
    cout << "Thank you" << endl;
    return 0;
}