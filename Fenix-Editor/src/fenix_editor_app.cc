#include <fenix/fenix.hh>
#include <fenix/core/entry_point.hh>

#include "editor_layer.hh"

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
