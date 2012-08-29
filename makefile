ALLEGRO_LIBRARIES := allegro-5.0 allegro_image-5.0 allegro_primitives-5.0 allegro_ttf-5.0 allegro_font-5.0
install:
	g++ hello.cpp output.cpp -o hello $(shell pkg-config --cflags --libs $(ALLEGRO_LIBRARIES))
