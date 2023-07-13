/* PONG.
*/
#include <windows.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> 
#include <GL/freeglut.h> 
#include <time.h>

#include "loadShaders.h"
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define KEY_DOWN( vk_code ) ( ( GetAsyncKeyState( vk_code ) & 0x8000 ) ? 1 : 0 ) // tasta apasata

//////////////////////////////////////

GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId,
myMatrixLocation,
matrScaleLocation,
matrTranslLocation,
matrRotlLocation,
codColLocation;

glm::mat4
myMatrix, resizeMatrix, matrTransl, matrTransl1, matrTransl2, matrTranslP1, matrTranslP2, matrTranslMiscare, matrTranslMiscare2, matrScale, matrRot, mTest;

int codCol;
float width = 1600, height = 1000;
float PI = 3.141592, angle = 0;
float ty1 = 0; float ty2 = 0;
float i = 0.0, j = 0.0, alpha = 0.0, step = 0.0, beta = 0.009;
int click = 0, directie = 0, punctMarcat = 0;
int scorP1 = 0, scorP2 = 0;

void sleep(float sec)
{
	float end = clock() / CLOCKS_PER_SEC + sec;
	while ((clock() / CLOCKS_PER_SEC) < end);
}

void invarte(void)
{
	if (click == 0)
		angle = angle - beta;
	if (click == 1)
		
	glutPostRedisplay();
}

void misca1(unsigned char key, int x, int y)
{
	if (KEY_DOWN(38)) {
		if (ty2 < 395.0) {
			ty2 += 20;
		}
	}	
	if (KEY_DOWN(40)) {
		if (ty2 > -395.0) {
			ty2 -= 20;
		}
	}	
	if (KEY_DOWN(87)) {
		if (ty1 < 395.0) {
			ty1 += 20;
		}
	}	
	if (KEY_DOWN(83)) {
		if (ty1 > -395.0) {
			ty1 -= 20;
		}
	}
}

void misca2(int key, int x, int y)
{
	if (KEY_DOWN(38)) {
		if (ty2 < 395.0) {
			ty2 += 20;
		}
	}	
	if (KEY_DOWN(40)) {
		if (ty2 > -395.0) {
			ty2 -= 20;
		}
	}	
	if (KEY_DOWN(87)) {
		if (ty1 < 395.0) {
			ty1 += 20;
		}
	}	
	if (KEY_DOWN(83)) {
		if (ty1 > -395.0) {
			ty1 -= 20;
		}
	}
}

int lovirePlayer1(void)
{
	if (j + 15 <= ty1 + 80 && j - 15 >= ty1 - 80) //patratul este cuprins total de P1
	{
		return 1;
	}
	if (j - 15 <= ty1 + 80 && j + 15 >= ty1 + 80) //patratul se afla cu jumatatea inferioara in dreptul lui P1 si cea superioara deasupra lui
	{
		return 1;
	}
	if (j + 15 >= ty1 - 80 && j - 15 <= ty1 - 80) //patratul se afla cu jumatatea superioara in dreptul lui P1 si cea inferioara sub
	{
		return 1;
	}
	return 0;
}

int lovirePlayer2(void)
{
	if (j + 15 <= ty2 + 80 && j - 15 >= ty2 - 80) //patratul este cuprins total de P2
	{
		return 1;
	}
	if (j - 15 <= ty2 + 80 && j + 15 >= ty2 + 80) //patratul se afla cu jumatatea inferioara in dreptul lui P2 si cea superioara deasupra lui
	{
		return 1;
	}
	if (j + 15 >= ty2 - 80 && j - 15 <= ty2 - 80) //patratul se afla cu jumatatea superioara in dreptul lui P2 si cea inferioara sub
	{
		return 1;
	}
	return 0;
}

