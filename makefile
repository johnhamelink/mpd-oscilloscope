ALLEGRO_LIBRARIES := allegro-5.0 allegro_image-5.0 allegro_primitives-5.0 allegro_font-5.0 allegro_ttf-5.0
install:
	g++ fifo.cpp output.cpp main.cpp -o visualise -Xlinker -zmuldefs $(shell pkg-config --cflags --libs $(ALLEGRO_LIBRARIES))
