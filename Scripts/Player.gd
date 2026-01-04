extends RigidBody2D


const THRUST = 300.0
const JUMP_VELOCITY = -400.0


func _integrate_forces(state: PhysicsDirectBodyState2D) -> void:
	
	look_at(get_global_mouse_position())
	
	if Input.is_action_pressed(("Thrust")):
		state.apply_central_force(transform.x * THRUST)
