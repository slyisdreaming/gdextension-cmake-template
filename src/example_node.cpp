#include "example_node.hpp"

#include "helpers.hpp"

#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/window.hpp>

namespace {
	const char PRINT_CATEGORY[] = "ExampleNode";
}

// Check that property has been modified and that node is ready.
#define PROPERTY_GUARD(property_name)					\
	if (property_name == p_##property_name)				\
		return;											\
	if (!is_node_ready()) {								\
		property_name = p_##property_name;				\
		return;											\
	}

// Check that can modify editor.
#define EDITOR_GUARD(property_name)						\
	if (is_editor()) {									\
		property_name = p_##property_name;				\
		return;											\
	}

namespace godot {

void ExampleNode::_bind_methods() {	
	BIND_PROPERTY_WITH_SIGNAL(ExampleNode, Variant::FLOAT, amplitude);
	BIND_PROPERTY_WITH_HINT(ExampleNode, Variant::FLOAT, speed, PROPERTY_HINT_RANGE, "0, 20, 0.01");

	ADD_SIGNAL(MethodInfo("position_changed", PropertyInfo(Variant::OBJECT, "node"), PropertyInfo(Variant::VECTOR2, "new_position")));
}

void ExampleNode::_ready() {
	start_position = get_position();
}

void ExampleNode::_process(double delta) {
	if (is_editor())
		return;

	time_passed += speed * delta;

	start_position = get_window()->get_size();
	start_position *= 0.5f;

	Vector2 new_position = start_position + Vector2(
		amplitude * sin(time_passed * 2.0),
		amplitude * cos(time_passed * 1.5)
	);

	set_position(new_position);

	time_emit += delta;
	if (time_emit > 1.0) {
		emit_signal("position_changed", this, new_position);
		time_emit = 0.0;
	}
}

#pragma region PROPERTIES

DEFINE_PROPERTY_GET(ExampleNode, float, amplitude)
DEFINE_PROPERTY_GET(ExampleNode, float, speed)
DEFINE_PROPERTY_SET(ExampleNode, float, speed)

void ExampleNode::set_amplitude(const float p_amplitude) {
	PROPERTY_GUARD(amplitude);
		
	if (is_editor()) {
		amplitude = p_amplitude;
		return;
	}

	amplitude = p_amplitude;

	EMIT_SIGNAL_PROPERTY_CHANGED(amplitude);
}

#pragma endregion

}
