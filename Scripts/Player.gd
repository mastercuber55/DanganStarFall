extends RigidBody2D

const THRUST := 300.0
const RECOIL := -50 

const cooldownMS := 250
var nextTime := 0.0

func _ready() -> void:
	get_node("HealthComponent").health_changed.connect(update_progress_bar)
	update_progress_bar()

func _integrate_forces(state: PhysicsDirectBodyState2D) -> void:
	
	look_at(get_global_mouse_position())
	
	if Input.is_action_pressed("Thrust"):
		$Tail.visible = true
		state.apply_central_force(transform.x * THRUST)
	else:
		$Tail.visible = false
		
	if Input.is_action_pressed("Shoot"):
		var currentTime = Time.get_ticks_msec()
		
		if currentTime >= nextTime:
			%Bullets.shootBullet(self)
			state.apply_central_impulse(transform.x * RECOIL)
			nextTime = currentTime + cooldownMS
		
func update_progress_bar() -> void:
	$"../User Interface/Health Label".text = "HP: " + str($HealthComponent.health)
