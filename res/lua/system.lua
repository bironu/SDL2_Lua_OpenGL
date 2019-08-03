print("system.lua load.")

window = {
	width=1280,
	height=720,
}

screen = {
	width=1280,
	height=720,
}

system = {
	lang = "japanese",
--	lang = "english",
}

keyRepeat = {
	delay = 300,
	interval = 200,
}

keyAssing = {
	enter = 0,
	cancel = 1,
}

animation = {
	duration = 200,
	interpolator = 0,
-- 0 : AccelerateDecelerateInterpolator
-- 1 : AccelerateInterpolator
-- 2 : AnticipateInterpolator
-- 3 : AnticipateOvershootInterpolator
-- 4 : BounceInterpolator
-- 5 : CycleInterpolator
-- 6 : DecelerateInterpolator
-- 7 : LinearInterpolator
-- 8 : OvershootInterpolator
}

camera = {
	x = 0.0,
	y = 4.0,
	z = -40.0,
	translateX = 0.0,
	translateY = -10.0,
	translateZ = 0.0,
	radius = 20.0,
}
