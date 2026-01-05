extends RigidBody2D

const THRUST := 300.0
const RECOIL := -100 

@onready var bulletsContainer := %Bullets
@onready var progressBar := $"../CanvasLayer/Label"

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
		
	if Input.is_action_just_pressed("Shoot"):
		bulletsContainer.shootBullet(self)
		state.apply_central_impulse(transform.x * RECOIL)
		
func update_progress_bar() -> void:
	progressBar.text = "HP: " + str($HealthComponent.health)