void miscaPatrat(void)
{
	if (directie == 0)
	{
		i += 0.5;
		j += 0.5;
	}
	else if (directie == 1)
	{
		i += 0.5;
		j -= 0.5;
	}
	else if (directie == 2)
	{
		i -= 0.5;
		j -= 0.5;
	}
	else if (directie == 3)
	{
		i -= 0.5;
		j += 0.5;
	}

	//schimbarea directiei 
	if (j >= 465 && directie == 0) //lovire sus venind din stanga
	{
		directie = 1; //0 sus dreapta, 1 jos dreapta, 2 jos stanga, 3 sus stanga
	}
	else if (j >= 465 && directie == 3) //lovire sus venind din dreapta
	{
		directie = 2;
	}
	else if (j <= -465 && directie == 1) //lovire jos venind din stanga
	{
		directie = 0;
	}
	else if (j <= -465 && directie == 2) //lovire jos venind din dreapta
	{
		directie = 3;
	}
	else if (i <= -675 && i >= -700 && directie == 2 && lovirePlayer1()) //lovire P1 venind de sus
	{
		directie = 1;
	}
	else if (i <= -675 && i >= -700 && directie == 3 && lovirePlayer1()) //lovire P1 venind de jos
	{
		directie = 0;
	}
	else if (i >= 675 && i <= 700 && directie == 1 && lovirePlayer2()) //lovire P1 venind de sus
	{
		directie = 2;
	}
	else if (i >= 675 && i <= 700 && directie == 0 && lovirePlayer2()) //lovire P1 venind de jos
	{
		directie = 3;
	}

	//obtinere punct
	else if (i >= 830 && directie == 1) //lovire dreapta venind de sus
	{
		i = 0;
		j = 0;
		ty1 = 0;
		ty2 = 0;
		punctMarcat = 1;
		srand(time(NULL));
		int val = rand() % 2;
		if (val == 0)
		{
			directie = 2;
		}
		else
		{
			directie = 3;
		}
		scorP1++;
	}
	else if (i >= 830 && directie == 0) //lovire dreapta venind de jos
	{
		i = 0;
		j = 0;
		ty1 = 0;
		ty2 = 0;
		punctMarcat = 1;
		srand(time(NULL));
		int val = rand() % 2;
		if (val == 0)
		{
			directie = 2;
		}
		else
		{
			directie = 3;
		}
		scorP1++;
	}
	else if (i <= -830 && directie == 3) //lovire stanga venind de jos
	{
		i = 0;
		j = 0;
		ty1 = 0;
		ty2 = 0;
		punctMarcat = 1;
		srand(time(NULL));
		int val = rand() % 2;
		if (val == 0)
		{
			directie = 0;
		}
		else
		{
			directie = 1;
		}
		scorP2++;
	}
	else if (i <= -830 && directie == 2) //lovire stanga venind de sus
	{
		i = 0;
		j = 0;
		ty1 = 0;
		ty2 = 0;
		punctMarcat = 1;
		srand(time(NULL));
		int val = rand() % 2;
		if (val == 0)
		{
			directie = 0;
		}
		else
		{
			directie = 1;
		}
		scorP2++;
	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON && click == 0:
		click = 1;
		srand(time(NULL));
		directie = rand() % 4;
		glutIdleFunc(miscaPatrat);
		break;
	default:
		break;
	}
}

