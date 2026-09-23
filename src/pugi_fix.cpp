// Dummy fix for pugi::xml_node destructor linker error

#if defined(_WIN32) || defined(_MSC_VER) || defined(GEODE_IS_WINDOWS)
// MSVC mangling: provide symbol via asm label
extern "C" void win_pugi_dtor() asm("??1xml_node@pugi@@QEAA@XZ");
void win_pugi_dtor() {}
// Also provide alternative mangling that lld might look for
extern "C" void win_pugi_dtor2() asm("??1xml_node@pugi@@QAE@XZ");
void win_pugi_dtor2() {}
void pugi_fix_dummy_win() {}
#else
extern "C" void _ZN4pugi8xml_nodeD1Ev(void* self) {}
extern "C" void _ZN4pugi8xml_nodeD2Ev(void* self) {}
#endif
