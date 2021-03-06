#ifndef AURA_BACKEND_SHARED_MEMORY_TAG_HPP
#define AURA_BACKEND_SHARED_MEMORY_TAG_HPP

namespace boost
{
namespace aura 
{

enum class memory_tag
{
	ro,
	wo,
	rw
};

enum class memory_access
{
	seldom,
	frequent
};

} // namespace aura
} // boost

#endif // AURA_BACKEND_SHARED_MEMORY_TAG_HPP

