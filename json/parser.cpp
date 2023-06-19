
#include "parser.hpp"
#define THROW_ERROR(error) throw std::logic_error((#error))

using namespace aclolinta::json;

Parser::Parser() {
    m_str = "";
    m_index = 0;
}

void Parser::Clear() {
    if (m_instance != nullptr) {
        delete m_instance;
        m_instance = nullptr;
    }
}

Parser* Parser::GetInstance() {
    if (m_instance == nullptr) {
        m_instance = new Parser();
        std::atexit(Parser::Clear);
    }
    return m_instance;
}

void Parser::init(std::string_view str) {
    // 读入字符串
    m_str = str;  // 这是深copy
    m_index = 0;
}

char Parser::GetNextToken() {
    // 去除空格
    while (std::isspace(m_str[m_index])) {
        ++m_index;
    }
    // auto ch = m_str[m_index];
    return m_str[m_index];
}
// 类型解析

Json Parser::ParserStart() {
    // 开始分析
    char token_ = GetNextToken();

    if (token_ == 'n' || token_ == 'N') {
        return ParserNull();
    } else if ((token_ == 't' || token_ == 'f' || token_ == 'T' ||
                token_ == 'F') &&
               isBoolType()) {
        return ParserBool();
    } else if (token_ == '-' || std::isdigit(token_)) {
        return ParserNum();
    } else if (token_ == '\"') {
        return ParserString();
    } else if (token_ == '[') {
        return ParserList();
    } else if (token_ == '{') {
        return ParserObj();
    }

    THROW_ERROR(UNEXPECTED CHARACTER IN START PARSER JSON);
}
// 具体数据类型分析
Json Parser::ParserNull() {
    std::string str_ = m_str.substr(m_index, 4);  // 截取一下后面的四个字符
    std::transform(str_.begin(), str_.end(), str_.begin(),
                   ::tolower);  // 全都弄成小写
    if (str_.compare("null") == 0) {
        m_index += 4;
        return Json();
    }
    THROW_ERROR(PARSER NULL ERROR);
}

bool Parser::ParserBool() {
    std::string str_ =
        (m_str[m_index] == 't' || m_str[m_index] == 'T')
            ? m_str.substr(m_index, 4)
            : m_str.substr(m_index, 5);  // 截取一下后面的四个字符或者五个字符

    if (m_str.begin() + str_.size() + 1 == m_str.end()) {
        // 判断字符串后面还有没有剩余字符,有则直接抛出异常
        THROW_ERROR(UNEXPECT CHARACTER AFTER BOOL VALUE);
    }
    std::transform(str_.begin(), str_.end(), str_.begin(),
                   ::tolower);  // 全都弄成小写
    if (str_.compare("true") == 0) {
        m_index += 4;
        return true;
    } else if (str_.compare("false") == 0) {
        m_index += 5;
        return false;
    }

    THROW_ERROR(PARSE BOOL ERROR);
}

Json Parser::ParserNum() {
    size_t startpos_ = m_index;  // 起始位置

    // 先处理符号位
    if (m_str[m_index] == '-') ++m_index;
    // 处理逗号前面的部分
    if (std::isdigit(m_str[m_index])) {
        while (std::isdigit(m_str[m_index])) {
            ++m_index;
        }
    } else {
        THROW_ERROR(INVALID CHARACTER IN NUMBER);
    }
    // 处理没有逗号的情况
    if (m_str[m_index] != '.') {
        return Json(static_cast<int_t>(
            std::stoll(m_str.c_str() + startpos_, nullptr, 10)));
    }

    if (m_str[m_index] == '.') {
        // 处理逗号的情况,即小数部分
        ++m_index;
        if (!std::isdigit(m_str[m_index])) {
            // 逗号后面不是数字
            THROW_ERROR(EXPECT FIGURE AFTER DOT);
        } else {
            while (std::isdigit(m_str[m_index])) {
                ++m_index;
            }
        }
        // 在某些特殊情况下仍然会错误的截断字符串，但是不会报错
        //  if (m_str[m_index]!=std::string::npos){
        //      THROW_ERROR(EXPECT CHARACTER AFTER DOT);
        //  }
        return Json(static_cast<double_t>(
            std::stod(m_str.c_str() + startpos_, nullptr)));
    }

    THROW_ERROR(INVALID NUMBER);
}

