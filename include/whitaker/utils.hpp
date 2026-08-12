#pragma once

#include <string>
#include <charconv>
#include <vector>

namespace words {
    //Taken from https://mobiarch.wordpress.com/2022/12/12/string-to-number-conversion-in-modern-c/
    template <typename T>
    bool vtonum(const std::string_view &view, T& value) {
        if (view.empty()) {
            return false;
        }
        
        const char* first = view.data();
        const char* last = view.data() + view.length();
        
        std::from_chars_result res = std::from_chars(first, last, value);
        
        if (res.ec != std::errc()) {
            return false;
        }
        
        if (res.ptr != last) {
            return false;
        }
        
        return true;
    }


    //AI SLOP
    inline std::string_view rtrim(std::string_view s) {
        while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r')) {
            s.remove_suffix(1);
        }
        return s;
    }

    inline std::string_view ltrim(std::string_view s) {
        while (!s.empty() && (s.front() == ' ' || s.front() == '\t')) {
            s.remove_prefix(1);
        }
        return s;
    }

    inline std::string_view trim(std::string_view s) { return rtrim(ltrim(s)); }



    inline std::vector<std::string_view> tokenize_sv(std::string_view line, size_t max_tokens){
        std::vector<std::string_view> arr;
        size_t index = 0;
        size_t start = 0;
        while (index < max_tokens) {
            while (start < line.size() && line[start] == ' ') start++;
            if (start >= line.size()) break;

            size_t end = line.find(" ", start);
            if (end == std::string_view::npos) end = line.size();

            arr.push_back(line.substr(start, end - start));
            ++index;
            start = end;
        }
        return arr;
    }

    inline std::string_view trim_trailing_comm(std::string_view s){
        if (s.empty()) return s;

        size_t pos = s.find("--");
        if (pos == std::string_view::npos) return s;

        return s.substr(0, pos);


    }
}