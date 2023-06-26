
# JSON String Parser

JSON parser coded in c++ that replicates the JSON parser in Javascript. This program can parse a string to individual key and pair values and allows user to search and manipulate them when provided a JSON string 


## Run Locally

NOTE: have a C++ compiler setup to execute the command

Go to the project directory

```bash
  g++ Json_string_generator
```

```bash
  ./a.out
```



## Screenshots

Sample string passed in: "{\"RadioArray\":{\"tom\":[\"123\",{\"tom_2\":78},{\"tom_3\":78},{\"tom_4\":{\"tom_5\":78}},true,null]}}";

<img width="592" alt="image" src="https://github.com/aarjun2/JSON_string_parser/assets/136024177/49edb19d-ac8f-4069-83f3-53fb11ba978b">



## Features

- Handling of nested value types
- Ability to search all key value pairs, whether nested or not quickly
- Ability to map to what object class it belongs to
- Handles complex strings and formats strings automatically if entered wrong



## FAQ

#### What do the underscores mean?

Each nested key is mapped to its parent object for easy access

#### Do i have to type the full name of a key?

No, all related keys can be displayed by just typing a character that is in the key.

#### Why do you have multiple test strings, and how to input?

As per the requirements, the user wanted to manually input their strings, i have included other 
test strings to show the test cases that were tested, to change and test your string, change the variable
titled test string
  

