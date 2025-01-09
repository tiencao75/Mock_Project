#ifndef CONTROLLER_BASE_HPP
#define CONTROLLER_BASE_HPP

class ControllerBase {
public:
    virtual void initialize() = 0; // Phương thức ảo thuần túy
    virtual ~ControllerBase() = default;
};

#endif // CONTROLLER_BASE_HPP
