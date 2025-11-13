# 🔥 XorLang - Modern Programming Language

## 📖 Introduction

XorLang is a modern, compiled programming language designed with Persian-friendly syntax and advanced capabilities. This language was created to simplify programming and provide powerful tools for Iranian developers while maintaining international standards.

## ✨ Key Features

- 🚀 **Fast & Optimized Compiler** - Generates optimized C code
- 🎨 **Beautiful Persian Syntax** - Uses Persian keywords for ease of use
- 📚 **Complete Standard Library** - Math, String, File, Time, System, Networking
- 🔗 **Advanced Import System** - Module management with `putlib ... from ...`
- 🌐 **Networking Capabilities** - HTTP GET/POST, Download, Internet connectivity
- 🛡️ **Error Management** - Safe operations and intelligent error handling
- 🎯 **Beautiful Output** - Colorful messages and emojis in compiler

## 🛠️ Installation & Setup

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get install gcc libcurl4-openssl-dev

# CentOS/RHEL
sudo yum install gcc libcurl-devel

# macOS
brew install curl
```

### Building XorLang
```bash
git clone <repository>
cd xorlang
make
```

### Usage
```bash
# Compile XorLang file
./xorlang program.xor

# Run the program
./program.xor.out
```

## 📝 Syntax & Commands

### Variables
```xorlang
bucket name = 'Ali';
bucket age = 25;
bucket height = 1.75;
bucket is_student = yes;
```

### Arrays
```xorlang
bucket numbers[] = [1, 2, 3, 4, 5];
bucket names[] = ['Ali', 'Sara', 'Hassan'];
bucket mixed[] = [1, 'Hello', yes, 3.14];
```

### Conditionals
```xorlang
when if (age >= 18) {
    show('Adult');
} when else {
    show('Minor');
}
```

### Loops
```xorlang
// While loop
while loop (age < 30) {
    show(age);
    age = age + 1;
}

// For loop
for loop (bucket i = 0; i < 10; i = i + 1) {
    show(i);
}
```

### Functions
```xorlang
make function greet(bucket name) {
    show('Hello ' + name);
    give back name;
}

bucket result = greet('Ali');
```

### User Input
```xorlang
bucket user_name = ask('Enter your name: ');
show('Hello ' + user_name);
```

## 📚 Standard Library

### Math Module
```xorlang
show(math_sqrt(25));           // 5.00
show(math_pow(2, 3));          // 8.00
show(math_abs(-42));           // 42
show(math_max(10, 20));        // 20
show(math_min(5, 3));          // 3
show(math_round(3.7));         // 4
show(math_random());           // Random number
show(math_random_range(1, 10)); // Random number between 1-10
```

### String Module
```xorlang
show(string_to_upper('hello'));     // Convert to uppercase
show(string_to_lower('HELLO'));     // Convert to lowercase
show(string_trim('  hello  '));     // Remove whitespace
show(string_contains('hello world', 'world')); // 1 (found)
show(string_starts_with('hello', 'h')); // 1 (starts with)
```

### File Module
```xorlang
show(file_write('test.txt', 'Hello World'));  // 1 (success)
show(file_read('test.txt'));                  // 'Hello World'
show(file_exists('test.txt'));                // 1 (exists)
show(file_size('test.txt'));                  // File size in bytes
show(file_delete('test.txt'));                // 1 (deleted)
```

### Time Module
```xorlang
show(time_now());              // Current timestamp
time_sleep(2);                 // Sleep for 2 seconds
show(time_format(time_now())); // Formatted time
```

### System Module
```xorlang
show(system_run('ls -la'));           // Execute system command
show(system_get_env('HOME'));         // Get environment variable
```

### Networking Module
```xorlang
show(is_online());                    // Check internet connection
show(http_get('https://api.github.com')); // GET request
show(http_post('https://httpbin.org/post', 'data=test')); // POST request
show(download('https://example.com/file.txt', 'local.txt')); // Download file
```

### Error Handling
```xorlang
show(safe_divide(10, 2));     // 5 (safe division)
show(safe_divide(10, 0));     // 0 (prevents error)
show(error('Test error'));    // Display error message
```

## 🔗 Import System

### Import Specific Functions
```xorlang
putlib math_sqrt, math_pow from math;
show(math_sqrt(25));
```

### Import All Functions
```xorlang
putlib * from string;
show(string_to_upper('hello'));
```

### Import from Multiple Modules
```xorlang
putlib file_read, file_write from file;
putlib http_get from networking;
putlib time_now from time;
```

## 🎯 Practical Examples

### Simple Calculator
```xorlang
bucket num1 = ask('Enter first number: ');
bucket num2 = ask('Enter second number: ');

bucket sum = num1 + num2;
bucket product = num1 * num2;

