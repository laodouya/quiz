all:
	gcc -o detect_video_format.o -c detect_video_format.c -g
	gcc -o detect_video_format detect_video_format.o -lavdevice -lavfilter -lavformat -lavcodec -lswresample -lswscale -lavutil -lxcb -lxcb-shm -lxcb -lxcb-xfixes -lxcb-render -lxcb-shape -lxcb -lX11 -lm -lz -pthread -lrt -g

.PHONY: clean
clean:
	-rm detect_video_format.o detect_video_format