std::string Parser::ParserString() {
    size_t startpos_ = ++m_index;               //["]后面的位置
    size_t endpos_ = m_str.find('"', m_index);  // 获取第一个引号结束的位置

    auto c_ = m_str[m_index];

    // 下面开始处理
    if (endpos_ != std::string::npos) {
        // 处理转义字符
        while (true) {
            if (m_str[endpos_ - 1] != '\\')
                break;  // 读取到的["]不是转义字符，进入处理流程
            if (isMulitEscape(endpos_)) break;
            endpos_ = m_str.find('"', ++endpos_);  // 找下一个["]

            if (endpos_ == std::string::npos) {
                THROW_ERROR(UNEXPECT MISSING '"' IN PARSER STRING);
            }
        }
        m_index = ++endpos_;  // 指针滑动到引号之后
        return m_str.substr(startpos_, m_index - startpos_ - 1);
    }

    THROW_ERROR(UNEXPECT ERROR IN PARSER STRING);
}

Json Parser::ParserList() {
    // 先创建一个Json对象
    Json jsonlist_(json::TYPE_LIST);

    ++m_index;
    char ch_ = GetNextToken();
    // 如果是空的列表
    if (ch_ == ']') {
        ++m_index;
        return jsonlist_;
    }
    // 开始处理非空列表
    while (true) {
        jsonlist_.emplace(ParserStart());  // 获取下一个obj
        ch_ = GetNextToken();
        // 结束标记
        if (ch_ == ']') {
            ++m_index;
            break;
            // 结束处理流程
        }
        if (ch_ != ',') {
            // 列表内的元素应该使用[，]分割。若读入的非逗号，应该抛出错误
            THROW_ERROR(UNEXPECTED DOT IN PARSE LIST);
        }
        ++m_index;
    }

    return jsonlist_;
}

Json Parser::ParserObj() {
    // 先创建一个Json对象
    Json jsonobj_(json::TYPE_OBJ);

    ++m_index;
    char ch_ = GetNextToken();
    // 先处理空列表
    if (ch_ == '}') {
        ++m_index;
        return jsonobj_;
    }

    // 开始处理非空dict
    while (true) {
        // 解析Key
        // ch_ = GetNextToken();
        string key_ = ParserString();
        ch_ = GetNextToken();

        // 处理冒号[:],Key后面必须跟的是[:]
        if (ch_ != ':') {
            THROW_ERROR(R"(MISSING ':' IN PARSE OBJ)");
        }
        ++m_index;

        // 处理Key
        jsonobj_[key_] = ParserStart();  // 读入value
        ch_ = GetNextToken();
        if (ch_ == '}') {  // 完成读取了
            ++m_index;
            break;
        }
        // 处理下一对K-V
        if (ch_ != ',') {  // 对象之间用[,]分割
            THROW_ERROR(R"(MISSING ',' IN PARSE OBJ)");
        } else {
            // 跳过逗号
            ++m_index;
            // 跳过逗号后面可能存在的空格，ParserString()只能处理[\"]开头的
            if (std::isspace(m_str[m_index])) {
                GetNextToken();
            }
        }
    }
    return jsonobj_;
}
// 辅助函数
bool Parser::isMulitEscape(size_t pos) {
    // 处理多个斜杠的情况
    size_t end_pos = pos;
    while (m_str[pos] == '\\') --pos;
    return ((end_pos - pos) & 1) == 0;  // 偶数个[\]就抵消了
}

bool Parser::isBoolType() {
    std::string turestr_ = m_str.substr(m_index, 4);
    std::string falsestr_ = m_str.substr(m_index, 5);

    std::transform(turestr_.begin(), turestr_.end(), turestr_.begin(),
                   ::tolower);  // 全都弄成小写
    std::transform(falsestr_.begin(), falsestr_.end(), falsestr_.begin(),
                   ::tolower);  // 全都弄成小写
    if (turestr_.compare("true") == 0) {
        return true;
    }
    if (falsestr_.compare("false") == 0) {
        return true;
    }

    return false;
}

//
Parser* Parser::m_instance = nullptr;