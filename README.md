# 🚀 XorLang Programming Language

**XorLang** is a modern compiled programming language designed with Persian syntax and advanced capabilities for software development.

## 📋 Table of Contents

- [Features](#features)
- [Installation & Setup](#installation--setup)
- [Language Syntax](#language-syntax)
- [Standard Libraries](#standard-libraries)
- [Practical Examples](#practical-examples)
- [Project Structure](#project-structure)
- [Compilation & Execution](#compilation--execution)

## 🌟 Features

### Core Features
- **Compiled Language**: Generates optimized and fast C code
- **Persian Syntax**: Keywords in Persian language
- **Strong Type System**: Automatic type inference for variables
- **Rich Libraries**: Ready-made modules for various tasks
- **Network Support**: HTTP and download capabilities
- **Error Management**: Safe error handling system

### Data Types
- **Integers**: `bucket x = 42;`
- **Floats**: `bucket pi = 3.14;`
- **Strings**: `bucket name = 'Ali';`
- **Booleans**: `bucket flag = yes;` / `bucket flag = no;`
- **Arrays**: `bucket numbers[] = [1, 2, 3];`

## 🛠 Installation & Setup

### Prerequisites
```bash
# Install required tools
sudo apt update
sudo apt install gcc make libcurl4-openssl-dev
```

### Compile the Compiler
```bash
git clone https://github.com/mr-ali-jafari/xorlang.git
cd xorlang
make
```

### Run Programs
```bash
# Compile XorLang file
./xorlang program.xor

# Run compiled program
./program.xor.out
```

## 📝 Language Syntax

### Comments
```xorlang
note: This is a single line comment
note start:
This is a
multi-line comment
note end:
```

### Variable Declaration
```xorlang
bucket name = 'Ali Jafari';
bucket age = 25;
bucket height = 1.75;
bucket is_student = yes;
bucket numbers[] = [1, 2, 3, 4, 5];
```

### Control Structures

#### Conditionals
```xorlang
when if (age > 18) {
    show('Adult');
} when else {
    show('Child');
}
```

#### Loops
```xorlang
# While loop
bucket i = 0;
while loop (i < 5) {
    show(i);
    bucket i = i + 1;
}

# For loop
for loop (bucket j = 0; j < 10; bucket j = j + 1) {
    show(j);
}
```

### Functions
```xorlang
make function greet(name) {
    show('Hello ' + name);
    give back 'Welcome';
}

bucket result = greet('Ali');
```

### Input and Output
```xorlang
bucket user_name = ask('Enter your name: ');
show('Hello ' + user_name);
```

## 📚 Standard Libraries

### Math Module
```xorlang
bucket sqrt_result = math_sqrt(25);        # 5.0
bucket power_result = math_pow(2, 3);      # 8.0
bucket abs_result = math_abs(-42);         # 42
bucket max_result = math_max(10, 20);      # 20
bucket random_num = math_random_range(1, 10);
```

### String Module
```xorlang
bucket upper_text = string_to_upper('hello'); # "HELLO"
bucket contains = string_contains('hello world', 'world'); # 1
bucket trimmed = string_trim('  text  ');
```

### File Module
```xorlang
bucket content = file_read('data.txt');
file_write('output.txt', 'New content');
bucket exists = file_exists('myfile.txt');
bucket size = file_size('document.pdf');
```

### Time Module
```xorlang
bucket current_time = time_now();
bucket formatted = time_format(current_time, '%Y-%m-%d');
time_sleep(2); # Sleep for 2 seconds
```

### Network Module
```xorlang
bucket online = is_online();
bucket response = http_get('https://api.example.com/data');
bucket post_result = http_post('https://api.example.com/submit', 'data=value');
bucket downloaded = download('https://example.com/file.zip', 'local_file.zip');
```

### Error Handling
```xorlang
bucket safe_result = safe_divide(100, 0); # Returns 0 instead of error
bucket error_code = error('Custom error'); # Print error and return -1
```

### Array Module
```xorlang
bucket length = len(numbers);
push(numbers, 6);
bucket last = pop(numbers);
bucket sorted = array_sort(numbers);
bucket reversed = array_reverse(numbers);
```

## 💡 Practical Examples

### Simple Calculator
```xorlang
bucket num1 = ask('Enter first number: ');
bucket num2 = ask('Enter second number: ');
bucket operation = ask('Operation (+, -, *, /): ');

when if (operation == '+') {
    show('Result: ' + (num1 + num2));
} when else when if (operation == '-') {
    show('Result: ' + (num1 - num2));
} when else when if (operation == '*') {
    show('Result: ' + (num1 * num2));
} when else when if (operation == '/') {
    bucket result = safe_divide(num1, num2);
    show('Result: ' + result);
}
```

### File Manager
```xorlang
bucket filename = ask('Enter filename: ');

when if (file_exists(filename)) {
    bucket content = file_read(filename);
    show('File content: ' + content);
    show('File size: ' + file_size(filename) + ' bytes');
} when else {
    show('File not found!');
    bucket new_content = ask('Enter new content: ');
    file_write(filename, new_content);
    show('File created!');
}
```

### Web Request Handler
```xorlang
when if (is_online()) {
    show('Internet connection is available');
    bucket api_response = http_get('https://httpbin.org/json');
    show('API Response: ' + api_response);
    
    bucket download_result = download('https://httpbin.org/json', 'api_data.json');
    when if (download_result == 1) {
        show('File downloaded successfully');
    } when else {
        show('Error downloading file');
    }
} when else {
    show('No internet connection');
}
```

## 🏗 Project Structure

```
xorlang/
├── src/
│   ├── include/
│   │   ├── lexer.h          # Lexer definitions
│   │   ├── parser.h         # Parser definitions
│   │   ├── AST.h           # Abstract Syntax Tree
│   │   ├── codegen.h       # Code generator
│   │   └── token.h         # Token definitions
│   ├── lexer.c             # Lexer implementation
│   ├── parser.c            # Parser implementation
│   ├── AST.c              # AST implementation
│   ├── codegen.c          # C code generator
│   ├── token.c            # Token implementation
│   └── main.c             # Main compiler program
├── Makefile               # Build file
└── README.md             # English documentation
```

### Compilation Pipeline
1. **Lexer**: Convert source code to tokens
2. **Parser**: Convert tokens to Abstract Syntax Tree (AST)
3. **Code Generator**: Generate C code from AST
4. **C Compiler**: Compile C code to executable

## ⚡ Compilation & Execution

### Build the Compiler
```bash
make clean  # Clean previous files
make        # Build compiler
```

### Using the Compiler
```bash
# Compile XorLang program
./xorlang program.xor [output.c]

# Run the program
./program.xor.out
```

### Complete Example
```bash
# Create program file
echo "bucket name = ask('Your name: '); show('Hello ' + name);" > hello.xor

# Compile
./xorlang hello.xor

# Execute
./hello.xor.out
```

## 🔧 Advanced Features

### Import System
```xorlang
putlib math_sqrt, math_pow from math;
putlib string_to_upper from string;
putlib * from file;
```

### Memory Management
- Automatic memory allocation for strings and arrays
- Automatic memory deallocation in generated code
- Optimized memory usage

### Optimizations
- Compile-time type inference
- Mathematical operation optimization
- Dead code elimination

## 🌐 Standard Library Modules

### Complete Function List

#### Math Module
- `math_sqrt(x)` - Square root
- `math_pow(base, exp)` - Power function
- `math_abs(x)` - Absolute value
- `math_max(a, b)` - Maximum value
- `math_min(a, b)` - Minimum value
- `math_round(x)` - Round to nearest integer
- `math_random()` - Random number 0-1
- `math_random_range(min, max)` - Random in range

#### String Module
- `string_to_upper(str)` - Convert to uppercase
- `string_to_lower(str)` - Convert to lowercase
- `string_contains(str, substr)` - Check if contains substring
- `string_starts_with(str, prefix)` - Check if starts with prefix
- `string_trim(str)` - Remove whitespace
- `string_split(str, delimiter)` - Split string
- `string_join(array, separator)` - Join array elements
- `string_replace(str, old, new)` - Replace substring

#### Array Module
- `len(array)` - Get array length
- `push(array, element)` - Add element to end
- `pop(array)` - Remove and return last element
- `array_sort(array)` - Sort array
- `array_reverse(array)` - Reverse array
- `array_unique(array)` - Remove duplicates
- `array_find(array, element)` - Find element index
- `array_slice(array, start, end)` - Extract portion

#### File Module
- `file_read(filename)` - Read file content
- `file_write(filename, content)` - Write to file
- `file_exists(filename)` - Check if file exists
- `file_delete(filename)` - Delete file
- `file_size(filename)` - Get file size

#### Network Module
- `is_online()` - Check internet connectivity
- `http_get(url)` - HTTP GET request
- `http_post(url, data)` - HTTP POST request
- `download(url, filename)` - Download file

#### Time Module
- `time_now()` - Current timestamp
- `time_format(timestamp, format)` - Format time
- `time_sleep(seconds)` - Sleep for duration

#### System Module
- `system_run(command)` - Execute system command
- `system_get_env(variable)` - Get environment variable

#### Error Handling
- `safe_divide(a, b)` - Safe division (returns 0 on division by zero)
- `error(message)` - Print error message and return -1

## 📊 Performance Characteristics

- **Compilation Speed**: Fast compilation to C code
- **Runtime Performance**: Near-native C performance
- **Memory Usage**: Efficient memory management
- **Binary Size**: Compact executables
- **Standard Library**: Optimized built-in functions

## 🛣 Roadmap

### Current Version (v1.0)
- ✅ Complete lexer and parser
- ✅ Full standard library (50+ functions)
- ✅ Error handling system
- ✅ Network capabilities
- ✅ File operations
- ✅ Multi-statement programs

### Future Versions
- 🔄 Object-oriented programming
- 🔄 Module system improvements
- 🔄 Debugging tools
- 🔄 IDE integration
- 🔄 Package manager
- 🔄 Cross-platform compilation

## 📞 Contact & Support

- **Email**: info@xorix.ir
- **GitHub**: [github.com/mr-ali-jafari/xorlang](https://github.com/mr-ali-jafari/xorlang)
- **Website**: [xorix.ir](https://xorix.ir)

## 🤝 Contributing

We welcome contributions! Please see our contributing guidelines and feel free to:
- Report bugs
- Suggest features
- Submit pull requests
- Improve documentation

## 📄 License

This project is released under the MIT License.

---

**XorLang** - Modern Programming Language with Persian Syntax 🇮🇷