show('Sum: ' + sum);
show('Product: ' + product);
```

### File Management
```xorlang
putlib file_write, file_read, file_exists from file;

bucket content = 'This is a test file';
file_write('data.txt', content);

when if (file_exists('data.txt')) {
    bucket data = file_read('data.txt');
    show('File content: ' + data);
}
```

### HTTP Request
```xorlang
putlib http_get, is_online from networking;

when if (is_online()) {
    bucket response = http_get('https://api.github.com');
    show('API Response: ' + response);
} when else {
    show('No internet connection');
}
```

### Array Processing
```xorlang
putlib math_max from math;

bucket numbers[] = [5, 2, 8, 1, 9];
bucket max_num = numbers[0];

for loop (bucket i = 1; i < 5; i = i + 1) {
    max_num = math_max(max_num, numbers[i]);
}

show('Maximum number: ' + max_num);
```

## 🔧 Project Structure

```
xorlang/
├── src/
│   ├── lexer.c          # Lexical analysis
│   ├── parser.c         # Syntax analysis
│   ├── codegen.c        # Code generation
│   ├── AST.c           # Abstract Syntax Tree
│   ├── main.c          # Main program
│   └── include/        # Header files
├── Makefile            # Build file
├── README.md           # English documentation
├── README_FA.md        # Persian documentation
└── examples/           # Example programs
```

## 🎨 Compiler Output Colors

- 🔥 **Blue**: Compiler name and version
- 🚀 **Purple**: Compilation start
- 🔧 **Cyan**: C code generation
- ⚡ **Yellow**: C code compilation
- ✅ **Green**: Success
- ❌ **Red**: Error

## 📊 Language Specifications

### Data Types
- **int**: Integer numbers
- **double**: Floating-point numbers
- **char***: Strings
- **int**: Boolean values (yes/no)
- **arrays**: Collections of elements

### Operators
- **Arithmetic**: `+`, `-`, `*`, `/`
- **Comparison**: `==`, `!=`, `>`, `<`, `>=`, `<=`
- **Logical**: `&&`, `||`, `!`
- **Assignment**: `=`

### Keywords
- `bucket`: Variable declaration
- `when if` / `when else`: Conditionals
- `while loop` / `for loop`: Loops
- `make function`: Function definition
- `give back`: Return statement
- `show`: Print/output
- `ask`: User input
- `yes` / `no`: Boolean values
- `putlib` / `from`: Import statements

## 🚀 Performance

XorLang compiles to optimized C code, providing:
- **Fast execution** comparable to C programs
- **Small binary size** due to efficient code generation
- **Memory safety** through careful resource management
- **Cross-platform compatibility** via C compilation

## 🧪 Testing

Run the test suite:
```bash
# Test standard library functions
./xorlang test_math.xor && ./test_math.xor.out
./xorlang test_string.xor && ./test_string.xor.out
./xorlang test_file.xor && ./test_file.xor.out

# Test networking features
./xorlang networking_test.xor && ./networking_test.xor.out

# Test import system
./xorlang test_import.xor && ./test_import.xor.out
```

## 🤝 Contributing

To contribute to XorLang development:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Create a Pull Request

### Development Guidelines
- Follow the existing code style
- Add tests for new features
- Update documentation for changes
- Ensure all tests pass before submitting

## 🐛 Bug Reports

When reporting bugs, please include:
- XorLang version
- Operating system
- Minimal code example that reproduces the issue
- Expected vs actual behavior

## 📈 Roadmap

### Upcoming Features
- [ ] Advanced array operations
- [ ] JSON processing module
- [ ] Database connectivity
- [ ] Regular expressions
- [ ] Cryptographic functions
- [ ] Package manager
- [ ] IDE integration
- [ ] Debugging tools

## 📄 License

This project is licensed under the MIT License. See the LICENSE file for details.

## 🙏 Acknowledgments

Thanks to all contributors who have helped develop XorLang:
- Core language design and implementation
- Standard library development
- Documentation and examples
- Testing and bug reports

## 📞 Support

For support and questions:
- Create an issue on GitHub
- Join our community discussions
- Check the documentation and examples

---

**XorLang - Modern Programming Language for Persian Developers** 🇮🇷

### Quick Start Example

```xorlang
// Hello World in XorLang
show('Hello, World!');

// Variables and calculations
bucket radius = 5;
bucket area = math_pow(radius, 2) * 3.14159;
show('Circle area: ' + area);

// User interaction
bucket name = ask('What is your name? ');
show('Nice to meet you, ' + name + '!');

// File operations
file_write('greeting.txt', 'Hello from XorLang!');
bucket content = file_read('greeting.txt');
show('File says: ' + content);
```

**Start coding with XorLang today!** 🚀