void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {
		 //varfuri pentru tabla de joc
		 20.0f, 980.0f, 0.0f, 1.0f,
		 1580.0f, 980.0f, 0.0f, 1.0f,
		 1580.0f, 20.0f, 0.0f, 1.0f,
		 20.0f, 20.0f, 0.0f, 1.0f,

		 //varfuri pentru player 1 (stanga)
		 80.0f, 420.0f, 0.0f, 1.0f,
		 110.0f, 420.0f, 0.0f, 1.0f,
		 110.0f, 580.0f, 0.0f, 1.0f,
		 80.0f, 580.0f, 0.0f, 1.0f,

		 //varfuri pentru player 2 (dreapta)
		 1490.0f, 580.0f, 0.0f, 1.0f,
		 1520.0f, 580.0f, 0.0f, 1.0f,
		 1520.0f, 420.0f, 0.0f, 1.0f,
		 1490.0f, 420.0f, 0.0f, 1.0f,

		 //varfuri pentru dreptunghi interior player 1 (stanga)
		 90.0f, 570.0f, 0.0f, 1.0f,
		 100.0f, 570.0f, 0.0f, 1.0f,
		 100.0f, 430.0f, 0.0f, 1.0f,
		 90.0f, 430.0f, 0.0f, 1.0f,

		 //varfuri pentru dreptunghi interior player 2 (dreapta)
		 1500.0f, 570.0f, 0.0f, 1.0f,
		 1510.0f, 570.0f, 0.0f, 1.0f,
		 1510.0f, 430.0f, 0.0f, 1.0f,
		 1500.0f, 430.0f, 0.0f, 1.0f,

		 //patratul de joc
		 785.0f, 515.0f, 0.0f, 1.0f,
		 815.0f, 515.0f, 0.0f, 1.0f,
		 815.0f, 485.0f, 0.0f, 1.0f,
		 785.0f, 485.0f, 0.0f, 1.0f,

	};

	GLfloat Colors[] = {
	  1.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f,
	  1.0f, 0.0f, 0.0f, 1.0f,
	};

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

void CreateShaders(void)
{
	ProgramId = LoadShaders("Pong_Shader.vert", "Pong_Shader.frag");
	glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	glClearColor(0.5f, 1.0f, 0.5f, 1.0f); // culoarea de fond a ecranului
	CreateVBO();
	CreateShaders();
	codColLocation = glGetUniformLocation(ProgramId, "codCuloare");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	resizeMatrix = glm::ortho(0.0f, width, 0.0f, height);
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
	// Translatia 1: centrul patratului este translatat
	matrTransl1 = glm::translate(glm::mat4(1.0f), glm::vec3(-800.f, -500.f, 0.0));
	// Translatia 2: inversa/opusa translatiei T1
	matrTransl2 = glm::translate(glm::mat4(1.0f), glm::vec3(800.f, 500.f, 0.0));
	matrTranslP1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, ty1, 0.0));
	matrTranslP2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, ty2, 0.0));
	matrTranslMiscare = glm::translate(glm::mat4(1.0f), glm::vec3(i, j, 0.0)); 
	matrScale = glm::scale(glm::mat4(1.0f), glm::vec3(2.5, 2.5, 0.0));

	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	//tabla de joc
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 0, 4);

	//player 1
	myMatrix = resizeMatrix * matrTranslP1 ;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 2;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 4, 4);

	codCol = 3;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 12, 4);

	//player 2
	myMatrix = resizeMatrix * matrTranslP2 ;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 2;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 8, 4);

	codCol = 4;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 16, 4);

	//patratul de joc
	if (click == 0){
		myMatrix = resizeMatrix * matrTransl2 * matrScale * matrRot * matrTransl1;
		glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

		codCol = 2;
		glUniform1i(codColLocation, codCol);
		glDrawArrays(GL_POLYGON, 20, 4);
	}
	else if (click == 1 && punctMarcat == 0) {
		myMatrix = resizeMatrix * matrTranslMiscare;
		glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
		codCol = 2;
		glUniform1i(codColLocation, codCol);
		glDrawArrays(GL_POLYGON, 20, 4);
	}
	else if (punctMarcat == 1)
	{
		punctMarcat = 0;
		std::cout << "   "<<scorP1 << "			   " << scorP2 << "\n";
		sleep(2);	
	}

	glutPostRedisplay();
	glFlush();
}

void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

int main(int argc, char* argv[])
{
	std::cout << "		Scor\n";
	std::cout << "Player 1		Player 2\n";
	std::cout << "   0			   0\n";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(125, 0);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Pong");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(invarte);
	glutMouseFunc(mouse);
	glutKeyboardFunc(misca1);
	glutSpecialFunc(misca2);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

