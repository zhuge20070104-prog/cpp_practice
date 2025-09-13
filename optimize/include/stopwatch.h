#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <iostream>

template <class T>
class basic_stopwatch: public T {
public:
    using BaseTimer = T;
    using tick_t = typename T::tick_t;

    // 创建可选的，开始对一个行为计时
    explicit basic_stopwatch(bool start);
    explicit basic_stopwatch(char const* activity="Stopwatch",  
        bool start=true);

    basic_stopwatch(std::ostream& log,
                    char const* activtity="Stopwatch",
                    bool start=true);
    
    ~basic_stopwatch();

    // 获取上次stop以后lap的时间
    tick_t LapGet() const;

    bool IsStarted() const;

    tick_t Show(char const* event="show");

    tick_t Start(char const* event_name="start");

    tick_t Stop(char const* event_name="stop");

private:
    char const* m_activity;
    tick_t m_lap;
    std::ostream& m_log;
};

template <class T>
inline basic_stopwatch<T>::basic_stopwatch(bool start_now):
    m_activity("StopWatch"),
    m_lap(0),
    m_log(std::cout) {
        if(start_now) {
            Start();
        }
    }

template <class T>
inline basic_stopwatch<T>::basic_stopwatch(char const* activity,  
        bool start):
        m_activity(activity&&activity[0]? activity: nullptr),
        m_lap(0),
        m_log(std::cout) {
            if(start) {
                if(m_activity) {
                    Start();
                }else {
                    // 没有activity，连事件名都没有
                    Start(nullptr);
                }
            }
        }


template <typename T>
inline basic_stopwatch<T>::basic_stopwatch(std::ostream& log,
                    char const* activtity,
                    bool start):
                    m_activity(activtity&&activtity[0]? activtity: nullptr),
                    m_lap(0),
                    m_log(log) {
                        if(start) {
                            Start();
                        } else {
                            Start(nullptr);
                        }
                    }



template <class T>
inline basic_stopwatch<T>::~basic_stopwatch() {
    if(IsStarted()) {
        if(m_activity) {
            Stop();
        } else {
            Stop(nullptr);
        }
    }
}


template <class T>
inline bool basic_stopwatch<T>::IsStarted() const {
    return BaseTimer::IsStarted();
}


template <class T>
inline typename basic_stopwatch<T>::tick_t basic_stopwatch<T>::LapGet() const {
    return m_lap;
}

template <class T>
inline typename basic_stopwatch<T>::tick_t basic_stopwatch<T>::Show(char const* event_name) {
    if(IsStarted()) {
        m_lap = BaseTimer::GetMs();
        if(event_name && event_name[0]) {
            if(m_activity) {
                m_log << m_activity << ": ";
            }

            m_log << event_name << " at " << m_lap << " mS" << std::endl << std::flush;  
        }
    }else {
        if(m_activity) {
            m_log << m_activity << ": not started" << std::endl << std::flush;
        }
    }
    return m_lap;
}


template <class T>
inline typename basic_stopwatch<T>::tick_t basic_stopwatch<T>::Start(char const* event_name) {
    if(IsStarted()) {
        Stop(event_name);
    } else {
        if(event_name && event_name[0]) {
            if(m_activity) {
                m_log << m_activity << ": ";
            }

            m_log << event_name << std::endl << std::flush;
        }
    }

    BaseTimer::Start();
    return m_lap;
}


template <class T>
inline typename basic_stopwatch<T>::tick_t basic_stopwatch<T>::Stop(char const* event_name) {
    if(IsStarted()) {
        m_lap = BaseTimer::GetMs();
        if(event_name && event_name[0]) {
            if(m_activity) {
                m_log << m_activity << ": ";
            }
            m_log << event_name << " " << m_lap << "mS" << std::endl << std::flush;
        }
    }

    BaseTimer::Clear();
    return m_lap;
}


#endif