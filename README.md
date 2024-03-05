# About:
k2v(key-to-value) is a very very simple config file format.       
It's simple, rigid, without super cow power, and maybe stupid.      
It only designed for one purpose:      
- Get the `value` of the `key`.

# Why:
K2V looks like TOML(Tom's Obvious, Minimal Language).      
TOML prioritizes humans, but K2V only prioritizes the developer.      
TOML is very powerful, but K2V is simple, and it's good enough in many scenarios.      
K2V can be easily convert to bash with `k2sh`.      
libk2v only contain 1000- lines of code, while tomlc99 have 2000+.      
# K2V standard:
```
 * We will always use a (char *)key to get the value.
 * The comment line starts with `#`, and `#` should be the first character of the line.
 * All the value should be wrapped by `"`, and do not use `'`.
 * The key should not be wrapped.
 * The end of a line is '\n', and will not contain `;` or `,`.
 * The array is wrapped by `[]`,and each value should be separated by `,`.
 * It does not support multi-line, so use single line for one key/value pair.
```
# Supported types:
```toml
# Bool value.
bool_val="true"
# String.
char_val="string"
# Int.
int_val="114514"
# float.
float_val="19.19810"
# Int array.
int_array_val=["1","2","3"]
# float array.
float_array_val=["1.0","2.0","3.0"]
# Char array.
char_array_val=["string1","string2","string3"]
```
# K2SH:
`k2sh` is a binary that converts k2v to shell format.            
The above config will be converted to:         
```sh
bool_val="true"
char_val="string"
int_val="114514"
float_val="19.19810"
int_array_val=("1" "2" "3")
float_array_val=("1.0" "2.0" "3.0")
char_array_val=("string1" "string2" "string3")
```
# Hello world:
test/hello.conf:
```toml
string="Hello world!"
```
test/hello.c:
```C
#include "../src/include/k2v.h"
int main(void)
{
        // Read the config to memory.
        char *buf = k2v_open_file("./test/hello.conf", 1024);
        // Get the value of `string`.
        char *str = key_get_char("string", buf);
        // Print the value.
        printf("%s\n", str);
        // libk2v will automatically allocate memory.
        // Do not forget to free(2) the memory after using it.
        free(buf);
        free(str);
}
```
Compile, and run:
```log
~/libk2v # cc -lk2v test/hello.c
~/libk2v # ./a.out
Hello world!
~/libk2v #
```
# Using libk2v:
You can just simply include the k2v.c and k2v.h files in your project.      
# Example program using libk2v:
[ruri/src/rurienv.c](https://github.com/Moe-hacker/ruri/blob/main/src%2Frurienv.c)
[ruri/src/config.c](https://github.com/Moe-hacker/ruri/blob/main/src%2Fconfig.c)
# Function list:
```C
char *key_get_char(const char *key, const char *buf);
int key_get_int(const char *key, const char *buf);
float key_get_float(const char *key, const char *buf);
bool key_get_bool(const char *key, const char *buf);
int key_get_int_array(const char *key, const char *buf, int *array);
int key_get_char_array(const char *key, const char *buf, char *array[]);
int key_get_float_array(const char *key, const char *buf, float *array);
bool have_key(const char *key, const char *buf);
char *k2v_open_file(char *path, size_t bufsize);
void k2v_to_shell(const char *buf);
char *char_to_k2v(const char *key, const char *val);
char *int_to_k2v(const char *key, int val);
char *bool_to_k2v(const char *key, bool val);
char *float_to_k2v(const char *key, float val);
char *char_array_to_k2v(const char *key, char *const *val, int len);
char *int_array_to_k2v(const char *key, int *val, int len);
char *float_array_to_k2v(const char *key, float *val, int len);
```
For usage, see [test/test.c](test/test.c).      
# Global variables:
```C
// Exit when the config file have unrecognized lines.
// Default: false
extern bool k2v_stop_at_warning;
// Show warning when the config file have unrecognized lines.
// Default: true.
extern bool k2v_show_warning;
```
# Benchmarking:
K2V is designed only for small config files, it need not to be very fast for large config files.      
Here is a 23 lines config test, it only takes <0.02s on my Nothing Phone(2).      
```log
~/libk2v # time ./testk2v
libk2v warning: unrecognized line: ryudhhdgdg
libk2v warning: unrecognized line: jdjdhdhhsb=
libk2v warning: unrecognized line: hdhhhdhdh="
libk2v warning: unrecognized line: shhdhdh=[
libk2v warning: unrecognized line: hdusjhsb  jsjsgh hsjdhhd
null char
string
true
114514
19.198099
1 2 3
1.000000 2.000000 3.000000
string1 string2 string3

real    0m0.015s
user    0m0.007s
sys     0m0.008s
```
