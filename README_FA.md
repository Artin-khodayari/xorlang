# 🔥 XorLang - زبان برنامه‌نویسی مدرن

## 📖 معرفی

XorLang یک زبان برنامه‌نویسی مدرن و کامپایل شده است که با syntax فارسی و قابلیت‌های پیشرفته طراحی شده است. این زبان برای آسان‌سازی برنامه‌نویسی و ارائه ابزارهای قدرتمند برای توسعه‌دهندگان ایرانی ساخته شده است.

## ✨ ویژگی‌های کلیدی

- 🚀 **کامپایلر سریع و بهینه** - تولید کد C بهینه
- 🎨 **Syntax زیبا و فارسی** - استفاده از کلمات فارسی برای راحتی
- 📚 **کتابخانه استاندارد کامل** - Math, String, File, Time, System, Networking
- 🔗 **سیستم Import پیشرفته** - مدیریت ماژول‌ها با `putlib ... from ...`
- 🌐 **قابلیت‌های شبکه** - HTTP GET/POST, Download, اتصال اینترنت
- 🛡️ **مدیریت خطا** - عملیات امن و مدیریت خطاهای هوشمند
- 🎯 **خروجی زیبا** - پیام‌های رنگی و emoji در کامپایلر

## 🛠️ نصب و راه‌اندازی

### پیش‌نیازها
```bash
# Ubuntu/Debian
sudo apt-get install gcc libcurl4-openssl-dev

# CentOS/RHEL
sudo yum install gcc libcurl-devel
```

### کامپایل XorLang
```bash
git clone <repository>
cd xorlang
make
```

### استفاده
```bash
# کامپایل فایل XorLang
./xorlang program.xor

# اجرای برنامه
./program.xor.out
```

## 📝 Syntax و دستورات

### متغیرها
```xorlang
bucket name = 'علی';
bucket age = 25;
bucket height = 1.75;
bucket is_student = yes;
```

### آرایه‌ها
```xorlang
bucket numbers[] = [1, 2, 3, 4, 5];
bucket names[] = ['علی', 'مریم', 'حسن'];
bucket mixed[] = [1, 'سلام', yes, 3.14];
```

### شرطی‌ها
```xorlang
when if (age >= 18) {
    show('بزرگسال');
} when else {
    show('نوجوان');
}
```

### حلقه‌ها
```xorlang
// حلقه while
while loop (age < 30) {
    show(age);
    age = age + 1;
}

// حلقه for
for loop (bucket i = 0; i < 10; i = i + 1) {
    show(i);
}
```

### توابع
```xorlang
make function greet(bucket name) {
    show('سلام ' + name);
    give back name;
}

bucket result = greet('علی');
```

### ورودی از کاربر
```xorlang
bucket user_name = ask('نام خود را وارد کنید: ');
show('سلام ' + user_name);
```

## 📚 کتابخانه استاندارد

### ماژول Math
```xorlang
show(math_sqrt(25));           // 5.00
show(math_pow(2, 3));          // 8.00
show(math_abs(-42));           // 42
show(math_max(10, 20));        // 20
show(math_min(5, 3));          // 3
show(math_round(3.7));         // 4
show(math_random());           // عدد تصادفی
show(math_random_range(1, 10)); // عدد تصادفی بین 1 تا 10
```

### ماژول String
```xorlang
show(string_to_upper('سلام'));     // تبدیل به حروف بزرگ
show(string_to_lower('HELLO'));    // تبدیل به حروف کوچک
show(string_trim('  سلام  '));     // حذف فاصله‌های اضافی
show(string_contains('سلام دنیا', 'دنیا')); // 1 (پیدا شد)
show(string_starts_with('سلام', 'س')); // 1 (شروع می‌شود با)
```

### ماژول File
```xorlang
show(file_write('test.txt', 'سلام دنیا'));  // 1 (موفق)
show(file_read('test.txt'));                // 'سلام دنیا'
show(file_exists('test.txt'));              // 1 (وجود دارد)
show(file_size('test.txt'));                // اندازه فایل
show(file_delete('test.txt'));              // 1 (حذف شد)
```

