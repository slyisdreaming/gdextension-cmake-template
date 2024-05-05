#pragma once

#include "helpers.hpp"

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class ExampleNode : public Sprite2D {
	GDCLASS(ExampleNode, Sprite2D)

public:
	DECLARE_PROPERTY(float, amplitude, 50)
	DECLARE_PROPERTY(float, speed, 1)

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;

protected:
	static void _bind_methods();

private:
	Vector2 start_position;
	float time_passed = 0;
	float time_emit = 0;
};

}
