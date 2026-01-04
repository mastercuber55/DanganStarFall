extends Node2D

@export var asteroidScene: PackedScene
@export var asteroidsCount := 200

@onready var screenSize = get_viewport_rect().size

func _spawn_asteroid():
	var newAsteroid := asteroidScene.instantiate()
		
	newAsteroid.position = Vector2(
		randf_range(0, screenSize.x),
		randf_range(0, screenSize.y)
	)	
	
	var s = randf_range(0.5, 2.0)
	
	for child in newAsteroid.get_children():	
		child.scale = Vector2(s, s)
	
	add_child(newAsteroid)

func _ready() -> void:
	$Timer.start()

func _on_timer_timeout() -> void:
	$Timer.wait_time = randf_range(0.5, 2.0)
	_spawn_asteroid()
