extends RigidBody2D


const THRUST := 300.0
const BULLET_IMPULSE := 400 

@onready var bulletsContainer := $"../Bullets"
@export var bulletScene: PackedScene

func _integrate_forces(state: PhysicsDirectBodyState2D) -> void:
	
	look_at(get_global_mouse_position())
	
	if Input.is_action_pressed("Thrust"):
		$Tail.visible = true
		state.apply_central_force(transform.x * THRUST)
	else:
		$Tail.visible = false
		
	if Input.is_action_just_pressed("Shoot"):
		var bullet := bulletScene.instantiate()
		bullet.global_position = $BulletSpawn.global_position
		bulletsContainer.add_child(bullet)
		bullet.apply_central_impulse(transform.x * BULLET_IMPULSE)
		state.apply_central_impulse(transform.x * -BULLET_IMPULSE/4)
