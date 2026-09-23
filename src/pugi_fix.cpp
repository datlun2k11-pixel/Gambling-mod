// Dummy fix for pugi::xml_node destructor linker error
// Provide symbols without including headers to avoid redefinition

#if defined(_WIN32) || defined(_MSC_VER) || defined(GEODE_IS_WINDOWS)
// MSVC mangling for pugi::xml_node::~xml_node is ??1xml_node@pugi@@QEAA@XZ
// Use inline assembly to define it without C++ redefinition
__asm__(".globl \"??1xml_node@pugi@@QEAA@XZ\"\n\"??1xml_node@pugi@@QEAA@XZ\":\n\tret\n");
void pugi_fix_dummy_win() {}
#else
// Itanium ABI (Android/macOS/iOS/Linux) - use extern C which works for these
extern "C" void _ZN4pugi8xml_nodeD1Ev(void* self) {}
extern "C" void _ZN4pugi8xml_nodeD2Ev(void* self) {}
#endif
