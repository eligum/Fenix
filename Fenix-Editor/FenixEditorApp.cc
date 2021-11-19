#include <Fenix/Fenix.hh>
#include <Fenix/Core/EntryPoint.hh>

#include "EditorLayer.hh"

namespace fenix {

    class FenixEditor : public Application
    {
    public:
        FenixEditor()
            : Application("FENIX::Editor")
        {
            PushLayer(new EditorLayer());
        }

        ~FenixEditor()
        {
        }
    };

    Application* CreateApplication()
    {
        return new FenixEditor;
    }

} // namespace fenix
