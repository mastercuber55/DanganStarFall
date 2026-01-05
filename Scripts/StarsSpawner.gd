extends Parallax2D

@export var starScene: PackedScene
@export var starCount := 200

func _ready() -> void:
	
	var screenSize = repeat_size
	
	for i in range(starCount):
		var star = starScene.instantiate()
		
		star.position = Vector2(
			randf_range(0, screenSize.x),
			randf_range(0, screenSize.y)
		)	
		
		star.modulate = Color(randf(), randf(), randf(), randf_range(0.3, 1.0))
		
		add_child(star)
