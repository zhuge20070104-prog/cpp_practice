#include "stopwatch11.h"
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

// 获取当前流的大小， return -1 on fail
std::streamoff stream_size(std::istream& f) {
    std::istream::pos_type current_pos = f.tellg();
    if(-1 == current_pos) {
        return -1;
    }
    f.seekg(0, std::istream::end);
    std::istream::pos_type end_pos = f.tellg();
    f.seekg(current_pos);
    return end_pos - current_pos;
}

// 直接使用std::stringstream 读取f.rdbuf
void stream_read_streambuf(std::istream& f, std::string& result) {
    std::stringstream s;
    s << f.rdbuf();
    std::string str(s.str());
    std::swap(result, str);
}

// 使用streambuf_iterator读取，返回string
std::string stream_read_streambuf_stringstream_noarg(std::istream& f) {
    std::stringstream s;
    std::copy(std::istreambuf_iterator<char>(f.rdbuf()),
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(s));
    return s.str();
}

// 使用streambuf_iterator读取，参数返回
void stream_read_streambuf_stringstream(std::istream& f, std::string& result) {
    std::stringstream s;
    std::copy(std::istreambuf_iterator<char>(f.rdbuf()),
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(s));
    std::string str(s.str());
    std::swap(result, str);
}

// 使用streambuf_iterator读取，直接assign给string
void stream_read_streambuf_string(std::istream& f, std::string& result) {
    result.assign(
        std::istreambuf_iterator<char>(f.rdbuf()),
        std::istreambuf_iterator<char>()
    );
}

// 先获取长度，分配缓存，再用std::string::assign
void stream_read_streambuf_string_reserve(std::istream& f, std::string& result) {
    f.seekg(0, std::istream::end);
    std::streamoff len = f.tellg();
    f.seekg(0);

    if(len > 0) {
        result.reserve(static_cast<std::string::size_type>(len));
    }
    result.assign(
        std::istreambuf_iterator<char>(f.rdbuf()),
        std::istreambuf_iterator<char>()
    );
}

// 传一个缓冲区长度进来
void stream_read_streambuf_string_2(std::istream& f, std::string& result, std::streamoff len = 0) {
    if(len > 0) {
        result.reserve(static_cast<std::string::size_type>(len));
    }

    result.assign(
        std::istreambuf_iterator<char>(f.rdbuf()),
        std::istreambuf_iterator<char>()
    );
} 


// 逐行读取
void stream_read_getline(std::istream& f, std::string& result) {
    std::string line;
    result.clear();

    while(std::getline(f, line)) {
        (result += line) += "\n";
    }
}

// 逐行读取，预先分配缓冲区
void stream_read_getline_2(std::istream& f, std::string& result, std::streamoff len = 0) {
    std::string line;
    result.clear();

    if(len > 0) {
        result.reserve(static_cast<std::string::size_type>(len));
    }
    
    while(std::getline(f, line)) {
        (result += line) += "\n";
    }
}

// 1. 先获取长度，并分配缓冲区，
// 2. 再用buf::sgetn 获取
bool stream_read_sgetn(std::istream& f, std::string& result) {
    std::streamoff len = stream_size(f);
    if(len == -1) {
        return false;
    }

    result.resize(static_cast<std::string::size_type>(len));
    f.rdbuf()->sgetn(&result[0], len);
    return true;
}

// 1.堆上分配char数组
// 2.f.read读取到char
// 3.result.assign设置到string返回
bool stream_read_array(std::istream& f, std::string& result) {
    std::streamoff len = stream_size(f);
    if(len == -1) {
        return false;
    }
    
    std::unique_ptr<char> data(new char[static_cast<std::size_t>(len)]);
    f.read(data.get(), static_cast<std::streamsize>(len));
    result.assign(data.get(), static_cast<std::string::size_type>(len)); 
    return true;
}

// 使用std::string 先resize, 再f.read
bool stream_read_string(std::istream& f, std::string& result) {
    std::streamoff len = stream_size(f);
    if(len == -1) {
        return false;
    }

    result.resize(static_cast<std::string::size_type>(len));
    f.read(&result[0], result.length());
    return true;
}


// 使用自定义buf读取，很慢
class custombuf: public std::streambuf {
public:
    custombuf(std::string& target): target_(target) {
        this->setp(this->buffer_, this->buffer_ + bufsize -1);
    }
private:
    std::string& target_;
    enum {bufsize = 8192};
    // 缓冲区的长度是 8192
    char buffer_[bufsize];
    int overflow(int c) {
        // 每次读一个字节
		// 直到读到超越缓冲区，8192，或者读到EOF，没有东西
        if(!traits_type::eq_int_type(c, traits_type::eof())) {
            *this->pptr() = traits_type::to_char_type(c);
            this->pbump(1);
        }
        // 把8192 append上去，重置指针
        this->target_.append(this->pbase(), this->pptr() - this->pbase());
        this->setp(this->buffer_, this->buffer_ + bufsize - 1);
        return traits_type::not_eof(c);
    }

