#include <Fenix/Fenix.hh>
#include <Fenix/Core/EntryPoint.hh>

#include "EditorLayer.hh"

namespace Fenix {

    class FenixEditor : public Application
    {
    public:
        FenixEditor()
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

} // namespace Fenix
