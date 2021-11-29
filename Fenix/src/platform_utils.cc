#include "fenix/util/platform_utils.hh"
#include "fenix/core/base.hh"

#include <nfd.hpp>

#ifdef FENIX_PLATFORM_WINDOWS
#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#endif

namespace fenix {

    std::string FileDialog::OpenFile(const char* filter)
    {
        NFD::Guard nfd_guard;     // initialize NFD
        NFD::UniquePath out_path; // auto-freeing memory

        // prepare filters for the dialog
        nfdfilteritem_t filterItem[1] = { { "Fenix scene", "fenix" } };

        // show the dialog
        nfdresult_t result = NFD::OpenDialog(out_path, filterItem, 1);
        switch (result) {
            case NFD_OKAY: {
                std::string selection = out_path.get();
                FENIX_CORE_TRACE("Selected file: {0}", selection);
                return selection;
            }
            case NFD_CANCEL:
                FENIX_CORE_TRACE("User pressed cancel.");
                break;
            default:
                FENIX_CORE_ERROR("{0}", NFD::GetError());
                break;
        }

        return std::string {};
    }

    std::string FileDialog::SaveFile(const char* filter)
    {
        NFD::Guard nfd_guard;
        NFD::UniquePath out_path;

        nfdfilteritem_t filterItem[1] = { { "Fenix scene", "fenix" } };

        nfdresult_t result = NFD::SaveDialog(out_path, filterItem, 1, nullptr, "untitled_scene.fenix");
        switch (result) {
            case NFD_OKAY: {
                std::string selection = out_path.get();
                FENIX_CORE_TRACE("Saved file as {0}", selection);
                return selection;
            }
            case NFD_CANCEL:
                FENIX_CORE_TRACE("User pressed cancel.");
                break;
            default:
                FENIX_CORE_ERROR("{0}", NFD::GetError());
                break;
        }

        return std::string {};
    }

} // namespace fenix
