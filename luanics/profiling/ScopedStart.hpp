#pragma once

namespace luanics::profiling {

template <typename NodeManagerT>
class ScopedStart {
public:
	ScopedStart(NodeManagerT * manager) : _manager{manager} {
		_manager->current()->start();
	}

	~ScopedStart() {
		_manager->current()->stop();
	}

private:
	NodeManagerT * _manager;
}; // class ScopedStart

} // namespace luanics::profiling
