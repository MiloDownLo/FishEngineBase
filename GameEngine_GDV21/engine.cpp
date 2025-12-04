#include "engine.h"
#include "graphics.h"
#include "input.h"


void PrepareEngine(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(700, 300);
	glutInitWindowSize(450, 400);
	glutCreateWindow("MyOpenGL");

	//register callbacks
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeWindowSize);
	//glutIdleFunc(renderScene); //Renders program at uncapped FPS
	glutTimerFunc(16, Timer, 0); //Renders program at ~60fps :]

	glutKeyboardFunc(&keyPressed);
	glutKeyboardUpFunc(&keyPressedUp);
	// you can also support special keyboard buttons using glutSpecialFunc
	//glutSpecialFunc

	// Setup Camera
	gluLookAt(0.0f, 0.0f, 20.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	// Call initialize here 
	Initialize();

	//enter GLUT event processing cycle
	glutMainLoop();
}