    int sync() {
        this->overflow(traits_type::eof());
        return 0;
    }
};


std::string stream_read_custombuf(std::istream& f) {
    std::string data;
    custombuf sbuf(data);
    std::ostream(&sbuf) << f.rdbuf() << std::flush;
    return data;
}


void file_writer(std::ostream& f, int nlines) {
    std::string line;
    for(int i=0; i<20; ++i) {
        line += "blah ";
    }

    line += "\n";

    for(int i=0; i<nlines; ++i) {
        f << line;
    }
    f.flush();
}


void stream_write_line(std::ostream& f, std::string const& line) {
    f << line << std::endl;
}

void stream_write_line_noflush(std::ostream& f, std::string const& line) {
    f << line << "\n";
}

int test_read_stream(int test_no, unsigned long multiplier) {
    bool rc = true;
    char const filename[] = "file_optimization_tester.txt";
    unsigned long const iterations = multiplier;
    std::string s;

    std::ofstream out(filename);
    if(!out) {
        std::cout << "Can't open " << filename << " for writting" << std::endl;
        return 0;
    }

    // 写了10000 行，一行是101个字符
    unsigned nlines = (test_no > 1) ? 10000: 10;
    std::size_t flen = 101 * nlines;

    file_writer(out, nlines);
    out.close();

    std::ifstream in;
    in.open(filename);

    if(!in) {
        std::cout << "Can't open " << filename << " for reading" << std::endl;
        return 0;
    }

    std::ifstream in8k;
    in8k.open(filename);
    if(!in8k) {
        std::cout << "Can't open " << filename 
            << " buffered stream for reading" << std::endl;
        return 0;
    }

    // 设置流有1个buffer，buffer大小为 8k
    // 默认是一下读完
    char buf[8192];
    in8k.rdbuf()->pubsetbuf(buf, sizeof(buf));

    switch(test_no) {
        case 0: return 7;
        default: return -1;
        case 1: {
            {
                s = stream_read_streambuf_stringstream_noarg(in);
                in.clear(); in.seekg(0);
                rc &= (s.length() == flen);

                stream_read_streambuf_stringstream(in, s);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                stream_read_streambuf_string(in, s);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                stream_read_streambuf_string_reserve(in, s);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                stream_read_streambuf_string_2(in, s);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                stream_read_streambuf(in, s);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                //  这里函数内部没用buffer，但是传递了一个带buffer的流进去，就buffer了
                stream_read_streambuf(in8k, s);
                in8k.clear(); in8k.seekg(0); 
                rc &= (s.length() == flen);
                
                stream_read_streambuf(in8k, s);

                stream_read_getline(in, s);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                stream_read_getline_2(in, s, 100);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                // 加nlines这些个应该是多了一个换行符，待会debug 看一下
                stream_read_sgetn(in, s);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                stream_read_array(in, s);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                stream_read_string(in, s);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);

                // end nlines

                s = stream_read_custombuf(in);
                in.clear();	in.seekg(0); 
                rc &= (s.length() == flen);
            }

            {//	verify behavior of stream_size()
                std::ifstream f;
                std::streamsize len1 = stream_size(f);
                rc &= (len1 == -1);
                f.open(filename);
                std::streamsize len2 = stream_size(f);
                rc &= (len2 > 100);
                std::getline(f, s);
                std::streamsize len3 = stream_size(f);
                rc &= (len2 > len3);

                // 这里用stringstring包了一下s，然后测量长度，应该等于s.length
                std::stringstream ins;
                ins.str(s);
                std::streamsize len4 = stream_size(ins);
                rc &= (len4 == s.length());
            }
        }
            break;
        
        case 2: {
            {
                StopWatch sw("stream_read_streambuf_stringstream_noarg()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    s = stream_read_streambuf_stringstream_noarg(in);
                    in.clear();	in.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
            {
                StopWatch sw("stream_read_streambuf_stringstream()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_streambuf_stringstream(in, s);
                    in.clear();	in.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
            {
                StopWatch sw("stream_read_streambuf_string()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_streambuf_string(in, s);
                    in.clear();	in.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
            {
                StopWatch sw("stream_read_streambuf_string_reserve()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_streambuf_string_reserve(in, s);
                    in.clear();	in.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
            {
                StopWatch sw("stream_read_streambuf_string_2()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_streambuf_string_2(in, s, stream_size(in));
                    in.clear();	in.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
            {
                StopWatch sw("stream_read_streambuf_string_2(in8k)");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_streambuf_string_2(in8k, s, stream_size(in8k));
                    in8k.clear(); in8k.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
            {
                StopWatch sw("stream_read_streambuf()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_streambuf(in, s);
                    in.clear();	in.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
            {
                StopWatch sw("stream_read_streambuf(8k buffer)");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_streambuf(in8k, s);
                    in8k.clear(); in8k.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
    
        }
            break;

        case 3: {
            {
                StopWatch sw("stream_read_getline()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_getline(in, s);
                    in.clear();	in.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
            {
                StopWatch sw("stream_read_getline_2()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_getline_2(in, s, stream_size(in));
                    in.clear();	in.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
            {	
                // TODO: 明天debug 看下stream_size(in8k是多大)， 应该是 8k吧
                StopWatch sw("stream_read_getline_2(in8k)");
                for (unsigned long i = 0; i < iterations; ++i) {
                    stream_read_getline_2(in8k, s, stream_size(in8k));
                    in8k.clear(); in8k.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
        }
            break;
        
        case 4: {
            {
                StopWatch sw("stream_read_sgetn()");
                bool err = true;
                for (unsigned long i = 0; i < iterations; ++i) {
                    err &= stream_read_sgetn(in, s);
                    in.clear();	in.seekg(0); 
                }
                rc &= (err == true && s.length() == flen);
            }
            {
                StopWatch sw("stream_read_sgetn(in8k)");
                bool err = true;
                for (unsigned long i = 0; i < iterations; ++i) {
                    err &= stream_read_sgetn(in8k, s);
                    in8k.clear(); in8k.seekg(0); 
                }
                rc &= (err == true && s.length() == flen);
            }
        }
            break;

        case 5: {
            {
                StopWatch sw("stream_read_array()");
                bool err = true;
                for (unsigned long i = 0; i < iterations; ++i) {
                    err &= stream_read_array(in, s);
                    in.clear();	in.seekg(0); 
                }
                rc &= (err == true && s.length() == flen);
            }
            {
                StopWatch sw("stream_read_string()");
                bool err = true;
                for (unsigned long i = 0; i < iterations; ++i) {
                    err &= stream_read_string(in, s);
                    in.clear();	in.seekg(0); 
                }
                rc &= (err == true && s.length() == flen);
            }
            {
                StopWatch sw("stream_read_string(in8k)");
                bool err = true;
                for (unsigned long i = 0; i < iterations; ++i) {
                    err &= stream_read_string(in8k, s);
                    in8k.clear(); in8k.seekg(0); 
                }
                rc &= (err == true && s.length() == flen);
            }
        }
            break;
        
        case 6: {
            {
                StopWatch sw("stream_read_custombuf()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    s = stream_read_custombuf(in);
                    in.clear(); in.seekg(0); 
                }
                rc &= (s.length() == flen);
            }
        }
            break;

        case 7: {
            std::remove(filename);
            out.open(filename);
            {
                std::string line;
                for (unsigned i = 0; i < 20; ++i)
                    line += "blah ";
                StopWatch sw("stream_write_line()");
                // 带flush的写会比较慢
                for (unsigned long i = 0; i < iterations; ++i) {
                    out.seekp(0);
                    for (unsigned j = 0; j < nlines; ++j) {
                        stream_write_line(out, line);
                    }
                }
            }
            out.close();
            std::remove(filename);
            // no flush，最后flush一次的会快一点
            out.open(filename);
            {
                std::string line;
                for (unsigned i = 0; i < 20; ++i)
                    line += "blah ";
                StopWatch sw("stream_write_line_noflush()");
                for (unsigned long i = 0; i < iterations; ++i) {
                    out.seekp(0);
                    for (unsigned j = 0; j < nlines; ++j) {
                        stream_write_line_noflush(out, line);
                    }
                    out.flush();
                }
            }
            out.close();

            // 写整个文件，写大string，不flush，这个会更快
            std::remove(filename);
            out.open(filename);
            {
                std::string line;
                for (unsigned i = 0; i < 20; ++i)
                    line += "blah ";
                std::string file;
                for (unsigned j = 0; j < nlines; ++j) 
                    file += line;

                StopWatch sw("stream_write_line_noflush(file)");
                for (unsigned long i = 0; i < iterations; ++i) {
                    out.seekp(0);
                    stream_write_line_noflush(out, file);
                    out.flush();
                }
            }
            out.close();
        }
            break;
    }

    std::remove(filename);
    return (rc) ? 1: 0;
}