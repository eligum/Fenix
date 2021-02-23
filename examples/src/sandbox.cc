#include "Firefly/Firefly.hh"

class Sandbox : public flyCore::Application
{
public:
    Sandbox() {}

    ~Sandbox() {}
};

flyCore::Application* flyCore::CreateApplication()
{
    return new Sandbox;
}