### ماژول Time
```xorlang
show(time_now());              // timestamp فعلی
time_sleep(2);                 // توقف 2 ثانیه
show(time_format(time_now())); // فرمت زمان
```

### ماژول System
```xorlang
show(system_run('ls -la'));           // اجرای دستور سیستم
show(system_get_env('HOME'));         // دریافت متغیر محیطی
```

### ماژول Networking
```xorlang
show(is_online());                    // بررسی اتصال اینترنت
show(http_get('https://api.github.com')); // درخواست GET
show(http_post('https://httpbin.org/post', 'data=test')); // درخواست POST
show(download('https://example.com/file.txt', 'local.txt')); // دانلود فایل
```

### مدیریت خطا
```xorlang
show(safe_divide(10, 2));     // 5 (تقسیم امن)
show(safe_divide(10, 0));     // 0 (جلوگیری از خطا)
show(error('خطای تست'));      // نمایش پیام خطا
```

## 🔗 سیستم Import

### Import توابع خاص
```xorlang
putlib math_sqrt, math_pow from math;
show(math_sqrt(25));
```

### Import همه توابع
```xorlang
putlib * from string;
show(string_to_upper('سلام'));
```

### Import از ماژول‌های مختلف
```xorlang
putlib file_read, file_write from file;
putlib http_get from networking;
putlib time_now from time;
```

## 🎯 مثال‌های کاربردی

### محاسبه‌گر ساده
```xorlang
bucket num1 = ask('عدد اول را وارد کنید: ');
bucket num2 = ask('عدد دوم را وارد کنید: ');

bucket sum = num1 + num2;
bucket product = num1 * num2;

show('جمع: ' + sum);
show('ضرب: ' + product);
```

### مدیریت فایل
```xorlang
putlib file_write, file_read, file_exists from file;

bucket content = 'این یک فایل تست است';
file_write('data.txt', content);

when if (file_exists('data.txt')) {
    bucket data = file_read('data.txt');
    show('محتوای فایل: ' + data);
}
```

### درخواست HTTP
```xorlang
putlib http_get, is_online from networking;

when if (is_online()) {
    bucket response = http_get('https://api.github.com');
    show('پاسخ API: ' + response);
} when else {
    show('اتصال اینترنت موجود نیست');
}
```

### پردازش آرایه
```xorlang
putlib math_max from math;

bucket numbers[] = [5, 2, 8, 1, 9];
bucket max_num = numbers[0];

for loop (bucket i = 1; i < 5; i = i + 1) {
    max_num = math_max(max_num, numbers[i]);
}

show('بزرگترین عدد: ' + max_num);
```

## 🔧 ساختار پروژه

```
xorlang/
├── src/
│   ├── lexer.c          # تحلیل واژگانی
│   ├── parser.c         # تحلیل نحوی
│   ├── codegen.c        # تولید کد
│   ├── AST.c           # درخت نحوی انتزاعی
│   ├── main.c          # برنامه اصلی
│   └── include/        # فایل‌های header
├── Makefile            # فایل ساخت
├── README.md           # مستندات انگلیسی
├── README_FA.md        # مستندات فارسی
```



## 🤝 مشارکت

برای مشارکت در توسعه XorLang:

1. Repository را Fork کنید
2. شاخه جدید بسازید (`git checkout -b feature/amazing-feature`)
3. تغییرات را commit کنید (`git commit -m 'Add amazing feature'`)
4. به شاخه push کنید (`git push origin feature/amazing-feature`)
5. Pull Request ایجاد کنید

## 📄 مجوز

این پروژه تحت مجوز MIT منتشر شده است. برای جزئیات بیشتر فایل LICENSE را مطالعه کنید.

## 🙏 تشکر

از همه کسانی که در توسعه XorLang مشارکت کرده‌اند، تشکر می‌کنیم.

---

**XorLang - زبان برنامه‌نویسی مدرن برای توسعه‌دهندگان ایرانی** 🇮🇷
