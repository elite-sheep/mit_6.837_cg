#include "GL/freeglut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "include/vecmath/vecmath.h"
using namespace std;

#define DEBUG 1

// Globals

// This is the list of points (3D vectors)
vector<Vector3f> vecv;

// This is the list of normals (also 3D vectors)
vector<Vector3f> vecn;

// This is the list of faces (indices into vecv and vecn)
vector<vector<unsigned> > vecf;


// You will need more global variables to implement color and position changes


// These are convenience functions which allow us to call OpenGL 
// methods on Vec3d objects
inline void glVertex(const Vector3f &a) 
{ glVertex3fv(a); }

inline void glNormal(const Vector3f &a) 
{ glNormal3fv(a); }

// The index of the current color
int colorIndex = 0;

// The number of color that can be chosen.
const int NUM_OF_COLOR = 4;

// The offset of light spot from the init pos
GLfloat lightOffsetX = 0.0;
GLfloat lightOffsetY = 0.0;


// This function is called whenever a "Normal" key press is received.
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
        // add code to change color here
				colorIndex = (colorIndex + 1) % NUM_OF_COLOR;
        break;
    default:
        cout << "Unhandled key press " << key << "." << endl;        
    }

	// this will refresh the screen so that the user sees the color change
    glutPostRedisplay();
}

// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:
			lightOffsetY -= 0.5;
			break;
    case GLUT_KEY_DOWN:
				lightOffsetY += 0.5;
			break;
    case GLUT_KEY_LEFT:
				lightOffsetX -= 0.5;
			break;
    case GLUT_KEY_RIGHT:
				lightOffsetX += 0.5;
			break;
    }

	// this will refresh the screen so that the user sees the light position
    glutPostRedisplay();
}

// This function is responsible for displaying the object.
void drawScene(void)
{
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[colorIndex]);

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
	GLfloat Lt0pos[] = {1.0f + lightOffsetX, 1.0f + lightOffsetY, 5.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

	// This GLUT method draws a teapot.  You should replace
	// it with code which draws the object you loaded.
	glutSolidTeapot(1.0);
    
    // Dump the image to the screen.
    glutSwapBuffers();


}

// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
    glEnable(GL_LIGHTING);     // Enable lighting calculations
    glEnable(GL_LIGHT0);       // Turn on light #0.

#if DEBUG
		cout << "Loading faces" << endl;
#endif

		glBegin(GL_TRIANGLES);
		vector<vector<unsigned> >::iterator it;
		for(it=vecf.begin(); it!=vecf.end(); ++it)
		{
			glNormal3d(vecn[(*it)[6]-1][0], vecn[(*it)[6]-1][1], vecn[(*it)[6]-1][2]);
			glVertex3d(vecn[(*it)[0]-1][0], vecn[(*it)[0]-1][1], vecn[(*it)[0]-1][2]);
			glNormal3d(vecn[(*it)[7]-1][0], vecn[(*it)[7]-1][1], vecn[(*it)[7]-1][2]);
			glVertex3d(vecn[(*it)[1]-1][0], vecn[(*it)[1]-1][1], vecn[(*it)[1]-1][2]);
			glNormal3d(vecn[(*it)[8]-1][0], vecn[(*it)[8]-1][1], vecn[(*it)[8]-1][2]);
			glVertex3d(vecn[(*it)[2]-1][0], vecn[(*it)[2]-1][1], vecn[(*it)[2]-1][2]);
		}

#if DEBUG
		cout << "Face Loaded" << endl;
#endif
		glEnd();
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

void loadInput()
{
	// load the OBJ file here
#define MAXSIZE 256

	char buf[MAXSIZE];

#if DEBUG
	cout << "Loading file" << endl;
#endif
	
	while(cin.getline(buf, MAXSIZE))
	{
		stringstream ss(buf);

		string s;

		ss >> s;
		if(s == "v")
		{
			float x, y, z;
			ss >> x >> y >> z;
			Vector3f v(x, y, z);
			vecv.push_back(v);
		}
		else if(s == "vn")
		{
			float x, y, z;
			ss >> x >> y >> z;
			Vector3f v(x, y, z);
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
#if DEBUG
	cout << "Loaded file" << endl;
#endif
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

#if DEBUG
		cout << "Start Rendering" << endl;
#endif

    // Initialize OpenGL parameters.
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

     // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;	// This line is never reached.
}
