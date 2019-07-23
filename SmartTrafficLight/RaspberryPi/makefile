MY_VAR := $(shell hostname)
HOST := 192.168.0.34
TOPIC := stl/message
LOG_PATH := ./flags.txt

set_cam0:
	guvcview -d /dev/video0 img0.jpg

set_cam2:
	guvcview -d /dev/video2 img2.jpg
	
setup:
	echo "FLAGS LOG" > $(LOG_PATH)
	make -j 2  set_cam0 set_cam2

listen:
	mosquitto_sub -h $(HOST) -t "$(TOPIC)" >> $(LOG_PATH) &

exec:
	python3 ./source/main.py
	
run: setup listen exec
