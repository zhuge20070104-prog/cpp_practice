#ifndef _FREDRIC_FARM_H_
#define _FREDRIC_FARM_H_

// forward declaration
class Dog;


class Farm {

public:
    // works if only the name is needed
    // won't work if we call member function which is in the Dog class - we need to include the header file
    void include_dog(const Dog& dog);
};

#endif