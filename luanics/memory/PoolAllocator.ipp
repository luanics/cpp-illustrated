#include "luanics/logging/Contract.hpp"
#include "luanics/memory/PoolAllocator.hpp"

namespace luanics::memory {

template <typename T, std::size_t BlockSizeV>
PoolAllocator<T, BlockSizeV>::PoolAllocator() :
	_current_block{nullptr},
	_current_slot{},
	_free_list_head{nullptr}
{}

template <typename T, std::size_t BlockSizeV>
PoolAllocator<T, BlockSizeV>::PoolAllocator(PoolAllocator && other) :
	PoolAllocator{}
{
	swap(other);
}

template <typename T, std::size_t BlockSizeV>
PoolAllocator<T, BlockSizeV>::PoolAllocator(PoolAllocator const & other) :
	PoolAllocator{}
{}

template <typename T, std::size_t BlockSizeV>
template <typename U>
PoolAllocator<T, BlockSizeV>::PoolAllocator(PoolAllocator<U> const & other) :
	PoolAllocator{}
{}

template <typename T, std::size_t BlockSizeV>
PoolAllocator<T, BlockSizeV> & PoolAllocator<T, BlockSizeV>::operator=(PoolAllocator && other) {
	if (this != &other) {
		swap(other);
	}
	return this;
}

template <typename T, std::size_t BlockSizeV>
PoolAllocator<T, BlockSizeV>::~PoolAllocator() {
	while (_current_block != nullptr) {
		Block * previous_block = _current_block->prev;
		delete _current_block;
		_current_block = previous_block;
	}
}

template <typename T, std::size_t BlockSizeV>
T * PoolAllocator<T, BlockSizeV>::allocate(std::size_t n) {
	ENSURES(n == 1, n);
	bool const have_space_in_free_list = _free_list_head != nullptr;
	if (have_space_in_free_list) {
		T * result = reinterpret_cast<T*>(_free_list_head);
		_free_list_head = _free_list_head->next;
		return result;
	}
	else {
		bool const have_space_in_current_block =
			_current_block
			and _current_slot != _current_block->data.end();
		if (not have_space_in_current_block) {
			allocate_block();
		}
		return reinterpret_cast<T*>(&(*_current_slot++));
	}
}

template <typename T, std::size_t BlockSizeV>
void PoolAllocator<T, BlockSizeV>::deallocate(T * p, std::size_t n) {
	ENSURES(n == 1, n);
	Slot * freed = reinterpret_cast<Slot *>(p);
	freed->next = _free_list_head;
	_free_list_head = freed;
}


//template <typename T, std::size_t BlockSizeV>
//template <typename U, typename ... ArgsT>
//void PoolAllocator<T, BlockSizeV>::construct(U * p, ArgsT && ... args) {
//	new (p) U{std::forward<ArgsT>(args)...};
//}
//
//template <typename T, std::size_t BlockSizeV>
//template <typename U>
//void PoolAllocator<T, BlockSizeV>::destroy(U * p) {
//	p->~U();
//}

template <typename T, std::size_t BlockSizeV>
void PoolAllocator<T, BlockSizeV>::swap(PoolAllocator & other) {
	std::swap(_current_block, other._current_block);
	std::swap(_current_slot, other._current_slot);
	std::swap(_free_list_head, other._free_list_head);
}

template <typename T, std::size_t BlockSizeV>
void PoolAllocator<T, BlockSizeV>::allocate_block() {
	Block * new_block = reinterpret_cast<Block *>(operator new(sizeof(Block)));
	new_block->prev = _current_block;
	_current_block = new_block;
	_current_slot = _current_block->data.begin();
}

} // namespace luanics::memory
