#pragma once

namespace luanics::profiling {

template <typename NodeManagerT>
class ScopedEntrance {
public:
	using NameType = typename NodeManagerT::NameType;

	ScopedEntrance(NodeManagerT * manager, NameType nodeName) :
		_manager{manager}
	{
		_manager->enter(std::move(nodeName));
	}

	~ScopedEntrance() {
		_manager->exit();
	}

private:
	NodeManagerT * _manager;
}; // class Guard

} // namespace luanics::profiling
