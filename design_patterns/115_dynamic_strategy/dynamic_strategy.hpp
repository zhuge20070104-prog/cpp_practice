#ifndef _FREDRIC_DYNAMIC_STRATEGY_HPP_
#define _FREDRIC_DYNAMIC_STRATEGY_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>

enum class OutputFormat {
    Markdown,
    Html
};

struct ListStrategy {
    virtual ~ListStrategy() = default;
    virtual void add_list_item(std::stringstream& oss, std::string const& item) {}
    virtual void start(std::stringstream& oss) {}
    virtual void end(std::stringstream& oss) {}
};

struct MarkdownListStrategy: public ListStrategy {
    void add_list_item(std::stringstream& oss, std::string const& item) override {
        oss << " * " << item << "\n";
    }
};

struct HtmlListStrategy: public ListStrategy {
    void add_list_item(std::stringstream& oss, std::string const& item) override {
        oss << "<li>" << item << "</li>" << std::endl;
    }

    void start(std::stringstream& oss) override {
        oss << "<ul>" << std::endl;
    }

    virtual void end(std::stringstream& oss) override {
        oss << "</ul>" << std::endl;
    }
};

struct TextProcessor {
    void clear() {
        oss.str("");
        oss.clear();
    }

    void append_list(std::vector<std::string> const& items) {
        list_strategy->start(oss);
        for(auto&& item: items) {
            list_strategy->add_list_item(oss, item);
        }
        list_strategy->end(oss);
    }

    void set_output_format(OutputFormat const format) {
        switch(format) {
            case OutputFormat::Markdown:
                list_strategy = std::make_unique<MarkdownListStrategy>();
                break;
            case OutputFormat::Html:
                list_strategy = std::make_unique<HtmlListStrategy>();
                break;
            default:
                throw std::runtime_error("Unsupported strategy.");
                break;
        }
    }

    std::string str() const {
        return oss.str();
    }
private:
    std::stringstream oss;
    std::unique_ptr<ListStrategy> list_strategy;    
};


#endif