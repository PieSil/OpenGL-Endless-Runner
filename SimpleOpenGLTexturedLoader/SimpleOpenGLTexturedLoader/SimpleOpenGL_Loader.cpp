// ----------------------------------------------------------------------------
// Simple sample to prove that Assimp is easy to use with OpenGL.
// It takes a file name as command line parameter, loads it using standard
// settings and displays it.
//
// If you intend to _use_ this code sample in your app, do yourself a favour 
// and replace immediate mode calls with VBOs ...
//
// The vc8 solution links against assimp-release-dll_win32 - be sure to
// have this configuration built.
// ----------------------------------------------------------------------------

#include "GameLogic.h"
#include "GLutils.h"
#include "Timer.h"
#include "Context.h"
#include "AudioPlayer.h"

// ----------------------------------------------------------------------------
GameLogic game = GameLogic();

double aspectRatio;
const double fieldOfView = 45.0;


void reshape(int width, int height)
{
	aspectRatio = (float)width / height;
	Context::getContext()->setWidthHeight((float)width, (float)height);

	game.setPerspective(false);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(fieldOfView, aspectRatio,
	//	1, 1000.0);  // Znear and Zfar 
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(1);
		break;
	default:
		//game.handleInput(key);
		game.handleInput(key,x ,y);
		//glutPostRedisplay();
		break;
	}
}

void specialKeyboard(int key, int x, int y) {
	game.handleSpecialInput(key, x, y);
}

void specialKeyboardUp(int key, int x, int y) {
	game.handleSpecialInputUp(key, x, y);
}

void keyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	default:
		game.handleInputUp(key, x, y);
		break;
	}
}

void mouseMotion(int x, int y) {
	game.mouseMotion(x, y);
}

void activeMouseMotion(int x, int y) {
	game.activeMouseMotion(x, y);
}

void mouse(int button, int state, int x, int y) {
	game.mouse(button, state, x, y);
}

void display()
{
	float tmp;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	game.setCamera();

	//without this code nothing works
	tmp = scene_max.x - scene_min.x;
	tmp = aisgl_max(scene_max.y - scene_min.y, tmp);
	tmp = aisgl_max(scene_max.z - scene_min.z, tmp);
    tmp = 10.f / tmp; //<--the bigger it is the closer the camera (increase float value to zoom in)
	Context::getContext()->setScaleFactor(tmp);
	tmp = Context::getContext()->getScaleFactor();
	//glScalef(tmp, tmp, tmp);

	//glTranslatef(-scene_center.x, -scene_center.y, -scene_center.z);

	//draw the scene
	game.display();
	glutSwapBuffers();
}

void idle(void)
{
	Timer::getTimer()->updateElapsed();
	game.update();
	glutPostRedisplay();
}

void timerFunc(int value) {
	/*game.update();
	glutPostRedisplay();
	Timer::getTimer()->updateElapsed();
	glutTimerFunc(1000 / 120, timerFunc, 0);*/
}

int main(int argc, char **argv)
{
	AudioPlayer::getAudioPlayer(); //calls AudioPlayer constructor and loads all sound files
	struct aiLogStream stream;

	glutInitWindowSize(900,600);
	glutInitWindowPosition(100,100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	glutCreateWindow("The Collector Game");
	//glutTimerFunc(1000 / 120, timerFunc, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialKeyboard);
	glutSpecialUpFunc(specialKeyboardUp);
	glutPassiveMotionFunc(mouseMotion);
	glutMouseFunc(mouse);
	glutMotionFunc(activeMouseMotion);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// get a handle to the predefined STDOUT log stream and attach
	// it to the logging system. It will be active for all further
	// calls to aiImportFile(Ex) and aiApplyPostProcessing.

	stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
	aiAttachLogStream(&stream);

	// ... exactly the same, but this stream will now write the
	// log file to assimp_log.txt
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"assimp_log.txt");
	aiAttachLogStream(&stream);
	
	// the model name can be specified on the command line. 
	if(argc>=2)
		loadasset( argv[1] );
	else // otherwise the model is specified statically 
	{
		//char* modelToLoad = "models\\suzanne.obj";
		char* modelToLoad = "models\\blender_imports.obj";
		fprintf(stdout, "loading: %s", modelToLoad);		
		loadasset(modelToLoad);
	}	
	

	if (!InitGL())
	{
		fprintf(stderr,"Initialization failed");
		return FALSE;
	}

	glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();

	// cleanup - calling 'aiReleaseImport' is important, as the library 
	// keeps internal resources until the scene is freed again. Not 
	// doing so can cause severe resource leaking.
	aiReleaseImport(scene);

	// We added a log stream to the library, it's our job to disable it
	// again. This will definitely release the last resources allocated
	// by Assimp.
	aiDetachAllLogStreams();	

	return 0;
}