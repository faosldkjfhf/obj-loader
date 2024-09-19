IDIR := ./include
ODIR := .
OBJDIR := ./bin

CC := g++
CFLAGS := -std=c++20
INCLUDES := -I./include
LIBS := `pkg-config --libs --cflags glfw3` -lGLEW -lGL -lGLU
SOURCES := main.cpp window.cpp engine.cpp shader_program.cpp shader.cpp vertex_array.cpp vertex_buffer.cpp
SOURCES += vertex_buffer_layout.cpp index_buffer.cpp
OBJECTS := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))

$(ODIR)/prog: $(OBJECTS)
	$(CC) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
	rm -f prog
