#ifndef _FREDRIC_CLASSIC_STATE_IMPL_HPP_
#define _FREDRIC_CLASSIC_STATE_IMPL_HPP_

#include <iostream>
#include <string>
#include <memory>

class LightSwitch;

struct State {
    // 在on的时候再on，调用默认行为
    virtual void on(LightSwitch* ls) {
        std::cout << "Light is already on\n";
    }

    // 在off的时候再off，调用默认行为
    virtual void off(LightSwitch* ls) {
        std::cout << "Light is already off\n";
    }
};

struct OnState: public State {
    OnState() {
        std::cout << "Light Turned On\n";
    }

    void off(LightSwitch* ls) override;
};

struct OffState: public State {
    OffState() {
        std::cout << "Light Turned Off\n";
    }
    void on(LightSwitch* ls) override;
};

class LightSwitch {
    std::shared_ptr<State> state;

public:
    LightSwitch() {
        state = std::make_shared<OffState>();
    }

    std::shared_ptr<State> get_state() {
        return state;
    }

    void set_state(std::shared_ptr<State> state_) {
        // set_state之前先删除原先的状态的子对象，保留父对象
        // 这样原先的状态就只能set_state 一次
        // 后面调用的就都是父对象的set_state
        // already on 或者already off
        state.reset();
        state = state_;
    }

    void on() {
        state->on(this);
    }

    void off() {
        state->off(this);
    }
};

// On状态off，不能再off, 去掉子类的off方法
// 在set_state 方法中实现
void OnState::off(LightSwitch* ls) {
    std::cout << "Switching Light off...\n";
    auto off_state = std::make_shared<OffState>();
    ls->set_state(off_state);
}

// Off状态on, 不能再 on, 会去掉子类的on方法
// 在set_state 方法中实现
void OffState::on(LightSwitch* ls) {
    std::cout << "Switch Light on...\n";
    auto on_state = std::make_shared<OnState>();
    ls->set_state(on_state);
}



#endif