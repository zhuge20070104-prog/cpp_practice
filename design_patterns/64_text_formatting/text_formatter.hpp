#ifndef _FREDRIC_TEXT_FORMATTER_HPP_
#define _FREDRIC_TEXT_FORMATTER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class FormatterText {
    std::string plain_text;
    std::vector<bool> caps;

public:
    FormatterText(std::string const& plain_text_): plain_text(plain_text_), caps(plain_text_.size(), false) {}
    ~FormatterText() {}

    void capitalise(int start, int end) {
        for(int i=start; i<=end; ++i) {
            caps[i] = true;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, FormatterText const& fmt) {
        std::stringstream ss;
        for(int i=0; i<fmt.plain_text.size(); ++i) {
            char c = fmt.plain_text[i];
            ss << static_cast<char>(fmt.caps[i]? std::toupper(c): c);
        }
        return os << ss.str();
    }
};

class BetterFormatterText {
public:
    BetterFormatterText(std::string const& plain_text_): plain_text(plain_text_) {}

    struct TextRange {

        TextRange(int start_, int end_): start(start_), end(end_) {}
        int start, end;
        bool capitalise; // 或者bold, italic
        bool covers(int pos) const {
            return pos >= start && pos <= end;
        }
    };

    TextRange& get_range(int start, int end) {
        formatting.emplace_back(start, end);
        return *formatting.rbegin();
    }

    friend std::ostream& operator<<(std::ostream& os, BetterFormatterText const& fmt) {
        std::stringstream ss;
        for(int i=0; i<fmt.plain_text.size(); ++i) {
            char c = fmt.plain_text[i];
            // Apply ranges
            for(auto const& rng: fmt.formatting) {
                if(rng.covers(i) && rng.capitalise) {
                    c = std::toupper(c);
                    break;
                }
            }
            ss << static_cast<char>(c);
        }
        return os << ss.str();
    }
private:
    std::string plain_text;
    std::vector<TextRange> formatting;
};
#endif