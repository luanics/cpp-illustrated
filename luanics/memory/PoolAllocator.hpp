#pragma once

#include <array>
#include <cstdint>

namespace luanics::memory {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class PoolAllocator
///
/// @brief Stateful allocator that uses memory pool
///
/// @note Works only with containers that do single-item allocation,
///   i.e., std::list but not std::vector.
///
/// @see https://github.com/cacay/MemoryPool/blob/master/C-11/MemoryPool.h
///
/// | | | | | = block of n=5 slots
///
/// |*| = active slot
/// | | = inactive slot
///
/// |*|*| | | |      |*|*|*|*|*|
///
/// @tparam T is the element type.
/// @tparam BlockSizeV is the number of elements per block.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t BlockSizeV = 1024>
struct PoolAllocator {

	using size_type = std::size_t;
	using value_type = T;
//	using pointer = T*;
//	using const_pointer = T const *;
//	using reference = T&;
//	using const_reference = T const &;

	using propagate_on_container_copy_assignment = std::false_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;

	PoolAllocator();
	template <typename U>
	PoolAllocator(PoolAllocator<U> const & other);
	PoolAllocator(PoolAllocator const & other);
	PoolAllocator & operator=(PoolAllocator const & other) = delete;
	PoolAllocator(PoolAllocator && other);
	PoolAllocator & operator=(PoolAllocator && other);
	~PoolAllocator();

	/// @pre n == 1
	T * allocate(std::size_t n);
	/// @pre n == 1
	void deallocate(T * p, std::size_t n);

//	template <typename U>
//	void destroy(U * p);
//	template <typename U, typename ... ArgsT>
//	void construct(U * p, ArgsT && ... args);

	constexpr size_type max_size() const {return 1;}

	// Misfit type metafunction uses "other" instead of "type"
	template <typename U> struct rebind {
		using other = PoolAllocator<U, BlockSizeV>;
	};

private:
	void swap(PoolAllocator & other);
	void allocate_block();

	union Slot {
		Slot * next;
		T element;
	};

	using block_array_type = std::array<Slot, BlockSizeV>;
	struct Block {
		Block * prev;
		block_array_type data;
	};

	Block * _current_block;
	typename block_array_type::iterator _current_slot;
	Slot * _free_list_head;
};

template <typename T1, std::size_t V1, typename T2, std::size_t V2>
bool operator==(PoolAllocator<T1, V1> const &, PoolAllocator<T2, V2> const &) {
	// Storage allocated via one can never be deallocated via the other
	return false;
}

template <typename T1, std::size_t V1, typename T2, std::size_t V2>
bool operator!=(PoolAllocator<T1, V1> const &, PoolAllocator<T2, V2> const &) {
	return true;
}

} // namespace luanics::memory

#include "luanics/memory/PoolAllocator.ipp"
