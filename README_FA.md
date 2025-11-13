# 🚀 زبان برنامه‌نویسی XorLang

**XorLang** یک زبان برنامه‌نویسی کامپایل شده و مدرن است که با سینتکس فارسی طراحی شده و قابلیت‌های پیشرفته‌ای برای توسعه نرم‌افزار ارائه می‌دهد.

## 📋 فهرست مطالب

- [ویژگی‌ها](#ویژگی‌ها)
- [نصب و راه‌اندازی](#نصب-و-راه‌اندازی)
- [سینتکس زبان](#سینتکس-زبان)
- [کتابخانه‌های استاندارد](#کتابخانه‌های-استاندارد)
- [مثال‌های کاربردی](#مثال‌های-کاربردی)
- [ساختار پروژه](#ساختار-پروژه)
- [کامپایل و اجرا](#کامپایل-و-اجرا)

## 🌟 ویژگی‌ها

### ویژگی‌های اصلی
- **زبان کامپایل شده**: تولید کد C بهینه و سریع
- **سینتکس فارسی**: کلمات کلیدی به زبان فارسی
- **سیستم نوع قوی**: تشخیص خودکار نوع متغیرها
- **کتابخانه‌های غنی**: ماژول‌های آماده برای کارهای مختلف
- **پشتیبانی از شبکه**: قابلیت‌های HTTP و دانلود
- **مدیریت خطا**: سیستم مدیریت خطای ایمن

### انواع داده‌ها
- **اعداد صحیح**: `bucket x = 42;`
- **اعداد اعشاری**: `bucket pi = 3.14;`
- **رشته‌ها**: `bucket name = 'علی';`
- **بولین**: `bucket flag = yes;` / `bucket flag = no;`
- **آرایه‌ها**: `bucket numbers[] = [1, 2, 3];`

## 🛠 نصب و راه‌اندازی

### پیش‌نیازها
```bash
# نصب ابزارهای مورد نیاز
sudo apt update
sudo apt install gcc make libcurl4-openssl-dev
```

### کامپایل کامپایلر
```bash
git clone https://github.com/mr-ali-jafari/xorlang.git
cd xorlang
make
```

### اجرای برنامه
```bash
# کامپایل فایل XorLang
./xorlang program.xor

# اجرای برنامه کامپایل شده
./program.xor.out
```

## 📝 سینتکس زبان

### کامنت گذاری
‍‍‍```xorlang
note: hey this is comment
```

### تعریف متغیرها
```xorlang
bucket name = 'علی جعفری';
bucket age = 25;
bucket height = 1.75;
bucket is_student = yes;
bucket numbers[] = [1, 2, 3, 4, 5];
```

### ساختارهای کنترلی

#### شرطی‌ها
```xorlang
when if (age > 18) {
    show('بزرگسال است');
} when else {
    show('کودک است');
}
```

#### حلقه‌ها
```xorlang
# حلقه while
bucket i = 0;
while loop (i < 5) {
    show(i);
    bucket i = i + 1;
}

# حلقه for
for loop (bucket j = 0; j < 10; bucket j = j + 1) {
    show(j);
}
```

### توابع
```xorlang
make function greet(name) {
    show('سلام ' + name);
    give back 'خوش آمدید';
}

bucket result = greet('علی');
```

### ورودی و خروجی
```xorlang
bucket user_name = ask('نام خود را وارد کنید: ');
show('سلام ' + user_name);
```

## 📚 کتابخانه‌های استاندارد

### ماژول ریاضی
```xorlang
bucket sqrt_result = math_sqrt(25);        # 5.0
bucket power_result = math_pow(2, 3);      # 8.0
bucket abs_result = math_abs(-42);         # 42
bucket max_result = math_max(10, 20);      # 20
bucket random_num = math_random_range(1, 10);
```

### ماژول رشته
```xorlang
bucket upper_text = string_to_upper('hello'); # "HELLO"
bucket contains = string_contains('سلام دنیا', 'دنیا'); # 1
bucket trimmed = string_trim('  متن  ');
```

### ماژول فایل
```xorlang
bucket content = file_read('data.txt');
file_write('output.txt', 'محتوای جدید');
bucket exists = file_exists('myfile.txt');
bucket size = file_size('document.pdf');
```

### ماژول زمان
```xorlang
bucket current_time = time_now();
bucket formatted = time_format(current_time, '%Y-%m-%d');
time_sleep(2); # توقف 2 ثانیه‌ای
```

### ماژول شبکه
```xorlang
bucket online = is_online();
bucket response = http_get('https://api.example.com/data');
bucket post_result = http_post('https://api.example.com/submit', 'data=value');
bucket downloaded = download('https://example.com/file.zip', 'local_file.zip');
```

### مدیریت خطا
```xorlang
bucket safe_result = safe_divide(100, 0); # برمی‌گرداند 0 به جای خطا
bucket error_code = error('خطای سفارشی'); # چاپ خطا و برگرداندن -1
```

### ماژول آرایه
```xorlang
bucket length = len(numbers);
push(numbers, 6);
bucket last = pop(numbers);
bucket sorted = array_sort(numbers);
bucket reversed = array_reverse(numbers);
```

## 💡 مثال‌های کاربردی

### محاسبه‌گر ساده
```xorlang
bucket num1 = ask('عدد اول را وارد کنید: ');
bucket num2 = ask('عدد دوم را وارد کنید: ');
bucket operation = ask('عملیات (+, -, *, /): ');

when if (operation == '+') {
    show('نتیجه: ' + (num1 + num2));
} when else when if (operation == '-') {
    show('نتیجه: ' + (num1 - num2));
} when else when if (operation == '*') {
    show('نتیجه: ' + (num1 * num2));
} when else when if (operation == '/') {
    bucket result = safe_divide(num1, num2);
    show('نتیجه: ' + result);
}
```

### مدیر فایل
```xorlang
bucket filename = ask('نام فایل را وارد کنید: ');

when if (file_exists(filename)) {
    bucket content = file_read(filename);
    show('محتوای فایل: ' + content);
    show('اندازه فایل: ' + file_size(filename) + ' بایت');
} when else {
    show('فایل یافت نشد!');
    bucket new_content = ask('محتوای جدید را وارد کنید: ');
    file_write(filename, new_content);
    show('فایل ایجاد شد!');
}
```

### درخواست وب
```xorlang
when if (is_online()) {
    show('اتصال اینترنت برقرار است');
    bucket api_response = http_get('https://httpbin.org/json');
    show('پاسخ API: ' + api_response);
    
    bucket download_result = download('https://httpbin.org/json', 'api_data.json');
    when if (download_result == 1) {
        show('فایل با موفقیت دانلود شد');
    } when else {
        show('خطا در دانلود فایل');
    }
} when else {
    show('اتصال اینترنت برقرار نیست');
}
```

## 🏗 ساختار پروژه

```
xorlang/
├── src/
│   ├── include/
│   │   ├── lexer.h          # تعاریف لکسر
│   │   ├── parser.h         # تعاریف پارسر
│   │   ├── AST.h           # ساختار درخت نحوی
│   │   ├── codegen.h       # تولیدکننده کد
│   │   └── token.h         # تعاریف توکن‌ها
│   ├── lexer.c             # پیاده‌سازی لکسر
│   ├── parser.c            # پیاده‌سازی پارسر
│   ├── AST.c              # پیاده‌سازی درخت نحوی
│   ├── codegen.c          # تولیدکننده کد C
│   ├── token.c            # پیاده‌سازی توکن‌ها
│   └── main.c             # برنامه اصلی کامپایلر
├── Makefile               # فایل ساخت
└── README_FA.md          # مستندات فارسی
```

### مراحل کامپایل
1. **لکسر (Lexer)**: تبدیل کد منبع به توکن‌ها
2. **پارسر (Parser)**: تبدیل توکن‌ها به درخت نحوی (AST)
3. **تولیدکننده کد (Codegen)**: تولید کد C از درخت نحوی
4. **کامپایلر C**: کامپایل کد C به فایل اجرایی

## ⚡ کامپایل و اجرا

### کامپایل کامپایلر
```bash
make clean  # پاک کردن فایل‌های قبلی
make        # ساخت کامپایلر
```

### استفاده از کامپایلر
```bash
# کامپایل برنامه XorLang
./xorlang program.xor [output.c]

# اجرای برنامه
./program.xor.out
```

### مثال کامل
```bash
# ایجاد فایل برنامه
echo "bucket name = ask('نام شما: '); show('سلام ' + name);" > hello.xor

# کامپایل
./xorlang hello.xor

# اجرا
./hello.xor.out
```

## 🔧 ویژگی‌های پیشرفته

### سیستم Import
```xorlang
putlib math_sqrt, math_pow from math;
putlib string_to_upper from string;
putlib * from file;
```

### مدیریت حافظه
- تخصیص خودکار حافظه برای رشته‌ها و آرایه‌ها
- آزادسازی خودکار حافظه در کد تولید شده
- بهینه‌سازی استفاده از حافظه

### بهینه‌سازی‌ها
- تشخیص نوع در زمان کامپایل
- بهینه‌سازی عملیات ریاضی
- حذف کدهای غیرضروری

## 📞 تماس و پشتیبانی

- **ایمیل**: info@xorix.ir
- **گیت‌هاب**: [github.com/mr-ali-jafari/xorlang](https://github.com/mr-ali-jafari/xorlang)
- **وب‌سایت**: [xorix.ir](https://xorix.ir)

## 📄 مجوز

این پروژه تحت مجوز MIT منتشر شده است.

---

**XorLang** - زبان برنامه‌نویسی مدرن با سینتکس فارسی 🇮🇷
