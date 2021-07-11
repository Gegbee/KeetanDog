extends Control


func _input(event):
	if Input.is_action_pressed("space"):
		$leftAudio.play()
		$rightAudio.play()
	elif Input.is_action_pressed("a"):
		$leftAudio.play()
		$rightAudio.stop()
	elif Input.is_action_pressed("d"):
		$rightAudio.play()
		$leftAudio.stop()
	else:
		$rightAudio.stop()
		$leftAudio.stop()
