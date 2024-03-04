#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h> /* size_t */

#define LEPT_KEY_NOT_EXIST ((size_t)-1)

// 所有解析情况的枚举的枚举
enum {
    // 解析成功
    LEPT_PARSE_OK = 0,
    // 只含有空白
    LEPT_PARSE_EXPECT_VALUE,
    // 含有无效的值
    LEPT_PARSE_INVALID_VALUE,
    // 一个值在空白后还有其他值
    LEPT_PARSE_ROOT_NOT_SINGULAR,
    // 数字太大
    LEPT_PARSE_NUMBER_TOO_BIG,
    // 缺少引号
    LEPT_PARSE_MISS_QUOTATION_MARK,
    // 无效的转移字符
    LEPT_PARSE_INVALID_STRING_ESCAPE,
    // 无效字符
    LEPT_PARSE_INVALID_STRING_CHAR,
    // 无效的UTF-8编码
    LEPT_PARSE_INVALID_UNICODE_HEX,
    // 无效的UTF-8编码代理
    LEPT_PARSE_INVALID_UNICODE_SURROGATE,
    // 缺少中括号
    LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,
    // 缺少键值
    LEPT_PARSE_MISS_KEY,
    // 缺少冒号
    LEPT_PARSE_MISS_COLON,
    // 缺少大括号
    LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET
};

// 所有的JSON数据类型，用枚举的形式
typedef enum { 
    LEPT_NULL, 
    LEPT_FALSE, 
    LEPT_TRUE, 
    LEPT_NUMBER, 
    LEPT_STRING, 
    LEPT_ARRAY, 
    LEPT_OBJECT
} lept_type;

// 前向声明
typedef struct lept_value lept_value;
typedef struct lept_member lept_member;

// 树状数据结构，用来存储JSON解析结果
struct lept_value {
    union {
        struct { lept_member* m; size_t o_size, o_capacity; };      // object
        struct { lept_value* e; size_t a_size, a_capacity; };       // array
        struct { char* s; size_t len; };                // string
        double n;                                       // number
    };
    lept_type type;
};

// JSON对象结构体
struct lept_member {
    char* k; size_t klen;   /* member key string, key string length */
    lept_value v;           /* member value */
};

// 宏函数初始化JSON类型
#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)

// JSON解析函数
int lept_parse(lept_value* v, const char* json);
// 生成JSON字符串
char* lept_stringify(const lept_value* v, size_t* length);

// 复制
void lept_copy(lept_value* dst, const lept_value* src);
// 移动
void lept_move(lept_value* dst, lept_value* src);
// 交换
void lept_swap(lept_value* lhs, lept_value* rhs);

// 释放JSON数据空间
void lept_free(lept_value* v);

// 获取JSON类型
lept_type lept_get_type(const lept_value* v);
// 是否相等
int lept_is_equal(const lept_value* lhs, const lept_value* rhs);

// 将JSON数据类型设置为空
#define lept_set_null(v) lept_free(v)

// 获取布尔型JSON值
int lept_get_boolean(const lept_value* v);
// 设置布尔型JSON值
void lept_set_boolean(lept_value* v, int b);

// 获取数字型JSON值
double lept_get_number(const lept_value* v);
// 设置布尔型JSON值
void lept_set_number(lept_value* v, double n);

// 获取字符型JSON值
const char* lept_get_string(const lept_value* v);
// 获取字符型JSON字符长度
size_t lept_get_string_length(const lept_value* v);
// 设置字符型JSON值
void lept_set_string(lept_value* v, const char* s, size_t len);

void lept_set_array(lept_value* v, size_t capacity);
// 获取数组型JSON大小
size_t lept_get_array_size(const lept_value* v);
size_t lept_get_array_capacity(const lept_value* v);
void lept_reserve_array(lept_value* v, size_t capacity);
void lept_shrink_array(lept_value* v);
void lept_clear_array(lept_value* v);
// 获取数组型JSON数据的元素
lept_value* lept_get_array_element(const lept_value* v, size_t index);
lept_value* lept_pushback_array_element(lept_value* v);
void lept_popback_array_element(lept_value* v);
lept_value* lept_insert_array_element(lept_value* v, size_t index);
void lept_erase_array_element(lept_value* v, size_t index, size_t count);

void lept_set_object(lept_value* v, size_t capacity);
// 获取JSON对象的大小
size_t lept_get_object_size(const lept_value* v);
size_t lept_get_object_capacity(const lept_value* v);
void lept_reserve_object(lept_value* v, size_t capacity);
void lept_shrink_object(lept_value* v);
void lept_clear_object(lept_value* v);
// 获取JSON对象的键值
const char* lept_get_object_key(const lept_value* v, size_t index);
// 获取JSON对象的键值长度
size_t lept_get_object_key_length(const lept_value* v, size_t index);
// 获取JSON对象的值
lept_value* lept_get_object_value(const lept_value* v, size_t index);
size_t lept_find_object_index(const lept_value* v, const char* key, size_t klen);
lept_value* lept_find_object_value(lept_value* v, const char* key, size_t klen);
lept_value* lept_set_object_value(lept_value* v, const char* key, size_t klen);
void lept_remove_object_value(lept_value* v, size_t index);

#endif /* LEPTJSON_H__ */