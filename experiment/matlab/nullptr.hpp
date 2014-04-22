#ifndef AURA_NULLPTR_HPP
#define AURA_NULLPTR_HPP


namespace std
{
    //based on SC22/WG21/N2431 = J16/07-0301
    struct nullptr_t
    {
        template<typename any> operator any * () const
    {
        return 0;
    }
    template<class any, typename T> operator T any:: * () const
    {
        return 0;
    }

#ifdef _MSC_VER
    struct pad {};
    pad __[sizeof(void*)/sizeof(pad)];
#else
    char __[sizeof(void*)];
#endif
private:
    //  nullptr_t();// {}
    //  nullptr_t(const nullptr_t&);
    //  void operator = (const nullptr_t&);
    void operator &() const;
    template<typename any> void operator +(any) const
    {
        /*I Love MSVC 2005!*/
    }
    template<typename any> void operator -(any) const
    {
        /*I Love MSVC 2005!*/
    }
    };
static const nullptr_t __nullptr = {};
}

#ifndef nullptr
#define nullptr std::__nullptr
#endif

#endif // AURA_NULLPTR_HPP

