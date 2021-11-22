// Platform detection using predefined macros
#ifdef _WIN32
    /* Windows x64/x86 */
<<<<<<< Updated upstream
=======
    //#error "Windows is not supported yet"
>>>>>>> Stashed changes
    #ifdef _WIN64
        /* Windows x64  */
        #define FX_PLATFORM_WINDOWS
    #else
        /* Windows x86 */
        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    /* TARGET_OS_MAC exists on all the platforms
    * so we must check all of them (in this order)
    * to ensure that we're running on MAC
    * and not some other Apple platform */
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #define FX_PLATFORM_IOS
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #define FX_PLATFORM_MACOS
        #error "MacOS is not supported!"
    #else
        #error "Unknown Apple platform!"
    #endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
    #define FX_PLATFORM_ANDROID
    #error "Android is not supported!"
#elif defined(__linux__)
    #define FX_PLATFORM_LINUX
#else
    #error "Unknown platform!"
#endif // End of platform detection
