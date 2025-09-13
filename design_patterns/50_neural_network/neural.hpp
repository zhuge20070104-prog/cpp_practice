#ifndef _FREDRIC_NEURAL_HPP_
#define _FREDRIC_NEURAL_HPP_

#include "log.h"
#include <memory>
#include <string>
#include <vector>
#include <iostream>

struct Neuron;

template <typename Self>
struct SomeNeurons {
    template <typename T>
    void connect_to(T& other) {
        for(Neuron& from: *static_cast<Self*>(this)) {
            for(Neuron& to: other) {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

struct Neuron: public SomeNeurons<Neuron> {
    std::vector<Neuron*> in, out;
    unsigned int id;

    Neuron() {
        static int id = 1;
        this->id = id++;
    }

    Neuron* begin() {
        return this;
    }

    Neuron* end() {
        return this + 1;
    }

    friend std::ostream& operator<<(std::ostream& os, Neuron const& obj) {
        for(Neuron* n: obj.in) {
             os << n->id << "\t-->\t[" << obj.id << "]" << std::endl;
        }

        for(Neuron* n: obj.out) {
            os << "[" << obj.id << "]\t-->\t" << n->id << std::endl;
        }
        return os;
    } 
};

struct NeuronLayer:  SomeNeurons<NeuronLayer> {
    using NeuronIterator = std::vector<Neuron>::iterator;
    std::vector<Neuron> neurons;
    NeuronLayer(int count) {
        while(count-- > 0) {
            neurons.emplace_back(Neuron{});
        }
    }
   
   NeuronIterator  begin() {
        return neurons.begin();
    }

    NeuronIterator end() {
        return neurons.end();
    }

    friend std::ostream& operator<<(std::ostream& os, NeuronLayer& obj) {
        for (auto const& n : obj) {
            os << n;
        }
        return os;
    }
};
#endif