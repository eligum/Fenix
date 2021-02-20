#include "Firefly.hh"

class Sandbox : public flyCore::Application
{
public:
    Sandbox() {}

    ~Sandbox() {}
};

int main()
{
    Sandbox* sandbox = new Sandbox();
    sandbox->Run();
    delete sandbox;
}
