#ifndef _FREDRIC_MACHINE_HPP_
#define _FREDRIC_MACHINE_HPP_

#include <string>
#include <iostream>
#include <memory>

struct Document {
    std::string text;
};

struct IPrinter {
    virtual void print(Document const& doc) = 0;
};

struct IScanner {
    virtual void scan(Document const& doc) = 0;
};

struct IFax {
    virtual void fax(Document const& doc) = 0;
};

struct Printer {
    std::unique_ptr<IPrinter> p_printer;
    Printer(std::unique_ptr<IPrinter> printer_): p_printer(std::move(printer_)) {
    }

    void print(Document const& doc) {
        p_printer->print(doc);
    }
};

struct Machine {
    std::unique_ptr<IPrinter> p_printer;
    std::unique_ptr<IScanner> p_scanner;

    Machine(std::unique_ptr<IPrinter> printer_, std::unique_ptr<IScanner> scanner_): p_printer(std::move(printer_)), p_scanner(std::move(scanner_)){}
   
    void print(Document const& doc) {
        p_printer->print(doc);
    }

    void scan(Document const& doc) {
        p_scanner->scan(doc);
    }
};

struct PrinterImpl: public IPrinter {
    void print(Document const& doc) override {
        std::cout << "PrintImpl print: " << doc.text << "\n";
    }
};

struct ScannerImpl: public IScanner {
    void scan(Document const& doc) override {
        std::cout << "ScannerImpl scan: " << doc.text << "\n";
    }
};
#endif