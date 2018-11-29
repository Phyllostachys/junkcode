from OpenGL.GL import *
import glfw

glfw.init()
window = glfw.create_window(640, 480, "Thing", None, None)
glfw.make_context_current(window)

glClearColor(0.3, 0.5, 0.6, 1.0)

while not glfw.window_should_close(window):
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON)
    glColor3f(1.0, 0.0, 0.0)
    glVertex3f(-0.5, -0.5, 0.0)

    glColor3f(0.0, 1.0, 0.0)
    glVertex3f(0.5, -0.5, 0.0)

    glColor3f(0.0, 0.0, 1.0)
    glVertex3f(0.0, 0.5, 0.0)
    glEnd()

    glfw.swap_buffers(window)
    glfw.poll_events()

glfw.terminate()
