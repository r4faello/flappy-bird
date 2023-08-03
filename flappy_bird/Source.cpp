#include <iostream>
#include <GL/glut.h>
#include<string>


using namespace std;
float _1_wall_pos=0;
float _2_wall_pos = 1.25;
float gap = 0.4;
float height1;
float height2;
float player_pos = 0;
bool pressed = false;
int timer = 0;
int timer2 = 0;
int score = 0;


double kilimo_speed = 0.002;
double kritimo_speed = 0.0002;

double kilimo_speed_t = kilimo_speed;
double kritimo_speed_t = kritimo_speed;


bool parasyta = false;
bool parasyta2 = false;

bool running = true;


void drawText(const char* text, int length, float x, float y) {
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}




void Drawing() {
	//reset color memory
	glClear(GL_COLOR_BUFFER_BIT);


	// 1 SIENA
	glPushMatrix();
	glTranslatef(_1_wall_pos, 0, 0);
	// Apatine siena
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(1, height1);//kaire virsus
	glVertex2f(1.25, height1);//desine virsus
	glVertex2f(1.25, -1); ////desine apacia
	glVertex2f(1, -1); //kaire apacia
	glEnd();
	
	// Virsutine siena
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(1, 1); //kaire virsus
	glVertex2f(1.25, 1); //desine virsus
	glVertex2f(1.25, height1+gap); //desine apacia
	glVertex2f(1, height1+gap); //kaire apacia
	glEnd();
	glPopMatrix();


	// 2 SIENA
	glPushMatrix();
	glTranslatef(_2_wall_pos, 0, 0);
	// Apatine siena
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(1, height2);//kaire virsus
	glVertex2f(1.25, height2);//desine virsus
	glVertex2f(1.25, -1); ////desine apacia
	glVertex2f(1, -1); //kaire apacia
	glEnd();

	// Virsutine siena
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(1, 1); //kaire virsus
	glVertex2f(1.25, 1); //desine virsus
	glVertex2f(1.25, height2 + gap); //desine apacia
	glVertex2f(1, height2 + gap); //kaire apacia
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, player_pos, 0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-0.05, 0.05);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.05, -0.05);
	glVertex2f(-0.05, -0.05);
	glEnd();
	glPopMatrix();

	glColor3f(0, 1, 0);
	string text;
	text = "Score: " + to_string(score);
	drawText(text.data(), text.size(), -0.9, 0.9);


	if (pressed && timer<150) {
		kritimo_speed_t = 0;
		timer2 = 0;
		player_pos += kilimo_speed_t;
		kilimo_speed_t -= kilimo_speed / 150;
		timer++;
	}
	else {
		if (timer2 < 1000) {
			player_pos -= kritimo_speed_t;
			kritimo_speed_t += kritimo_speed / 1000;
		}
		else {
			player_pos -= kritimo_speed;
		}
		timer2++;
		kilimo_speed_t = kilimo_speed;
		timer = 0;
		pressed = false;
	}

	_1_wall_pos -= 0.0001;
	if (_1_wall_pos+0.25 < -2) {
		_1_wall_pos = 0.25;
		height1 = rand() % int(100 - (gap * 100)) * 0.01;
		if (rand() % 2) {
			height1 *= -1;
		}
	}

	
	_2_wall_pos -= 0.0001;
	if (_2_wall_pos+0.25 < -2) {
		_2_wall_pos = 0.25;
		height2 = rand() % int(100 - (gap * 100)) * 0.01;
		if (rand() % 2) {
			height2 *= -1;
		}
	}
	
	
	if ((_1_wall_pos + 1) < 0 && (_1_wall_pos + 1.25)>0 && (height1 + gap>player_pos + 0.05 && height1 < player_pos - 0.05)) {
		if (!parasyta) {
			score++;
			cout << score << endl;
			//cout << "Tarpe" << endl;
			parasyta = true;
		}
	}
	else {
		parasyta = false;
	}

	if ((_2_wall_pos + 1) < 0.05 && 0.05 < (_2_wall_pos + 1.25) && (height2 + gap<player_pos + 0.05 || height2 > player_pos - 0.05)) {
		running = false;
	}
	else if ((_1_wall_pos + 1) < 0.05 && 0.05 < (_1_wall_pos + 1.25) && (height1 + gap<player_pos + 0.05 || height1 > player_pos - 0.05)) {
		running = false;
	}
	else if (player_pos - 0.05 < -1) {
		running = false;
	}
	else if (player_pos + 0.05 > 1) {
		running = false;
	}


	if (running) {
		glutPostRedisplay(); // auto refresh
	}
	else {
		cout << "Pralaimejai" << endl;
	}






	if ((_2_wall_pos + 1) < 0 && (_2_wall_pos + 1.25) > 0 && (height2 + gap > player_pos + 0.05 && height2 < player_pos - 0.05)) {
		if (!parasyta2) {
			score++;
			cout << score << endl;
			//cout << "Tarpe" << endl;
			parasyta2 = true;
		}
	}
	else {
		parasyta2 = false;
	}

	cout << endl;
	glFlush();//refresh
	
}

void MainInit() {
	//Define matrix
	glMatrixMode(GL_PROJECTION);
	//Load matrix
	glLoadIdentity();
	//Set 2d/3d environment
	gluOrtho2D(-1, 1, -1, 1);
	//Set background color
	glClearColor(0.58, 0.12, 1, 0);
}

void KeyboardFunc(int key, int x, int y)
{
	/*if (key == GLUT_KEY_UP)
	{
		cout << "test" << endl;
		pressed = true;
		glutPostRedisplay();
	}
	else {
		pressed = false;
	}*/
	pressed = (key == GLUT_KEY_UP);
	//cout << pressed << endl;
}

int main(int argc, char** argv) {
	// Initialize glut
	glutInit(&argc, argv);
	// Set display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set windows size
	glutInitWindowSize(500, 700);
	// Set window startup position
	glutInitWindowPosition(200, 200);
	//Show window
	glutCreateWindow("Flappy Bird");
	//Define environment
	MainInit();
	glutDisplayFunc(Drawing);
	glutSpecialFunc(KeyboardFunc);
	//Infinite window
	glutMainLoop();




	return 0;
}