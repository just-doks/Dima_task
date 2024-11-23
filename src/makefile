CFLAGS = $$(pkg-config --cflags gtk4)
LIBS = $$(pkg-config --libs gtk4)
h_f = pack_funcs.c string_funcs.c other_funcs.c
header_funcs = funcs/*.c
main_funcs = set_page.c fill_stack.c main.c
app: $(header_funcs) $(main_funcs)
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm app