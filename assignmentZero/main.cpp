#include "include/GL/freeglut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "include/vecmath/vecmath.h"
using namespace std;

bool start = false;
int interval = 100;
GLfloat theta = 5.0f;
GLuint displayList;

// Globals

// This is the list of points (3D vectors)
vector<Vector3f> vecv;

// This is the list of normals (also 3D vectors)
vector<Vector3f> vecn;

// This is the list of faces (indices into vecv and vecn)
vector<vector<unsigned> > vecf;


// You will need more global variables to implement color and position changes

void timeFunc(int t)
{
	if(start)
	{
		cout << theta << endl;
		theta = theta + 5.0;
		if(theta > 360.0)
		{
			theta -= 360.0;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(interval, timeFunc, 0);
}

// These are convenience functions which allow us to call OpenGL 
// methods on Vec3d objects
inline void glVertex(const Vector3f &a) 
{ glVertex3fv(a); }

inline void glNormal(const Vector3f &a) 
{ glNormal3fv(a); }


// This function is called whenever a "Normal" key press is received.
int color = 0;
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
				//change the color with a key
				color = (color + 1)%4;
				break;
		case 'r':
				if(!start)start = true;
				else start = false;
				break;
        // add code to change color here
		cout << "Unhandled key press " << key << "." << endl; 
        break;
    default:
        cout << "Unhandled key press " << key << "." << endl;        
    }

	// this will refresh the screen so that the user sees the color change
    glutPostRedisplay();
}

// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
GLfloat Lt0pos[] = {1.0f, 1.0f, 5.0f, 1.0f};
void specialFunc( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:
			Lt0pos[1] += 0.5;
			break;
    case GLUT_KEY_DOWN:
			Lt0pos[1] -= 0.5;
			break;
    case GLUT_KEY_LEFT:
				Lt0pos[0] -= 0.5;
				break;
    case GLUT_KEY_RIGHT:
				Lt0pos[0] += 0.5;
		break;
    }

	// this will refresh the screen so that the user sees the light position
    glutPostRedisplay();
}

// This function is responsible for displaying the object.
void drawScene(void)
{
//	cout << "calling" << endl;
    int i;

    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the image
    glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
    glLoadIdentity();              // Initialize to the identity

    // Position the camera at [0,0,5], looking at [0,0,0],
    // with [0,1,0] as the up direction.
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Set material properties of object

	// Here are some colors you might use - feel free to add more
    GLfloat diffColors[4][4] = { {0.5, 0.5, 0.9, 1.0},
                                 {0.9, 0.5, 0.5, 1.0},
                                 {0.5, 0.9, 0.3, 1.0},
                                 {0.3, 0.8, 0.9, 1.0} };
    
	// Here we use the first color entry as the diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[color]);

	// Define specular color and shininess
    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};

	// Note that the specular color and shininess can stay constant
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  
    // Set light properties

    // Light color (RGBA)
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    // Light position
//GLfloat Lt0pos[] = {1.0f, 1.0f, 5.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

		//load the spin matrix
		glPushMatrix();
		glRotatef(theta, 0.0, 0.0, 1.0);

		glCallList(displayList);


		glPopMatrix();
		glutSwapBuffers();
}

// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
    glEnable(GL_LIGHTING);     // Enable lighting calculations
    glEnable(GL_LIGHT0);       // Turn on light #0.

		//use display list for high-performance rendering
		displayList = glGenLists(1);
		glNewList(displayList, GL_COMPILE);
		//draw the objects
		glBegin(GL_TRIANGLES);
		vector<vector<unsigned> >::iterator it;
		for(it=vecf.begin();it!=vecf.end();++it)
		{
			glNormal3d(vecn[(*it)[6]-1][0], vecn[(*it)[6]-1][1], vecn[(*it)[6]-1][2]);
			glVertex3d(vecv[(*it)[0]-1][0], vecv[(*it)[0]-1][1], vecv[(*it)[0]-1][2]);
			glNormal3d(vecn[(*it)[7]-1][0], vecn[(*it)[7]-1][1], vecn[(*it)[7]-1][2]);
			glVertex3d(vecv[(*it)[1]-1][0], vecv[(*it)[1]-1][1], vecv[(*it)[1]-1][2]);
			glNormal3d(vecn[(*it)[8]-1][0], vecn[(*it)[8]-1][1], vecn[(*it)[8]-1][2]);
			glVertex3d(vecv[(*it)[2]-1][0], vecv[(*it)[2]-1][1], vecv[(*it)[2]-1][2]);
		}
		glEnd();
		glEndList();
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
    // Always use the largest square viewport possible
    if (w > h) {
        glViewport((w - h) / 2, 0, h, h);
    } else {
        glViewport(0, (h - w) / 2, w, w);
    }

    // Set up a perspective view, with square aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 50 degree fov, uniform aspect ratio, near = 1, far = 100
    gluPerspective(50.0, 1.0, 1.0, 100.0);
}

#define MAXSIZE 256
void loadInput()
{
	char buf[MAXSIZE];
	while(cin.getline(buf, MAXSIZE))
	{
		stringstream ss(buf);
		string s;

		ss >> s;
		if(s == "v")
		{
			float a,b,c;
			ss >> a >> b >> c;
			Vector3f v(a,b,c);
			vecv.push_back(v);
		}
		else if(s == "vn")
		{
			float a,b,c;
			ss >> a >> b >> c;
			Vector3f v(a,b,c);
			vecn.push_back(v);
		}
		else if(s == "f")
		{
			vector<unsigned> v;
			int a,b,c,d,e,f,g,h,i;
			char ch;
			ss >> a >> ch >> b >> ch >> c;
			ss >> d >> ch >> e >> ch >> f;
			ss >> g >> ch >> h >> ch >> i;
			v.push_back(a); v.push_back(d); v.push_back(g);
			v.push_back(b); v.push_back(e); v.push_back(h);
			v.push_back(c); v.push_back(f); v.push_back(i);
			vecf.push_back(v);
		}
		else
		{
			continue;
		}
	}
	return;
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    loadInput();

    glutInit(&argc,argv);

    // We're going to animate it, so double buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow("Assignment 0");

    // Initialize OpenGL parameters.
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys
		glutTimerFunc(100, timeFunc, 0);

     // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );
    return 0;	// This line is never reached.
}
