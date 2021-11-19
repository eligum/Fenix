import os

class ProjectSetup:
    fenixVersion = "0.1.0"

    @classmethod
    def check_vulkan_SDK(self):
        vulkanSDK = os.environ.get("VULKAN_SDK")
        if (vulkanSDK is None):
            print("You don't have the Vulkan SDK installed!")
            return False
        else:
            print(f"Located Vulkan SDK at {vulkanSDK}")

    @classmethod
    def print_version(self):
        print("Fenix Engine version:", self.fenixVersion)

if __name__ == "__main__":
    ProjectSetup.print_version()
    ProjectSetup.check_vulkan_SDK()
